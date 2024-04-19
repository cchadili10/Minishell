/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yessemna <yessemna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 17:59:59 by yessemna          #+#    #+#             */
/*   Updated: 2024/04/19 10:27:12 by yessemna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Function to print the current directory

// Function to take input 
int takeInput(char* str) 
{ 
    char* buf;
    char prompt[12] = "Minishell> ";
    buf = readline(prompt); 
    if (ft_strlen(buf) != 0) { 
        add_history(buf); 
        ft_strcpy(str, buf); 
        return 0; 
    } else { 
        return 1; 
    } 
}

int is_pipe(char *line)
{
    int i = 0;
    while (line[i] != '\0')
    {
        if (line[i] == '|')
            return (1);
        i++;
    }
    return (0);
}

void *processline(char *line, t_env *list)
{
    int i;

    i = 0;
    
    while (line[i] != '\0')
    {
        if (line[i] == '|')
        {
            lst_add_back(&list, lst_new("PIPE", PIPE));
        }
        else if (line[i] == '<')
        {
            lst_add_back(&list, lst_new("IN", IN));
        }
        else if (line[i] == '>')
        {
            lst_add_back(&list, lst_new("OUT", OUT));
        }
        else if (line[i] == ' ')
        {
            lst_add_back(&list, lst_new("CMD", CMD));
        }
        else if (line[i] == '\'')
        {
            lst_add_back(&list, lst_new("Sgl_q", Sgl_q));
        }
        else if (line[i] == '"')
        {
            lst_add_back(&list, lst_new("Dbl_q", Dbl_q));
        }
        i++;
    }
    
}

// Main function
int main(int ac, char **av, char **env)
{
    (void)ac;
    (void)av;
    (void)env;
    char line[MAXCMD];
    int execFlag = 0;
    t_env *list;
    
    // initshell(env);
    while (1)
    {
        if (takeInput(line))
            continue;

        processline(line , &list);

        
        // printf("---->%d\n", execFlag);
    }
}