/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaju <jaju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:44:23 by jaju              #+#    #+#             */
/*   Updated: 2023/08/07 19:06:41 by jaju             ###   ########.fr       */
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

//heredoc에 사용할 tmp파일의 이름
static void	heredoc_filename(char *dst, int idx)
{
	copy("_00.tmp", dst, 8);
	dst[1] = (idx / 10) + '0';
	dst[2] = (idx % 10) + '0';
}

//heredoc 입력을 받기 위한 프롬프트 열기
static void	heredoc_prompt(char const *filename, char const *end)
{
	int const	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	char*const	parsed_delim = unquote(end);
	char		*str;
	char		*tmp;

	if (fd == -1)
		ft_panic("Failed to create tmp file for heredoc");
	while (1)
	{
		str = readline("> ");
		tmp = replace_env(str);
		if (str == (void *)0)
		{
			g_minishell.exit_code = 0;
			break ;
		}
		if (str_equals(tmp, parsed_delim))
			break ;
		write(fd, tmp, str_length(tmp));
		write(fd, "\n", 1);
		free(str);
	}
	free(parsed_delim);
	close(fd);
}

//heredoc 임시파일 삭제
void	heredoc_unlink_tmp(void)
{
	int		i;
	char	name[20];

	i = 0;
	while (i < 16)
	{
		heredoc_filename(name, i);
		unlink(name);
		i++;
	}
}

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
	{
		//write(2, "TOO MANY HEREDOC\n", 17);
		//printf("DEBUG\n");
		//exit(1);
		ft_panic("TOO MANY HEREDOC");
	}
}

//<<를 <로 치환, delimiter를 tmp파일로 치환, heredoc 프롬프트 생성
int	heredoc_substitute(t_list *tokens)
{
	int		heredoc_idx;
	pid_t	pid;
	int		exit_code;
	t_list	limit_strings;
	char	filename[20];

	list_init(&limit_strings);
	heredoc_replace(tokens, &limit_strings);
	//printf("DEBUG\n");
	pid = fork();
	if (pid == -1)
		ft_panic("Fork error!");
	if (pid == 0)
	{
		signal(SIGINT, main_sigint_handler_heredoc);
		heredoc_idx = 0;
		while (list_get(&limit_strings, heredoc_idx) != (void *)0)
		{
			heredoc_filename(filename, heredoc_idx);
			heredoc_prompt(filename, list_get(&limit_strings, heredoc_idx));
			heredoc_idx++;
		}
		exit(0);
	}
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
