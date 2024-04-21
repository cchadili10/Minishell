/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yessemna <yessemna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 06:12:01 by yessemna          #+#    #+#             */
/*   Updated: 2024/04/21 15:46:13 by yessemna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env   *lst_new(char *key, t_type value)
{
    t_env *new;
    
    if (!key)
        return (NULL);
    new = (t_env *)malloc(sizeof(t_env));
    if (!new)
        return (NULL);
    new->key = key;
    new->value = value;
    new->next = NULL;
    return (new);
}
void    lst_add_back(t_env **head, t_env *new)
{
    t_env *tmp = *head;

    if(!head || !new)
        return ;
    
    if(!*head)
        *head = new;
    else
    {
        while(tmp->next)
            tmp = tmp->next;
        tmp->next = new;
    }
}