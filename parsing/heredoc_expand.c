/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yessemna <yessemna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 05:45:42 by yessemna          #+#    #+#             */
/*   Updated: 2024/07/13 10:51:29 by yessemna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char  *heredoc_expand(char *line, t_env *envi)
{
    t_env *tmp_env = envi;
    char *ret = NULL;
    int found = 0;
    char *var = NULL;
    // int len = 0;
    
    if(*line == '\'' || *line == '\"')
    {
        while(*line && (*line == '\'' || *line == '\"'))
            line++;
        while (*line)
        {
            if(*line == '\'' || *line == '\"')
                break;
            if(*line == '$')
                line++;
            var = join_char(var, *line);
            ++line;
        }
        // printf("line = %s\n", var);
        // line = ft_substr(line, 0, len);
    }if(*line == '$')
    {
        line++;
        var = ft_strdup(line);
    }
    while(tmp_env)
    {
        if(ft_strcmp(var, tmp_env->key) == 0)
        {
            ret = ft_strdup_env(tmp_env->value);
            found = 1;
            break;
        }
        tmp_env = tmp_env->next;
    }
    if (!found)
    {
        ret = "";
        tmp_env = envi;
    }
    return (ret);
}