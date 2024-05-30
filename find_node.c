/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yessemna <yessemna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 01:29:48 by yessemna          #+#    #+#             */
/*   Updated: 2024/05/20 09:11:46 by yessemna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_strncmp(const char *s1, const char *s2, size_t n)
{
    unsigned char *str1;
    unsigned char *str2;

    str1 = (unsigned char *)s1;
    str2 = (unsigned char *)s2;
    if (n == 0)
        return (0);
    while (*str1 && *str2 && *str1 == *str2 && --n)
    {
        str1++;
        str2++;
    }
    return (*str1 - *str2);
}

void find_node(t_env *envi, t_token *list)
{
    int found = 0;
    t_token *tmp = list;
    t_env *tmp_env = envi;
    while (tmp)
    {
        found = 0;
        if (tmp->value == VAR)
        {
            while (tmp_env)
            {
                if (ft_strncmp(tmp->key, tmp_env->key, ft_strlen(tmp->key)) == 0)
                {
                    tmp->key = tmp_env->value;
                    tmp_env = envi;
                    found = 1;
                    break ;
                }
                tmp_env = tmp_env->next;
            }
            if (!found)
            {
                tmp->key = NULL;
                tmp_env = envi;
            }
        }
        tmp = tmp->next;
    }
}
