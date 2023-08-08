/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaju <jaju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 20:33:08 by jaju              #+#    #+#             */
/*   Updated: 2023/08/08 15:12:01 by jaju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include <libft/libft.h>
#include <str/str.h>
#include <stdlib.h>
#include <stdio.h>
#include <shell/minishell.h>

//리다이렉션, 파이프라인과 같은 기호를 토큰으로 만듦, 오류 시 0
static int	tokenize_symbol(char const **str, t_token *token)
{
	token->type = TK_INVALID;
	token->content = (void *)0;
	if ((*str)[0] == '<')
	{
		if ((*str)[1] == '<')
			return (token->type = TK_HRD, (*str) += 2, 1);
		return (token->type = TK_IRD, (*str)++, 1);
	}
	else if ((*str)[0] == '>')
	{
		if ((*str)[1] == '>')
			return (token->type = TK_ARD, (*str) += 2, 1);
		return (token->type = TK_ORD, (*str)++, 1);
	}
	else if ((*str)[0] == '|')
		return (token->type = TK_PIPE, (*str)++, 1);
	return (printerr("bash: syntax error: invalid token\n"),
		g_minishell.exit_code = 258, 0);
}

//기호가 아닌 나머지를 토큰으로 만듦
static int	tokenize_non_symbol(char const **str, t_token *token)
{
	int	i;

	token->type = TK_STR;
	i = 0;
	while ((*str)[i] != '\0' && !str_includes(" \t|><&()\\;", (*str)[i]))
	{
		if ((*str)[i] == '\'')
			while ((*str)[++i] != '\0' && (*str)[i] != '\'')
				;
		if ((*str)[i] == '\"')
			while ((*str)[++i] != '\0' && (*str)[i] != '\"')
				;
		if ((*str)[i] == '\0')
			return (printerr("bash: syntax error: quote not closed\n"),
				g_minishell.exit_code = 258, 0);
		i++;
	}
	token->content = str_substr(*str, 0, i);
	*str += i;
	return (1);
}

// | < << > >> whitespace를 기준으로 토큰을 나눔
int	tokenize(char const *s, t_token **token)
{
	static char const	*str;

	if (s != (void *)0)
		str = s;
	if (str == (void *)0)
		return (*token = (void *)0, 1);
	while (*str != '\0' && str_includes(" \t", *str))
		str++;
	if (*str == '\0')
		return (str = (void *)0, *token = (void *)0, 1);
	*token = allocate(sizeof(t_token));
	if (str_includes("|><&()\\;", *str))
		return (tokenize_symbol(&str, *token));
	else
		return (tokenize_non_symbol(&str, *token));
}

//주어진 문자열을 토큰 리스트로 만들어 리턴함
int	tokenize_command(char const *str, t_list *list)
{
	t_token	*token;

	if (!tokenize(str, &token))
		return (free(token), 0);
	while (token != (void *)0)
	{
		list_add(list, token);
		if (!tokenize((void *)0, &token))
			return (free(token), 0);
	}
	return (free(token), 1);
}

void	token_free(void *token)
{
	t_token*const	this = token;

	free(this->content);
}
