/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yessemna <yessemna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 01:29:48 by yessemna          #+#    #+#             */
/*   Updated: 2024/07/02 23:17:24 by yessemna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
char *cpy_part(char *src , int start , int end)
{
    int lenght = (end - start);
    int i = -1;
    char *out = malloc(lenght + 2);
    while (++i <= lenght)
        out[i] = src[i];
    out[i] = '\0';
    return(out);
}

int ft_strcmp(const char *s1, const char *s2)
{
    unsigned char *str1;
    unsigned char *str2;

    str1 = (unsigned char *)s1;
    str2 = (unsigned char *)s2;
    if(*str1 == '$')
        str1++;
    while (*str1 && *str2 && *str1 == *str2)
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
    // int start = 0;
    // int end = 0;
    while (tmp)
    {
        found = 0;
        if (tmp->value == VAR)
        {
            while (tmp_env)
            {
                if (ft_strcmp(tmp->key, tmp_env->key) == 0)//PATH PA
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
        else if(tmp->value == DBL_Q)
        {
            tmp_env = envi;
            int x = 0;
            char *line = "";
            while (tmp->key[x])
            {
                if(tmp->key[x] != '$')
                {
                    line = join_char(line, tmp->key[x]);
                    x++;
                }
                else
                {
                    x++;
                    int start = x;
                    while (tmp->key[x] && is_alnum(tmp->key[x]))
                        x++;
                    int end = x - 1;
                    char *var;
                    var = cpy_part(tmp->key + start ,start , end);
                    //printf("----> %s\n", var);
                    while (tmp_env)
                    {
                        if (ft_strcmp(var, tmp_env->key) == 0)//PATH PA
                        {
                            int i = 0;
                            while (tmp_env->value[i])
                                line = join_char(line, tmp_env->value[i++]);
                            found = 1;
                            break ;
                        }
                        tmp_env = tmp_env->next;
                    }
                    if (!found)
                    {
                        line = NULL;
                        tmp_env = envi;
                    }
                    tmp_env = envi;
                }
            }
            tmp->key = line;
        }
    tmp = tmp->next; // echo $HOME+$HOME       -----<  nani
    }
}

/*

"'$HOME'"

cmd -> file -> option

vars in dbl_q

*/
