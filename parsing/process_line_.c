/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_line_.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yessemna <yessemna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 15:19:32 by hchadili          #+#    #+#             */
/*   Updated: 2024/08/26 22:29:20 by yessemna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_red(char c)
{
	return (c == '<' || c == '>');
}
int is_redir(int n)
{
	return (n == IN || n == OUT || n == APPEND || n == HEREDOC);
}

void	spc_pipe_red(char *line, t_token **list, int *i)
{
	if (line[*i] == '|')
		lst_add_back(list, lst_new(ft_substr(line, (*i)++, 1), PIPE));
	else if (is_space(line[*i]))
	{
		while (is_space(line[(*i) + 1]))
			(*i)++;
		lst_add_back(list, lst_new(ft_substr(line, (*i)++, 1), SPC));
	}
	else if (line[*i] == '<')
	{
		if (line[(*i) + 1] == '<')
			lst_add_back(list, lst_new(ft_substr(line, (*i)++, 2), HEREDOC));
		else
			lst_add_back(list, lst_new(ft_substr(line, *i, 1), IN));
		(*i)++;
	}
	else if (line[*i] == '>')
	{
		if (line[(*i) + 1] == '>')
			lst_add_back(list, lst_new(ft_substr(line, (*i)++, 2), APPEND));
		else
			lst_add_back(list, lst_new(ft_substr(line, *i, 1), OUT));
		(*i)++;
	}
}

int	single_quote(char *line, t_token **list, int *i)
{
	int	end;

	end = 0;
	if (line[*i] == '$')
		(*i)++;
	if (line[(*i) + 1] == '\'')
	{
		lst_add_back(list, lst_new("", SNGL_Q));
		(*i)++;
	}
	else
	{
		end = find_char(line + (*i) + 1, '\'');
		if (end)
			lst_add_back(list, lst_new(ft_substr(line, (*i) + 1, end), SNGL_Q));
		else
			return (ft_exit_status(122, SET)
				, print_error("Error: missing single quote"), 0);
		(*i) += end + 1;
	}
	(*i)++;
	return (1);
}

int	double_quotes(char *line, t_token **list, int *i)
{
	int	end;

	end = 0;
	if (line[*i] == '$' && line[(*i) + 1] == '?')
		token_exit_status(&line, list, i);
	if (line[*i] == '$')
		(*i)++;
	if (line[*i + 1] == '\"')
	{
		lst_add_back(list, lst_new("", DBL_Q));
		(*i) += 1;
	}
	else
	{
		end = find_char(line + (*i) + 1, '\"');
		if (end)
			lst_add_back(list, lst_new(ft_substr(line, (*i) + 1, end), DBL_Q));
		else
			return (print_error("Error: missing double quote"), 0);
		(*i) += end + 1;
	}
	(*i)++;
	return (1);
}

int	quotes(char *line, t_token **list, int *i)
{
	if (line[*i] == '\'' || (line[*i] == '$' && line[(*i) + 1] == '\''))
	{
		if (!single_quote(line, list, i))
			return (0);
	}
	else if (line[*i] == '\"' || (line[*i] == '$' && line[(*i) + 1] == '\"'))
	{
		if (!double_quotes(line, list, i))
			return (0);
	}
	return (1);
}
