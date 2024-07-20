/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 15:40:16 by hchadili          #+#    #+#             */
/*   Updated: 2024/07/20 17:33:51 by hchadili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_cd(t_cmd *cmnd, t_env **env)
{
	(void)env;
	(void)cmnd;
	char arr[PATH_MAX];
	t_env *tmp;
	t_env *tmp2;
	tmp = *env;
	tmp2 = *env;
	int x = 0;
	while (tmp)
	{
		if (strcmp(tmp->key, "HOME") == 0)
			break;
		tmp = tmp->next;
	}
	while (cmnd->cmds[x])
		x++;
	if (x == 1)
	{
		if (chdir(tmp->value))
		{
			perror("chdir erorr");
			return;
		}
		tmp = *env;	
		while (tmp)
		{
			if (strcmp(tmp->key, "PWD") == 0)
				break;
			tmp = tmp->next;
		}
		while (tmp2)
		{
			if (strcmp(tmp2->key, "OLDPWD") == 0)
				break;
			tmp2 = tmp2->next;
		}
		if (tmp2 && tmp)
			tmp2->value = tmp->value;
		getcwd(arr, sizeof(arr));
		if (tmp)
			tmp->value = ft_strdup_env(arr);
	}
	else
	{
		if (chdir(cmnd->cmds[1]) || x != 2)
		{
			perror("chdir erorr");
			return;
		}
		tmp = *env;
		while (tmp)
		{
			if (strcmp(tmp->key, "PWD") == 0)
				break;
			tmp = tmp->next;
		}
		while (tmp2)
		{
			if (strcmp(tmp2->key, "OLDPWD") == 0)
				break;
			tmp2 = tmp2->next;
		}
		if (tmp2 && tmp)
			tmp2->value = tmp->value;
		getcwd(arr, sizeof(arr));
		if (tmp)
			tmp->value = ft_strdup_env(arr);

	}
}
