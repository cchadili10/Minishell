/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 07:29:29 by hchadili          #+#    #+#             */
/*   Updated: 2024/09/17 19:59:59 by hchadili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_look_for_pwd_env(t_env **tmp, char *str)
{
	while (*tmp)
	{
		if (strcmp((*tmp)->key, str) == 0)
			break ;
		*tmp = (*tmp)->next;
	}
}

void	ft_go_to_home_env(t_env **env)
{
	static int	check;
	char		arr[PATH_MAX];
	t_env		*tmp;
	t_env		*tmp2;

	tmp = *env;
	tmp2 = *env;
	ft_look_for_pwd_env(&tmp, "HOME");
	tmp = *env;
	ft_look_for_pwd_env(&tmp, "PWD");
	ft_look_for_pwd_env(&tmp2, "OLDPWD");
	ft_exit_status(0, SET);
	getcwd(arr, sizeof(arr));
	if (!tmp2 && !check && tmp)
	{
		lst_add_back_env(env, lst_new_env("OLDPWD", tmp->value));
		check = 1;
	}
	else if (tmp2 && tmp)
		tmp2->value = tmp->value;
	if (tmp)
		tmp->value = ft_strdup_env(arr);
}

void	ft_set_path_for_env(t_env **env)
{
	static int	check;
	char		arr[PATH_MAX];
	t_env		*tmp;
	t_env		*tmp2;

	tmp = *env;
	tmp2 = *env;
	ft_look_for_pwd_env(&tmp, "PWD");
	ft_look_for_pwd_env(&tmp2, "OLDPWD");
	getcwd(arr, sizeof(arr));
	if (!tmp2 && !check && tmp)
	{
		lst_add_back_env(env, lst_new_env("OLDPWD", tmp->value));
		check = 1;
	}
	else if (tmp2 && tmp)
		tmp2->value = tmp->value;
	if (tmp)
		tmp->value = ft_strdup_env(arr);
}
