/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaju <jaju@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 14:49:06 by jaju              #+#    #+#             */
/*   Updated: 2023/07/26 14:50:39 by jaju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

typedef unsigned char	t_byte;

void	copy(void *src, void *dst, int size)
{
	t_byte*const	src_ptr = src;
	t_byte*const	dst_ptr = dst;
	int				i;

	i = 0;
	while (i < size)
	{
		dst_ptr[i] = src_ptr[i];
		i++;
	}
}
