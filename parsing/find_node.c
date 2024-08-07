/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yessemna <yessemna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 01:29:48 by yessemna          #+#    #+#             */
/*   Updated: 2024/08/07 16:24:18 by yessemna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *cpy_part(char *src, int start, int end)
{
    int lenght = (end - start);
    int i = -1;
    char *out = g_malloc(lenght + 2, MALLOC);
    if(!out)
        return (NULL); 
    while (++i <= lenght)
        out[i] = src[i];
    out[i] = '\0';
    return (out);
}

void find_node(t_env *envi, t_token *list)
{
    int found = 0;
    t_token *tmp = list;
    t_env *tmp_env = envi;

    if(tmp && tmp->value != HEREDOC)
    {
        while (tmp)
        {
            found = 0;
                if (tmp->value == VAR)
                {
                    while (tmp_env)
                    {
                        if (ft_strcmp(tmp->key + 1, tmp_env->key) == 0)
                        {
                            tmp->key = tmp_env->value;
                            if(count_word(tmp_env->value) == 1)
                                tmp->value = CMD;
                            else
                                tmp->value = EXPND;
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
            else if (tmp->value == DBL_Q)
            {
                tmp_env = envi;
                int x = 0;
                char *line = "";
                while (tmp->key[x])
                {
                    if (tmp->key[x] != '$' || (tmp->key[x] == '$' && tmp->key[x + 1] == '\'')
                        || (tmp->key[x] == '$' && tmp->key[x + 1] == '\0') || (tmp->key[x] == '$' && tmp->key[x + 1] == '$'))
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
                        var = cpy_part(tmp->key + start, start, end); // variable name
                        while (tmp_env)
                        {
                            if (ft_strcmp(var, tmp_env->key) == 0)
                            {
                                int i = 0;
                                while (tmp_env->value[i])
                                    line = join_char(line, tmp_env->value[i++]); // $a = "ls -la"
                                if(count_word(tmp_env->value) == 1)
                                    tmp->value = CMD;
                                else
                                    tmp->value = EXPND;
                                found = 1;
                                break;
                            }
                            tmp_env = tmp_env->next;
                        }
                        if (!found)
                        {
                            line = "";
                            tmp_env = envi;
                        }
                        tmp_env = envi;
                    }
                }
                tmp->key = line;
            }
            tmp = tmp->next;
        }
    }
}


int count(t_token *list)
{
    int i = 0;

    while (list)
    {
        if (list->value == CMD)
            i++;
        list = list->next;
    }
    return (i);
}



