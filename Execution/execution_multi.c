/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_multi.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 10:10:52 by hchadili          #+#    #+#             */
/*   Updated: 2024/08/18 20:07:18 by hchadili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_set_zero(t_exection_var *exp)
{
	exp->arr_join = NULL;
	exp->arr_phat = NULL;
	exp->env = NULL;
	exp->id = 0;
	exp->std_d = 0;
	exp->p[0] = 0;
	exp->p[1] = 0;
	exp->flag = 0;
}

void	ft_excute(t_cmd **cmnds, t_exp **export, t_env **node_env)
{
	t_cmd			*tmp;
	int				num;
	t_exection_var	exp;

	ft_set_zero(&exp);
	(1) && (num = ft_count_cmnds(cmnds), tmp = *cmnds);
	exp.env = ft_get_charenv(node_env);
	exp.arr_phat = ft_split(ft_look_for_paht(node_env), ':', 9);
	while (tmp && num)
	{
		if (num == ft_count_cmnds(cmnds))
			ft_first_cmnd(tmp, node_env, export, &exp);
		else if (num != 1)
			ft_mid_cmnd(tmp, node_env, export, &exp);
		else if (num == 1)
			ft_last_cmnd(tmp, node_env, export, &exp);
		if (tmp->redir_out != 1)
			close(tmp->redir_out);
		if (tmp->redir_in != 0)
			close(tmp->redir_in);
		((1) && (tmp = tmp->next, num--));
	}
	((1) && (close(exp.p[0]), close(exp.p[1]), num = ft_count_cmnds(cmnds)));
	while (num--)
		wait(NULL);
}
