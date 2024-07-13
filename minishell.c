/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 17:59:59 by yessemna          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/07/13 10:58:52 by yessemna         ###   ########.fr       */
=======
/*   Updated: 2024/07/13 20:17:21 by hchadili         ###   ########.fr       */
>>>>>>> b9c3b618bd4c986bbf0f8704eb270262af73f9cf
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// print list as a table

void print_list(t_token *list)
{
    t_token *tmp = list;
    while (tmp)
    {
        printf(" (%s)  ->  ", tmp->key);
        if (tmp->value == PIPE)
            printf("PIPE\n");
        else if (tmp->value == SPACE)
            printf("SPACE\n");
        else if (tmp->value == IN)
            printf("IN\n");
        else if (tmp->value == HEREDOC)
            printf("HEREDOC\n");
        else if (tmp->value == OUT)
            printf("OUT\n");
        else if (tmp->value == APPEND)
            printf("APPEND\n");
        else if (tmp->value == SNGL_Q)
            printf("Sgl_q\n");
        else if (tmp->value == DBL_Q)
            printf("Dbl_q\n");
        else if (tmp->value == VAR)
            printf("VAR\n");
        else if (tmp->value == CMD)
            printf("CMD\n");
        else if (tmp->value == DBL_VAR)
            printf("DBL_VAR\n");
        tmp = tmp->next;
    }
}

int processline(char *line, t_token **list)
{
    int i;
    int start;
    int end;

    start = 0;
    end = 0;
    i = 0;
    if (line == NULL)
        return (0);
    while (line[i] != '\0')
    {
        if (line[i] == '|')
            lst_add_back(list, lst_new(ft_substr(line, i++, 1), PIPE));
        else if (is_space(line[i]))
        {
            while (is_space(line[i + 1]))
                i++;
            lst_add_back(list, lst_new(ft_substr(line, i++, 1), SPACE));
        }
        else if (line[i] == '<')
        {
            if (line[i + 1] == '<')
                lst_add_back(list, lst_new(ft_substr(line, i++, 2), HEREDOC));
            else
                lst_add_back(list, lst_new(ft_substr(line, i, 1), IN));
            i++;
        }
        else if (line[i] == '>')
        {
            if (line[i + 1] == '>')
                lst_add_back(list, lst_new(ft_substr(line, i++, 2), APPEND));
            else
                lst_add_back(list, lst_new(ft_substr(line, i, 1), OUT));
            i++;
        }
        else if (line[i] == '\'' || (line[i] == '$' && line[i + 1] == '\''))
        {
            if (line[i] == '$')
                i++;
            if (line[i + 1] == '\'')
            {
                lst_add_back(list, lst_new("", SNGL_Q));
                i++;
            }
            else
            {
                end = find_char(line + i + 1, '\'');
                if (end)
                    lst_add_back(list, lst_new(ft_substr(line, i + 1, end), SNGL_Q));
                else
                    return(print_error("Error: missing single quote\n"), 0);
                i += end + 1;
            }
            i++;
        }
        else if (line[i] == '\"' || (line[i] == '$' && line[i + 1] == '\"'))
        {
            if (line[i] == '$')
                i++;
            if (line[i + 1] == '\"')
            {
                lst_add_back(list, lst_new("", DBL_Q));
                i += 1;
            }
            else
            {
                end = find_char(line + i + 1, '\"');
                if (end)
                    lst_add_back(list, lst_new(ft_substr(line, i + 1, end), DBL_Q));
                else
                    return(print_error("Error: missing double quote\n"), 0);
                i += end + 1;
            }
            i++;
        }
        else if (line[i] == '$' && (line[i + 1] >= '0' && line[i + 1] <= '9'))
        {
            lst_add_back(list, lst_new(ft_substr(line, i++, 2), VAR));
            i++;
        }
        else if (line[i] == '$' && line[i + 1] == '$')
        {
            lst_add_back(list, lst_new(ft_substr(line, i++, 2), DBL_VAR));
            i++;
        }
        else if (line[i] == '$')
        {
            if (!is_alnum(line[i + 1]))
                lst_add_back(list, lst_new(ft_substr(line, i++, 1), CMD));
            else
            {
                start = i;
                i++;
                while (is_alnum(line[i]) && !is_special(line[i]))
                {
                    if (!is_alnum(line[i + 1]))
                        break;
                    i++;
                }
                end = i - start;
                lst_add_back(list, lst_new(ft_substr(line, start, end + 1), VAR));
                i++;
            }
        }
        else
        {
            start = i;
            while (line[i] && !is_special(line[i]))
            {
                if (is_special(line[i + 1]))
                    break;
                i++;
            }
            end = i - start;
            lst_add_back(list, lst_new(ft_substr(line, start, end + 1), CMD));
            i++;
        }
    }
    return (1);
}
// Main function
#include "libc.h"

