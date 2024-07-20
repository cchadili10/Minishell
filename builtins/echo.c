/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:43:08 by hchadili          #+#    #+#             */
/*   Updated: 2024/07/20 16:47:35 by hchadili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
int	ft_check_n(char *str)
{
	int x;
	x = 0;
	if (!str[x])
		return 0;
	while (str[x])
	{
		if(str[x] != 'n')
			return 0;
		x++;
	}
	return 1;
}

int	ft_look_for_n(char *str)
{
	if(str[0] == '-')
		return ft_check_n(str+1);
	else
		return 0;
}

void ft_echo(t_cmd *cmnd)
{
	int	i = 0;
	int	x = 2;
	t_cmd *tmp = cmnd; 
	
	while (tmp->cmds[i])
		i++;
	if (i == 1)
		printf("\n");
	// tmp = cmnd;
	else
	{
		if (ft_look_for_n(tmp->cmds[1]))
		{
			while (x < i)
			{
				if( x == 2)
					write(1,tmp->cmds[x],ft_strlen(tmp->cmds[x]));
				else
				{
					write(1," ",1);
					write(1,tmp->cmds[x],ft_strlen(tmp->cmds[x]));
				}
				x++;
			}
			
		}
		else
		{
			x = 1;
			while (x < i)
			{
				if(x == 1)
					printf("%s",tmp->cmds[x]);
				else
					printf(" %s",tmp->cmds[x]);
				x++;
			}
			printf("\n");
		}
	}
	
}