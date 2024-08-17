/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_node_.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yessemna <yessemna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 01:29:48 by yessemna          #+#    #+#             */
/*   Updated: 2024/08/17 21:46:35 by yessemna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	core_var(t_env *envi, t_token **tmp, int found)
{
	t_env	*tmp_env;

	tmp_env = envi;
	while (tmp_env)
	{
		if (ft_strcmp((*tmp)->key + 1, tmp_env->key) == 0)
		{
			(*tmp)->key = tmp_env->value;
			(*tmp)->value = CMD;
			found = 1;
			break ;
		}
		tmp_env = tmp_env->next;
	}
	if (!found)
	{
		(*tmp)->key = NULL;
		tmp_env = envi;
	}
}

void	core_q_helper(char **line, t_token **tmp, t_env *tmp_env, int *found)
{
	int	i;

	i = 0;
	while (tmp_env->value[i])
		(*line) = join_char((*line), tmp_env->value[i++]);
	(*tmp)->value = CMD;
	*found = 1;
}

int	set_end_of_word(char *key, int *x)
{
	int	arr;

	arr = 0;
	while ((key[*x] && is_alnum(key[*x])) || key[*x] == '?')
	{
		if (key[*x] == '?')
		{
			(*x)++;
			break ;
		}
		(*x)++;
	}
	arr = (*x) - 1;
	return (arr);
}

void	core_dbl_q(t_token **tmp, char **line, int *x, t_env **envi)
{
	char	*var;
	int		arr[2];
	int		found;
	t_env	*tv;

	((1) && (arr[0] = *x, arr[1] = 0, found = 0, tv = *envi, arr[0] = ++(*x)));
	arr[1] = set_end_of_word((*tmp)->key, x);
	var = cpy_part((*tmp)->key + arr[0], arr[0], arr[1]);
	if (ft_strcmp(var, "?") == 0)
	{
		(*line) = ft_srtjoin((*line), ft_itoa(ft_exit_status(0, GET)));
		found = 1;
	}
	while (tv)
	{
		if (ft_strcmp(var, tv->key) == 0)
		{
			core_q_helper(line, tmp, tv, &found);
			break ;
		}
		tv = tv->next;
	}
	if (!found)
		(*line) = "";
	tv = *envi;
}

void	handle_expand(t_env *envi, t_token **tmp, int found)
{
	t_env	*tmp_env;
	int		x;
	char	*line;

	((1) && (x = 0, line = "", tmp_env = envi));
	if ((*tmp)->value == VAR)
		core_var(envi, tmp, found);
	else if ((*tmp)->value == DBL_Q)
	{
		tmp_env = envi;
		while ((*tmp)->key[x])
		{
			if ((*tmp)->key[x] != '$'
				|| ((*tmp)->key[x] == '$' && (*tmp)->key[x + 1] == '\'')
				|| ((*tmp)->key[x] == '$' && (*tmp)->key[x + 1] == '\0')
				|| ((*tmp)->key[x] == '$' && (*tmp)->key[x + 1] == '$'))
			{
				line = join_char(line, (*tmp)->key[x]);
				x++;
			}
			else
				core_dbl_q(tmp, &line, &x, &tmp_env);
		}
		(*tmp)->key = line;
	}
}
