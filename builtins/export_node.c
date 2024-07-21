/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 17:46:50 by hchadili          #+#    #+#             */
/*   Updated: 2024/07/21 17:47:39 by hchadili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strdup_(const char *s1)
{
	char	*array;
	int		x;
	int		size;

	x = 0;
	if(!s1)
		return 0;
	size = ft_strlen(s1);
	array = (char *) malloc(sizeof(char) * (size + 1));
	if (!(array))
		return (0);
	while (s1[x])
	{
		array[x] = s1[x];
		x++;
	}
	array[x] = '\0';
	return (array);
}

t_export	*create_node(char *key, char *value)
{
	t_export	*new_node;

	new_node = malloc(sizeof(t_export));
	if (!new_node)
		return (0);
	new_node->key = key;
	new_node->value = value;
	new_node->next = NULL;
	return (new_node);
}

void	insert_end(t_export **head, char *key, char *value)
{
	t_export	*new_node;
	t_export	*temp;

	new_node = create_node(ft_strdup_(key), ft_strdup_(value));
	// new_node = create_node(key, value);
	if (*head == NULL)
	{
		*head = new_node;
		return ;
	}
	temp = *head;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new_node;
}