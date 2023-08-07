/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaju <jaju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 22:25:57 by jaju              #+#    #+#             */
/*   Updated: 2023/08/07 19:11:19 by jaju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser/compiler.h>
#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <shell/minishell.h>

int	pwd_main(t_process *this)
{
	char	pwd[PATH_MAX];

	(void)this;
	if (getcwd(pwd, PATH_MAX) != (void *)0)
		printf("%s\n", pwd);
	else
	{
		perror("bash: pwd");
	}
	return (SUCCES_EXIT);
}
