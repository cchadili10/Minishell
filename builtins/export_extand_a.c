/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_extand_a.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:14:41 by hchadili          #+#    #+#             */
/*   Updated: 2024/08/06 16:17:22 by hchadili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_set_zero_to_struct(t_export_var *exp)
{
	exp->append = 0;
	exp->update_ = 0;
	exp->key = 0;
	exp->start = 0;
	exp->value = 0;
}

char	*ft_strjoin_(char const *s1, char const *s2)
{
	int		x;
	int		y;
	char	*array;
	int		size;

	x = 0;
	y = 0;
	if (!s1 && !s2)
		return (0);
	size = (ft_strlen(s1) + ft_strlen(s2));
	array = (char *) g_malloc_env((sizeof(char) * size) + 1 , MALLOC);
	if (!array)
		return (0);
	while (s1[x])
	{
		array[x] = s1[x];
		x++;
	}
	while (s2[y])
		array[x++] = s2[y++];
	array[size] = '\0';
	return (array);
}

int	ft_chek_true(char *str, int x)
{
	while (str[x])
	{
		if (str[x] == '=')
			return (x);
		x++;
	}
	return (x);
}

int	ft_check_false(char *str, int x, t_export_var *exp)
{
	if (str[x] == '+')
	{
		if (str[x + 1] == '=')
		{
			exp->update_ = 1;
			exp->append = 1;
			return (x);
		}
	}
	else
	{
		exp->update_ = 1;
		return (x);
	}
	return (0);
}

int	ft_count_eq(char *str, int chek, t_export_var *exp)
{
	int	x;

	x = 0;
	if (chek)
		return (ft_chek_true(str, x));
	else
	{
		while (str[x])
		{
			if (str[x] == '+' || str[x] == '=')
				return (ft_check_false(str, x, exp));
			x++;
		}
		return (x);
	}
}
