/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unquote3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaju <jaju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 21:04:04 by jaju              #+#    #+#             */
/*   Updated: 2023/08/07 21:12:42 by jaju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <collection/list.h>
#include <stdio.h>
#include <stdlib.h>
#include <shell/minishell.h>

int		is_power_of_two(int x);
void	str_push(char **str, char c);
void	str_push_str(char **new, char const *str);
int		unquote_single(char const *src, char**dst);
char	*int_to_str(int i);
int		parse_var(char const *src, char **out);
int		unquote_double(char const *src, char **dst);

//$로 시작하는 문자열에서 변수 이름을 찾고 그 값을 리턴
int	parse_var(char const *src, char **out)
{
	char	*name;
	char	*value;
	int		i;

	if (is_alphabet(src[1]) || src[1] == '_')
	{
		i = 1;
		while (is_alphabet(src[i]) || is_number(src[i]) || src[i] == '_')
			i++;
		name = str_substr(src, 1, i);
		value = str_clone(get_env(name));
		return (free(name), (*out) = value, i);
	}
	else if (src[1] == '?')
		return ((*out) = int_to_str(g_minishell.exit_code), 2);
	return ((*out) = (void *)0, 1);
}

int	unquote_double(char const *src, char **dst)
{
	char	*value;
	int		size;
	int		i;

	i = 1;
	while (src[i] != '\"')
	{
		if (src[i] == '$')
		{
			size = parse_var(&src[i], &value);
			if (size == 1)
				str_push(dst, src[i]);
			else
				str_push_str(dst, value);
			free(value);
			i += size;
		}
		else
		{
			str_push(dst, src[i]);
			i++;
		}
	}
	return (i + 1);
}
