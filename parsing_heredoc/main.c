/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 16:41:01 by jaju              #+#    #+#             */
/*   Updated: 2023/07/28 22:53:38 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include "str.h"
#include "list.h"
#include "tokenizer.h"
#include "syntax.h"
#include "heredoc.h"

#include "minishell.h"

void	visualize(t_list tokens)
{
	int		i;
	t_token	*token;

	printf("syntax_wrong: %d\n\n", syntax_check(&tokens));
	i = 0;
	while (i < tokens.length)
	{
		token = list_get(&tokens, i);
		if (token->type == TK_STR)
		{
			printf("%s\n", token->content);
			free(token->content);
		}
		else if (token->type == TK_IRD)
			printf("<\n");
		else if (token->type == TK_HRD)
			printf("<<\n");
		else if (token->type == TK_ORD)
			printf(">\n");
		else if (token->type == TK_ARD)
			printf(">>\n");
		else if (token->type == TK_PIPE)
			printf("|\n");
		else if (token->type == TK_INVALID)
			printf("(invalid)\n");
		//free(token);
		i++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;
	(void) envp;
	char	*str;
	t_list	tokens;
	t_envp *pair;


	//= 기준으로 환경변수 다 들고오기
	pair = minishell_init(envp);
	// while (pair->next)
	// {
	// 	printf("pair->key %s , pair.name : %s\n", pair->key, pair->name);
	// 	pair = pair->next;
	// }
	exit(0);
	while (1)
	{
		str = readline("minishell$ ");
		if (str == (void *)0)
			exit(1);
		if (str_length(str) == 0)
			continue ;
		add_history(str);
		tokens = tokenize_command(str);
		heredoc_substitute(&tokens);
		pipe_start();
		visualize(tokens);
		heredoc_unlink_tmp();
		free(str);
	}

	return (0);
}
