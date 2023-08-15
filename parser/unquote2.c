/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unquote2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaju <jaju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 20:43:54 by jaju              #+#    #+#             */
/*   Updated: 2023/08/07 21:15:40 by jaju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <collection/list.h>
#include <stdio.h>
#include <stdlib.h>
#include <shell/minishell.h>

int	is_power_of_two(int x)
{
	return ((x & (x - 1)) == 0);
}

//문자열 str에 문자 c를 붙임
void	str_push(char **str, char c)
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
void	str_push_str(char **new, char const *str)
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
		digit /= 10;
	}
	return (new);
}
