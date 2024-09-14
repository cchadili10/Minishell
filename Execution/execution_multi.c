/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_multi.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 10:10:52 by hchadili          #+#    #+#             */
/*   Updated: 2024/09/14 20:00:13 by hchadili         ###   ########.fr       */
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
	exp->status = 0;
	exp->pids = NULL;
	exp->cont = 0;
	exp->num_cmnd = 0;
}

void	ft_set_exp(t_exection_var *exp, t_env **node_env)
{
	exp->env = ft_get_charenv(node_env);
	exp->arr_phat = ft_split(ft_look_for_paht(node_env), ':', 9);
	exp->pids = g_malloc((exp->num_cmnd * sizeof(int)), MALLOC);
}

void	ft_excute(t_cmd **cmnds, t_exp **export, t_env **node_env)
{
	t_cmd			*tmp;
	t_exection_var	exp;

	ft_set_zero(&exp);
	(1) && (exp.num_cmnd = ft_count_cmnds(cmnds), tmp = *cmnds);
	ft_set_exp(&exp, node_env);
	if (!exp.pids)
		return ;
	while (tmp && exp.num_cmnd)
	{
		if (exp.num_cmnd == ft_count_cmnds(cmnds))
			ft_first_cmnd(tmp, node_env, export, &exp);
		else if (exp.num_cmnd != 1)
			ft_mid_cmnd(tmp, node_env, export, &exp);
		else if (exp.num_cmnd == 1)
			ft_last_cmnd(tmp, node_env, export, &exp);
		((1) && (tmp = tmp->next, exp.num_cmnd--));
	}
	((1) && (close(exp.p[0]), close(exp.p[1]), exp.num_cmnd = 0));
	while (exp.num_cmnd < exp.cont)
		waitpid(exp.pids[exp.num_cmnd++], &exp.status, 0);
	ft_exit_status(WEXITSTATUS(exp.status), SET);
}
