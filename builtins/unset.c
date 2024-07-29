/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 14:33:24 by hchadili          #+#    #+#             */
/*   Updated: 2024/07/29 11:09:53 by hchadili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

void	ft_remove_key_export(t_export **export, char *key)
{
	t_export *tmp = *export;
	t_export *for_free_export;
	int check = 0;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			check = 1;
			break;
		}
		else if (ft_strcmp(tmp->next->key, key) == 0)
			break;
		tmp = tmp->next;
	}
	if(check)
	{
		for_free_export = *export;
		*export = for_free_export->next;
		free(for_free_export);
	}
	else if(tmp->next->next)
	{
		for_free_export = tmp->next;
		tmp->next = tmp->next->next;
		free(for_free_export);
	}
	else if(!tmp->next->next && tmp->next)
	{
		for_free_export = tmp->next;
		tmp->next = NULL;
		free(for_free_export);
	}
}
void	ft_remove_key_env(t_env **env, char *key)
{
	t_env *tmp = *env;
	t_env *for_free_env;
	int check = 0;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			check = 1;
			break;
		}
		else if(tmp->next)
		{
			if (ft_strcmp(tmp->next->key, key) == 0)
				break;
		}
		tmp = tmp->next;
	}
	if(!tmp)
		return ;
	else if(check)
	{
		for_free_env = *env;
		*env = for_free_env->next;
		free(for_free_env);
	}
	else if(tmp->next->next)
	{
		for_free_env = tmp->next;
		tmp->next = tmp->next->next;
		free(for_free_env);
	}
	else if(!tmp->next->next && tmp->next)
	{
		for_free_env = tmp->next;
		tmp->next = NULL;
		free(for_free_env);
	}
}
void ft_unset(t_cmd *cmnd, t_export **export, t_env **env)
{
	int x = 0;
	int check = 0;
	while (cmnd->cmds[x])
		x++;
	if(x == 1)
	{
		ft_exit_status(0, SET);
		return ;
	}
	else
	{
		x = 1;
		while (cmnd->cmds[x])
		{
		
			if (ft_check_key(cmnd->cmds[x]))
			{
				if(ft_find_key(export,cmnd->cmds[x]))
				{
					ft_remove_key_export(export, cmnd->cmds[x]);
					ft_remove_key_env(env, cmnd->cmds[x]);
				}
			}
			else
			{
				printf("unset: `%s': not a valid identifier\n", cmnd->cmds[x]);
				check = 1;	
			}
			
			x++;
		}
		if (check)
			ft_exit_status(1, SET);
		else
			ft_exit_status(0, SET);
	}
}
