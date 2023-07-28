/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaju <jaju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 20:31:39 by jaju              #+#    #+#             */
/*   Updated: 2023/07/28 19:21:21 by jaju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "list.h"

typedef enum e_token_type
{
	TK_STR,
	TK_IRD,
	TK_ORD,
	TK_HRD,
	TK_ARD,
	TK_PIPE,
	TK_INVALID,
	TK_EXPANDED_STR,
	TK_QUOTED_STR
}t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*content;
}t_token;

t_list	tokenize_command(char *str);

#endif