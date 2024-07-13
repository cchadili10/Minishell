/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 21:09:41 by hchadili          #+#    #+#             */
/*   Updated: 2024/07/13 04:51:06 by hchadili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
char	*ft_get_path(char **arr_phat, char *first_cmnd)
{
	char *arr_join_one;
	char *arr_join;
	int x = 0;
	while (arr_phat[x])
	{
		
		arr_join_one = ft_srtjoin(arr_phat[x],"/");
		arr_join = ft_srtjoin(arr_join_one,first_cmnd);
		int res = access(arr_join, F_OK | X_OK);
		if (res == 0)
			break;
		else if (res == -1  && !arr_phat[x+1])
		{
			perror("zsh: command not found");
			return NULL;
		}
		x++;
	}
	return arr_join;
}

void ft_excute_one(t_cmd **cmnds, char *path)
{
	t_cmd *tmp = *cmnds;
	char **arr_phat = ft_split(path, ':');
	char *arr_join = ft_get_path(arr_phat, tmp->cmds[0]);
	int id = fork();
	if (id == 0)
	{
		execve(arr_join, tmp->cmds, NULL);
		
	}
	wait(NULL);
}

void ft_excute(t_cmd **cmnds, char *path ,int num_cmnd)
{
	// char *phath[] = {"/bin/ls", "/usr/bin/grep", "/usr/bin/grep", "/usr/bin/wc", NULL};
	t_cmd *tmp = *cmnds;
	(void)num_cmnd;
	char **arr_phat = ft_split(path, ':');
	char *arr_join =NULL;
	
	// printf("this  --> %s \n", arr_join);
	
	int p[2];
	int first = num_cmnd;
	int id;
	int std_d;
	while (num_cmnd)
	{
		printf("%s\n",tmp->cmds[0]);
		arr_join = ft_get_path(arr_phat,tmp->cmds[0]);
		// printf("%s\n",arr_join);
		if (first == num_cmnd)
		{
			pipe(p);
			id = fork();
		
			if (id == 0)
			{
				dup2(p[1], STDOUT_FILENO);
				close(p[0]);
				close(p[1]);
				execve(arr_join, tmp->cmds, NULL);
			
			}
			tmp =  tmp->next;
			close(p[1]);
		}
		else if (num_cmnd != 1)
		{
			std_d = p[0];
			pipe(p);
			id = fork();
			if (id == 0)
			{
				dup2(std_d, STDIN_FILENO);
				dup2(p[1], STDOUT_FILENO);
				close(std_d);
				close(p[0]);
				close(p[1]);
				execve(arr_join, tmp->cmds, NULL);
			}
			close(p[1]);
			tmp =  tmp->next;
		}
		else if (num_cmnd == 1)
		{
			id = fork();
			if (id == 0)
			{
				dup2(p[0], STDIN_FILENO);
				close(p[0]);
				close(p[1]);
				execve(arr_join, tmp->cmds, NULL);
				
			}
		}
		num_cmnd--;
		tmp = tmp->next;
		printf("fdfg\n");
		printf("%s\n",tmp->cmds[0]);
	}
	close(std_d);
	// close(p[0]);
	// close(p[1]);
	while (first)
	{
		wait(NULL);
		first--;
	}
	// return ;
}


void	ft_execution (t_cmd **cmnds, t_env **env)
{

	(void)env;
	t_cmd *tmp = *cmnds; 
	int count_cmnd;

	count_cmnd = 0;
	while (tmp)
	{
		count_cmnd++;
		tmp = tmp->next;
	}
	t_env *tmp2 = *env; 
	printf("%d\n\n",count_cmnd);
	
	(void)cmnds;
	while (tmp2)
	{
		// while(tmp->cmds[i])
		// {
			
		// 	i++;
		// }
		if(ft_strcmp(tmp2->key,"PATH") == 0)
			break;
		// printf("\n");
		tmp2 = tmp2->next;
	}
	// printf("%s  --> %s \n",tmp2->key, tmp2->value);
	if(count_cmnd == 1)
		ft_excute_one(cmnds,tmp2->value);
	else
		ft_excute(cmnds,tmp2->value, count_cmnd);
	// while (env[i])
	// {
	// 	printf("%s\n",);
	// 	i++;
	// }
	
}