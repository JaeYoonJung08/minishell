/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaju <jaju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 16:49:09 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/08/07 20:38:28 by jaju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "runner.h"
#include <shell/minishell.h>
#include <parser/compiler.h>
#include <libft/libft.h>
#include <signal/signal.h>
#include <readline/readline.h>
#include <string.h>

void	exit_code_handler(int status, int *flag_printed, int pid, int child);
void	parent_process(int *prev_read_fd, int *next);
int		child_process(t_process	*tmp, int *prev_read_fd, int *next);
int		execute_builtins(int builtin_idx, t_process *tmp);
int		execute(t_process *process);

static void	pipe_init(int *fd, int a, int b)
{
	fd[0] = a;
	fd[1] = b;
}

//builtin 첫 번째 
void	execute_no_fork(t_process *tmp, int builtin_idx)
{
	int	stdout_copy;

	if (tmp->bad_process)
		return ;
	stdout_copy = dup(1);
	dup2(tmp->out_fd, 1);
	g_minishell.exit_code = execute_builtins(builtin_idx, tmp);
	dup2(stdout_copy, 1);
	close(stdout_copy);
}

int	execute_fork(t_list *p_test)
{
	int			i;
	int			pid;
	int			next[2];
	int			prev_read_fd;
	t_process	*tmp;

	i = 0;
	pipe_init(next, 0, 1);
	prev_read_fd = dup(0);
	while (i < p_test->length)
	{
		tmp = list_get(p_test, i);
		if (i != p_test->length - 1)
			pipe(next);
		else
			pipe_init(next, dup(0), dup(1));
		if (!tmp->bad_process)
			pid = child_process(tmp, &prev_read_fd, next);
		close(prev_read_fd);
		close(next[1]);
		prev_read_fd = next[0];
		i++;
	}
	close(prev_read_fd);
	return (pid);
}

//끝난 자식의 프로세스 exit_code 반영과, 표준 입력을 받을 때 signal 
void	wait_process(int pid)
{
	int	flag_printed;
	int	status;
	int	child;

	flag_printed = 0;
	child = waitpid(0, &status, 0);
	while (child > 0)
	{
		exit_code_handler(status, &flag_printed, pid, child);
		child = waitpid(0, &status, 0);
	}
}

//builtin인 검사
int	check_builtin(char *name, int *idx)
{
	static char	*builtins[] = (char *[]){
		"echo",
		"cd",
		"pwd",
		"export",
		"unset",
		"env",
		"exit",
	};
	int			i;

	if (name == (void *)0)
		return (0);
	i = 0;
	while (i < 7)
	{
		if (str_equals(name, builtins[i]) == 1)
			return (*idx = i, 1);
		i++;
	}
	return (0);
}
