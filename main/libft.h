/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaju <jaju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 18:22:34 by jaju              #+#    #+#             */
/*   Updated: 2023/07/28 17:28:47 by jaju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

void	*allocate(int size);
void	copy(void *src, void *dst, int size);
int		is_alphabet(char c);
int		is_number(char c);
void	panic(char *msg);

#endif