/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaju <jaju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 17:40:16 by jaju              #+#    #+#             */
/*   Updated: 2023/07/29 13:42:31 by jaju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <collection/list.h>

typedef struct s_envp
{
	char	*name;
	char	*value;
}t_envp;

typedef struct s_minishell
{
	t_list	env_list;
	int		exit_code;
}t_minishell;

t_minishell	g_minishell;

//미니쉘(전역변수) 초기화
void		minishell_init(char **envp);
//문자열에 대응하는 환경변수의 값을 리턴
char const	*get_env(char const *str);

#endif