/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_execute.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaju <jaju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 21:59:04 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/08/08 14:38:47 by jaju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "runner.h"
#include <signal/signal.h>
#include <shell/minishell.h>

void	sig_quit(int code);

void	process_run(t_list *tokens)
{
	t_list		process_list;
	t_process	*tmp;
	int			pid;
	int			builtin_idx;

	process_list = compile(tokens);
	tmp = list_get(&process_list, 0);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, sig_quit);
	if (process_list.length == 1 && check_builtin(tmp->name, &builtin_idx))
		execute_no_fork(tmp, builtin_idx);
	else
	{
		pid = execute_fork(&process_list);
		wait_process(pid);
	}
	signal(SIGINT, main_sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	list_free_all(&process_list, process_free);
}
