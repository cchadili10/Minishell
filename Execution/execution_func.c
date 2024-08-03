/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_func.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 10:45:31 by hchadili          #+#    #+#             */
/*   Updated: 2024/08/03 17:35:49 by hchadili         ###   ########.fr       */
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

void	ft_fill_export(t_export **export, t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		insert_end(export, tmp->key, tmp->value);
		tmp = tmp->next;
	}
	ft_sort_export(export);
}

char	*ft_get_path(char **arr_phat, char *first_cmnd)
{
	char	*arr_join_one;
	char	*arr_join;
	int		x;
	int		res;

	x = -1;
	if (!arr_phat)
		return (NULL);
	while (arr_phat[++x])
	{
		res = access(first_cmnd, F_OK | X_OK);
		if (res == 0)
			return (first_cmnd);
		else
		{
			arr_join_one = ft_srtjoin(arr_phat[x], "/");
			arr_join = ft_srtjoin(arr_join_one, first_cmnd);
			res = access(arr_join, F_OK | X_OK);
			if (res == 0)
				break ;
			else if (res == -1 && !arr_phat[x + 1])
				return (NULL);
		}
	}
	return (arr_join);
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
		arr_joined = ft_srtjoin(tmp->key, "=");
		arr[y] = ft_srtjoin(arr_joined, tmp->value);
		y++;
		tmp = tmp->next;
	}
	arr[y] = NULL;
	return (arr);
}
