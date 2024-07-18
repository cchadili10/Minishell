/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:40:25 by hchadili          #+#    #+#             */
/*   Updated: 2024/07/18 15:17:39 by hchadili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
// int	ft_look_for_pwd(char *str)
// {
// 	int x;
// 	x = 0;
// 	char str2[] = "PWD=/";
// 	while (str2[x])
// 	{
// 		if(str[x] != str2[x])
// 			return 0;
// 		x++;
// 	}
// 	return 1;
// }

void	ft_pwd(void)
{
	char arr[PATH_MAX];
	printf("%s\n",getcwd(arr,sizeof(arr)));	
}