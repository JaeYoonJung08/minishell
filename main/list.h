/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaju <jaju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 20:21:42 by jaju              #+#    #+#             */
/*   Updated: 2023/07/24 20:32:32 by jaju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

typedef struct s_list{
	void	**data;
	int		length;
	int		capacity;
}t_list;

void	list_init(t_list *this);
void	list_add(t_list *this, void *element);
void	*list_get(t_list *this, int i);


#endif