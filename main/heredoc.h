/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaju <jaju@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 13:56:33 by jaju              #+#    #+#             */
/*   Updated: 2023/07/27 00:34:46 by jaju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

# include "list.h"
# include "tokenizer.h"
# include <unistd.h>
# include <fcntl.h>
# include "str.h"
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>

//<<를 <로 치환 heredoc_substitute(t_list* tokens)
void	heredoc_substitute(t_list *tokens);
//heredoc 임시파일 삭제
void	heredoc_unlink_tmp(void);
#endif
