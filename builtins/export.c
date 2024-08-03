/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 17:53:16 by hchadili          #+#    #+#             */
/*   Updated: 2024/07/31 18:09:56 by hchadili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_print_export(t_export **export)
{
	t_export	*tmp1;

	tmp1 = *export;
	while (tmp1)
	{
		printf("declare -x %s=\"%s\"\n", tmp1->key, tmp1->value);
		tmp1 = tmp1->next;
	}
	ft_exit_status(0, SET);
}

void	ft_add_export_or_env(t_env **env, t_export **export, t_export_var *exp)
{
	if (ft_find_key(export, exp->key) == 0)
	{
		if (exp->value[0] || exp->update_ == 1)
		{
			lst_add_back_env(env, lst_new_env(exp->key, exp->value));
			insert_end(export, exp->key, exp->value);
		}
		else
			insert_end(export, exp->key, exp->value);
	}
	else
	{
		ft_replace_value_for_export(export, exp->key, exp->value, exp->update_);
		ft_replace_value_for_env(env, exp->key, exp->value, exp->update_);
	}
}

void	ft_add_var_to_env_export(t_env **env,
			t_export **export, t_export_var *exp)
{
	if (ft_find_key(export, exp->key))
		ft_add_to_env_export(export, env, exp->key, exp->value);
	else
	{
		if (exp->value[0] || exp->update_ == 1)
		{
			lst_add_back_env(env, lst_new_env(exp->key, exp->value));
			insert_end(export, exp->key, exp->value);
		}
		else
			insert_end(export, exp->key, exp->value);
	}
}

void	ft_export_add(t_cmd *cmnd, t_env **env, t_export **export)
{
	t_export_var	exp;
	int				x;

	x = 1;
	ft_set_zero_to_struct(&exp);
	while (cmnd->cmds[x])
	{
		exp.start = ft_count_eq(cmnd->cmds[x], 1, &exp) + 1;
		exp.key = ft_substr_env(cmnd->cmds[x], 0,
				(ft_count_eq(cmnd->cmds[x], 0, &exp)));
		exp.value = ft_substr_env(cmnd->cmds[x],
				exp.start, (ft_strlen(cmnd->cmds[x]) - exp.start));
		if (ft_check_key(exp.key) == 0)
		{
			print_error("export: not valid in this context:");
			ft_exit_status(1, SET);
			return ;
		}
		else if (exp.append == 0)
			ft_add_export_or_env(env, export, &exp);
		else
			ft_add_var_to_env_export(env, export, &exp);
		((1) && (exp.append = 0, exp.update_ = 0, x++));
		ft_exit_status(1, SET);
	}
}

void	ft_export(t_cmd *cmnd, t_env **env, t_export **export)
{
	int	x;

	x = 0;
	while (cmnd->cmds[x])
		x++;
	if (x == 1)
		ft_print_export(export);
	else
	{
		ft_export_add(cmnd, env, export);
		ft_sort_export(export);
	}
}
