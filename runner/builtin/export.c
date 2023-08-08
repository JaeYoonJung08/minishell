/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaju <jaju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 01:39:01 by jaju              #+#    #+#             */
/*   Updated: 2023/08/08 02:40:15 by jaju             ###   ########.fr       */
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

t_env	**to_array(t_list *env_list);

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

static int	export_view(void)
{
	t_env**const		envp = to_array(&g_minishell.env_list);
	int					i;

	i = 0;
	while (envp[i] != (void *)0)
	{
		if (envp[i]->value == (void *)0)
			printf("declare -x %s\n", envp[i]->name);
		else
			printf("declare -x %s=\"%s\"\n", envp[i]->name, envp[i]->value);
		i++;
	}
	return (free(envp), 0);
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
			printerr("bash: export: `");
			printerr(this->argv[i]);
			printerr("` not a valid identifier\n");
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
