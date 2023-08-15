/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unqoute2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaju <jaju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 20:43:54 by jaju              #+#    #+#             */
/*   Updated: 2023/08/07 21:00:40 by jaju             ###   ########.fr       */
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
