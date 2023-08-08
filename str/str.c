/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaju <jaju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 20:18:01 by jaju              #+#    #+#             */
/*   Updated: 2023/08/07 20:28:57 by jaju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"
#include "libft/libft.h"
#include <stdlib.h>

//문자열의 길이를 리턴
int	str_length(char const *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

//str의 [start, end)만큼을 복사, str[end]는 포함하지 않음
char	*str_substr(char const *str, int start, int end)
{
	int const	length = str_length(str);
	char		*copy;
	int			i;

	if (end < start)
		return ((void *)0);
	copy = allocate((end - start + 1) * sizeof(char));
	i = start;
	while (i < end)
	{
		if (i >= length)
			return (copy);
		copy[i - start] = str[i];
		i++;
	}
	return (copy);
}

//str안에 c가 있으면 1, 없으면 0
int	str_includes(char const *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

//strtok과 같음
char	*str_tokenize(char *str, char const *delim)
{
	static char	*saved;
	char		*tmp;

	if (str != (void *)0)
		saved = str;
	if (saved == (void *)0)
		return ((void *)0);
	while (str_includes(delim, *saved))
		saved++;
	tmp = saved;
	while (*saved != '\0' && !str_includes (delim, *saved))
		saved++;
	if (*saved == '\0')
		saved = (void *)0;
	else
		*(saved++) = '\0';
	return (tmp);
}
