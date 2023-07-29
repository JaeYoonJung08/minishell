/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaju <jaju@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 17:20:21 by jaju              #+#    #+#             */
/*   Updated: 2023/07/25 19:03:40 by jaju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	process_create(void (*func)(void *), int fd_in, int fd_out)
{
	int const	pid = fork();

	if (pid == -1)
		exit(1); // ERROR
	if (pid > 0)
		return (pid);
	func(0);
	exit(0);
}
