
#include "minishell.h"
#include "str/str.h"
#include <stdlib.h>
#include <stdio.h>
#include "libft/libft.h"

void	env_free(void *this);

//미니쉘(전역변수) 초기화
void	minishell_init(char **envp)
{
	t_env	*pair;
	t_list	env;
	int		i;
	int		index;

	list_init(&env);
	i = 0;
	while (envp[i] != (void *)0)
	{
		pair = allocate(sizeof(t_env));
		index = str_indexof(envp[i], '=');
		pair->name = str_substr(envp[i], 0, index);
		pair->value = str_substr(envp[i], index + 1, str_length(envp[i]));
		list_add(&env, pair);
		i++;
	}
	g_minishell.env_list = env;
}

void	minishell_free(void)
{
	list_free_all(&g_minishell.env_list, env_free);
}
