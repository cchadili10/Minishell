/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yessemna <yessemna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 04:12:59 by yessemna          #+#    #+#             */
/*   Updated: 2024/08/11 17:45:35 by yessemna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_findchar(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	putin_fd(int fd, char *line)
{
	int	i;

	i = 0;
	while (line && line[i])
	{
		write(fd, &line[i], 1);
		i++;
	}
	write(fd, "\n", 1);
}

void	search_in_env(char **ret, char **exp, t_env **envi)
{
	t_env	*tmp_env;
	int		found;

	tmp_env = *envi;
	found = 0;
	while (tmp_env)
	{
		if (ft_strcmp(*exp, tmp_env->key) == 0)
		{
			*ret = ft_srtjoin(*ret, ft_strdup(tmp_env->value));
			found = 1;
			break ;
		}
		tmp_env = tmp_env->next;
	}
	if (!found)
		*ret = "";
}

char	*heredoc_expand(char *line, t_env *envi)
{
	int		i;
	char	*ret;
	char	*exp;

	((1) && (ret = NULL, exp = NULL, i = 0));
	while (line[i])
	{
		while (line[i] == '\'' || line[i] == '\"')
			((1) && (ret = join_char(ret, line[i]), i++));
		if (line[i] == '$')
		{
			i++;
			while (line[i] && is_alnum(line[i]))
				((1) && (exp = join_char(exp, line[i]), i++));
			search_in_env(&ret, &exp, &envi);
		}
		else
			((1) && (ret = join_char(ret, line[i]), i++));
	}
	return (ret);
}

void	ft_here_doc(t_token *cmd, t_env *envi, int *red_in)
{
	t_token	*tmp;
	char	*line;
	int		fd_write;

	tmp = cmd;
	fd_write = open("/tmp/dog", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_write != -1)
		*red_in = fd_write;
	ft_signal();
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (line && ft_strlen(line) != 0)
			add_history(line);
		if (!ft_strcmp(line, tmp->key))
			break ;
		if (!(tmp->value == DBL_Q || tmp->value == SNGL_Q))
			line = heredoc_expand(line, envi);
		putin_fd(fd_write, line);
	}
	free(line);
	ft_exit_status(0, SET);
}
