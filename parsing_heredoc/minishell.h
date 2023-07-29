/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 17:40:16 by jaju              #+#    #+#             */
/*   Updated: 2023/07/28 22:32:26 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "list.h"

typedef struct s_envp
{
	char			*key;
	char			*name;

	//next 넣어주기
	struct s_envp	*next;
}t_envp;

typedef struct s_minishell
{
	t_list	env_list;
	int		exit_code;
}t_minishell;

t_minishell	g_minishell;

t_envp	*minishell_init(char **envp);
char const	*get_envp(char const *str);

#endif