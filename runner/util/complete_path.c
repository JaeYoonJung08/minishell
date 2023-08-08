/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complete_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaju <jaju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 20:06:52 by jaeyojun          #+#    #+#             */
/*   Updated: 2023/08/07 20:23:44 by jaju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../runner.h"
#include <libft/libft.h>

//환경변수 + / + 명령어를 한 것 리턴
static char	*path_join(char const *env, char const *cmd)
{
	char*const	new = allocate(str_length(env) + str_length(cmd) + 2);
	char		*ptr;

	ptr = new;
	while (*env != '\0')
		*(ptr++) = *(env++);
	*(ptr++) = '/';
	while (*cmd != '\0')
		*(ptr++) = *(cmd++);
	return (new);
}

//환경변수 실행 권한 확인
char	*complete_path(char const *env_path, char *cmd)
{
	char		*paths;
	char		*path;
	char		*combine;
	int			cmd_exists;

	paths = str_clone(env_path);
	cmd_exists = access(cmd, X_OK);
	if (cmd_exists != -1)
		return (free(paths), cmd);
	path = str_tokenize(paths, ":");
	while (path != (void *)0)
	{
		combine = path_join(path, cmd);
		cmd_exists = access(combine, X_OK);
		if (cmd_exists != -1)
			return (free(paths), combine);
		free(combine);
		path = str_tokenize((void *)0, ":");
	}
	return (free(paths), (void *)0);
}
