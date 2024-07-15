/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yessemna <yessemna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 04:12:59 by yessemna          #+#    #+#             */
/*   Updated: 2024/07/15 03:47:44 by yessemna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_findchar(char *str, char c)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == c)
            return (1);
        i++;
    }
    return (0);
}

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
void ft_here_doc(t_token *cmd, t_env *envi, int *red_out)
{
    (void)envi;
    char *line;
    int fd_write;
    t_token *tmp = cmd;
    int pid;
    int status;
    
    fd_write = open("dog",O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_write != -1)
        *red_out = fd_write;
    pid = fork();
    if (pid == 0)
    {

    // int fd_read;
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
            if(!(tmp->value == SNGL_Q || tmp->value == DBL_Q))
            {
                if (line[0] == '$' || (line[0] == '\"' && line[1] == '$') || (line[0] == '\'' && line[1] == '$'))
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
        exit(0);
    }
    else
    {
        waitpid(pid, &status, 0);
        if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
        {
            write(1, "\n", 1);
            // set exit code to 1 before that handle signals
        }
            
    }
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