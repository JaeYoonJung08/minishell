/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaju <jaju@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 01:39:01 by jaju              #+#    #+#             */
/*   Updated: 2023/08/07 00:31:30 by jaju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser/compiler.h>
#include <str/str.h>
#include <libft/libft.h>
#include <shell/minishell.h>
#include <parser/parser.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

static int	syntax_var_name(char const *str)
{
	int	i;

	if (str[0] == '_' || is_alphabet(str[0]))
	{
		i = 1;
		while (str[i] != '\0')
		{
			if (!(str[0] == '_' || is_alphabet(str[0]) || is_number(str[0])))
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}

static int	parse_arg(char const *str, char **name, char **value)
{
	int const	equals_idx = str_indexof(str, '=');

	if (equals_idx == -1)
	{
		*name = str_clone(str);
		*value = (void *)0;
	}
	else
	{
		*name = str_substr(str, 0, equals_idx);
		*value = str_substr(str, equals_idx + 1, str_length(str));
	}
	return (syntax_var_name(*name));
}

//export var: 없으면 변수 생성, 있으면 아무것도 안함
//export var=value: 없으면 값 생성 후 대입, 있으면 그냥 대입
//export: 모든 환경변수를 보여줌. 환경변수 값은 ""로 감쌈, 값이 없는 변수는 이름만 보임

static int	export_view()
{
	t_list*const	env_list = &g_minishell.env_list;
	t_env			*env;
	int				i;

	i = 0;
	while (i < env_list->length)
	{
		env = list_get(env_list, i);
		if (env->value == (void *)0)
			printf("declare -x %s\n", env->name);
		else
			printf("declare -x %s=\"%s\"\n", env->name, env->value);
		i++;
	}
	return (0);
}

static int	export_set(t_process *this)
{
	char	*name;
	char	*value;
	int		exit_code;
	int		i;

	exit_code = 0;
	i = 1;
	while (i < this->argc)
	{
		if (parse_arg(this->argv[i], &name, &value))
			set_env(name, value);
		else
		{
			printf("bash: export: `%s`: not a valid identifier\n",
				this->argv[i]);
			exit_code = 1;
		}
		free(name);
		free(value);
		i++;
	}
	return (exit_code);
}

int	export_main(t_process *this)
{
	if (this->argc == 1)
		return (export_view());
	else
		return (export_set(this));
}
