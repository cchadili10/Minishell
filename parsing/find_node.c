/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 21:39:25 by yessemna          #+#    #+#             */
/*   Updated: 2024/09/14 19:59:32 by hchadili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fill_line(t_token **tmp, char **line, int *x)
{
	if ((*tmp)->key[*x] == '$' && (*tmp)->key[(*x) + 1] == '$')
	{
		while ((*tmp)->key[(*x)] == '$')
			(*line) = join_char((*line), (*tmp)->key[(*x)++]);
	}
	else
		(*line) = join_char((*line), (*tmp)->key[(*x)++]);
}

void	check_if_hd(t_token *list, int *flag)
{
	t_token	*tmp;

	tmp = list;
	while (tmp)
	{
		if (tmp->value == HEREDOC)
		{
			*flag = 1;
			break ;
		}
		tmp = tmp->next;
	}
}

void	find_node(t_env *envi, t_token *list)
{
	t_token	*tmp;
	t_token	*tmp2;
	int		found;
	int		flag;

	flag = 0;
	tmp = list;
	tmp2 = list;
	found = 0;
	check_if_hd(list, &flag);
	if (tmp && tmp->value != HEREDOC)
	{
		while (tmp)
		{
			found = 0;
			if (flag == 0 && (tmp->value == VAR || tmp->value == DBL_Q))
				handle_expand(envi, &tmp, found);
			tmp = tmp->next;
		}
	}
}

char	*join_char(char *str, char c)
{
	char	*out;
	int		i;
	int		len;

	i = 0;
	if (!str)
		str = ft_strdup("");
	len = ft_strlen(str);
	out = g_malloc(len + 2, MALLOC);
	while (str[i] != '\0')
	{
		out[i] = str[i];
		i++;
	}
	out[i] = c;
	out[i + 1] = '\0';
	return (out);
}
