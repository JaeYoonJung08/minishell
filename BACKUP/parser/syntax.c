/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaju <jaju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 12:38:51 by jaju              #+#    #+#             */
/*   Updated: 2023/08/05 18:25:59 by jaju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax.h"
#include <stdio.h>

//맨 앞과 맨 뒤에 있는 토큰이 그 자리에 있어도 되는가?
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

//연속적으로 오는 두 개의 토큰이 존재할 수 있는 조합인가?
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
		invalid = (curr->type != TK_STR && next->type != TK_STR);
		invalid = invalid || (curr->type == TK_PIPE && next->type == TK_PIPE);
		if (invalid)
			return (1);
		i++;
	}
	return (0);
}

static int	any_invalid(t_list *tokens)
{
	t_token	*curr;
	int		i;

	i = 0;
	while (i < tokens->length)
	{
		curr = list_get(tokens, i);
		if (curr->type == TK_INVALID)
			return (1);
		i++;
	}
	return (0);
}

//토큰 리스트 단위 문법 체크
int	syntax_check(t_list *tokens)
{
	int const	is_wrong = any_invalid(tokens)
		|| first_last_check(tokens)
		|| successive_token_check(tokens);

	if (is_wrong)
		printf("minishell: invalid syntax\n");
	return (is_wrong);
}
