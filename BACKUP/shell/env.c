/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaju <jaju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 03:49:42 by jaju              #+#    #+#             */
/*   Updated: 2023/08/07 19:19:50 by jaju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <str/str.h>
#include <libft/libft.h>
#include <stdlib.h>

/*
get_env
set_env
remove_env
get_envp
*/

//envp구조체를 char *로 만들어 줌
char	*env_to_str(t_env *env);
void	env_init(t_env *this, char *name, char *value);
void	env_free(void *this);

//문자열에 대응하는 환경변수의 값을 리턴
char const	*get_env(char const *str)
{
	t_list*const	env_list = &g_minishell.env_list;
	t_env			*env;
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

void	set_env(char const *name, char const *value)
{
	t_list*const	env_list = &g_minishell.env_list;
	int				i;
	t_env			*env;

	i = 0;
	while (i < env_list->length)
	{
		env = list_get(env_list, i++);
		if (str_equals(env->name, name))
		{
			if (value == (void *)0)
				return ;
			else
				return (free(env->value), env->value = str_clone(value), (void)0);
		}
	}
	env = allocate(sizeof(t_env));
	env_init(env, str_clone(name), str_clone(value));
	list_add(env_list, env);
}

void	remove_env(char const *name)
{
	t_list*const	env_list = &g_minishell.env_list;
	t_env			*env;
	int				i;

	i = 0;
	while (i < env_list->length)
	{
		env = list_get(env_list, i);
		if (str_equals(env->name, name))
			break ;
		i++;
	}
	if (i == env_list->length)
		return ;
	env_free(env);
	free(env);
	list_remove(env_list, i);
}

char	**get_envp(void)
{
	t_list*const	env_list = &g_minishell.env_list;
	char**const		envp = allocate((env_list->length + 1) * sizeof(char *));
	t_env			*env;
	int				i;
	int				j;

	i = 0;
	j = 0;
	while (i < env_list->length)
	{
		env = list_get(env_list, i);
		if (env->value != (void *)0)
			envp[j++] = env_to_str(env);
		i++;
	}
	return (envp);
}
