/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unquote.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaju <jaju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 15:47:44 by jaju              #+#    #+#             */
/*   Updated: 2023/08/07 21:08:22 by jaju             ###   ########.fr       */
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

//따옴표가 붙지 않은 경우
int	unquote_normal(char const *src, char **dst)
{
	char	*value;
	int		size;

	if (src[0] == '$')
	{
		size = parse_var(&src[0], &value);
		if (size == 1)
			str_push(dst, src[0]);
		else
			str_push_str(dst, value);
		return (free(value), size);
	}
	else
	{
		str_push(dst, src[0]);
		return (1);
	}
}

//작은 따옴표 ('')를 제외한 부분에서 환경변수 치환
char	*unquote_env(char const *str)
{
	char	*new;
	int		i;

	new = allocate(1 * sizeof(char));
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'')
			i += unquote_single(str + i, &new);
		else if (str[i] == '\"')
			i += unquote_double(str + i, &new);
		else
			i += unquote_normal(str + i, &new);
	}
	return (new);
}

char	*replace_env(char const *str)
{
	char	*new;
	int		i;

	new = allocate(1 * sizeof(char));
	i = 0;
	while (str[i] != '\0')
		i += unquote_normal(str + i, &new);
	return (new);
}

//환경변수 치환 없이 따옴표 제거
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
