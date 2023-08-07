/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unquote.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaju <jaju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 15:47:44 by jaju              #+#    #+#             */
/*   Updated: 2023/08/07 19:55:02 by jaju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <collection/list.h>
#include <stdio.h>
#include <stdlib.h>
#include <shell/minishell.h>

static int	is_power_of_two(int x)
{
	return ((x & (x - 1)) == 0);
}

//문자열 str에 문자 c를 붙임
static void	str_push(char **str, char c)
{
	int const	len = str_length(*str);
	char		*new;

	if (is_power_of_two(len + 1))
	{
		new = allocate(len * 2 + 2);
		copy(*str, new, len);
		free(*str);
		(*str) = new;
	}
	(*str)[len] = c;
}

//문자열 new에 주어진 문자열 str을 환경변수로 치환해 붙임
static void	str_push_str(char **new, char const *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		str_push(new, str[i]);
		i++;
	}
}

//작은 따옴표 안의 내용 파싱
int	unquote_single(char const *src, char**dst)
{
	int	i;

	i = 1;
	while (src[i] != '\'')
	{
		str_push(dst, src[i]);
		i++;
	}
	return (i + 1);
}

//int를 문자열로 변환
char	*int_to_str(int i)
{
	long long	abs;
	char*const	new = allocate(11 * sizeof(char));
	int			digit;

	if (i == 0)
		return (new[0] = '0', new);
	abs = i;
	if (abs < 0)
	{
		new[str_length(new)] = '-';
		abs *= -1;
	}
	digit = 1;
	while (i / digit >= 10)
		digit *= 10;
	while (digit >= 1)
	{
		new[str_length(new)] = (abs / digit) % 10 + '0';
		//printf("new : %lld\n", (abs / digit) % 10);
		digit /= 10;
	}
	return (new);
}

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