/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 17:53:16 by hchadili          #+#    #+#             */
/*   Updated: 2024/09/17 21:41:38 by hchadili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_print_export(t_exp **export)
{
	t_exp	*tmp1;

	tmp1 = *export;
	while (tmp1)
	{
		printf("declare -x %s", tmp1->key);
		if (tmp1->value)
			printf("=\"%s\"\n", tmp1->value);
		else
			printf("\n");
		tmp1 = tmp1->next;
	}
	ft_exit_status(0, SET);
}

void	ft_add_export_or_env(t_env **env, t_exp **export, t_export_var *exp)
{
	if (ft_find_key(export, exp->key) == 0)
	{
		if (exp->value[0] || exp->update_ == 1)
		{
			lst_add_back_env(env, lst_new_env(exp->key, exp->value));
			insert_end(export, exp->key, exp->value);
		}
		else
			insert_end(export, exp->key, NULL);
	}
	else
	{
		ft_replace_value_for_export(export, exp->key, exp->value, exp->update_);
		ft_replace_value_for_env(env, exp->key, exp->value, exp->update_);
	}
}

void	ft_add_var_to_env_export(t_env **env,
			t_exp **export, t_export_var *exp)
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

void	ft_export_add(t_cmd *cmnd, t_env **env, t_exp **export)
{
	t_export_var	exp;
	int				x;
	int				check;

	(1) && (x = 1, check = 0);
	ft_set_zero_to_struct(&exp);
	while (cmnd->cmds[x])
	{
		exp.start = ft_count_eq(cmnd->cmds[x], 1, &exp) + 1;
		exp.key = ft_substr_env(cmnd->cmds[x], 0,
				(ft_count_eq(cmnd->cmds[x], 0, &exp)));
		exp.value = ft_substr_env(cmnd->cmds[x],
				exp.start, (ft_strlen(cmnd->cmds[x]) - exp.start));
		if (ft_check_key(exp.key) == 0)
			ft_display_erorr_export(cmnd->cmds[x], &check);
		else if (exp.append == 0)
			ft_add_export_or_env(env, export, &exp);
		else
			ft_add_var_to_env_export(env, export, &exp);
		((1) && (exp.append = 0, exp.update_ = 0, x++));
	}
	if (check == 0)
		ft_exit_status(0, SET);
}

int ft_look_for_spaice(char *str)
{
	int	x;

	x = 0;
	while (str[x])
	{
		if(str[x] == ' ')
			return 1;
		x++;
	}
	return 0;
}
void	ft_export(t_cmd *cmnd, t_env **env, t_exp **export)
{
	int	x;
	char **str;
	char **str2;

	x = 0;
	str = NULL;
	str2 = NULL;
	while (cmnd->cmds[x])
	{
		// printf("++%s++\n",cmnd->cmds[x]);
		// if(ft_look_for_spaice(cmnd->cmds[x]))
		// {
		// 	str2 = ft_split(cmnd->cmds[x], ' ', '\t');
		// 	if (!str)
		// 		return ;
		// 	while (*str2)
		// 	{
		// 		str = dbl_join(str, *str2);
		// 		str2++;
		// 	}
		// }
		// else
		// 	str = dbl_join(str, cmnd->cmds[x]);
		x++;
	}
	// x = 0;
	// while (str[x])
	// {
	// 	printf("++%s++\n",str[x++]);
	// }
	
	if (x == 1)
		ft_print_export(export);
	else
	{
		ft_export_add(cmnd, env, export);
		ft_sort_export(export);
	}
}
