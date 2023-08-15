/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaju <jaju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 20:35:17 by jaju              #+#    #+#             */
/*   Updated: 2023/08/08 13:46:30 by jaju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <collection/list.h>
#include <signal/signal.h>
#include <fcntl.h>
#include <shell/minishell.h>
#include <unistd.h>
#include <libft/libft.h>
#include <stdio.h>
#include <readline/readline.h>
#include <str/str.h>
#include "parser/parser.h"
#include "parser/heredoc.h"

void	main_sigint_handler(int sign);
void	main_sigint_handler_heredoc(int sig);

//heredoc에 사용할 tmp파일의 이름
void	heredoc_filename(char *dst, int idx)
{
	copy("_00.tmp", dst, 8);
	dst[1] = (idx / 10) + '0';
	dst[2] = (idx % 10) + '0';
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

//heredoc 입력을 받기 위한 프롬프트 열기
void	heredoc_prompt(char const *filename, char const *end)
{
	int const	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	char*const	parsed_lim = unquote(end);
	char		*str;
	char		*tmp;

	if (fd == -1)
		ft_panic("Failed to create tmp file for heredoc");
	while (1)
	{
		str = readline("> ");
		if (str == (void *)0)
		{
			g_minishell.exit_code = 0;
			break ;
		}
		tmp = replace_env(str);
		if (str_equals(tmp, parsed_lim))
			break ;
		write(fd, tmp, str_length(tmp));
		write(fd, "\n", 1);
		free(tmp);
		free(str);
	}
	free(parsed_lim);
	close(fd);
}

int	heredoc_fork(t_list *limit_strings)
{
	int const	pid = fork();
	char		filename[20];
	int			heredoc_idx;

	heredoc_idx = 0;
	if (pid == -1)
		ft_panic("Fork error!");
	if (pid > 0)
		return (pid);
	signal(SIGINT, main_sigint_handler_heredoc);
	heredoc_idx = 0;
	while (list_get(limit_strings, heredoc_idx) != (void *)0)
	{
		heredoc_filename(filename, heredoc_idx);
		heredoc_prompt(filename, list_get(limit_strings, heredoc_idx));
		heredoc_idx++;
	}
	exit(0);
}
