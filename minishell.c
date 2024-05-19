/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yessemna <yessemna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 17:59:59 by yessemna          #+#    #+#             */
/*   Updated: 2024/05/19 17:56:33 by yessemna         ###   ########.fr       */
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
        if(tmp->value == PIPE)
            printf("PIPE\n");
        else if(tmp->value == SPACE)
            printf("SPACE\n");
        else if(tmp->value == IN)
            printf("IN\n");
        else if(tmp->value == HEREDOC)
            printf("HEREDOC\n");
        else if(tmp->value == OUT)
            printf("OUT\n");
        else if(tmp->value == APPEND)
            printf("APPEND\n");
        else if(tmp->value == SNGL_Q)
            printf("Sgl_q\n");
        else if(tmp->value == DBL_Q)
            printf("Dbl_q\n");
        else if(tmp->value == VAR)
            printf("VAR\n");
        else if(tmp->value == CMD)
            printf("CMD\n");
        else if(tmp->value == DBL_VAR)
            printf("DBL_VAR\n");
        tmp = tmp->next;
    }
}

int is_space(char c)
{
    return (c == ' ' || (c > 9 && c < 13));
}

int is_special(char c)
{
    return (c == '|' || c == '<' || c == '>' || c == '\'' || c == '\"' || c == '$' || is_space(c));
}
int find_char(char *str, char c)
{
    int i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == c)
            return (i);
        i++;
    }
    return (0);
}
int is_alnum(char c)
{
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_');
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
            if(line[i] == '$')
                i++;
            if (line[i + 1] == '\'')
                lst_add_back(list, lst_new(ft_substr(line, i++, 2), SNGL_Q));
            else
            {
                start = i;
                end = find_char(line + i + 1, '\'');
                if(end)
                    lst_add_back(list, lst_new(ft_substr(line, start, end + 2), SNGL_Q));
                else
                    print_error("Error: missing single quote\n");
                i += end + 1;
            }
            i++;
        }
        else if (line[i] == '\"' || (line[i] == '$' && line[i + 1] == '\"'))
        {
            if(line[i] == '$')
                i++;
            if (line[i + 1] == '\"')
                lst_add_back(list, lst_new(ft_substr(line, i++, 2), DBL_Q));
            else
            {
                start = i;
                end = find_char(line + i + 1, '\"');
                if(end)
                    lst_add_back(list, lst_new(ft_substr(line, start, end + 2), DBL_Q));
                else
                    print_error("Error: missing double quote\n");
                i += end + 1;
            }
            i++;
        }
        else if(line[i] == '$' && (line[i + 1] >= '0' && line[i + 1] <= '9'))
        {
            lst_add_back(list, lst_new(ft_substr(line, i++, 2), VAR));
            i++;
        }
        else if(line[i] == '$' && line[i + 1] == '$')
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
                    if(!is_alnum(line[i + 1]))
                        break;
                    i++;
                }
                end = i - start;
                lst_add_back(list, lst_new(ft_substr(line, start, end+1),VAR));
                i++;
            }
        }
        else
        {
            start = i;
            while (line[i] && !is_special(line[i]))
            {
                if(is_special(line[i + 1]))
                    break;
                i++;
            }
            end = i - start;
            lst_add_back(list, lst_new(ft_substr(line, start, end + 1), CMD));
            i++;
        }
    }
    return (0);
}
// Main function
    #include "libc.h"

void    initenv(char **env, t_env **envi)
{
    (void)env;
    (void)envi;
    char **str;
    int i;
    i = 0;
    // printf("%lu", strlen(*env));
    while (env[i])
    {
        str = ft_split(env[i], '=');
        lst_add_back_env(envi, lst_new_env(str[0], str[1]));
        i++;
        free(str);
    }
}

// find leaks
void f()
{
    system("leaks minishell");
}
int main(int ac, char **av, char **env)//$home.c
{
    atexit(f);
    (void)ac;
    (void)av;
    t_env *envi;
    envi = NULL;
    (void)env;
    char *line;
    // // int execFlag = 0;
    t_token *list;
    list = NULL;
    
    initenv(env, &envi);
    while (1)
    { 
        line =  readline("Minishell> "); 
        if (ft_strlen(line) != 0)
            add_history(line);
        // if (takeInput(line))
        //     continue;

        processline(line , &list);
        if(catch_errors(&list) == 1)
            continue;
        printf("\n-----------\n");
        print_list(list);

        free(line);
        ft_lstclear(&list);
        // ft_lstclear_env(&envi);
    }
    
}// ???????????????????????


/*

--> "$HOME" 
--> print env
--> env: r: No such file or directory



??
--> export
--> unset


--> 

*/