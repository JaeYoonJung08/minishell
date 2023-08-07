/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaju <jaju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 18:22:34 by jaju              #+#    #+#             */
/*   Updated: 2023/08/07 15:53:01 by jaju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

//malloc + 모든 바이트 0으로 초기화. 실패 시 exit
void	*allocate(int size);
//memcpy, src에서 dst로 size 바이트만큼 복사
void	copy(void *src, void *dst, int size);
//주어진 문자가 알파벳이면 1, 아니면 0
int		is_alphabet(char c);
//주어진 문자가 숫자면 1, 아니면 0
int		is_number(char c);
//주어진 문자열을 출력하고 exit
void	ft_panic(char *msg);
//int를 나타내는 string을 생성

#endif