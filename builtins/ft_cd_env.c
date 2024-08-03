/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 07:29:29 by hchadili          #+#    #+#             */
/*   Updated: 2024/08/03 09:44:59 by hchadili         ###   ########.fr       */
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
	t_env	*tmp;
	t_env	*tmp2;

	tmp = *env;
	tmp2 = *env;
	ft_look_for_pwd_env(&tmp, "HOME");
	if (chdir(tmp->value))
	{
		perror("chdir erorr");
		ft_exit_status(1, SET);
		return ;
	}
	tmp = *env;
	ft_look_for_pwd_env(&tmp, "PWD");
	ft_look_for_pwd_env(&tmp2, "OLDPWD");
	ft_exit_status(0, SET);
	if (tmp2 && tmp)
		tmp2->value = tmp->value;
	if (tmp)
		tmp->value = ft_strdup_env(getcwd(0, 0));
}

void	ft_set_path_for_env(t_env **env)
{
	t_env	*tmp;
	t_env	*tmp2;
	char	arr[PATH_MAX];

	tmp = *env;
	tmp2 = *env;
	ft_look_for_pwd_env(&tmp, "PWD");
	ft_look_for_pwd_env(&tmp2, "OLDPWD");
	getcwd(arr, sizeof(arr));
	if (tmp2 && tmp)
		tmp2->value = tmp->value;
	if (tmp)
		tmp->value = ft_strdup_env(arr);
}
