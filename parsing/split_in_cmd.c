/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_in_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yessemna <yessemna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 03:39:01 by yessemna          #+#    #+#             */
/*   Updated: 2024/09/24 03:39:10 by yessemna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	split_in_cmd(char ***cmd_strs, t_token **tmp)
{
	char	**arr;
	int		i;
	int		j;

	i = -1;
	j = -1;
	if ((*tmp && (*tmp)->value == CMD))
	{
		(*tmp)->value = VAR;
		arr = ft_split((*tmp)->key, 32, 9);
		if (!arr)
			return ;
		while (arr[++i])
			*cmd_strs = dbl_join(*cmd_strs, arr[i]);
	}
	else
		*cmd_strs = dbl_join(*cmd_strs, (*tmp)->key);
}
