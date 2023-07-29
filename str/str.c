/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 20:18:01 by jaju              #+#    #+#             */
/*   Updated: 2023/07/29 16:48:00 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"
#include "libft/libft.h"
#include <stdlib.h>

int	str_length(char const *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}


char	*str_substr(char const *str, int start, int end)
{
	int const	length = str_length(str);
	char		*copy;
	int			i;

	if (end <= start)
		return ((void *)0);
	copy = allocate((end - start + 1) * sizeof(char));
	i = start;
	while (i < end)
	{
		if (i >= length)
			return (copy);//or exit(1);
		copy[i - start] = str[i];
		i++;
	}
	return (copy);
}

int		str_includes(char const *str, char c)
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
		return (saved = (void *)0, (void *)0);
	else
		*(saved++) = '\0';
	return (tmp);
}

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

int	str_equals(char const *a, char const *b)
{
	int	i;

	i = 0;
	while (a[i] != '\0' && b[i] != '\0' && a[i] == b[i])
		i++;
	return (a[i] == b[i]);
}

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

int	str_indexof(char *str, char c)
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

char	*str_clone(char const *string)
{
	char	*temp;
	int		i;
	int		count;

	i = 0;
	if (!string)
		return (0);
	count = str_length(string);
	temp = (char *)malloc(sizeof(char) * (count + 1));
	if (!temp)
		return (0);
	while (string[i])
	{
		temp[i] = string[i];
		i++;
	}
	temp[i] = '\0';
	return (temp);
}
