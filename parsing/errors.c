/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yessemna <yessemna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 15:38:09 by yessemna          #+#    #+#             */
/*   Updated: 2024/05/13 01:24:39 by yessemna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int is_redirection(t_type type)
{
    if(type == APPEND || type == HEREDOC || type == IN || type == OUT)
        return (1);
    return (0);
}

int print_err(char *str, t_env **arg)
{
    if(str == NULL)
        ft_putendl_fd("syntax error", 2);
    ft_lstclear(arg);
    return (1);
}

int catch_errors(t_env **arg)
{
    t_env *cur;
    // t_env *prev;

    cur = *arg;

    if(!cur)
        return (0);
    if(cur->value == PIPE)
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
		cur = cur->next;
	}
	

    return (0);
}

/*

        '| echo'
        '||' , '| |'
        '| 0' , '|0'
		
        '>|' , '> |' --> DONE!
        '> 0' , '>0'  --> DONE!
		'><' , '> <'  --> DONE!



while (cur)
	{
		if (is_redirection(cur->type))
		{
			if (cur->next == NULL || (cur->next->type == SPACE && cur->next->next == NULL))
				return print_error(NULL);
			if (cur->next->type == PIPE || is_redirection(cur->next->type))
				return print_error(NULL);
			else if ( cur->next->type == SPACE && cur->next->next &&
				(cur->next->next->type == PIPE || is_redirection(cur->next->next->type)))
				return print_error(NULL);
			if (cur->next->type == PIPE || is_redirection(cur->next->type))
				return print_error(NULL);
			else if ( cur->next->type == SPACE && cur->next->next && 
					(cur->next->next->type == PIPE || is_redirection(cur->next->next->type)))
				return print_error(NULL);
		}
		if (cur->type != SPACE)
			prev = cur;
		cur = cur->next;
	}
	if (prev && prev->type == PIPE)
		return (print_error(NULL));
	return (0);
*/