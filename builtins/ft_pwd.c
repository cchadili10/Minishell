/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:40:25 by hchadili          #+#    #+#             */
/*   Updated: 2024/08/15 22:50:23 by hchadili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pwd(t_env **env)
{
	t_env	*tmp;
	char	arr[PATH_MAX];

	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "PWD") == 0)
			break ;
		tmp = tmp->next;
	}
	getcwd(arr, sizeof(arr));
	if (arr[0])
		printf("%s\n", arr);
	else if (tmp)
		printf("%s\n", tmp->value);
	ft_exit_status(0, SET);
}
