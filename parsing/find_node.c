/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yessemna <yessemna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 01:29:48 by yessemna          #+#    #+#             */
/*   Updated: 2024/08/10 00:10:36 by yessemna         ###   ########.fr       */
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

void core_var(t_env *envi, t_token **tmp, int found)
{
    t_env *tmp_env = envi;
    
    while (tmp_env)
        {
            if (ft_strcmp((*tmp)->key + 1, tmp_env->key) == 0)
            {
                (*tmp)->key = tmp_env->value;
                if(count_word(tmp_env->value) == 1)
                    (*tmp)->value = CMD;
                else
                    (*tmp)->value = EXPND;
                found = 1;
                break ;
            }
            tmp_env = tmp_env->next;
        }
        if (!found)
        {
            (*tmp)->key = NULL;
            tmp_env = envi;
        }
}

void core_dbl_q(t_token **tmp, char **line, int *x, t_env **envi)
{
    char    *var;
    int     arr[3];
    int     found = 0;
    t_env   *tmp_env = *envi;

    ((1) && (arr[0] = 0, arr[1] = *x, arr[2] = 0));
    (*x)++;
    arr[1] = (*x);
    while ((*tmp)->key[*x] && is_alnum((*tmp)->key[*x]))
        (*x)++;
    arr[2] = (*x) - 1;
    var = cpy_part((*tmp)->key + arr[1], arr[1], arr[2]);
    while (tmp_env)
    {
        if (ft_strcmp(var, tmp_env->key) == 0)
        {
            arr[0] = 0;
            while (tmp_env->value[arr[0]])
                (*line) = join_char((*line), tmp_env->value[arr[0]+=1]);
            if(count_word(tmp_env->value) == 1)
                (*tmp)->value = CMD;
            else
                (*tmp)->value = EXPND;
            found = 1;
            break;
        }
        tmp_env = tmp_env->next;
    }
    if (!found)
    {
        (*line) = "";
        tmp_env = *envi;
    }
    tmp_env = *envi;
}

void handle_expand(t_env *envi, t_token **tmp, int found)
{
    t_env *tmp_env = envi;
    int x;
    char *line;
    
    x = 0;
    line = "";
    if ((*tmp)->value == VAR)
        core_var(envi, tmp, found);
    else if ((*tmp)->value == DBL_Q)
    {
        tmp_env = envi;
        while ((*tmp)->key[x])
        {
            if ((*tmp)->key[x] != '$' || ((*tmp)->key[x] == '$' && (*tmp)->key[x + 1] == '\'')
                || ((*tmp)->key[x] == '$' && (*tmp)->key[x + 1] == '\0') || ((*tmp)->key[x] == '$' && (*tmp)->key[x + 1] == '$'))
            {
                line = join_char(line, (*tmp)->key[x]);
                x++;
            }
            else
                core_dbl_q(tmp, &line, &x, &tmp_env);
        }
        (*tmp)->key = line;
    }
}

void find_node(t_env *envi, t_token *list)
{
    int found = 0;
    t_token *tmp = list;

    if(tmp && tmp->value != HEREDOC)
    {
        while (tmp)
        {
            found = 0;
            if(tmp->value == VAR || tmp->value == DBL_Q)
                handle_expand(envi, &tmp, found);
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



