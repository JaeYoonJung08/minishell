/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaju <jaju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 00:32:58 by jaju              #+#    #+#             */
/*   Updated: 2023/07/29 13:38:25 by jaju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <collection/list.h>
#include <stdio.h>
#include <stdlib.h>
#include <shell/minishell.h>

static void	str_add_char(char **str, char c)
{
	int const	length = str_length(*str);
	char		*new;

	if (length % 64 == 0)
	{
		new = allocate((length + 64 + 1) * sizeof(char));
		copy(*str, new, length);
		free(*str);
		*str = new;
	}
	(*str)[length] = c;
}

static void	str_add(char **str, char const *a)
{
	int	i;

	i = 0;
	while (a[i] != '\0')
	{
		str_add_char(str, a[i]);
		i++;
	}
}

static void	str_add_env(char **new, char const **str)
{
	char	*substr;
	char const	*env;
	int		i;

	i = 0;
	(*str)++;
	while (is_alphabet((*str)[i]) || is_number((*str)[i]) || (*str)[i] == '_')
		i++;
	substr = str_substr(*str, 0, i);
	env = get_env(substr);
	str_add(new, env);
	printf("unquote: %s", env);
	free(substr);
	*str += i - 1;
}

void	str_add_exit_code(char **new)
{
	int const	exit_code = g_minishell.exit_code;

	if (exit_code / 100 % 10 != 0)
	{
		str_add_char(new, (exit_code / 100 % 10) + '0');
		str_add_char(new, (exit_code / 10 % 10) + '0');
		str_add_char(new, (exit_code % 10) + '0');
	}
	else if (exit_code / 10 % 10 != 0)
	{
		str_add_char(new, (exit_code / 10 % 10) + '0');
		str_add_char(new, (exit_code % 10) + '0');
	}
	else
		str_add_char(new, (exit_code % 10) + '0');
}

void	str_add_dq(char **new, char const **str)
{
	if (**str == '$' && (is_alphabet((*str)[1]) || (*str)[1] == '_'))
		str_add_env(new, str);
	else if (**str == '$' && (*str)[1] == '?')
		str_add_exit_code(new);
	else
		str_add_char(new, **str);
}

char	*unquote_env(char const *str)
{
	char	*new;

	new = allocate(1 * sizeof(char));
	while (*str != '\0')
	{
		if (*str == '\'')
			while (*(++str) != '\'')
				str_add_char(&new, *str);
		else if (*str == '\"')
			while (*(++str) != '\"')
				str_add_dq(&new, &str);
		else
			str_add_dq(&new, &str);
		str++;
	}
	return (new);
}

char	*unquote(char const *str)
{
	char*const	new = allocate(str_length(str) + 1);
	int			i;
	int			j;
	char		quotation_mark;

	i = 0;
	j = 0;
	quotation_mark = '\0';
	while (str[i] != '\0')
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			quotation_mark = str[i++];
			while (str[i] != quotation_mark)
				new[j++] = str[i++];
			quotation_mark = '\0';
			i++;
		}
		else
			new[j++] = str[i++];
	}
	return (new);
}
