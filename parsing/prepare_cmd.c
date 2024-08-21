/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 04:35:26 by yessemna          #+#    #+#             */
/*   Updated: 2024/08/21 22:07:11 by hchadili         ###   ########.fr       */
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
	int		i;
	int		j;

	i = -1;
	j = -1;
	if (*tmp && (*tmp)->value == CMD)
	{
		(*tmp)->value = VAR;
		arr = ft_split((*tmp)->key, 32, 9);
		while (arr[++i])
			*cmd_strs = dbl_join(*cmd_strs, arr[i]);
	}
	else
		*cmd_strs = dbl_join(*cmd_strs, (*tmp)->key);
}

void	short_hand(t_main_prepare_cmd *t, t_cmd **cmd)
{
	if (t->cmd_strs)
		lst_add_back_cmd(cmd, lst_new_cmd(t->cmd_strs, t->red_in, t->red_out));
	else
		close(t->red_in);
	if (!ttyname(0))
		ft_exit_herdog(1, SET);
	(dup2(t->std, 0), close(t->std), rl_catch_signals = 0);
	ft_signal(1);
}

void	main_prepare_cmd(t_token **tmp, t_cmd **cmd, t_env *envi)
{
	t_main_prepare_cmd	t;

	(signal(SIGINT, ft_herdoc), rl_catch_signals = 1);
	(1) && (t.red_in = 0, t.red_out = 1, t.cmd_strs = NULL, t.std = dup(0));
	while (*tmp && (*tmp)->value != PIPE)
	{
		find_node(envi, *tmp);
		join_nodes(tmp);
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
		if ((*tmp)->key == NULL)
			continue ;
		(split_in_cmd(&t.cmd_strs, tmp), *tmp = (*tmp)->next);
	}
	short_hand(&t, cmd);
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
