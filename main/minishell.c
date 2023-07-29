/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaju <jaju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 17:57:55 by jaju              #+#    #+#             */
/*   Updated: 2023/07/28 18:54:51 by jaju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "str.h"

void	minishell_init(char **envp)
{
	char	*env;
	t_envp	*pair;
	int		i;

	pair = *envp;
	while (pair != (void *)0)
	{
		str_indexof(pair, '=');
		pair = *(++envp);
	}
}

char const	*get_envp(char const *str)
{
	t_list*const	env_list = &g_minishell.env_list;
	t_envp			*env;
	int				i;

	i = 0;
	while (i < env_list->length)
	{
		env = list_get(env_list, i);
		if (str_equals(str, env->key))
			return (env->name);
		i++;
	}
	return ("");
}
