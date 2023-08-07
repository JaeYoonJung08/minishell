/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 16:35:44 by jaju              #+#    #+#             */
/*   Updated: 2023/08/05 18:32:50 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "compiler.h"
#include <str/str.h>
#include <unistd.h>
#include <fcntl.h>
#include <libft/libft.h>
#include <stdlib.h>
#include <parser/tokenizer.h>
#include <parser/parser.h>
#include <shell/minishell.h>

#define STD_IN 0
#define STD_OUT 1

//프로세스 구조체 초기화
void	process_init(t_process *process);
//프로세스의 이름 설정
void	set_name(t_process *process, char const *name);
//프로세스의 옵션 추가
void	add_arg(t_process *process, char const *arg);
//프로세스의 출력 파일을 설정, 실패 시 0, 성공 시 1 리턴
int		set_output(t_process *process, char *filename, int append);
//프로세스의 입력을 설정, 실패 시 0 리턴, 성공 시 1 리턴
int		set_input(t_process *process, char *filename);

//프로세스 구조체 초기화
void	process_init(t_process *process)
{
	process->bad_process = 0;
	process->in_fd = 0;
	process->out_fd = 1;
	process->name = (void *)0;
	process->argc = 0;
	process->argv = allocate(1 * sizeof(char *));
}

void	process_free(void *this)
{
	t_process*const	process = this;
	int				i;

	i = 0;
	while (process->argv[i] != (void *)0)
	{
		free(process->argv[i]);
		i++;
	}
	free(process->argv);
	free(process->name);
}

//프로세스의 이름 설정
void	set_name(t_process *process, char const *name)
{
	process->name = unquote_env(name);
	add_arg(process, name);
}

//프로세스의 옵션 추가
void	add_arg(t_process *process, char const *arg)
{
	int		length;
	char	**tmp;

	length = 0;
	while (process->argv[length] != (void *)0)
		length++;
	if (length % 16 == 0)
	{
		tmp = allocate((length + 16 + 1) * sizeof(char *));
		copy(process->argv, tmp, length);
		free(process->argv);
		process->argv = tmp;
	}
	process->argc++;
	process->argv[length] = unquote_env(arg);
}
#include <stdio.h>

//프로세스의 출력 파일을 설정, 실패 시 0, 성공 시 1 리턴
int	set_output(t_process *process, char *filename, int append)
{
	if (process->out_fd != STD_OUT)
		if (close(process->out_fd))
			return (process->bad_process = 1, 0);
	process->out_fd = open(filename, O_WRONLY | O_CREAT, 0644);
	process->append = append;
	if (process->out_fd == -1)
	{
		write(2, "bash: ", 6);
		write(2, filename, str_length(filename));
		write(2, ": ", 2);
		perror("");
		g_minishell.exit_code = 1;
		return (process->bad_process = 1, 0);
	}
	return (1);
}

//프로세스의 입력을 설정, 실패 시 0 리턴, 성공 시 1 리턴
int	set_input(t_process *process, char *filename)
{
	if (process->in_fd != STD_IN)
		if (close(process->in_fd))
			return (process->bad_process = 1, 0);
	process->in_fd = open(filename, O_RDONLY);
	if (process->in_fd == -1)
	{
		write(2, "bash: ", 6);
		write(2, filename, str_length(filename));
		write(2, ": ", 2);
		perror("");
		g_minishell.exit_code = 1;
		return (process->bad_process = 1, 0);
	}
	return (1);
}
