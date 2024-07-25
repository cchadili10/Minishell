/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 17:59:59 by yessemna          #+#    #+#             */
/*   Updated: 2024/07/25 09:16:40 by hchadili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

// print list as a table

void print_list(t_token *list)
{
	t_token *tmp = list;
	while (tmp)
	{
		printf(" (%s)  ->  ", tmp->key);
		if (tmp->value == PIPE)
			printf("PIPE\n");
		else if (tmp->value == SPC)
			printf("SPC\n");
		else if (tmp->value == IN)
			printf("IN\n");
		else if (tmp->value == HEREDOC)
			printf("HEREDOC\n");
		else if (tmp->value == OUT)
			printf("OUT\n");
		else if (tmp->value == APPEND)
			printf("APPEND\n");
		else if (tmp->value == SNGL_Q)
			printf("Sgl_q\n");
		else if (tmp->value == DBL_Q)
			printf("Dbl_q\n");
		else if (tmp->value == VAR)
			printf("VAR\n");
		else if (tmp->value == CMD)
			printf("CMD\n");
		else if (tmp->value == DBL_VAR)
			printf("DBL_VAR\n");
		tmp = tmp->next;
	}
}

int processline(char *line, t_token **list)
{
	int i;
	int start;
	int end;

	start = 0;
	end = 0;
	i = 0;
	if (line == NULL)
		return (0);
	while (i < ft_strlen(line) && line[i] != '\0')
	{
		if (line[i] == '|')
			lst_add_back(list, lst_new(ft_substr(line, i++, 1), PIPE));
		else if (is_space(line[i]))
		{
			while (is_space(line[i + 1]))
				i++;
			lst_add_back(list, lst_new(ft_substr(line, i++, 1), SPC));
		}
		else if (line[i] == '<')
		{
			if (line[i + 1] == '<')
				lst_add_back(list, lst_new(ft_substr(line, i++, 2), HEREDOC));
			else
				lst_add_back(list, lst_new(ft_substr(line, i, 1), IN));
			i++;
		}
		else if (line[i] == '>')
		{
			if (line[i + 1] == '>')
				lst_add_back(list, lst_new(ft_substr(line, i++, 2), APPEND));
			else
				lst_add_back(list, lst_new(ft_substr(line, i, 1), OUT));
			i++;
		}
		else if (line[i] == '\'' || (line[i] == '$' && line[i + 1] == '\''))
		{
			if (line[i] == '$')
				i++;
			if (line[i + 1] == '\'')
			{
				lst_add_back(list, lst_new("", SNGL_Q));
				i++;
			}
			else
			{
				end = find_char(line + i + 1, '\'');
				if (end)
					lst_add_back(list, lst_new(ft_substr(line, i + 1, end), SNGL_Q));
				else
					return(print_error("Error: missing single quote\n"), 0);
				i += end + 1;
			}
			i++;
		}
		else if (line[i] == '\"' || (line[i] == '$' && line[i + 1] == '\"'))
		{
			if (line[i] == '$')
				i++;
			if (line[i + 1] == '\"')
			{
				lst_add_back(list, lst_new("", DBL_Q));
				i += 1;
			}
			else
			{
				end = find_char(line + i + 1, '\"');
				if (end)
					lst_add_back(list, lst_new(ft_substr(line, i + 1, end), DBL_Q));
				else
					return(print_error("Error: missing double quote\n"), 0);
				i += end + 1;
			}
			i++;
		}
		else if (line[i] == '$' && (line[i + 1] >= '0' && line[i + 1] <= '9'))
		{
			lst_add_back(list, lst_new(ft_substr(line, i++, 2), VAR));
			i++;
		}
		else if (line[i] == '$' && line[i + 1] == '$')
		{
			lst_add_back(list, lst_new(ft_substr(line, i++, 2), DBL_VAR));
			i++;
		}
		else if (line[i] == '$')
		{
			if (!is_alnum(line[i + 1]))
				lst_add_back(list, lst_new(ft_substr(line, i++, 1), CMD));
			else
			{
				start = i;
				i++;
				while (is_alnum(line[i]) && !is_special(line[i]))
				{
					if (!is_alnum(line[i + 1]))
						break;
					i++;
				}
				end = i - start;
				lst_add_back(list, lst_new(ft_substr(line, start, end + 1), VAR));
				i++;
			}
		}
		else
		{
			start = i;
			while (line[i] && !is_special(line[i]))
			{
				if (is_special(line[i + 1]))
					break;
				i++;
			}
			end = i - start;
			lst_add_back(list, lst_new(ft_substr(line, start, end + 1), CMD));
			i++;
		}
	}
	return (1);
}
// Main function
// #include "libc.h"
int ft_atoi(const char *str)
{
	int i;
	int sign;
	int res;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res * sign);
}
char *ft_itoi(int nbr)
{
	
	char *str;
	int i;
	int n;

	i = 0;
	n = nbr;
	while (n)
	{
		n /= 10;
		i++;
	}
	str = (char *)malloc(i + 1);
	if (!str)
		return (NULL);
	str[i] = '\0';
	while (i--)
	{
		str[i] = nbr % 10 + '0';
		nbr /= 10;
	}
	return (str);
	}

void initenv(char **env, t_env **envi)
{
	(void)env;
	(void)envi;

	int i;
	char *key;
	char *value;
	
	int index = 0;
	i = -1;
	
	while (env && env[++i])
	{
		index = find_char(env[i], '=');
		key = ft_substr_env(env[i], 0, index);
		value = ft_substr_env(env[i], index + 1, ft_strlen(env[i]) - index);
		if(ft_strcmp(key, "SHLVL") == 0)
			value = ft_itoi(ft_atoi(value) + 1);
		else if(ft_strcmp(key, "_") == 0)
			value = "/usr/bin/env";

		lst_add_back_env(envi, lst_new_env(key, value));
	}
}

int print_env(t_env *envi, t_token *list)
{
	char str[] = "env";
	t_env *tmp = envi;
	t_token *tmp2 = list;
	int flag = 0;
	int size = 0;

	size = ft_lstsize(tmp);
	if (tmp2 && !ft_strcmp(tmp2->key, str))
	{
		while (tmp && size)
		{
			write(1, tmp->key, ft_strlen(tmp->key));
			write(1, "=", 1);
			write(1, tmp->value, ft_strlen(tmp->value));
			write(1, "\n", 1);
			tmp = tmp->next;
			size--;
		}
		flag = 1;
	}
	return (flag);
}


void print_cmd(t_cmd **cmd)
{
	t_cmd *tmp = *cmd;
	int i = 0;
	printf("\n-----------\n");
	while (tmp)
	{
		i = 0;
		while (tmp->cmds && tmp->cmds[i])
		{
			printf("cmd[%d] : %s\n", i, tmp->cmds[i]);
			i++;
		}
		printf("redir_in: %d\n", tmp->redir_in);
		printf("redir_out: %d\n", tmp->redir_out);
		tmp = tmp->next;
	}
	printf("\n-----------\n");
}
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
	(void)av;
	envi = NULL;

	ft_signal();
	rl_catch_signals = 0;
    if (ac > 1)
        print_error("no argument needed");
    initenv(env, &envi);       // <---  problem in env ( should not split with '=' )
    while (1)
    {
        list = NULL;
        cmd = NULL;
        (void)env;
        line = readline(COLOR_ORANGE"Minishell🐚⤳ "COLOR_WHITE);
        if (!line)
		{
        	printf("exit\n");
			exit(0);
            // break ;
		}
		// if(line == EOF)
		
        // char  *save_line = line;
        if (line && ft_strlen(line) != 0)
            add_history(line);
        if(!processline(line, &list))//<--- to handle the line prepare the list
        {
            free((void*)line);
            continue;
        }    
        // if (!catch_errors(&list))    // <--- to catch errors
        // {
        //     free((void*)line);
        //     continue;
        // } 
        // if(print_env(envi, list))    // <--- to print the env
        // {
        //     free((void*)line);
        //     continue;
        // }
        find_node(envi, list);   // <--- to expand the variables
        join_nodes(&list);      // <--------------- join
        if (!prepare_cmd(list, &cmd, envi))// <--- to prepare the command
        {
            free((void*)line);
            continue;
        } 

		// printf("\n-----------\n");
		// print_list(list);      // print cmd list

        // print_cmd(&cmd);
        // if(!heredoc(list, envi))            // <--- to handle the heredoc
        //     continue ;
        
        // printf("\n-----------*****\n");
        // int i = 0;
        // while (env && env[i])
        // {
        //     printf("%s\n", env[i]);
        //     i++;
        // }
        

		ft_execution(&cmd, &envi);
		free((void*)line);
		g_malloc(0, FREE);
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