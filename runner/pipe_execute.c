/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_execute.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 21:59:04 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/08/08 16:54:34 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "runner.h"
#include <signal/signal.h>
#include <shell/minishell.h>


void	sig_quit(int code);

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (s == NULL)
		return ;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
}

void	ft_putendl_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (s == NULL)
		return ;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
	write(fd, "\n", 1);
}


void	*ft_memdel(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
	return (NULL);
}


int	ft_nbrlen(long n)
{
	int		size;

	size = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		size++;
	while (n != 0)
	{
		n = n / 10;
		size++;
	}
	return (size);
}


int	ft_power(int nbr, int pow)
{
	int	res;

	if (pow == 0)
		return (1);
	res = nbr;
	while (pow > 1)
	{
		res *= nbr;
		pow--;
	}
	return (res);
}


char	*ft_itoa(int n)
{
	long	nbr;
	char	*s;
	int		div;
	int		i;

	i = 0;
	nbr = n;
	s = malloc(sizeof(char) * (ft_nbrlen(nbr) + 1));
	if (!s)
		return (NULL);
	if (nbr < 0)
	{
		s[i++] = '-';
		nbr = -nbr;
	}
	div = ft_power(10, ft_nbrlen(nbr) - 1);
	while (div > 0)
	{
		s[i++] = nbr / div + '0';
		nbr = nbr % div;
		div = div / 10;
	}
	s[i] = '\0';
	return (s);
}


void	sig_quit(int code)
{
	char	*nbr;

	nbr = ft_itoa(code);
	//if (g_sig.pid != 0)
	//{
		ft_putstr_fd("Quit: ", 2);
		ft_putendl_fd(nbr, 2);
		//g_sig.exit_status = 131;
		//g_sig.sigquit = 1;
	//}
	//else
		ft_putstr_fd("\b\b  \b\b", 2);
	ft_memdel(nbr);
}

void	process_run(t_list *tokens)
{
	t_list		process_list;
	t_process	*tmp;
	int			pid;
	int			builtin_idx;

	process_list = compile(tokens);
	tmp = list_get(&process_list, 0);
	signal(SIGINT, SIG_IGN);
	//
	signal(SIGQUIT, &sig_quit);
	//
	if (process_list.length == 1 && check_builtin(tmp->name, &builtin_idx))
		execute_no_fork(tmp, builtin_idx);
	else
	{
		pid = execute_fork(&process_list);
		wait_process(pid);
	}
	signal(SIGINT, main_sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	list_free_all(&process_list, process_free);
}
