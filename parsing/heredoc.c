/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yessemna <yessemna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 04:12:59 by yessemna          #+#    #+#             */
/*   Updated: 2024/07/19 13:35:23 by yessemna         ###   ########.fr       */
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

char *heredoc_expand(char *line, t_env *envi)
{
    (void)envi;
    (void)line;
    int i = 0;
    // int x = 0;
    t_env *tmp_env = envi;
    int found = 0;
    char *ret = NULL;
    char *exp = NULL;
    
    while(line[i])
    {

        while(line[i] == '\'' || line[i] == '\"')
        {
            ret = join_char(ret, line[i]);
            i++;
        }
        if(line[i] == '$')
        {
            // printf("*********");
            i++;
            // printf/("line[i] = %c\n", line[i]);
            while(line[i] && is_alnum(line[i]))
            {
                exp = join_char(exp, line[i]);
                i++;
            }
            while(tmp_env)
            {
                if(ft_strcmp(exp, tmp_env->key) == 0)
                {
                    ret = ft_srtjoin(ret, ft_strdup(tmp_env->value));
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
        }
        else
        {
            ret = join_char(ret, line[i]);
            i++;
        }
    }
    return (ret);
}


void ft_here_doc(t_token *cmd, t_env *envi, int *red_in)
{
    (void)envi;
    char *line;
    int fd_write;
    t_token *tmp = cmd;
    int pid;
    int status;

    fd_write = open("/tmp/dog",O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_write != -1)
        *red_in = fd_write;
    pid = fork();
    if (pid == 0)
    {
        // int fd_read;
        while (1)
        {
            line = readline("> ");
            if (!line)
                break ;
            if (line && ft_strlen(line) != 0)
                add_history(line);
            // check if delimeter contain sgl or dbl quotes
            if(!ft_strcmp(line, tmp->key))
                break ;
            if(!(tmp->value == DBL_Q || tmp->value == SNGL_Q))
                line = heredoc_expand(line, envi);
            putin_fd(fd_write, line);
        }
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
