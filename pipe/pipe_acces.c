/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_acces.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 16:10:12 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/07/29 17:37:13 by jaeyojun         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"
#include "../parser/tokenizer.h"
#include "../shell/minishell.h"
#include "../str/str.h"


// int	count_str(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 		i++;
// 	return (i);
// }

// int	separator_slash(char tmp)
// {
// 	if (tmp == '/')
// 		return (0);
// 	return (1);
// }

// int	separator_colon(char tmp)
// {
// 	if (tmp == ':')
// 		return (0);
// 	return (1);
// }

// char	*word_split(char *envp_path)
// {
// 	int		i;
// 	int		count;
// 	char	*tmp;

// 	i = 0;
// 	count = count_str(envp_path);
// 	tmp = (char *)malloc(sizeof(char) * (count + 1));
// 	if (!tmp)
// 		return (0);
// 	while (envp_path[i] && separator_colon(envp_path[i]))
// 	{
// 		tmp[i] = envp_path[i];
// 		i++;
// 	}
// 	tmp[i] = '\0';
// 	return (tmp);
// }

// int	ma_count(char *envp_path)
// {
// 	int	i;
// 	int	count;

// 	i = 0;
// 	count = 0;
// 	while (envp_path[i])
// 	{
// 		while (envp_path[i] && separator_slash(envp_path[i]) == 1)
// 			i++;
// 		if (envp_path[i])
// 			count++;
// 		while (envp_path[i] && separator_colon(envp_path[i]) == 1)
// 			i++;
// 	}
// 	return (count);
// }


// char const	**envp_split(char const *envp_path)
// {
// 	char const	**envp;
// 	int			malloc_count;
// 	int			size;

// 	malloc_count = 0;
// 	size = ma_count(envp_path);
// 	envp = (char **)malloc(sizeof(char *) * (size + 1));
// 	if (!envp)
// 		return (0);
// 	while (*envp_path)
// 	{
// 		while (*envp_path && separator_slash(*envp_path) == 1)
// 			envp_path++;
// 		if (*envp_path)
// 		{
// 			envp[malloc_count++] = word_split(envp_path);
// 			if (envp[malloc_count - 1] == 0)
// 				return (ft_free(envp));
// 			envp_path++;
// 		}
// 		while (*envp_path && separator_colon(*envp_path) == 1)
// 			envp_path++;
// 	}
// 	envp[malloc_count] = 0;
// 	return (envp);
// }

char	const *check_acces(char *envp, char *cmd)
{
	char	*tmp;
	char	const *envp_plus;

	tmp = str_join("/", cmd);
	//printf("tmp : %s\n", tmp);
	envp_plus = str_join(envp, tmp);
	//printf("envp_plus : %s\n", envp_plus);
	free(tmp);
	return (envp_plus);

}

char const	*envp_split(char const *envp_path, char *cmd)
{
	char	*envp = str_clone(envp_path);
	char	*envp_split;
	char	const	*combine;
	int		fd;

	int i = 0;
	while (1)
	{
		if (i == 0)
		{
			envp_split = str_tokenize(envp, ":");
			i++;
		}
		else
			envp_split = str_tokenize((void *)0, ":");
		if (!envp_split)
			break ;
		combine = check_acces(envp_split, cmd);
		//printf("combine : %s\n" , combine );
		fd = access(combine, X_OK);
		if (fd != -1)
		{
			//free(envp_split);
			return (combine);
		}
		close(fd);
		//free(combine);
	}
	
	return (NULL);
}

	// printf("-----------------------\n");
	// printf("envp_path : %s\n", envp_path);
	// char	*envp = str_clone(envp_path);
	// printf("env p 12: %s\n", envp);
	// printf("-----------------------\n");

	// char	*envp_split = str_tokenize(envp, ":");
	// printf("env p : %s\n", envp);
	// printf("envp _  split : %s\n", envp_split);
	// //free(envp_split);
	
	// printf("-----------------------\n");
	// printf("env p : %s\n", envp);
	// envp_split = str_tokenize((void *)0, ":");
	// printf("envp _  split : %s\n", envp_split);
	
	// 	printf("-----------------------\n");
	// printf("env p : %s\n", envp);
	// envp_split = str_tokenize((void *)0, ":");
	// printf("envp _  split : %s\n", envp_split);

void	pipe_acces(t_list *tokens)
{
	//t_list *number = tokens;

	t_token *t = list_get(tokens, 0);
	//char	*result_join;
	printf("%s\n", t->content);
	
	//split
	t_list	*envp;
	//t_envp *a;
	envp = &g_minishell.env_list;
	//t_envp *a= list_get(envp, 0);
	//printf("%s", a->name);
	
	char const *path_envp = get_env("PATH");
	// if (path_envp == "")
	// 	return ;
	char const *path_split = envp_split(path_envp, t->content);
	printf("path_envp : %s\n", path_envp);
	printf("path_split : %s\n", path_split);
	// int i = 0;
	// while (envp->data[i])
	// {
	// 	a = list_get(envp, i);
	// 	//printf("%s\n", a->name);
	// 	i++;
	// }
	

}



void	pipe_start(t_list *tokens)
{
	pipe_acces(tokens);
}