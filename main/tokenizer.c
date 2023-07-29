/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaju <jaju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 20:33:08 by jaju              #+#    #+#             */
/*   Updated: 2023/07/28 19:16:09 by jaju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "libft.h"
#include "str.h"
#include <stdlib.h>

static t_token	tokenize_symbol(char **str)
{
	t_token	token;

	token.type = VOID;
	token.content = (void *)0;
	if ((*str)[0] == '<')
	{
		if ((*str)[1] == '<')
			return (token.type = TK_HRD, (*str) += 2, token);
		return (token.type = TK_IRD, (*str)++, token);
	}
	else if ((*str)[0] == '>')
	{
		if ((*str)[1] == '>')
			return (token.type = TK_ARD, (*str) += 2, token);
		return (token.type = TK_ORD, (*str)++, token);
	}
	else if ((*str)[0] == '|')
	{
		if ((*str)[1] == '|')
			return (token.type = TK_INVALID, (*str) += 2, token);
		return (token.type = TK_PIPE, (*str)++, token);
	}
	else if ((*str)[0] == '&' && (*str)[1] == '&')
		return (token.type = TK_INVALID, (*str) += 2, token);
	return (token.type = TK_INVALID, (*str)++, token);
}

static t_token	tokenize_non_symbol(char **str)
{
	char		*start;
	t_token		token;

	token.type = TK_STR;
	start = *str;
	while (**str != '\0' && !str_includes(" \t|><&()\\;", **str))
	{
		if ((*str)[0] == '\'')
			while (*++(*str) != '\0' && **str != '\'')
				;
		if ((*str)[0] == '\"')
			while (*++(*str) != '\0' && **str != '\"')
				;
		if (**str == '\0')
			panic("Syntax Error: quote not closed");
		(*str)++;
	}
	token.content = str_substr(start, 0, (*str) - start);
	return (token);
}

// | < << > >> whitespace
t_token	*tokenize(char *s)
{
	static char	*str;
	t_token		*token;

	if (s != (void *)0)
		str = s;
	while (*str != '\0' && str_includes(" \t", *str))
		str++;
	if (str == (void *)0 || *str == '\0')
		return (str = (void *)0, (void *)0);
	token = allocate(sizeof(t_token));
	if (str_includes("|><&()\\;", *str))
		*token = tokenize_symbol(&str);
	else
		*token = tokenize_non_symbol(&str);
	return (token);
}

t_list	tokenize_command(char *str)
{
	t_list	list;
	t_token	*token;

	list_init(&list);
	token = tokenize(str);
	while (token != (void *)0)
	{
		list_add(&list, token);
		token = tokenize((void *)0);
	}
	return (list);
}
