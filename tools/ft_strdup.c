/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 10:15:54 by yessemna          #+#    #+#             */
/*   Updated: 2024/08/24 23:17:44 by hchadili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strdup(const char *s)
{
	char	*out;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	out = g_malloc(ft_strlen(s) + 1, MALLOC);
	while (s && s[i])
	{
		out[i] = s[i];
		i++;
	}
	out[i] = '\0';
	return (out);
}

char	*ft_strdup_env(const char *s)
{
	char	*out;
	int		i;

	i = 0;
	out = g_malloc_env(ft_strlen(s) + 1, MALLOC);
	while (s && s[i])
	{
		out[i] = s[i];
		i++;
	}
	out[i] = '\0';
	return (out);
}
