/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 22:42:10 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/08/14 18:12:43 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../parser/compiler.h"
#include <parser/parser.h>
#include "../../str/str.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <shell/minishell.h>
#include <limits.h>

//cd를 실행시킨후 환경변수 PWD 초기화
void	update_pwd(void)
{
	char	pwd[PATH_MAX];

	if (getcwd(pwd, PATH_MAX) != (void *)0)
		set_env("PWD", pwd);
}

void	update_oldpwd(void)
{
	char	pwd[PATH_MAX];

	if (getcwd(pwd, PATH_MAX) != (void *)0)
		set_env("OLDPWD", pwd);
}

int	check_behind(t_process *this)
{
	int			fd;

	fd = chdir(this->argv[1]);
	if (fd == 0)
	{
		update_pwd();
		return (SUCCES_EXIT);
	}
	else
	{
		basherr(this->argv[1]);
		g_minishell.exit_code = 1;
		return (ERROR_EXIT);
	}
}

//SUCCES_EXIT 0, ERROR_EXIT 1, echo heredoc
int	cd_main(t_process *this)
{
	char const	*path_envp;

	update_oldpwd();
	if (this->argc == 1)
		path_envp = get_env("HOME");
	else
		path_envp = this->argv[1];
	if (chdir(path_envp) == -1)
	{
		basherr(this->argv[1]);
		g_minishell.exit_code = 1;
		return (ERROR_EXIT);
	}
	update_pwd();
	return (SUCCES_EXIT);
}
