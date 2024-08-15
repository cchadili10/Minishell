/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 07:29:48 by hchadili          #+#    #+#             */
/*   Updated: 2024/08/15 21:59:34 by hchadili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_look_for_pwd_export(t_exp **tmp, char *str)
{
	while (*tmp)
	{
		if (strcmp((*tmp)->key, str) == 0)
			break ;
		*tmp = (*tmp)->next;
	}
}

int	ft_go_to_home_export(t_exp **export)
{
	t_exp	*tmp;
	t_exp	*tmp2;

	tmp = *export;
	tmp2 = *export;
	ft_look_for_pwd_export(&tmp, "HOME");
	if (!tmp)
	{
		ft_printf("Minishell: cd: HOME not set\n");
		return (0);
	}
	if (chdir(tmp->value))
	{
		ft_exit_status(1, SET);
		return (0);
	}
	tmp = *export;
	ft_look_for_pwd_export(&tmp, "PWD");
	ft_look_for_pwd_export(&tmp2, "OLDPWD");
	ft_exit_status(0, SET);
	if (tmp2 && tmp)
		tmp2->value = tmp->value;
	if (tmp)
		tmp->value = ft_strdup_env(getcwd(0, 0));
	return (1);
}

int	ft_set_path_for_export(t_exp **export, t_cmd *cmnd, int x)
{
	t_exp	*tmp;
	t_exp	*tmp2;
	char	arr[PATH_MAX];

	tmp = *export;
	tmp2 = *export;
	ft_look_for_pwd_export(&tmp, "PWD");
	ft_look_for_pwd_export(&tmp2, "OLDPWD");
	if (chdir(cmnd->cmds[1]) == -1 || x != 2)
	{
		perror("chdir erorr");
		ft_exit_status(1, SET);
		return (0);
	}
	if (!getcwd(0, 0))
	{
		ft_printf("cd: error retrieving current directory: getcwd: cannot ");
		ft_printf("access parent directories: No such file or directory\n");
	}
	getcwd(arr, sizeof(arr));
	if (tmp2 && tmp)
		tmp2->value = tmp->value;
	if (tmp)
		tmp->value = ft_strdup_env(arr);
	return (1);
}
