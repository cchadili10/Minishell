/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yessemna <yessemna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 00:46:19 by yessemna          #+#    #+#             */
/*   Updated: 2024/08/07 01:36:07 by yessemna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static size_t	ft_countword(char const *s, char c)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
			count++;
		while (s[i] != c && s[i])
			i++;
	}
	return (count);
}

size_t	set_world_len(const char *s, char c)
{
	size_t	word_len;

	if (!s)
		return (0);
	if (!ft_strchr(s, c))
		word_len = ft_strlen(s);
	else
		word_len = ft_strchr(s, c) - s;
	return (word_len);
}

char	**ft_split(char const *s, char c)
{
	char	**lst;
	int		i;

	if (!s)
		return (0);
	lst = (char **)g_malloc((ft_countword(s, c) + 1) * sizeof(char *), MALLOC);
	if (!lst)
		return (0);
	i = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s)
		{
			lst[i] = ft_substr(s, 0, set_world_len(s, c));
			s += set_world_len(s, c);
			i++;
		}
	}
	lst[i] = NULL;
	return (lst);
}

char	**ft_split_env(char const *s, char c)
{
	char	**lst;
	int		i;

	if (!s)
		return (0);
	lst = g_malloc_env((ft_countword(s, c) + 1) * sizeof(char *), MALLOC);
	if (!lst)
		return (0);
	i = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s)
		{
			lst[i] = ft_substr_env(s, 0, set_world_len(s, c));
			s += set_world_len(s, c);
			i++;
		}
	}
	lst[i] = NULL;
	return (lst);
}
