/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 04:35:26 by yessemna          #+#    #+#             */
/*   Updated: 2024/08/15 21:39:38 by hchadili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	token_exit_status(char **line, t_token **list, int *i)
{
	if (*line[*i] == '$' && *line[(*i) + 1] == '?')
	{
		lst_add_back(list, lst_new("$?", DBL_Q));
		(*i) += 2;
	}
}

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
		(*tmp)->value = VAR;
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
	t_main_prepare_cmd	t;
	int					std;

	signal(SIGINT, ft_herdoc);
	rl_catch_signals = 1;
	(1) && (t.red_in = 0, t.red_out = 1, t.cmd_strs = NULL, std = dup(0));
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
		if (handle_redir(tmp, &t.red_in, &t.red_out, envi))
			continue ;
		(split_in_cmd(&t.cmd_strs, tmp), *tmp = (*tmp)->next);
	}
	if (t.cmd_strs)
		lst_add_back_cmd(cmd, lst_new_cmd(t.cmd_strs, t.red_in, t.red_out));
	else
		close(t.red_in);
	if (!ttyname(0))
		ft_exit_herdog(1, SET);
	(dup2(std, 0), close(std), rl_catch_signals = 0);
	ft_signal();
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
