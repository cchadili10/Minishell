/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 21:09:41 by hchadili          #+#    #+#             */
/*   Updated: 2024/08/23 19:10:55 by hchadili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_count_arg(char **str)
{
	int	x;

	x = 0;
	while (str[x])
		x++;
	return (x);
}

void	ft_close_fd(t_cmd **cmnds)
{
	t_cmd	*tmp;

	tmp = *cmnds;
	while (tmp)
	{
		if (tmp->redir_in != 0)
			close(tmp->redir_in);
		if (tmp->redir_out != 1)
			close(tmp->redir_out);
		tmp = tmp->next;
	}
}

void	ft_execution(t_cmd **cmnds, t_env **env)
{
	char			**arr_env;
	static t_exp	*export = NULL;

	if (!cmnds || !*cmnds || !env || !*env)
		return ;
	arr_env = ft_get_charenv(env);
	if (!export)
		ft_fill_export(&export, env);
	if (ft_count_cmnds(cmnds) == 1)
		ft_excute_one(cmnds, &export, arr_env, env);
	else
		ft_excute(cmnds, &export, env);
	ft_close_fd(cmnds);
}
