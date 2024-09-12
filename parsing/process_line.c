/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yessemna <yessemna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 14:28:30 by hchadili          #+#    #+#             */
/*   Updated: 2024/09/12 16:14:58 by yessemna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// ---------> variables
void	handle_var(char *line, t_token **list, int *i)
{
	int	start;
	int	end;

	start = 0;
	end = 0;
	if (!is_alnum(line[(*i) + 1]))
		lst_add_back(list, lst_new(ft_substr(line, (*i)++, 1), CMD));
	else
	{
		start = *i;
		(*i)++;
		while (is_alnum(line[*i]) && !is_special(line[*i]))
		{
			if (!is_alnum(line[(*i) + 1]))
				break ;
			(*i)++;
		}
		end = (*i) - start;
		lst_add_back(list, lst_new(ft_substr(line, start, end + 1), VAR));
		(*i)++;
	}
}

void	variables(char *line, t_token **list, int *i)
{
	if (line[*i] == '$' && (line[(*i) + 1] >= '0' && line[(*i) + 1] <= '9'))
	{
		lst_add_back(list, lst_new(ft_substr(line, (*i)++, 2), VAR));
		(*i)++;
	}
	else if (line[*i] == '$' && line[(*i) + 1] == '$')
	{
		lst_add_back(list, lst_new(ft_substr(line, (*i)++, 2), DBL_VAR));
		(*i)++;
	}
	else if (line[*i] == '$' && line[(*i) + 1] == '?')
	{
		lst_add_back(list, lst_new(ft_substr(line, (*i)++, 2), EXIT_STATUS));
		(*i)++;
	}
	else if (line[*i] == '$')
		handle_var(line, list, i);
}

void	handl_cmd(char *line, t_token **list, int *i)
{
	int	start;
	int	end;

	start = *i;
	while (line[*i] && !is_special(line[*i]))
	{
		if (is_special(line[(*i) + 1]))
			break ;
		(*i)++;
	}
	end = (*i) - start;
	lst_add_back(list, lst_new(ft_substr(line, start, end + 1), CMD));
	(*i)++;
}

void	expand_exit_status(t_token **list)
{
	t_token	*tmp;

	tmp = *list;
	while (tmp)
	{
		if (tmp->value == EXIT_STATUS)
			tmp->value = CMD;
		tmp = tmp->next;
	}
}

int	processline(char *line, t_token **list)
{
	int	i;

	i = 0;
	if (line == NULL)
		return (0);
	while (i < ft_strlen(line) && line[i] != '\0')
	{
		if (is_space(line[i]) || is_red(line[i]) || line[i] == '|')
			spc_pipe_red(line, list, &i);
		else if (line[i] == '\'' || (line[i] == '$' && line[i + 1] == '\'')
			|| line[i] == '\"' || (line[i] == '$' && line[i + 1] == '\"'))
		{
			if (!quotes(line, list, &i))
				return (0);
		}
		else if (line[i] == '$')
			variables(line, list, &i);
		else
			handl_cmd(line, list, &i);
	}
	expand_exit_status(list);
	return (1);
}