void initenv(char **env, t_env **envi)
{
    (void)env;
    (void)envi;

    int i;
    char *key;
    char *value;
    
    int index = 0;
    i = 0;
    
    while (env[i])
    {
        index = find_char(env[i], '=');
        key = ft_substr_env(env[i], 0, index);
        value = ft_substr_env(env[i], index + 1, ft_strlen(env[i]) - index);
        lst_add_back_env(envi, lst_new_env(key, value));
        i++;
    }
}

int print_env(t_env *envi, t_token *list)
{
    char str[] = "env";
    t_env *tmp = envi;
    t_token *tmp2 = list;
    int flag = 0;
    int size = 0;

    size = ft_lstsize(tmp);
    if (tmp2 && !ft_strcmp(tmp2->key, str))
    {
        while (tmp && size - 1)
        {
            write(1, tmp->key, ft_strlen(tmp->key));
            write(1, "=", 1);
            write(1, tmp->value, ft_strlen(tmp->value));
            write(1, "\n", 1);
            tmp = tmp->next;
            size--;
        }
        flag = 1;
    }
    return (flag);
}


void print_cmd(t_cmd **cmd)
{
    t_cmd *tmp = *cmd;
    int i = 0;
    printf("\n-----------\n");
    while (tmp)
    {
        i = 0;
        while (tmp->cmds && tmp->cmds[i])
        {
            printf("cmd[%d] : %s\n", i, tmp->cmds[i]);
            i++;
        }
        printf("redir_in: %d\n", tmp->redir_in);
        printf("redir_out: %d\n", tmp->redir_out);
        tmp = tmp->next;
    }
    printf("\n-----------\n");
}
void join_nodes(t_token **list)
{
    t_token *tmp = *list;
    t_token *tmp2;
    while (tmp)
    {
        if (tmp->next && (tmp->value == DBL_Q || tmp->value == SNGL_Q || tmp->value == VAR
            || tmp->value == DBL_VAR || tmp->value == CMD) && (tmp->next->value == DBL_Q
            || tmp->next->value == SNGL_Q || tmp->next->value == VAR || tmp->next->value == DBL_VAR
            || tmp->next->value == CMD))
        {
            tmp2 = tmp->next->next;
            tmp->key = ft_srtjoin(tmp->key, tmp->next->key);
            if (tmp->next->value == DBL_Q || tmp->next->value == SNGL_Q)
                tmp->value = tmp->next->value;
            tmp->next = tmp2;
        }
        else
            tmp = tmp->next;
    }
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
        if (!line || !ft_strcmp(line, tmp->key))
        {
            // free(line);
            break ;
        }
        
        // check if delimeter contain sgl or dbl quotes
        // if (find_char(dlm, '\'') || find_char(dlm, '\"'))
        //
        if(!(tmp->value == SNGL_Q || tmp->value == DBL_Q) && find_char(line, '$'))
        {
            line = heredoc_expand(line, envi);
        }
        putin_fd(fd_write, line);
    }
    close(fd_write);
    free(line);
}
int heredoc(t_token *list, t_env *envi)
{
    t_token *tmp = list;

    if (tmp && tmp-> value == HEREDOC)
    {
        tmp = tmp->next;
        if (tmp && tmp->value == SPACE)
            tmp = tmp->next;
        ft_here_doc(tmp, envi);
        return (0);
    }
    return (1);
}

int main(int ac, char **av, char **env) //$home.c
{
    t_env *envi;
    char *line;
    t_token *list;
    t_cmd *cmd;
    (void)av;
    envi = NULL;

    if (ac > 1)
        print_error("no argument needed");
    while (1)
    {
        list = NULL;
        cmd = NULL;
        (void)env;
        
         initenv(env, &envi);       // <---  problem in env ( should not split with '=' )
        line = readline("Minishell 🔴🔵 ");
        // char  *save_line = line;
        if (line && ft_strlen(line) != 0)
            add_history(line);
        if(!processline(line, &list))//<--- to handle the line prepare the list
        {
            free((void*)line);
            continue;
        }    
        if (!catch_errors(&list))    // <--- to catch errors
        {
            free((void*)line);
            continue;
        } 
        // if(print_env(envi, list))    // <--- to print the env
        // {
        //     free((void*)line);
        //     continue;
        // }
        find_node(envi, list);   // <--- to expand the variables
        join_nodes(&list);      // <--------------- join
        if(!heredoc(list, envi))             // <--- to handle the heredoc
            continue ;
        if (!prepare_cmd(list, &cmd))// <--- to prepare the command
        {
            free((void*)line);
            continue;
        } 

        // printf("\n-----------\n");
        // print_list(list);      // print cmd list

        // print_cmd(&cmd);
		ft_execution(&cmd, &envi);
        free((void*)line);
        g_malloc(0, FREE);
        
    }
        // g_malloc_env(0, FREE);
}

/*

--> "$HOME"                               ->DONE
--> print env                             ->DONE 
--> env: r: No such file or directory
sw


??
--> export
--> unset

-----> garbage collector   <-----        -->DONE
-->

*/
