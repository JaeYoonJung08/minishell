/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 17:03:12 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/08/11 15:50:53 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "signal.h"
#include <str/str.h>

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (s == NULL)
		return ;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
}

void	ft_putendl_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (s == NULL)
		return ;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
	write(fd, "\n", 1);
}

int	ft_nbrlen(long n)
{
	int		size;

	size = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		size++;
	while (n != 0)
	{
		n = n / 10;
		size++;
	}
	return (size);
}

int	ft_power(int nbr, int pow)
{
	int	res;

	if (pow == 0)
		return (1);
	res = nbr;
	while (pow > 1)
	{
		res *= nbr;
		pow--;
	}
	return (res);
}

char	*ft_itoa(int n)
{
	long	nbr;
	char	*s;
	int		div;
	int		i;

	i = 0;
	nbr = n;
	s = malloc(sizeof(char) * (ft_nbrlen(nbr) + 1));
	if (!s)
		return (NULL);
	if (nbr < 0)
	{
		s[i++] = '-';
		nbr = -nbr;
	}
	div = ft_power(10, ft_nbrlen(nbr) - 1);
	while (div > 0)
	{
		s[i++] = nbr / div + '0';
		nbr = nbr % div;
		div = div / 10;
	}
	s[i] = '\0';
	return (s);
}

void	sig_quit(int code)
{
	char	*nbr;

	nbr = ft_itoa(code);
	write(2, "^\\Quit: ", 8);
	write(2, nbr, str_length(nbr));
	write(2, "\n", 1);
	if (nbr)
	{
		free(nbr);
		nbr = NULL;
	}
}
