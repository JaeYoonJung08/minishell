/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaju <jaju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 23:11:35 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/08/08 13:51:31 by jaju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_H
# define SIGNAL_H

# include <stdlib.h>
# include <signal.h>
# include <str/str.h>
# include <unistd.h>

void	all_signal(void);
void	main_sigint_handler(int sign);
void	main_sigterm_handler(void);
void	sig_quit(int code);

#endif