/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 15:40:16 by hchadili          #+#    #+#             */
/*   Updated: 2024/07/19 22:54:41 by hchadili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_cd(t_cmd *cmnd, t_env **env)
{
	(void)env;
	char arr[PATH_MAX];
	t_env *tmp;
	t_env *tmp2;
	tmp = *env;
	tmp2 = *env;
	while (tmp)
	{
		if(strcmp(tmp->key ,"HOME") == 0)
			break;
		tmp = tmp->next;
	}
	if(!cmnd->cmds[2])
	{	
		if(!cmnd->cmds[1])
			chdir(tmp->value);
		else if(chdir(cmnd->cmds[1]))
		{
			perror("chdir erorr");
			return ;
		}
		tmp = *env;
		while (tmp)
		{
			if(strcmp(tmp->key ,"PWD") == 0)
				break;
			tmp = tmp->next;
		}
		while (tmp2)
		{
			if(strcmp(tmp2->key ,"OLDPWD") == 0)
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
		perror("chdir erorr");
}
 