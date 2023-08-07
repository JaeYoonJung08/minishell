/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaju <jaju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 22:08:14 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/08/07 18:47:41 by jaju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../parser/compiler.h"
#include <parser/parser.h>
#include "../../str/str.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <shell/minishell.h>

int	is_n_flag(char const *str)
{
	int	i;

	if (str == (void *)0)
		return (0);
	if (str[0] == '-' && str[1] == 'n')
	{
		i = 2;
		while (str[i] != '\0')
		{
			if (str[i] != 'n')
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}

int	echo_main(t_process *this)
{
	int		n_flag;
	int		i;

	n_flag = 0;
	i = 1;
	if (this->argc >= 2)
	{
		while (is_n_flag(this->argv[i]))
		{
			n_flag = 1;
			i++;
		}
	}
	while (i < this->argc)
	{
		printf("%s", this->argv[i]);
		if (i != this->argc - 1)
			printf(" ");
		i++;
	}
	if (!n_flag)
		printf("\n");
	return (SUCCES_EXIT);
}
