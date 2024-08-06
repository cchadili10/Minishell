/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 06:12:01 by yessemna          #+#    #+#             */
/*   Updated: 2024/08/05 15:04:25 by hchadili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*lst_new(char *key, t_type value)
{
	t_token	*new;

	if (!key)
		return (NULL);
	new = (t_token *)g_malloc(sizeof(t_token), MALLOC);
	if (!new)
		return (NULL);
	new->key = key;
	new->copy_key = key;
	new->value = value;
	new->next = NULL;
	return (new);
}

void	lst_add_back(t_token **head, t_token *new)
{
	t_token	*tmp;

	tmp = *head;
	if (!head || !new)
		return ;
	if (!*head)
		*head = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	lst_add_back_env(t_env **head, t_env *new)
{
	t_env	*tmp;

	tmp = *head;
	if (!head || !new)
		return ;
	if (!*head)
		*head = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

t_env	*lst_new_env(char *key, char *value)
{
	t_env	*new;

	if (!key)
		return (NULL);
	new = (t_env *)g_malloc_env(sizeof(t_env), MALLOC);
	if (!new)
		return (NULL);
	new->key = key;
	new->value = value;
	new->next = NULL;
	return (new);
}
