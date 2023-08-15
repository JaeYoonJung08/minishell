/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaju <jaju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 21:19:46 by jaju              #+#    #+#             */
/*   Updated: 2023/08/07 21:43:52 by jaju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser/compiler.h>
#include <str/str.h>
#include <libft/libft.h>
#include <shell/minishell.h>
#include <parser/parser.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

static int	ft_compare(t_env *a, t_env *b)
{
	int	i;

	i = 0;
	while ((a->name[i] != '\0' && b->name[i] != '\0')
		&& a->name[i] == b->name[i])
	{
		i++;
	}
	return (a->name[i] - b->name[i]);
}

static void	change_ft(int argc, t_env **argv)
{
	int		i;
	int		j;
	t_env	*tab;

	i = 0;
	while (i < argc)
	{
		j = i + 1;
		while (j < argc)
		{
			if (ft_compare(argv[i], argv[j]) > 0)
			{
				tab = argv[i];
				argv[i] = argv[j];
				argv[j] = tab;
			}
			j++;
		}
		i++;
	}
}

t_env	**to_array(t_list *env_list)
{
	t_env**const	array = allocate((env_list->length + 1) * sizeof(t_env *));
	int				i;

	i = 0;
	while (i < env_list->length)
	{
		array[i] = list_get(env_list, i);
		i++;
	}
	change_ft(env_list->length, array);
	return (array);
}
