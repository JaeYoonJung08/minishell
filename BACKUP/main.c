/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaju <jaju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 16:41:01 by jaju              #+#    #+#             */
/*   Updated: 2023/08/07 19:18:31 by jaju             ###   ########.fr       */
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
#include <runner/runner.h>
#include <parser/compiler.h>
#include <signal/signal.h>
#include <termios.h>

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


void	set_terminal_print_off(void)
// 터미널에 ^C, ^\등의 시그널표식을 출력하지않도록 설정
{
	struct termios	term; // 터미널 설정이 담겨있는 termios 구조체

	tcgetattr(1, &term); // 현재 터미널의 설정을 term에 가져옴
	term.c_lflag &= ~(ECHOCTL); // 시그널표식 출력이 true 라면 false로 변경
	tcsetattr(1, 0, &term); // 변경한 term 설정을 현재 터미널에 적용
}

void	set_terminal_print_on(void)
// 터미널에 ^C, ^\등의 시그널표식을 출력하도록 설정
{
	struct termios	term; // 터미널 설정이 담겨있는 termios 구조체

	tcgetattr(1, &term); // 현재 터미널의 설정을 term에 가져옴
	term.c_lflag |= (ECHOCTL); // 시그널표식 출력이 false 라면 true로 변경
	tcsetattr(1, 0, &term);  // 변경한 term 설정을 현재 터미널에 적용
}

void	minishell_exit(void)
{
	write(2, "\033[1A", 4);// 현재 커서의 위치를 한칸 위로 올려줌 
	write(2, "\033[11C", 5); // 현재 커서의 위치를 12번째칸으로 이동
	write(2, "exit\n", 5); // exit를 출력
	set_terminal_print_on();
	exit(g_minishell.exit_code = 0);
}

// void	leaks(void)
// {
// 	system("leaks minishell");
// }

#include <parser/parser.h>

void	run_command(void)
{
	char	*str;
	t_list	tokens;

	str = readline("minishell$ "); //1번 할당
	if (str == (void *)0)
		minishell_exit();
	if (str_length(str) == 0) //1번 실패
		return (free(str), (void)0);
	add_history(str);
	list_init(&tokens);
	if (!tokenize_command(str, &tokens)) //2번 할당 (토큰 리스트)
		return (free(str), list_free_all(&tokens, token_free), (void)0);
	if (syntax_check(&tokens))
		return (free(str), list_free_all(&tokens, token_free), (void)0);
	if (!heredoc_substitute(&tokens)) //3번째 할당
		return (free(str), list_free_all(&tokens, token_free), (void)0);
	process_run(&tokens);
	heredoc_unlink_tmp();
	list_free_all(&tokens, token_free);
	free(str);
}


int	main(int argc, char **argv, char **envp)
{
	// char	*str;
	// t_list	tokens;

	(void )	argc;
	(void )	argv;
	minishell_init(envp);
	set_terminal_print_off();
	all_signal();
	//atexit(leaks);
	while (1)
	{	
		//printf("main heredoc exit_cdoe : %d\n", g_minishell.exit_code);
		run_command();
		// str = readline("minishell$ ");
		// if (str == (void *)0)
		// 	minishell_exit();
		// if (str_length(str) == 0)
		// 	continue ;
		// add_history(str);
		// if (!tokenize_command(str, &tokens))
		// 	continue ;
		// if (syntax_check(&tokens))
		// 	continue ;
		// if (!heredoc_substitute(&tokens))
		// 	continue ;
		// process_run(&tokens);
		// heredoc_unlink_tmp();
		// free(str);
	}
	return (0);
}
