/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 01:56:35 by jaju              #+#    #+#             */
/*   Updated: 2023/08/06 16:48:12 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>



typedef unsigned char	t_byte;

void	*allocate(int size)
{
	void*const	ptr = malloc(size);
	int			i;

	if (ptr == (void *)0)
		exit(1);
	i = 0;
	while (i < size)
	{
		((t_byte *)ptr)[i] = (t_byte)0;
		i++;
	}
	return (ptr);
}
