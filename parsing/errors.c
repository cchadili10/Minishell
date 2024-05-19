/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yessemna <yessemna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 15:38:09 by yessemna          #+#    #+#             */
/*   Updated: 2024/05/18 20:26:36 by yessemna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int is_redirection(t_type type)
{
    if(type == APPEND || type == HEREDOC || type == IN || type == OUT)
        return (1);
    return (0);
}

int print_err(char *str, t_token **arg)
{
    if(str == NULL)
        ft_putendl_fd("syntax error", 2);
    ft_lstclear(arg);
    return (1);
}

int catch_errors(t_token **arg)
{
    t_token *cur;
    // t_token *prev;

    cur = *arg;

    if(!cur)
        return (0);
    if(cur->value == PIPE || (cur->value == SPACE && cur->next->value == PIPE))
        return (print_err(NULL, arg));
    
    while (cur)
	{
		if (is_redirection(cur->value))
		{
			if (cur->next == NULL || (cur->next->value == SPACE && cur->next->next == NULL))
				return print_err(NULL, arg);
			if (cur->next->value == PIPE || (cur->next->value == SPACE && (cur->next->next->value == PIPE)))
				return print_err(NULL, arg);
			if (is_redirection(cur->next->value) || (cur->next->value == SPACE && is_redirection(cur->next->next->value)))
				return print_err(NULL, arg);
		}
		if (cur->value == PIPE)
		{
			if (cur->next == NULL || (cur->next->value == SPACE && cur->next->next == NULL))
				return print_err(NULL, arg);
			if (cur->next->value == PIPE || (cur->next->value == SPACE && cur->next->next->value == PIPE))
				return print_err(NULL, arg);
		}
		cur = cur->next;
	}
	

    return (0);
}

/*

        '| echo'  --> DONE!
        '||' , '| |'
        '| 0' , '|0'
		
        '>|' , '> |' --> DONE!
        '> 0' , '>0'  --> DONE!
		'><' , '> <'  --> DONE!

*/