/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dbl_join.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 08:21:52 by yessemna          #+#    #+#             */
/*   Updated: 2024/08/24 23:16:56 by hchadili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strlen_2d(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str && str[i])
		i++;
	return (i);
}

char	**dbl_join(char **s1, char *s2)
{
	char	**out;
	int		i;

	i = 0;
	out = g_malloc(sizeof(char *) * (ft_strlen_2d(s1) + 2), MALLOC);
	if (!out)
		return (NULL);
	while (s1 && s1[i])
	{
		out[i] = ft_strdup(s1[i]);
		i++;
	}
	out[i] = ft_strdup(s2);
	i++;
	out[i] = NULL;
	return (out);
}
