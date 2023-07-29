/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 17:57:55 by jaju              #+#    #+#             */
/*   Updated: 2023/07/28 22:35:37 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "str.h"
#include <stdlib.h>
#include <stdio.h>


void	pair_init(t_envp *envp)
{
	envp->key = NULL;
	envp->name = NULL;
	envp->next = NULL;
}

void	struct_init(t_envp *pair, int count)
{
	t_envp	*tmp;
	t_envp 	*new;

	tmp = pair;
	int i = 0;
	while(i < count)
	{
		new = (t_envp *)malloc(sizeof(t_envp));
		pair_init(new);
		tmp->next = new;
		tmp = tmp->next;
		//free(new);
		i++;
	}
}

// 환경변수들 = 기준으로 다 넣어주기
t_envp	*minishell_init(char **envp)
{
	t_envp 	*pair;
	int		i = 0;
	int		index;
	int 	j;


	//pair초기화
	pair = (t_envp *)malloc(sizeof(t_envp));
	pair_init(pair);
	//환경변수 개수
	j = 0;
	while (envp[j])
		j++;
	//환경변수 만큼 구조체 만들어주기
	struct_init(pair, j);
	//환경변수 key, value에 값 넣어주기
	t_envp *tmp = pair;
	i = 0;
	while (envp[i])
	{
		index = str_indexof(envp[i], '=');
		tmp->key = str_substr(envp[i], 0, index);
		tmp->name = str_substr(envp[i], index + 1, str_length(envp[i]));
		tmp = tmp->next;
		i++;
	}
	//printf("%s", pair->name);
	return (pair);
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
