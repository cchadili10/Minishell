/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 04:35:26 by yessemna          #+#    #+#             */
/*   Updated: 2024/08/08 15:07:16 by hchadili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_prepare(char **cmd_strs, t_token **tmp, t_env *envi, t_cmd **cmd)
{
	int red_in;
	int red_out;
	char **arr;
	int i;

	red_in = 0;
	red_out = 1;
	cmd_strs = NULL;
	while ((*tmp) && (*tmp)->value != PIPE)
	{
		if ((!(*tmp)->next && (*tmp)->value == SPC) || (*tmp)->key == NULL)
		{
			(*tmp) = (*tmp)->next;
			continue ;
		}
		if (((*tmp) && (*tmp)->next && (*tmp)->value == SPC) || (*tmp)->key == NULL)
			(*tmp) = (*tmp)->next;
		if (((*tmp) && (*tmp)->value == PIPE) || (*tmp)->key == NULL)
			continue ;
		if ((*tmp)->next && (*tmp)->value == IN)
		{
			(*tmp) = (*tmp)->next;
			if ((*tmp) && (*tmp)->value == SPC)
				(*tmp) = (*tmp)->next;
			red_in = open((*tmp)->key, O_RDONLY);
			if (red_in < 0)
				return(perror((*tmp)->key), 0);
			(*tmp) = (*tmp)->next;
			continue ;
		}else if((*tmp)->next && (*tmp)->value == OUT)
		{
			if(red_out != 1)
				close(red_out);
			(*tmp) = (*tmp)->next;
			if ((*tmp) && (*tmp)->value == SPC)
				(*tmp) = (*tmp)->next;
			if(!(*tmp)->key)
			{
				printf("bash: %s: ambiguous redirect\n", (*tmp)->copy_key);
				ft_exit_status(1, SET);
				return (0);	
			}
			red_out = open((*tmp)->key, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (red_out < 0)
				return(perror((*tmp)->key), 0);
			(*tmp) = (*tmp)->next;
			continue ;
		}else if((*tmp)->next && (*tmp)->value == APPEND)
		{
			(*tmp) = (*tmp)->next;
			if ((*tmp) && (*tmp)->value == SPC)
				(*tmp) = (*tmp)->next;
			red_out = open((*tmp)->key, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (red_out < 0)
				return(perror((*tmp)->key), 0);
			(*tmp) = (*tmp)->next;
			continue ;
		}else if ((*tmp)->next && (*tmp)->value == HEREDOC)
		{
			(*tmp) = (*tmp)->next;
			if ((*tmp) && (*tmp)->value == SPC)
				(*tmp) = (*tmp)->next;
			ft_here_doc((*tmp), envi, &red_in);
			close(red_in);
			red_in = open("/(*tmp)/dog", O_RDONLY);
			if (red_in < 0)
				return(perror((*tmp)->key), 0);
			(*tmp) = (*tmp)->next;
			continue ;
		}
		if((*tmp) && (*tmp)->value == EXPND)
		{
			(*tmp)->value = CMD;
			arr = ft_split((*tmp)->key, ' '); 
			i = -1;
			while(arr[++i])
				cmd_strs = dbl_join(cmd_strs, arr[i]);
		}
		else
			cmd_strs = dbl_join(cmd_strs, (*tmp)->key);
		(*tmp) = (*tmp)->next;
	}
	 if (cmd_strs)
            lst_add_back_cmd(cmd, lst_new_cmd(cmd_strs, red_in, red_out));
	return (1);
}

int prepare_cmd(t_token *list, t_cmd **cmd, t_env *envi)
{
    t_token (*tmp);
    char **cmd_strs;
	
	tmp = list;
    while (tmp)
    {
        cmd_strs = NULL;
        if (tmp && tmp->value == SPC)
                tmp = tmp->next;
        if(!ft_prepare(cmd_strs, &tmp, envi, cmd))
			return(0);
        if (tmp)
            tmp = tmp->next;
    }
    // print_cmd(cmd);
    return (1);
}
