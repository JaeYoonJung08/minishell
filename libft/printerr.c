/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printerr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaju <jaju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 02:26:57 by jaju              #+#    #+#             */
/*   Updated: 2023/08/08 02:42:14 by jaju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include <str/str.h>
#include <stdio.h>

void	printerr(char const *str)
{
	write(2, str, str_length(str));
}

void	basherr(char const *str)
{
	write(2, "bash: ", 6);
	perror(str);
}

void	fakebasherr(char const *str, char const *err)
{
	write(2, "bash: ", 6);
	write(2, str, str_length(str));
	write(2, ": ", 2);
	write(2, err, str_length(err));
}
