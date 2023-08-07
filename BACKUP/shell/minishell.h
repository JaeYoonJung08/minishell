/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaju <jaju@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 17:40:16 by jaju              #+#    #+#             */
/*   Updated: 2023/08/06 23:44:05 by jaju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define ERROR_EXIT	1
# define SUCCES_EXIT 0

# include <collection/list.h>

//환경변수의 이름과 내용을 저장하는 구조체
typedef struct s_env
{
	char	*name;
	char	*value;
}t_env;

//미니쉘이 실행되는 동안 지니고 있어야 할 정보를 담는 구조체
typedef struct s_minishell
{
	t_list	env_list;
	int		exit_code;
}t_minishell;

//프로그램 종료까지 전역적으로 사용할 미니쉘 전역변수
t_minishell	g_minishell;

//미니쉘(전역변수) 초기화
void		minishell_init(char **envp);
//문자열에 대응하는 환경변수의 값을 리턴
char const	*get_env(char const *str);
//문자열에 대응하는 환경변수의 값을 설정
void		set_env(char const *name, char const *value);
//환경변수 삭제 (실패하면 아무 일도 일어나지 않음)
void		remove_env(char const *name);
//env_list를 char **로 만들어 리턴
char		**get_envp(void);

#endif