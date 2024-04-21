/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yessemna <yessemna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 17:59:59 by yessemna          #+#    #+#             */
/*   Updated: 2024/04/21 16:18:50 by yessemna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// print list as a table

void print_list(t_env *list)
{
    t_env *tmp = list;
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
        else if(tmp->value == Sgl_q)
            printf("Sgl_q\n");
        else if(tmp->value == Dbl_q)
            printf("Dbl_q\n");
        else if(tmp->value == VAR)
            printf("VAR\n");
        else if(tmp->value == CMD)
            printf("CMD\n");
        tmp = tmp->next;
    }

}

// Function to take input 
// int takeInput(char* str) 
// { 
//     char* buf;
//     char prompt[12] = "Minishell> ";
//     buf = readline(prompt); 
//     if (ft_strlen(buf) != 0) { 
//         add_history(buf); 
//         ft_strcpy(str, buf); 
//         return 0; 
//     } else { 
//         return 1; 
//     } 
// }

// int is_pipe(char *line)
// {
//     int i = 0;
//     while (line[i] != '\0')
//     {
//         if (line[i] == '|')
//             return (1);
//         i++;
//     }
//     return (0);
// }
int is_space(char c)
{
    return (c == ' ' || (c > 9 && c < 13));
}

int is_special(char c)
{
    return (c == '|' || c == '<' || c == '>' || c == '\'' || c == '\"' || c == '$' || is_space(c));
}

void processline(char *line, t_env **list)
{
    int i;
    int start;
    
    start = 0;
    i = 0;
    
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
                lst_add_back(list, lst_new(ft_substr(line, i++, 2), HEREDOC)); // 2
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
//         // else if (line[i] == '\'')
//         //     lst_add_back(&list, lst_new(ft_substr(line, i++, 1), Sgl_q));
//         // else if (line[i] == '\"')
//         //     lst_add_back(&list, lst_new(ft_substr(line, i++, 1), Dbl_q));
//         else if (line[i] == '$')
//             lst_add_back(&list, lst_new(ft_substr(line, i++, 1), VAR));
        else
        {
            start = i;
            while (line [i] &&  !is_special(line[i]))
                i++;
            lst_add_back(list, lst_new(ft_substr(line, start, i - start), CMD));
        }
        
    }
    
}

// Main function
int main(int ac, char **av, char **env)
{
    (void)ac;
    (void)av;
    (void)env;
    char *line;
    // int execFlag = 0;
    t_env *list;
    list = NULL;
    
    // initshell(env);
    while (1)
    { 
        line =  readline("Minishell> "); 
        if (ft_strlen(line) != 0)
            add_history(line); 
        // if (takeInput(line))
        //     continue;

        processline(line , &list);
        printf("\n----> %s\n", line);
        print_list(list);
        
        // printf("---->%d\n", execFlag);
        free(line);
        list = NULL;
    }
}