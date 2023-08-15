/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaju <jaju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 20:27:08 by jaju              #+#    #+#             */
/*   Updated: 2023/08/07 20:30:14 by jaju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include <stdlib.h>
#include <libft/libft.h>

void	resize(t_list *this, int new_size)
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

void	list_free(t_list *this)
{
	free(this->data);
}

void	list_free_all(t_list *this, void (*data_free)(void *))
{
	int	i;

	i = 0;
	while (i < this->length)
	{
		if (data_free != (void *)0)
			data_free(this->data[i]);
		free(this->data[i]);
		i++;
	}
	free(this->data);
}
