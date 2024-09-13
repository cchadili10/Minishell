/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yessemna <yessemna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 12:46:42 by yessemna          #+#    #+#             */
/*   Updated: 2024/09/13 02:26:23 by yessemna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*logic(char *str)
{
	char	*ret;

	ret = ft_strdup("");
	ret = join_char(ret, '\'');
	ret = ft_srtjoin(ret, str);
	ret = join_char(ret, '\'');
	return (ret);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;
	size_t	slen ;
	char	*ret;

	i = 0;
	if (!s)
		return (0);
	slen = ft_strlen(s);
	if (start > slen)
		return (ft_calloc(1, 1));
	if (len >= slen - start)
		len = slen - start;
	str = (char *)g_malloc(sizeof(char) * len + 1, MALLOC);
	if (!str)
		return (0);
	while (len--)
		str[i++] = s[start++];
	str[i] = '\0';
	if (ft_strstr(str, "$?"))
	{
		((1) && ret = ft_strdup(""), ret = logic(str));
		return (ret);
	}
	return (str);
}

char	*ft_substr_env(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;
	size_t	slen ;

	i = 0;
	if (!s)
		return (0);
	slen = ft_strlen(s);
	if (start > slen)
		return (ft_calloc(1, 1));
	if (len >= slen - start)
		len = slen - start;
	str = (char *)g_malloc_env(sizeof(char) * len + 1, MALLOC);
	if (!str)
		return (0);
	while (len--)
		str[i++] = s[start++];
	str[i] = '\0';
	return (str);
}
