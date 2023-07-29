/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaju <jaju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 18:13:46 by jaju              #+#    #+#             */
/*   Updated: 2023/07/28 18:53:35 by jaju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STR_H
# define STR_H

int		str_length(char const *str);
char	*str_substr(char const *str, int start, int end);
int		str_includes(char const *str, char c);
char	*str_tokenize(char *str, char const *delim);
char	*str_replace(char const *str, char const *replaced, char *with);
int		str_equals(char const *a, char const *b);
char	*str_join(char const *a, char const *b);
int		str_indexof(char *str, char c);

#endif