/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_multi.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 10:10:52 by hchadili          #+#    #+#             */
/*   Updated: 2024/08/03 13:41:59 by hchadili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"







void ft_excute(t_cmd **cmnds, t_export **export, t_env **node_env)
{
	t_cmd *tmp = *cmnds;
	int p[2];
	int num_cmnd = ft_count_cmnds(cmnds);

	while (tmp && num_cmnd)
	{
		if (num_cmnd == ft_count_cmnds(cmnds)) // first cmnd
			ft_first_cmnd(tmp, node_env, export, p);
		else if (num_cmnd != 1) // mid cmnd
			ft_mid_cmnd(tmp, node_env, export, p);
		else if (num_cmnd == 1) // last cmnd
			ft_last_cmnd(tmp, node_env, export, p);
		num_cmnd--;
		if (tmp->redir_out != 1)
			close(tmp->redir_out);
		tmp = tmp->next;
	}
	close(p[0]);
	close(p[1]);
	num_cmnd = ft_count_cmnds(cmnds);
	while (num_cmnd)
	{
		wait(NULL);
		num_cmnd--;
	}
}
