/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaju <jaju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 17:40:16 by jaju              #+#    #+#             */
/*   Updated: 2023/07/29 12:47:39 by jaju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "list.h"

typedef struct s_envp
{
	char	*key;
	char	*name;
}t_envp;

typedef struct s_minishell
{
	t_list	env_list;
	int		exit_code;
}t_minishell;

t_minishell	g_minishell;

void	minishell_init(char **envp);
char const	*get_envp(char const *str);

#endif