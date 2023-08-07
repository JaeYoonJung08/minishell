/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compiler.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaju <jaju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 15:48:33 by jaju              #+#    #+#             */
/*   Updated: 2023/08/04 18:07:42 by jaju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPILER_H
# define COMPILER_H

# include <collection/list.h>

// 파이프라인으로 구분되는 실행의 단위
typedef struct s_process
{
	char	*name;
	int		argc;
	char	**argv;
	int		out_fd;
	int		append;
	int		in_fd;
	int		bad_process;
}t_process;

//파이프라인 (|) 단위로 프로세스를 만들어 리스트에 넣고 리턴
t_list	compile(t_list const *tokens);
void	process_free(void *this);

#endif
