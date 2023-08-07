/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_execute.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaju <jaju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 21:59:04 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/08/07 20:00:05 by jaju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "runner.h"
#include <signal/signal.h>
#include <shell/minishell.h>

void	process_run(t_list *tokens)
{
	t_list		process_list;
	t_process	*tmp;
	int			pid;
	int			builtin_idx;

	process_list = compile(tokens);
	tmp = list_get(&process_list, 0);
	signal(SIGINT, SIG_IGN);
	if (process_list.length == 1 && check_builtin(tmp->name, &builtin_idx)) // fork 없이 빌트인 실행 조건
		execute_no_fork(tmp, builtin_idx);
	else // 그 외 일반적인 경우
	{
		pid = execute_fork(&process_list);
		wait_process(pid);
	}
	signal(SIGINT, main_sigint_handler);
	list_free_all(&process_list, process_free);
}
