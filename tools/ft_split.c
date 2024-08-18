/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 00:46:19 by yessemna          #+#    #+#             */
/*   Updated: 2024/08/18 22:06:49 by hchadili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static size_t	ft_countword(char const *s, char c, char t)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c || s[i] == t)
			i++;
		if (s[i])
			count++;
		while (s[i] != c && s[i] != t && s[i])
			i++;
	}
	return (count);
}

size_t	set_world_len(const char *s, char c, char t)
{
	size_t	word_len;

	if (!s)
		return (0);
	if (!ft_strchr(s, c, t))
		word_len = ft_strlen(s);
	else
		word_len = ft_strchr(s, c, t) - s;
	return (word_len);
}

char	**ft_split(char const *s, char c, char t)
{
	char	**lst;
	int		i;

	if (!s)
		return (0);
	lst = g_malloc((ft_countword(s, c, t) + 1) * sizeof(char *), MALLOC);
	if (!lst)
		return (0);
	i = 0;
	while (*s)
	{
		while ((*s == c || *s == t) && *s)
			s++;
		if (*s)
		{
			lst[i] = ft_substr(s, 0, set_world_len(s, c, t));
			s += set_world_len(s, c, t);
			i++;
		}
	}
	lst[i] = NULL;
	return (lst);
}

char	**ft_split_env(char const *s, char c, char t)
{
	char	**lst;
	int		i;

	if (!s)
		return (0);
	lst = g_malloc_env((ft_countword(s, c, t) + 1) * sizeof(char *), MALLOC);
	if (!lst)
		return (0);
	i = 0;
	while (*s)
	{
		while ((*s == c || *s == t) && *s)
			s++;
		if (*s)
		{
			lst[i] = ft_substr_env(s, 0, set_world_len(s, c, t));
			s += set_world_len(s, c, t);
			i++;
		}
	}
	lst[i] = NULL;
	return (lst);
}
