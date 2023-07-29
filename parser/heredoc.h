/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaju <jaju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 13:56:33 by jaju              #+#    #+#             */
/*   Updated: 2023/07/29 13:47:43 by jaju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

# include "collection/list.h"
# include <parser/tokenizer.h>//없어도 될 수 있음

//<<를 <로 치환, delimiter를 tmp파일로 치환.
void	heredoc_substitute(t_list *tokens);
//heredoc 임시파일 삭제
void	heredoc_unlink_tmp(void);
#endif
