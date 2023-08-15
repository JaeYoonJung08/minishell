/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaju <jaju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 21:01:29 by jaju              #+#    #+#             */
/*   Updated: 2023/08/08 10:57:59 by jaju             ###   ########.fr       */
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
#include <stdio.h>

#define STDIN 0
#define STDOUT 1

//프로세스의 입력을 설정, 실패 시 0 리턴, 성공 시 1 리턴
int	set_input(t_process *process, char *filename)
{
	if (process->in_fd != STDIN)
		if (close(process->in_fd))
			return (process->bad_process = 1, 0);
	process->in_fd = open(filename, O_RDONLY);
	if (process->in_fd == -1)
	{
		basherr(filename);
		g_minishell.exit_code = 1;
		return (process->bad_process = 1, 0);
	}
	return (1);
}
