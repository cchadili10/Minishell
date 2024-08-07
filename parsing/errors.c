/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 15:38:09 by yessemna          #+#    #+#             */
/*   Updated: 2024/08/06 18:10:24 by hchadili         ###   ########.fr       */
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
    (void)arg;
    if(str == NULL)
        ft_putendl_fd("syntax error", 2);
    else
        ft_putendl_fd(str, 2);
    return (1);
}

int catch_errors(t_token **arg)
{
    t_token *cur;
    // t_token *prev;

    cur = *arg;

    if(!cur || (cur->value == SPC && cur->next == NULL))
        return (0);
    if(cur && (cur->value == PIPE || (cur->value == SPC && cur->next->value == PIPE)))
        return (print_err("syntax error near unexpected token `|'", arg), 0);
    
    while (cur)
	{
		if (is_redirection(cur->value))
		{
			if (cur->next == NULL || (cur->next->value == SPC && cur->next->next == NULL))
				return (print_err(NULL, arg), 0);
			if (cur->next->value == PIPE || (cur->next->value == SPC && (cur->next->next->value == PIPE)))
				return (print_err(NULL, arg), 0);
			if (is_redirection(cur->next->value) || (cur->next->value == SPC && is_redirection(cur->next->next->value)))
				return (print_err(NULL, arg), 0);
		}
		if (cur->value == PIPE)
		{
			if (cur->next == NULL || (cur->next->value == SPC && cur->next->next == NULL))
				return (print_err(NULL, arg), 0);
			if (cur->next->value == PIPE || (cur->next->value == SPC && cur->next->next->value == PIPE))
				return (print_err(NULL, arg), 0);
            if ((cur->next->value == SPC && (cur->next->next->value != CMD)))
                return (print_err(NULL, arg), 0);
		}
		cur = cur->next;
	}
	

    return (1);
}

/*

        '| echo'  --> DONE!
        '||' , '| |'
        '| 0' , '|0'
		
        '>|' , '> |' --> DONE!
        '> 0' , '>0'  --> DONE!
		'><' , '> <'  --> DONE!

*/