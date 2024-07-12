/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 22:33:08 by hchadili          #+#    #+#             */
/*   Updated: 2024/07/12 22:33:25 by hchadili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>

typedef struct s_node
{
	char **data;
	struct s_node *next;

} t_node;

void ft_excute(int num_com,  t_node **node)
{
	char *args1[] = {"ls", "-l", NULL};
	char *args2[] = {"grep", "pipex", NULL};
	char *args3[] = {"grep", "pipex.h", NULL};
	t_node *tmp = *node;
	char *phath[] = {"/bin/ls", "/usr/bin/grep", "/usr/bin/grep", "/usr/bin/wc", NULL};
	int p[2];
	int first = num_com;
	int i = 0;
	int id = 6;
	int std_d;
	while (num_com)
	{
		if (first == num_com)
		{
			pipe(p);
			id = fork();
		
			if (id == 0)
			{
				dup2(p[1], STDOUT_FILENO);
				close(p[0]);
				close(p[1]);
				execve(phath[i], tmp->data, NULL);
				
			}
			tmp =  tmp->next;
			close(p[1]);
		}
		else if (num_com != 1)
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
				execve(phath[i], tmp->data, NULL);
			}
			close(p[1]);
			tmp =  tmp->next;
		}
		else if (num_com == 1)
		{
			dup2(p[0], STDIN_FILENO);
			close(p[0]);
			close(p[1]);
			execve(phath[i], tmp->data, NULL);
		}
		num_com--;
		i++;
	}
	close(std_d);
	// close(p[0]);
	// close(p[1]);
	while (first)
	{
		wait(NULL);
		first--;
	}
}

t_node *creat_node(int i)
{
	t_node *new_node;
	new_node = malloc(sizeof(t_node));
	if(!new_node)
	{
		return NULL;
	}

	new_node->data = (char **)malloc((i + 1) * sizeof(char *));
	new_node->next = NULL;
	return new_node;
}
void assign_data(t_node *node, char *cmd[])
{
	int i = 0;
	while (cmd[i] != NULL)
	{
		node->data[i] = strdup(cmd[i]);
	
		if (!node->data[i])
		{
			perror("strdup");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	node->data[i] = NULL; // NULL-terminate the array
}

int main()
{
	char *args1[] = {"ls", "-l", NULL};		   // Arguments for the new program
	char *args2[] = {"grep", "pipex", NULL};   // Arguments for the new program
	char *args3[] = {"grep", "pipex.h", NULL}; // Arguments for the new program
	char *args4[] = {"wc", "-l", NULL};		   // Arguments for the new program
	
	t_node *node0;
	t_node *node1;
	t_node *node2;
	t_node *node4;

	node4 = creat_node(2);
	node2 = creat_node(2);
	node1 = creat_node(2);
	node0 = creat_node(2);

	assign_data(node0, args1);
	assign_data(node1, args2);
	assign_data(node2, args3);
	assign_data(node4, args4);
	node0->next = node1;
	node1->next = node2;
	node2->next = node4;
	// printf("%s \n", node0->next->next->data[1]);
	ft_excute(4, &node0);
	// printf("sfsdfsdf\n");
	return 0;
}
