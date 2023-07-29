/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaju <jaju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 01:59:14 by jaju              #+#    #+#             */
/*   Updated: 2023/07/25 04:43:37 by jaju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include "libft.h"
#include <stdlib.h>

typedef unsigned int	t_byte;

static void	resize(t_list *this, int new_size)
{
	void**const	new = allocate(new_size * sizeof(void *));
	int			i;

	i = 0;
	while (i < this->capacity)
	{
		if (i >= new_size)
			break ;
		new[i] = this->data[i];
		i++;
	}
	free(this->data);
	this->data = new;
	this->capacity = new_size;
}

void	list_init(t_list *this)
{
	this->length = 0;
	this->capacity = 8;
	this->data = allocate(this->capacity * sizeof(void *));
}

void	list_add(t_list *this, void *element)
{
	if (this->length == this->capacity)
		resize(this, this->capacity * 2);
	this->data[this->length++] = element;
}

void	*list_get(t_list *this, int i)
{
	if (i < 0 || i >= this->length)
		return ((void *)0);
	return (this->data[i]);
}
