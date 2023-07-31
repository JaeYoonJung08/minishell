/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 16:41:01 by jaju              #+#    #+#             */
/*   Updated: 2023/07/31 21:33:33 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <str/str.h>
#include <collection/list.h>
#include <parser/tokenizer.h>
#include <parser/syntax.h>
#include <parser/heredoc.h>
#include <shell/minishell.h>
#include <pipe/pipe.h>
#include <parser/compiler.h>

void	visualize(t_list tokens)
{
	int		i;
	t_token	*token;

	//printf("syntax_wrong: %d\n\n", syntax_check(&tokens));
	i = 0;
	while (i < tokens.length)
	{
		token = list_get(&tokens, i);
		if (token->type == TK_STR)
		{
			//printf("%s\n", token->content);
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

	minishell_init(envp);
	while (1)
	{
		str = readline("minishell$ ");
		//printf("DEBUG");
		if (str == (void *)0)
			exit(1);
		//printf("DEBUG12");
		if (str_length(str) == 0)
			continue ;
		add_history(str);
		tokens = tokenize_command(str);
		heredoc_substitute(&tokens);
		t_list p_test = compile(&tokens);
		//exit(0);
		//visualize(tokens);
		
		pipe_start(&p_test);
		//exit(0);
		heredoc_unlink_tmp();
		free(str);
	}

	return (0);
}
