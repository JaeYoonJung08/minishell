/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaju <jaju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 22:42:10 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/08/07 18:43:25 by jaju             ###   ########.fr       */
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

//cd를 하기 전에 PWD값을 OLDPWD에 저장
/*
void	oldpwd_save(void)
{
	char			pwd[PATH_MAX];
	t_list*const	env_list = &g_minishell.env_list;
	t_env			*env;
	int				i;
	int				j;

	i = 0;
	while (i < env_list->length)
	{
		env = list_get(env_list, i++);
		if (str_equals(env->name, "OLDPWD"))
		{
			if (getcwd(pwd, PATH_MAX) != (void *)0)
			{
				char*const tmp = allocate(str_length(pwd));
				j = 0;
				while (pwd[j])
				{
					tmp[j] = pwd[j];
					j++;
				}
				tmp[j] = '\0';
				free(env->value);
				env->value = tmp;
			}
		}
	}
}
*/

int	check_behind(t_process *this)
{
	//char		*path;
	int			fd;

	fd = chdir(this->argv[1]);
	if (fd == 0)
	{
		update_pwd();
		return (SUCCES_EXIT);
	}
	else
	{
		write(2, "minishell: ", 12);
		perror(this->argv[1]);
		return (ERROR_EXIT);
	}
}

//SUCCES_EXIT 0
//ERROR_EXIT 1
//echo, heredoc
int	cd_main(t_process *this)
{
	char const	*path_envp;

	//cd를 하기 전에 OLDPWD에 저장 
	//실패해도 성공해도 저장이 됨.
	update_oldpwd();
	if (this->argc == 1)
		path_envp = get_env("HOME");
	else
		path_envp = this->argv[1];
	if (chdir(path_envp) == -1) // != 0 인지, == -1 인지 명확하게
	{
		write(2, "bash: ", 6);
		perror(this->argv[1]);
	}
	update_pwd();
	return (SUCCES_EXIT);
}
