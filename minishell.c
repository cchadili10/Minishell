/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yessemna <yessemna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 17:59:59 by yessemna          #+#    #+#             */
/*   Updated: 2024/08/07 04:50:25 by yessemna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

// print list as a table

// void print_list(t_token *list)
// {
// 	t_token *tmp = list;
// 	while (tmp)
// 	{
// 		printf(" (%s)  ->  ", tmp->key);
// 		if (tmp->value == PIPE)
// 			printf("PIPE\n");
// 		else if (tmp->value == SPC)
// 			printf("SPC\n");
// 		else if (tmp->value == IN)
// 			printf("IN\n");
// 		else if (tmp->value == HEREDOC)
// 			printf("HEREDOC\n");
// 		else if (tmp->value == OUT)
// 			printf("OUT\n");
// 		else if (tmp->value == APPEND)
// 			printf("APPEND\n");
// 		else if (tmp->value == SNGL_Q)
// 			printf("Sgl_q\n");
// 		else if (tmp->value == DBL_Q)
// 			printf("Dbl_q\n");
// 		else if (tmp->value == VAR)
// 			printf("VAR\n");	
// 		else if (tmp->value == CMD)
// 			printf("CMD\n");
// 		else if (tmp->value == DBL_VAR)
// 			printf("DBL_VAR\n");
// 		tmp = tmp->next;
// 	}
// }


// Main function
// #include "libc.h"




// int print_env(t_env *envi, t_token *list)
// {
// 	char str[] = "env";
// 	t_env *tmp = envi;
// 	t_token *tmp2 = list;
// 	int flag = 0;
// 	int size = 0;

// 	size = ft_lstsize(tmp);
// 	if (tmp2 && !ft_strcmp(tmp2->key, str))
// 	{
// 		while (tmp && size)
// 		{
// 			write(1, tmp->key, ft_strlen(tmp->key));
// 			write(1, "=", 1);
// 			write(1, tmp->value, ft_strlen(tmp->value));
// 			write(1, "\n", 1);
// 			tmp = tmp->next;
// 			size--;
// 		}
// 		flag = 1;
// 	}
// 	return (flag);
// }


// void print_cmd(t_cmd **cmd)
// {
// 	t_cmd *tmp = *cmd;
// 	int i = 0;
// 	printf("\n-----------\n");
// 	while (tmp)
// 	{
// 		i = 0;
// 		while (tmp->cmds && tmp->cmds[i])
// 		{
// 			printf("cmd[%d] : %s\n", i, tmp->cmds[i]);
// 			i++;
// 		}
// 		printf("redir_in: %d\n", tmp->redir_in);
// 		printf("redir_out: %d\n", tmp->redir_out);
// 		tmp = tmp->next;
// 	}
// 	printf("\n-----------\n");
// }
void join_nodes(t_token **list)
{
	t_token *tmp = *list;
	t_token *tmp2;
	while (tmp)
	{
		if (tmp->next && (tmp->value == DBL_Q || tmp->value == SNGL_Q || tmp->value == VAR
			|| tmp->value == DBL_VAR || tmp->value == CMD) && (tmp->next->value == DBL_Q
			|| tmp->next->value == SNGL_Q || tmp->next->value == VAR || tmp->next->value == DBL_VAR
			|| tmp->next->value == CMD))
		{
			tmp2 = tmp->next->next;
			tmp->key = ft_srtjoin(tmp->key, tmp->next->key);
			if (tmp->next->value == DBL_Q || tmp->next->value == SNGL_Q)
				tmp->value = tmp->next->value;
			tmp->next = tmp2;
		}
		else
			tmp = tmp->next;
	}
}


int main(int ac, char **av, char **env) //$home.c
{
	t_env *envi;
	char *line;
	t_token *list;
	t_cmd *cmd;
	struct termios term;
	envi = NULL;
	(void)av;
	tcgetattr(STDIN_FILENO, &term);
	ft_signal();
	rl_catch_signals = 0;
    if (ac > 1)
        print_error("no argument needed");
    initenv(env, &envi);       // <---  problem in env ( should not split with '=' )
    while (1)
    {
        list = NULL;
        cmd = NULL;
		int i = 3;
        (void)env;
        line = readline(COLOR_ORANGE"Minishell🐚⤳ "COLOR_WHITE);
        if (!line)
		{
        	printf("exit\n");
			exit(0);
		}
        if (line && ft_strlen(line) != 0)
            add_history(line);
        if(!processline(line, &list))//<--- to handle the line prepare the list
        {
            free((void*)line);
            continue;
        }    
        if (!catch_errors(&list))    // <--- to catch errors
        {
            free((void*)line);
            continue;
        } 

        find_node(envi, list);   // <--- to expand the variables
        join_nodes(&list);      // <--------------- join
        if (!prepare_cmd(list, &cmd, envi))// <--- to prepare the command
        {
            free((void*)line);
            continue;
        } 
		ft_execution(&cmd, &envi);
		free((void*)line);
		g_malloc(0, FREE);
		while (i < OPEN_MAX)
			close(i++);
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
	}
	g_malloc_env(0, FREE);
}

/*

--> "$HOME"                               ->DONE
--> print env                             ->DONE 
--> env: r: No such file or directory
-----> garbage collector   <-----        -->DONE
1 -- env -i ./minishell   --> done
sw

-------> 
??
--> export
--> unset
--> fix echo
--> exit status
--> env -i ./minishell should keep a secure path , some commands still work
--> split when there is a SPC in the value of the env variable

--> change (PWD && oldPWD ) when we use cd

-

*/