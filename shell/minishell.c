/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaju <jaju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 17:57:55 by jaju              #+#    #+#             */
/*   Updated: 2023/07/29 13:37:25 by jaju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "str/str.h"
#include <stdlib.h>
#include <stdio.h>
#include "libft/libft.h"


void	pair_init(t_envp *envp)
{
	envp->name = NULL;
	envp->value = NULL;
}

// 환경변수들 = 기준으로 다 넣어주기
void	minishell_init(char **envp)
{
	t_envp	*pair;
	t_list	env;
	int		i;
	int		index;

	list_init(&env);
	//환경변수 key, value에 값 넣어주기
	i = 0;
	while (envp[i] != (void *)0)
	{
		pair = allocate(sizeof(t_envp));
		index = str_indexof(envp[i], '=');
		pair->name = str_substr(envp[i], 0, index);
		pair->value = str_substr(envp[i], index + 1, str_length(envp[i]));
		list_add(&env, pair);
		i++;
	}
	g_minishell.env_list = env;
}

char const	*get_env(char const *str)
{
	t_list*const	env_list = &g_minishell.env_list;
	t_envp			*env;
	int				i;

	i = 0;
	while (i < env_list->length)
	{
		env = list_get(env_list, i);
		if (str_equals(str, env->name))
			return (env->value);
		i++;
	}
	return ("");
}