/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yessemna <yessemna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 01:29:48 by yessemna          #+#    #+#             */
/*   Updated: 2024/07/13 08:45:34 by yessemna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

    if(tmp->value != HEREDOC)
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
                            found = 1;
                            break;
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
                    if (tmp->key[x] != '$' || (tmp->key[x] == '$' && tmp->key[x + 1] == '\'') || (tmp->key[x] == '$' && tmp->key[x + 1] == '\0'))
                    {
                        line = join_char(line, tmp->key[x]);
                        x++;
                    }
                    else if (tmp->key[x] == '$' && tmp->key[x + 1] == '$')
                        x = x + 2;
                    else
                    {
                        x++;
                        int start = x;
                        while (tmp->key[x] && is_alnum(tmp->key[x]))
                            x++;
                        int end = x - 1;
                        char *var;
                        var = cpy_part(tmp->key + start, start, end);
                        while (tmp_env)
                        {
                            if (ft_strcmp(var, tmp_env->key) == 0)
                            {
                                int i = 0;
                                while (tmp_env->value[i])
                                    line = join_char(line, tmp_env->value[i++]);
                                found = 1;
                                break;
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
            tmp = tmp->next;
        }
    }
}
// ------> THIS code like SHIT <------
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
t_cmd   *lst_new_cmd(char **line, int in, int out)
{
    t_cmd *new;
    int i;

    i = 0;
    if (!line)
        return (NULL);
    new = g_malloc(sizeof(t_cmd), MALLOC);
    if (!new)
        return (NULL);
    
    new->cmds = line;
    new->redir_in = in;
    new->redir_out = out;
    new->next = NULL;
    return (new);
}
void    lst_add_back_cmd(t_cmd **head, t_cmd *new)
{
    t_cmd *tmp = *head;

    if(!head || !new)
        return ;
    
    if(!*head)
        *head = new;
    else
    {
        while(tmp->next)
            tmp = tmp->next;
        tmp->next = new;
    }
}

int prepare_cmd(t_token *list, t_cmd **cmd)
{
    t_token *tmp = list;
    char **cmd_strs;
    (void)cmd;
    int red_in;
    int red_out;

    while (tmp)
    {
        cmd_strs = NULL;
        red_in = 0;
        red_out = 1;
        if (tmp && tmp->value == SPACE)
                tmp = tmp->next;
        while (tmp && tmp->value != PIPE)
        {
            if (!tmp->next && tmp->value == SPACE)
            {
                tmp = tmp->next;
                continue ;
            }
            if (tmp && tmp->next && tmp->value == SPACE)
                tmp = tmp->next;
            if (tmp && tmp->value == PIPE)
                continue ;
            if (tmp && tmp->value == IN)
            {
                tmp = tmp->next;
                if (tmp && tmp->value == SPACE)
                    tmp = tmp->next;
                red_in = open(tmp->key, O_RDONLY);
                if (red_in < 0)
                    return(perror(tmp->key), 0);
                tmp = tmp->next;
                continue ;
            }else if(tmp && tmp->value == OUT)
            {
                if(red_out != 1)
                    close(red_out);
                tmp = tmp->next;
                if (tmp && tmp->value == SPACE)
                    tmp = tmp->next;
                red_out = open(tmp->key, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (red_out < 0)
                    return(perror(tmp->key), 0);
                tmp = tmp->next;
                continue ;
            }else if(tmp && tmp->value == APPEND)
            {
                tmp = tmp->next;
                if (tmp && tmp->value == SPACE)
                    tmp = tmp->next;
                red_out = open(tmp->key, O_WRONLY | O_CREAT | O_APPEND, 0644);
                if (red_out < 0)
                    return(perror(tmp->key), 0);
                tmp = tmp->next;
                continue ;
            }
            cmd_strs = dbl_join(cmd_strs, tmp->key);
            tmp = tmp->next;
        }
        if (cmd_strs)
            lst_add_back_cmd(cmd, lst_new_cmd(cmd_strs, red_in, red_out));
        if (tmp)
            tmp = tmp->next;
    }
    return (1);
}



/*
----- to do -----

"'$HOME'"               -> done

cmd -> file -> option   -> done

vars in dbl_q           -> done
*/


/*



*/