/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaju <jaju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 13:09:29 by jaju              #+#    #+#             */
/*   Updated: 2023/08/08 01:56:12 by jaju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser/compiler.h>
#include <shell/minishell.h>
#include <stdio.h>

int	env_main(t_process *this)
{
	t_list*const	env_list = &g_minishell.env_list;
	t_env			*env;
	int				i;

	(void)this;
	i = 0;
	while (i < env_list->length)
	{
		env = list_get(env_list, i);
		if (env->value != (void *)0)
			printf("%s=%s\n", env->name, env->value);
		i++;
	}
	return (SUCCES_EXIT);
}
