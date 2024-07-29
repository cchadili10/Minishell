/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 15:40:16 by hchadili          #+#    #+#             */
/*   Updated: 2024/07/29 10:26:44 by hchadili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int  ft_check_second_arg(char *str)
{
	int x;
	x = 0;
	if(!str[x])
		return 0;
	while (str[x])
	{
		if (str[x] != '.')
			return (0);
		x++;
	}
	return 1;
}

void	ft_add_to_path(t_env *pwd, t_env *oldpwd)
{
	if (pwd && oldpwd)
		oldpwd->value = pwd->value; 
	if (pwd)
		pwd->value = ft_strjoin_(pwd->value, "/..");
}

void ft_cd(t_cmd *cmnd, t_env **env)
{
	t_env *tmp;
	t_env *tmp2;
	DIR *dir;
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
			ft_exit_status(1, SET);
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
		ft_exit_status(0, SET);
		if (tmp2 && tmp)
			tmp2->value = tmp->value;
		if (tmp)
			tmp->value = ft_strdup_env(getcwd(0, 0));
	}
	else
	{
		tmp = *env;
		dir = opendir(cmnd->cmds[1]);
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
		if (chdir(cmnd->cmds[1]) || x != 2)
		{
			perror("chdir erorr");
			ft_exit_status(1, SET);
			return ;
		}
		
		if (!getcwd(0, 0))
		{
			printf("cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n");
			ft_exit_status(0, SET);
			return ;
		}
		if (tmp2 && tmp)
			tmp2->value = tmp->value;
		if (tmp)
			tmp->value = ft_strdup_env(getcwd(0, 0));
		ft_exit_status(0, SET);
	}
}
