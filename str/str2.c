/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaju <jaju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 20:28:25 by jaju              #+#    #+#             */
/*   Updated: 2023/08/07 20:29:14 by jaju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"
#include <libft/libft.h>
#include <stdlib.h>

//str에 있는 모든 replaced를 with로 치환한 문자열을 생성
char	*str_replace(char const *str, char const *replaced, char *with)
{
	int const	size = 1
		+ str_length(str) / str_length(replaced) * str_length(with)
		+ str_length(str) % str_length(replaced);
	char*const	new = allocate(size * sizeof(char));
	int			i;
	int			j;

	i = 0;
	while (str[0] != '\0')
	{
		j = 0;
		while (str[j] != '\0' && replaced[j] != '\0' && replaced[j] == str[j])
			j++;
		if (replaced[j] == '\0')
		{
			str += j;
			j = 0;
			while (with[j] != '\0')
				new[i++] = with[j++];
			continue ;
		}
		new[i++] = (str++)[0];
	}
	return (new);
}

//a와b가 같다면 1,다르다면 0
int	str_equals(char const *a, char const *b)
{
	int	i;

	i = 0;
	while (a[i] != '\0' && b[i] != '\0' && a[i] == b[i])
		i++;
	return (a[i] == b[i]);
}

//a와 b를 붙인 새로운 문자열을 생성
char	*str_join(char const *a, char const *b)
{
	int const	length = str_length(a) + str_length(b);
	char*const	new = allocate(length + 1);
	char		*ptr;

	ptr = new;
	while (*a != '\0')
		*(ptr++) = *(a++);
	while (*b != '\0')
		*(ptr++) = *(b++);
	return (new);
}

//str에서 c가 몇 번째 인덱스에 있는지 리턴, 없으면 -1
int	str_indexof(char const *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

//str을 복제하는 함수
char	*str_clone(char const *str)
{
	char	*new;
	char	*ptr;

	if (str == (void *)0)
		return ((void *)0);
	new = allocate((str_length(str) + 1) * sizeof(char));
	ptr = new;
	while (*str != '\0')
		*(ptr++) = *(str++);
	return (new);
}
