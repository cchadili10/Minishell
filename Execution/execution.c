/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 21:09:41 by hchadili          #+#    #+#             */
/*   Updated: 2024/07/23 14:42:21 by hchadili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../minishell.h"
#include <limits.h>

void ft_fill_export(t_export **export, t_env **env)
{
	t_env *tmp = *env;

	while (tmp)
	{
		insert_end(export,tmp->key,tmp->value);
		tmp = tmp->next;
	}
}

int ft_count_cmnds(t_cmd **cmnds)
{
	int x;
	t_cmd *tmp;

	x = 0;
	tmp = *cmnds;
	while (tmp)
	{
		x++;
		tmp = tmp->next;
	}
	return x;
}

int	ft_check_cmnd(t_cmd *cmnd)
{
	static char *builts[] = {"env","pwd","cd","echo", "export", "unset", "exit", NULL};
	int x = 0;
	t_cmd *tmp;

	tmp = cmnd;	
	// printf("%s\n",tmp->cmds[0]);
	while (builts[x])
	{
		if(strcmp(builts[x],tmp->cmds[0]) == 0)
			break;
		x++;
	}
	// printf("%d\n",x);
	if (x >= 7)
		return -1;
	return (x);
}

char	*ft_get_path(char **arr_phat, char *first_cmnd)
{
	char *arr_join_one;
	char *arr_join;
	int x = 0;
	int res;
	while (arr_phat[x])
	{
		res = access(first_cmnd, F_OK | X_OK);
		if(res == 0)
		{
			// printf("%s\n",first_cmnd);
			return first_cmnd;
		}
		else 
		{
			arr_join_one = ft_srtjoin(arr_phat[x],"/");
			arr_join = ft_srtjoin(arr_join_one,first_cmnd);
			res = access(arr_join, F_OK | X_OK);
			if (res == 0)
				break;
			else if (res == -1  && !arr_phat[x+1])
			{
				// perror("minishell");
				return first_cmnd;
			}
		}
		x++;
	}
	return arr_join;
}

void ft_buitin_cmnd(t_cmd *cmnds, t_env **env,t_export **export, int place)
{
	// static char *builts[] = {"env","pwd","cd","echo", "export", "unset", "exit", NULL};
	if (place == 0)
		ft_env(env, cmnds);
	if (place == 1)
		ft_pwd();
	if (place == 2)
		ft_cd(cmnds, env);
	if (place == 3)
		ft_echo(cmnds);
	if (place == 4)
		ft_export(cmnds, env, export);
	if (place == 5)
		ft_unset(cmnds, export, env);
	if (place == 6)
		exit(0);
	
}

char *ft_look_for_paht(t_env **env)
{
	t_env *tmp2 = *env; 
	while (tmp2)
	{
		if(ft_strcmp(tmp2->key,"PATH") == 0)
			break;
		tmp2 = tmp2->next;
	}
	return tmp2->value;
}

void ft_excute_one(t_cmd **cmnds, t_export **export, char **env, t_env **node_env)
{
	t_cmd *tmp = *cmnds;
	char **arr_phat = ft_split(ft_look_for_paht(node_env), ':');
	char *arr_join = ft_get_path(arr_phat, tmp->cmds[0]);
	if (!arr_join)
	{
		if ( tmp->redir_out != 1)
			close(tmp->redir_out);
		return;	
	}
	if (ft_check_cmnd(tmp) != -1)
	{
		int saved_stdout = dup(1);
		int saved_stdout_ = dup(0);
		if (tmp->redir_out != 1)
		{
			dup2(tmp->redir_out , 1);
			close(tmp->redir_out);
		}
		ft_buitin_cmnd(tmp, node_env, export, ft_check_cmnd(tmp));
		dup2(saved_stdout, 1);
		dup2(saved_stdout_, 0);
	}
	else
	{
		int id = fork();
		if (id == 0)
		{
			if (tmp->redir_out != 1)
			{
				dup2(tmp->redir_out , 1);
				close(tmp->redir_out);
			}
			execve(arr_join, tmp->cmds, env);
		}
		wait(NULL);
		if (tmp->redir_out != 1)
			close(tmp->redir_out);
	}
}  



void ft_excute(t_cmd **cmnds, t_export **export ,t_env **node_env, char **env)
{
	t_cmd *tmp = *cmnds;
	char **arr_phat = ft_split(ft_look_for_paht(node_env), ':');
	char *arr_join = NULL;
	int p[2];
	int num_cmnd = ft_count_cmnds(cmnds);
	int id;
	int std_d = -1;
	// printf("%s\n",tmp->cmds[0]);
	while (tmp && num_cmnd)
	{
		arr_join = ft_get_path(arr_phat,tmp->cmds[0]);
		if(!arr_join)
		{
			close(p[0]);
			close(p[1]);
			return ;
		}
		if (num_cmnd == ft_count_cmnds(cmnds)) // first cmnd
		{
			pipe(p);
			if (ft_check_cmnd(tmp) != -1)
			{
				int saved_stdout = dup(1);
				dup2(p[1], STDOUT_FILENO);
				if (tmp->redir_out != 1)
				{
					dup2(tmp->redir_out , 1);
					close(tmp->redir_out);
				}
				ft_buitin_cmnd(tmp, node_env, export, ft_check_cmnd(tmp));
				dup2(saved_stdout, 1);
			}
			else
			{
				id = fork();
				if (id == 0)
				{
					dup2(p[1], STDOUT_FILENO);
					if (tmp->redir_out != 1)
					{
						dup2(tmp->redir_out, STDIN_FILENO);
						close(tmp->redir_out);
					}
					close(p[0]);
					close(p[1]);
					execve(arr_join, tmp->cmds, env);
				
				}
			}
			close(p[1]);
		}
		else if (num_cmnd != 1) // mid cmnd
		{
			std_d = p[0];
			pipe(p);
			if (ft_check_cmnd(tmp) != -1)
			{
				int saved_stdout = dup(1);
				int saved_stdout_ = dup(0);
				dup2(std_d, STDIN_FILENO);
				dup2(p[1], STDOUT_FILENO);
				if (tmp->redir_out != 1)
				{
					dup2(tmp->redir_out , 1);
					close(tmp->redir_out);
				}
				ft_buitin_cmnd(tmp,node_env, export ,ft_check_cmnd(tmp));
				dup2(saved_stdout, 1);
				dup2(saved_stdout_, 0);
			}
			else
			{
				id = fork();
				if (id == 0)
				{
					dup2(std_d, STDIN_FILENO);
					dup2(p[1], STDOUT_FILENO);
					if (tmp->redir_out != 1)
					{
						dup2(tmp->redir_out, STDOUT_FILENO);
						close(tmp->redir_out);
					}
					close(std_d);
					close(p[0]);
					close(p[1]);
					execve(arr_join, tmp->cmds, env);
				}
			}
			close(p[1]);
			close(std_d);
			// tmp =  tmp->next;
		}
		else if (num_cmnd == 1) // last cmnd
		{ 
			if (ft_check_cmnd(tmp) != -1)
			{
				int saved_stdout = dup(1);
				int saved_stdout_ = dup(0);
				dup2(p[0], 0);
				if (tmp->redir_out != 1)
				{
					dup2(tmp->redir_out , 1);
					close(tmp->redir_out);
				}
				ft_buitin_cmnd(tmp, node_env, export, ft_check_cmnd(tmp));
				dup2(saved_stdout, 1);
				dup2(saved_stdout_, 0);
			}
			else
			{
				id = fork();
				if (id == 0)
				{
					dup2(p[0], STDIN_FILENO);
					if (tmp->redir_out != 1)
					{
						dup2(tmp->redir_out, STDOUT_FILENO);
						close(tmp->redir_out);
					}
					close(p[0]);
					close(p[1]);
					execve(arr_join, tmp->cmds, env);
				}
			}
		}
		num_cmnd--;
		if (tmp->redir_out != 1)
		{
			close(tmp->redir_out);
		}
		tmp = tmp->next;
	}
	close(std_d);
	close(p[0]);
	close(p[1]);
	num_cmnd = ft_count_cmnds(cmnds);
	while (num_cmnd)
	{
		wait(NULL);
		num_cmnd--;
	}
	
}

char **ft_get_charenv(t_env **env)
{
	t_env *tmp;
	int x;
	int y;
	char *arr_joined;
	char **arr;

	x = 0;
	y = 0;
	tmp = *env;
	while (tmp)
	{
		x++;
		tmp = tmp->next;
	}
	tmp = *env;
	arr = g_malloc(((x+1) * sizeof(char *)) , MALLOC );
	if (!arr)
		return NULL;
	while (y < x && tmp)
	{
		arr_joined = ft_srtjoin(tmp->key, "=");
		arr[y] = ft_srtjoin(arr_joined, tmp->value);
		y++;
		tmp = tmp->next;
	}
	arr[y] = NULL;
	return (arr);
}
void	ft_execution (t_cmd **cmnds, t_env **env)
{
	if (!cmnds || !*cmnds || !env || !*env)
		return;
	int count_cmnd;
	char **arr_env = NULL;
	static t_export *export=NULL;
	count_cmnd = 0;
	arr_env = ft_get_charenv(env);
	if (!export)
		ft_fill_export(&export, env);
	if(ft_count_cmnds(cmnds) == 1)
		ft_excute_one(cmnds, &export, arr_env, env);
	else
		ft_excute(cmnds, &export, env, arr_env);
	for (int i = 3; i < OPEN_MAX ; i++)
	{
		close(i);
	}
	// write(0,"0 shj\n",7);
	// write(1,"1 shj\n",7);
	// write(2,"2 shj\n",7);
}