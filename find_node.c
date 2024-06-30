/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yessemna <yessemna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 01:29:48 by yessemna          #+#    #+#             */
/*   Updated: 2024/06/30 22:11:50 by yessemna         ###   ########.fr       */
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
        // printf("- %c\n", src[i]);
    out[i] = '\0';
    // printf("size --> %d\n", lenght);
    printf("$$$$ --> %s\n", src);
    printf("$$$$ --> %s\n", out);
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
            char **line = ft_split(tmp->key, ' ');  // echo "hello $USR you are at $HOME" -> ["echo", "hello", "$USR", "you", "are", "at", "$HOME"]
            // char **ret = malloc(count_word(tmp->value));
            int i = 0;
            while (line[i])
            {
                while (tmp_env)
                {
                    if (ft_strcmp(line[i], tmp_env->key) == 0)//PATH PA
                    {
                        line[i] = ft_strcpy(line[i], tmp_env->value);// line[i] = tmp_env->value;
                        printf(" ###--> %s\n", line[i]);
                        printf(" ->>>>> %s\n", tmp_env->value);
                        tmp_env = envi;
                        found = 1;
                        break ;
                    }
                    tmp_env = tmp_env->next;
                }
                i++;
                tmp_env = envi;
            }
            char *ret = "";
            i = 0;
            printf(">>>>>\n");
            int j  =6;
            while (j--)
            {
                ret = ft_srtjoin(ret, line[i]);
                if (j)
                    ret = ft_srtjoin(ret, " ");
                i++;
            }
            tmp->key = ret;
        }
    
    
    tmp = tmp->next;
    }
}

/*

"'$HOME'"

cmd -> file -> option

vars in dbl_q

*/



/*


int i = 0;
            char *var;
            char *line = NULL;
            
            while (tmp->key[i])
            {
                if (tmp->key[i] == '\'' && tmp->key[i + 1] == '$')
                {
                    start = i += 2;
                    while (tmp->key[i])
                    {
                        if (is_special(tmp->key[i]))
                            break;
                        i++;
                    }
                    end = i - 1;
                    var = cpy_part(tmp->key + start ,start , end);
                    while (tmp_env)
                    {
                        if (ft_strcmp(var, tmp_env->key) == 0)//PATH PA
                        {
                            line = malloc(sizeof(char *) * ft_strlen(tmp_env->value));
                            line = ft_srtjoin(line, tmp_env->value);
                            found = 1;
                            break ;
                        }
                        tmp_env = tmp_env->next;
                    }
                    ft_strcpy(tmp->key , line);
                    i = i + ft_strlen(line);
                    printf("var ---> %s", line);
                }
                else
                    i++;


*/