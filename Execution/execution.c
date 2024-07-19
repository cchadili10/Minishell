/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 21:09:41 by hchadili          #+#    #+#             */
/*   Updated: 2024/07/18 15:17:21 by hchadili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../minishell.h"
#include <limits.h>

int	ft_check_cmnd(t_cmd *cmnd)
{
	static char *builts[] = {"env","pwd","cd","echo", "export", "unset", "exit", NULL};
	int x = 0;
	t_cmd *tmp;

	tmp = cmnd;	
	while (builts[x])
	{
		if(strcmp(builts[x],tmp->cmds[0]) == 0)
			break;
		x++;
	}
	if (x >= 6)
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
			printf("%s\n",first_cmnd);
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
				perror("minishell");
				return NULL;
			}
		}
		x++;
	}
	return arr_join;
}

void ft_buitin_cmnd(t_cmd *cmnds, char **env, int place)
{
	// static char *builts[] = {"env","pwd","cd","echo", "export", "unset", "exit", NULL};
	if (place == 0)
		ft_env(env, cmnds);
	if (place == 1)
		ft_pwd();
	if (place == 2)
		ft_cd(cmnds);
	if (place == 3){}
	if (place == 4){}
	if (place == 5){}
	if (place == 6){}
	
}

void ft_excute_one(t_cmd **cmnds, char *path, char **env)
{
	t_cmd *tmp = *cmnds;
	char **arr_phat = ft_split(path, ':');
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
			// saved_stdout = dup(1);
			dup2(tmp->redir_out , 1);
			close(tmp->redir_out);
		}
		ft_buitin_cmnd(tmp, env, ft_check_cmnd(tmp));
		// if (tmp->redir_out != 1)
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

void ft_excute(t_cmd **cmnds, char *path ,int num_cmnd, char **env)
{
	t_cmd *tmp = *cmnds;
	(void)num_cmnd;
	char **arr_phat = ft_split(path, ':');
	char *arr_join = NULL;
	int p[2];
	int first = num_cmnd;
	int id;
	int std_d = -1;
	while (tmp && num_cmnd)
	{
		arr_join = ft_get_path(arr_phat,tmp->cmds[0]);
		if(!arr_join)
		{
			close(p[0]);
			close(p[1]);
			return ;
		}
		if (first == num_cmnd) // first cmnd
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
				ft_buitin_cmnd(tmp, env, ft_check_cmnd(tmp));
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
				ft_buitin_cmnd(tmp, env, ft_check_cmnd(tmp));
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
			// printf("ahfsyhvbfsdk\n\n");
			// printf(" test ------------> %d\n", ft_check_cmnd(tmp));
			if (ft_check_cmnd(tmp) != -1)
			{
				// printf(" loloch %d\n",tmp->redir_out);
				int saved_stdout = dup(1);
				int saved_stdout_ = dup(0);
				dup2(p[0], 0);
				if (tmp->redir_out != 1)
				{
					dup2(tmp->redir_out , 1);
					close(tmp->redir_out);
				}
				ft_buitin_cmnd(tmp, env, ft_check_cmnd(tmp));
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
	while (first)
	{
		wait(NULL);
		first--;
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
	arr = (char **) malloc((x + 1) * sizeof(char *));
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
	t_cmd *tmp = *cmnds; 
	int count_cmnd;
	char **arr_env = NULL;
	count_cmnd = 0;
	arr_env = ft_get_charenv(env);
	while (tmp)
	{
		count_cmnd++;
		tmp = tmp->next;
	}
	t_env *tmp2 = *env; 
	
	// (void)cmnds;
	while (tmp2)
	{
		if(ft_strcmp(tmp2->key,"PATH") == 0)
			break;
		tmp2 = tmp2->next;
	}
	if(count_cmnd == 1)
		ft_excute_one(cmnds, tmp2->value, arr_env);
	else
		ft_excute(cmnds,tmp2->value, count_cmnd, arr_env);
	free(arr_env);
	arr_env = NULL;
	for (int i = 3; i < OPEN_MAX ; i++)
	{
		close(i);
	}
	// write(0,"0 shj\n",7);
	// write(1,"1 shj\n",7);
	// write(2,"2 shj\n",7);
}