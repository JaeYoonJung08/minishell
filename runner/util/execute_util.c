/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaju <jaju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 16:52:02 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/08/08 13:52:06 by jaju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../runner.h"
#include <shell/minishell.h>
#include <parser/compiler.h>
#include <libft/libft.h>
#include <signal/signal.h>
#include <readline/readline.h>
#include <string.h>

int		echo_main(t_process *this);
int		pwd_main(t_process *this);
int		cd_main(t_process *this);
int		export_main(t_process *this);
int		execute(t_process *process);
int		env_main(t_process *this);
int		exit_main(t_process *this);
int		unset_main(t_process *this);

void	parent_process(int *prev_read_fd, int *next)
{
	signal(SIGINT, SIG_IGN);
	close((*prev_read_fd));
	close(next[1]);
	(*prev_read_fd) = next[0];
}

int	child_process(t_process	*tmp, int *prev_read_fd, int *next)
{
	int const	pid = fork();

	if (pid == -1)
		ft_panic("FORK ERROR");
	else if (pid > 0)
		return (pid);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (tmp->in_fd == 0)
		tmp->in_fd = (*prev_read_fd);
	else
		close((*prev_read_fd));
	if (tmp->out_fd == 1)
		tmp->out_fd = next[1];
	else
		close(next[1]);
	dup2(tmp->in_fd, 0);
	dup2(tmp->out_fd, 1);
	close(tmp->out_fd);
	close(tmp->in_fd);
	close(next[0]);
	execute(tmp);
	return (0);
}

//builtins 실행
int	execute_builtins(int builtin_idx, t_process *tmp)
{
	if (builtin_idx == ECHO)
		return (echo_main(tmp));
	else if (builtin_idx == CD)
		return (cd_main(tmp));
	else if (builtin_idx == PWD)
		return (pwd_main(tmp));
	else if (builtin_idx == EXPORT)
		return (export_main(tmp));
	else if (builtin_idx == UNSET)
		return (unset_main(tmp));
	else if (builtin_idx == ENV)
		return (env_main(tmp));
	else if (builtin_idx == EXIT)
		return (exit_main(tmp));
	return (0);
}

//builtin or 명령어 실행
int	execute(t_process *process)
{
	char const	*env_path = get_env("PATH");
	int			builtin_idx;
	char		*full_path;

	if (process->name == (void *)0)
		exit(0);
	full_path = complete_path(env_path, process->name);
	if (check_builtin(process->name, &builtin_idx))
		return (exit(execute_builtins(builtin_idx, process)), 0);
	else
	{
		if (execve(full_path, process->argv, get_envp()) == -1)
		{
			fakebasherr(process->argv[0], "command not found\n");
			exit(127);
		}
		return (1);
	}
}

//signal에 대한 exitcode_넣어주기
void	exit_code_handler(int status, int *flag_printed, int pid, int child)
{
	int	signo;

	if (WIFSIGNALED(status))
	{
		signo = WTERMSIG(status);
		if ((*flag_printed) == 0)
		{
			if (signo == SIGINT)
				printf("^C\n");
			(*flag_printed) = 1;
		}
		if (child == pid)
			g_minishell.exit_code = 128 + signo;
	}
	else if (child == pid)
		g_minishell.exit_code = WEXITSTATUS(status);
}
