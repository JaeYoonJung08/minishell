/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaju <jaju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:44:23 by jaju              #+#    #+#             */
/*   Updated: 2023/08/08 14:36:01 by jaju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"
#include <libft/libft.h>
#include <parser/parser.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <shell/minishell.h>

//signal 함수
void	main_sigint_handler(int sign);
void	main_sigint_handler_heredoc(int sig);
int		heredoc_fork(t_list *limit_strings, int *heredoc_idx);
void	heredoc_filename(char *dst, int idx);

// "<< LIMIT STRING"을 "< heredoc_tmpfile"로 바꿈
static void	heredoc_replace(t_list *tokens, t_list *limit_strings)
{
	t_token	*token;
	int		i;
	int		heredoc_idx;
	char	filename[20];

	i = 0;
	heredoc_idx = 0;
	while (i < tokens->length)
	{
		token = list_get(tokens, i);
		if (token->type == TK_HRD)
		{
			token->type = TK_IRD;
			token = list_get(tokens, ++i);
			list_add(limit_strings, token->content);
			heredoc_filename(filename, heredoc_idx);
			token->content = str_clone(filename);
			heredoc_idx++;
		}
		i++;
	}
	if (heredoc_idx > 16)
		ft_panic("TOO MANY HEREDOC");
}

//<<를 <로 치환, delimiter를 tmp파일로 치환, heredoc 프롬프트 생성
int	heredoc_substitute(t_list *tokens)
{
	int		heredoc_idx;
	pid_t	pid;
	int		exit_code;
	t_list	limit_strings;

	list_init(&limit_strings);
	heredoc_replace(tokens, &limit_strings);
	pid = heredoc_fork(&limit_strings, &heredoc_idx);
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &exit_code, 0);
	list_free_all(&limit_strings, (void *)0);
	signal(SIGINT, main_sigint_handler);
	if (WIFEXITED(exit_code))
	{
		exit_code = WEXITSTATUS(exit_code);
		if (exit_code != 0)
		{
			heredoc_unlink_tmp();
			g_minishell.exit_code = exit_code;
			return (0);
		}
	}
	return (1);
}
