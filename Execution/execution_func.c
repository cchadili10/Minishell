/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_func.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 10:45:31 by hchadili          #+#    #+#             */
/*   Updated: 2024/08/19 17:29:18 by hchadili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_count_cmnds(t_cmd **cmnds)
{
	int		x;
	t_cmd	*tmp;

	x = 0;
	tmp = *cmnds;
	while (tmp)
	{
		x++;
		tmp = tmp->next;
	}
	return (x);
}

char	*ft_look_for_paht(t_env **env)
{
	t_env	*tmp2;

	tmp2 = *env;
	while (tmp2)
	{
		if (ft_strcmp(tmp2->key, "PATH") == 0)
			break ;
		tmp2 = tmp2->next;
	}
	if (tmp2)
		return (tmp2->value);
	return (NULL);
}

void	ft_fill_export(t_exp **export, t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "_") != 0)
			insert_end(export, tmp->key, tmp->value);
		tmp = tmp->next;
	}
	insert_end(export, "OLDPWD", NULL);
	ft_sort_export(export);
}

char	*ft_get_path(char **arr_phat, char *first_cmnd, t_exection_var *exp)
{
	struct stat	resp;

	if (stat(first_cmnd, &resp) == 0)
	{
		if (S_ISDIR(resp.st_mode))
			return (ft_check_cmd_erorrs(first_cmnd, exp, 3));
	}
	if (first_cmnd[0] == '/' || (first_cmnd[0] == '.' && first_cmnd[1] == '/'))
		return (ft_check_cmd_erorrs(first_cmnd, exp, 1));
	if (first_cmnd[ft_strlen(first_cmnd) - 1] == '/')
		return (ft_check_cmd_erorrs(first_cmnd, exp, 2));
	if (access(first_cmnd, F_OK) == 0)
	{
		if (access(first_cmnd, X_OK) == 0)
			return (first_cmnd);
		else
			exp->flag = 6;
	}
	return (ft_loop_for_path(arr_phat, first_cmnd, exp));
}

char	**ft_get_charenv(t_env **env)
{
	t_env	*tmp;
	int		x;
	int		y;
	char	*arr_joined;
	char	**arr;

	((1) && (x = 0, y = 0, tmp = *env));
	while (tmp)
	{
		x++;
		tmp = tmp->next;
	}
	tmp = *env;
	arr = g_malloc(((x + 1) * sizeof(char *)), MALLOC);
	if (!arr)
		return (NULL);
	while (y < x && tmp)
	{
		arr_joined = ft_strjoin_(tmp->key, "=");
		arr[y] = ft_strjoin_(arr_joined, tmp->value);
		y++;
		tmp = tmp->next;
	}
	arr[y] = NULL;
	return (arr);
}
