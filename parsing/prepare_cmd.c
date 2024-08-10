/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 04:35:26 by yessemna          #+#    #+#             */
/*   Updated: 2024/08/10 17:35:48 by hchadili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	split_in_cmd(char ***cmd_strs, t_token **tmp)
{
	char	**arr;
	char	**sub;
	int		i;
	int		j;

	i = -1;
	j = -1;
	if (*tmp && (*tmp)->value == EXPND)
	{
		(*tmp)->value = CMD;
		arr = ft_split((*tmp)->key, ' ');
		while (arr[++i])
		{
			if (find_char(arr[i], '\t'))
			{
				sub = ft_split(arr[i], '\t');
				while (sub[++j])
					*cmd_strs = dbl_join(*cmd_strs, sub[j]);
			}
			else
				*cmd_strs = dbl_join(*cmd_strs, arr[i]);
		}
	}
	else
		*cmd_strs = dbl_join(*cmd_strs, (*tmp)->key);
}

void	main_prepare_cmd(t_token **tmp, t_cmd **cmd, t_env *envi)
{
	char	**cmd_strs;
	int		red_in;
	int		red_out;

	((1) && (red_in = 0, red_out = 1, cmd_strs = NULL));
	while (*tmp && (*tmp)->value != PIPE)
	{
		if ((!(*tmp)->next && (*tmp)->value == SPC) || (*tmp)->key == NULL)
		{
			*tmp = (*tmp)->next;
			continue ;
		}
		if ((*tmp && (*tmp)->next && (*tmp)->value == SPC)
			|| (*tmp)->key == NULL)
			*tmp = (*tmp)->next;
		if ((*tmp && (*tmp)->value == PIPE) || (*tmp)->key == NULL)
			continue ;
		if (handle_redir(tmp, &red_in, &red_out, envi))
			continue ;
		split_in_cmd(&cmd_strs, tmp);
		*tmp = (*tmp)->next;
	}
	if (cmd_strs)
		lst_add_back_cmd(cmd, lst_new_cmd(cmd_strs, red_in, red_out));
}

int	prepare_cmd(t_token *list, t_cmd **cmd, t_env *envi)
{
	t_token	*tmp;

	tmp = list;
	while (tmp)
	{
		if (tmp && tmp->value == SPC)
			tmp = tmp->next;
		main_prepare_cmd(&tmp, cmd, envi);
		if (tmp)
			tmp = tmp->next;
	}
	return (1);
}
