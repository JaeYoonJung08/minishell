/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaju <jaju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:41:39 by jaju              #+#    #+#             */
/*   Updated: 2023/08/02 11:41:44 by jaju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STR_H
# define STR_H

//문자열의 길이를 리턴
int		str_length(char const *str);
//str의 [start, end)만큼을 복사, str[end]는 포함하지 않음 
char	*str_substr(char const *str, int start, int end);
//str안에 c가 있으면 1, 없으면 0
int		str_includes(char const *str, char c);
//strtok과 같음
char	*str_tokenize(char *str, char const *delim);
//str에 있는 모든 replaced를 with로 치환한 문자열을 생성
char	*str_replace(char const *str, char const *replaced, char *with);
//a와 b가 같다면 1, 다르다면 0
int		str_equals(char const *a, char const *b);
//a와 b를 붙인 새로운 문자열을 생성
char	*str_join(char const *a, char const *b);
//str에서 c가 몇 번째 인덱스에 있는지 리턴, 없으면 -1
int		str_indexof(char const *str, char c);
//str을 복제하는 함수
char	*str_clone(char const *str);

#endif