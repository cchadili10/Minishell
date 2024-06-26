/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yessemna <yessemna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 18:47:34 by yessemna          #+#    #+#             */
/*   Updated: 2024/07/01 18:44:26 by yessemna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int is_space(char c)
{
    return (c == ' ' || (c >= 9 && c <= 13));
}

int is_special(char c)
{
    return (c == '|' || c == '<' || c == '>' || c == '\'' || c == '\"' || c == '$' || is_space(c));
}
int find_char(char *str, char c)
{
    int i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == c)
            return (i);
        i++;
    }
    return (0);
}
int is_alnum(char c)
{
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_');
}

char *join_char(char *str, char c)
{
    char *out;
    int i = 0;
    int len = ft_strlen(str);
    out = malloc(len + 2);
    while (str[i] != '\0')
    {
        out[i] = str[i];
        i++;
    }
    out[i] = c;
    out[i + 1] = '\0';
    return (out);
}