/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:40:25 by hchadili          #+#    #+#             */
/*   Updated: 2024/07/28 14:47:50 by hchadili         ###   ########.fr       */
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

void	ft_pwd(t_env **env)
{
	t_env *tmp = *env;
	while (tmp)
	{
		if(ft_strcmp(tmp->key, "PWD") == 0)
			break;
		tmp = tmp->next;
	}
	
	char arr[PATH_MAX];
	getcwd(arr,sizeof(arr));
	if (arr[0])
		printf("%s\n",arr);
	else if(tmp)
		printf("%s\n",tmp->value);
		
}