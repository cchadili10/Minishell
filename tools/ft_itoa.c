/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 15:27:40 by hchadili          #+#    #+#             */
/*   Updated: 2024/08/06 15:29:38 by hchadili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *ft_itoi(int nbr)
{
	char *str;
	int i;
	int n;

	i = 0;
	n = nbr;
	while (n)
	{
		n /= 10;
		i++;
	}
	str = (char *)malloc(i + 1);
	if (!str)
		return (NULL);
	str[i] = '\0';
	while (i--)
	{
		str[i] = nbr % 10 + '0';
		nbr /= 10;
	}
	return (str);
}
