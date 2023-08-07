/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaju <jaju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 04:00:45 by jaju              #+#    #+#             */
/*   Updated: 2023/08/07 19:20:03 by jaju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <str/str.h>
#include <libft/libft.h>
#include <stdlib.h>

/*
env_to_str
env_init
env_free
*/

char	*env_to_str(t_env *env)
{
	int const	name_len = str_length(env->name);
	int const	value_len = str_length(env->value);
	char*const	new = allocate(name_len + value_len + 2);
	char		*ptr;

	ptr = new;
	copy(env->name, ptr, name_len);
	ptr += name_len;
	copy("=", ptr, 1);
	ptr += 1;
	copy(env->value, ptr, value_len);
	return (new);
}

void	env_init(t_env *this, char *name, char *value)
{
	this->name = name;
	this->value = value;
}

void	env_free(void *this)
{
	free(((t_env *)this)->name);
	free(((t_env *)this)->value);
}
