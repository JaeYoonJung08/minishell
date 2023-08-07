/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 23:11:35 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/08/03 17:12:35 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_H
# define SIGNAL_H

# include <stdlib.h>
# include <signal.h>

void	all_signal(void);
void	main_sigint_handler(int sign);
void	main_sigterm_handler(void);

#endif