/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 02:30:43 by hchadili          #+#    #+#             */
/*   Updated: 2024/08/06 14:22:02 by hchadili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_hexa(unsigned int n, int *count, char *HEXA_)
{
	if (n > 15)
	{
		ft_hexa(n / 16, count, HEXA_);
		ft_hexa(n % 16, count, HEXA_);
	}
	else
		ft_putchar(HEXA_[n], count);
}

void	ft_hexap(unsigned long long num, int *count, char *HEXA_)
{
	if (num > 15)
	{
		ft_hexap(num / 16, count, HEXA_);
		ft_hexap(num % 16, count, HEXA_);
	}
	else
		ft_putchar(HEXA_[num], count);
}
