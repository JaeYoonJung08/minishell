/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaju <jaju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 12:38:51 by jaju              #+#    #+#             */
/*   Updated: 2023/07/25 14:53:17 by jaju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax.h"

static int	first_last_check(t_list *tokens)
{
	t_token*const	first = list_get(tokens, 0);
	t_token*const	last = list_get(tokens, tokens->length - 1);
	int 			invalid;

	if (first == (void *)0 || last == (void *)0)
		return (0);
	invalid = first->type == TK_PIPE
		|| last->type != TK_STR
		|| first->type == TK_INVALID
		|| last->type == TK_INVALID;

	return (invalid);
}

static int	successive_token_check(t_list *tokens)
{
	t_token	*curr;
	t_token	*next;
	int		invalid;
	int		i;

	invalid = 0;
	i = 0;
	while (i + 1 < tokens->length)
	{
		curr = list_get(tokens, i);
		next = list_get(tokens, i + 1);
		invalid = (curr->type != TK_STR && next->type != TK_STR)
			|| (curr->type == TK_PIPE && next->type == TK_PIPE);
		invalid = invalid || curr->type == TK_INVALID;
		if (invalid)
			return (1);
		i++;
	}
	return (0);
}

int	syntax_check(t_list *tokens)
{
	return (
		first_last_check(tokens)
		|| successive_token_check(tokens)
	);
}
