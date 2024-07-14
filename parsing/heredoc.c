/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yessemna <yessemna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 04:12:59 by yessemna          #+#    #+#             */
/*   Updated: 2024/07/14 04:44:10 by yessemna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void putin_fd(int fd, char *line)
{
    int i;

    i = 0;
    while (line && line[i])
    {
        write(fd,&line[i],1);
        i++;
    }
    write(fd, "\n", 1);
}
void ft_here_doc(t_token *cmd, t_env *envi)
{
    char *line;
    int fd_write;
    t_token *tmp = cmd;
    // int fd_read;
    fd_write = open("dog",O_WRONLY | O_CREAT | O_TRUNC, 0644);
    while (1)
    {
        line = readline("> ");
        if (!line)
            break ;
        if(!ft_strcmp(line, tmp->key))
        {
            // free(line);
            break ;
        }
        
        // check if delimeter contain sgl or dbl quotes
        // if (find_char(dlm, '\'') || find_char(dlm, '\"'))
        //
        if(!(tmp->value == SNGL_Q || tmp->value == DBL_Q ||tmp->value == CMD))
        {
            line = heredoc_expand(line, envi);
            // putin_fd(fd_write, line);
        }
        // printf("line = %s\n", line);
        // }else
            putin_fd(fd_write, line);
            // line = heredoc_expand(line, envi);
    }
    close(fd_write);
    free(line);
}
// int heredoc(t_token *list, t_env *envi)
// {
//     t_token *tmp = list;

//     if (tmp && tmp-> value == HEREDOC)
//     {
//         tmp = tmp->next;
//         if (tmp && tmp->value == SPACE)
//             tmp = tmp->next;
//         ft_here_doc(tmp, envi);
//         return (0);
//     }
//     return (1);
// }