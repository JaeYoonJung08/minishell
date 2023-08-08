/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaju <jaju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 16:41:01 by jaju              #+#    #+#             */
/*   Updated: 2023/08/08 12:22:34 by jaju             ###   ########.fr       */
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
#include <parser/parser.h>

// 터미널에 ^C, ^\등의 시그널표식을 출력하지않도록 설정
void	set_terminal_print_off(void)
{
	struct termios	term;

	tcgetattr(1, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(1, 0, &term);
}

// 터미널에 ^C, ^\등의 시그널표식을 출력하도록 설정
void	set_terminal_print_on(void)
{
	struct termios	term;

	tcgetattr(1, &term);
	term.c_lflag |= (ECHOCTL);
	tcsetattr(1, 0, &term);
}

void	minishell_exit(void)
{
	write(2, "\033[1A", 4);
	write(2, "\033[11C", 5);
	write(2, "exit\n", 5);
	set_terminal_print_on();
	exit(g_minishell.exit_code = 0);
}

void	run_command(void)
{
	char	*str;
	t_list	tokens;

	str = readline("minishell$ ");
	if (str == (void *)0)
		minishell_exit();
	if (str_length(str) == 0)
		return (free(str), (void)0);
	add_history(str);
	list_init(&tokens);
	if (!tokenize_command(str, &tokens))
		return (free(str), list_free_all(&tokens, token_free), (void)0);
	if (syntax_check(&tokens))
		return (free(str), list_free_all(&tokens, token_free), (void)0);
	if (!heredoc_substitute(&tokens))
		return (free(str), list_free_all(&tokens, token_free), (void)0);
	process_run(&tokens);
	heredoc_unlink_tmp();
	list_free_all(&tokens, token_free);
	free(str);
}

int	main(int argc, char **argv, char **envp)
{
	(void )	argc;
	(void )	argv;
	minishell_init(envp);
	set_terminal_print_off();
	all_signal();
	while (1)
		run_command();
	return (0);
}
