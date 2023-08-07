/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaju <jaju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 20:31:39 by jaju              #+#    #+#             */
/*   Updated: 2023/08/04 18:16:37 by jaju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include <collection/list.h>

//토큰의 종류
typedef enum e_token_type
{
	TK_STR,
	TK_IRD,
	TK_ORD,
	TK_HRD,
	TK_ARD,
	TK_PIPE,
	TK_INVALID
}t_token_type;

//토큰의 종류와 내용을 저장하는 구조체
typedef struct s_token
{
	t_token_type	type;
	char			*content;
}t_token;

//주어진 문자열을 토근 단위로 나눠 저장한 리스트를 리턴하는 함수
int		tokenize_command(char const *str, t_list *list);
void	token_free(void *token);

#endif