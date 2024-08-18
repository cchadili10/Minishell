/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_extand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 13:41:38 by hchadili          #+#    #+#             */
/*   Updated: 2024/08/18 22:07:16 by hchadili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_key(char *key)
{
	int	x;

	x = 0;
	if ((key[x] >= 97 && key[x] <= 122)
		|| (key[x] >= 65 && key[x] <= 90) || key[x] == 95)
	{
		x++;
		while (key[x])
		{
			if ((key[x] >= 'a' && key[x] <= 'z') || key[x] == '_'
				|| (key[x] >= 'A' && key[x] <= 'Z')
				|| (key[x] >= '0' && key[x] <= '9'))
				x++;
			else
				return (0);
		}
		return (1);
	}
	return (0);
}

int	ft_find_key(t_exp **export, char *key)
{
	t_exp	*tmp;

	tmp = *export;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	ft_add_to_env_export(t_exp **export,
			t_env **env, char *key, char *value)
{
	t_exp	*tmp;
	t_env	*tmp_env;

	((1) && (tmp = *export, tmp_env = *env));
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
			break ;
		tmp = tmp->next;
	}
	while (tmp_env)
	{
		if (ft_strcmp(tmp_env->key, key) == 0)
			break ;
		tmp_env = tmp_env->next;
	}
	if (tmp)
		tmp->value = ft_strjoin_(tmp->value, value);
	if (tmp_env)
		tmp_env->value = ft_strjoin_(tmp_env->value, value);
	else if (!tmp_env)
		lst_add_back_env(env, lst_new_env(key, value));
}

void	ft_replace_value_for_env(t_env **env, char *key, char *value, int check)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
			break ;
		tmp = tmp->next;
	}
	if (tmp && check)
		tmp->value = ft_strdup_env(value);
	else if (!tmp && check)
		lst_add_back_env(env, lst_new_env(key, value));
}

void	ft_replace_value_for_export(t_exp **export,
				char *key, char *value, int check)
{
	t_exp	*tmp;

	tmp = *export;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
			break ;
		tmp = tmp->next;
	}
	if (tmp && check)
		tmp->value = ft_strdup_env(value);
}
