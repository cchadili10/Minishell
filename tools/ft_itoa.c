/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 15:27:40 by hchadili          #+#    #+#             */
/*   Updated: 2024/08/18 19:39:16 by hchadili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_count_number(long n)
{
	int	x;

	x = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n *= -1;
		x++;
	}
	while (n > 0)
	{
		n /= 10;
		x++;
	}
	return (x);
}

static char	last_num(long *c)
{
	int	last;

	last = *c % 10;
	*c = *c / 10;
	return (last + '0');
}

static void	ft_sin(long *l, int *s)
{
	*l *= -1;
	*s = 1;
}

char	*ft_itoa(int n)
{
	long	l;
	int		s;
	int		count;
	int		sum;
	char	*array;

	l = n;
	s = 0;
	count = ft_count_number(l);
	if (l < 0)
		ft_sin(&l, &s);
	sum = count;
	array = (char *) g_malloc(sizeof(char) * (count + 1), MALLOC);
	if (!(array))
		return (0);
	while (count - s > 0)
	{
		if (s == 1)
			array[0] = '-';
		array[count - 1] = last_num(&l);
		count--;
	}
	array[sum] = '\0';
	return (array);
}
