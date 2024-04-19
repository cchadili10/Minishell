/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yessemna <yessemna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 21:20:14 by yessemna          #+#    #+#             */
/*   Updated: 2024/04/16 22:45:02 by yessemna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	cr;
	char			*str;
	int				i;

	i = 0;
	cr = (unsigned char)c;
	str = (char *)s;
	while (str[i])
	{
		if (str[i] == cr)
			return (str + i);
		i++;
	}
	if (str[i] == cr)
		return (str + i);
	return (0);
}
