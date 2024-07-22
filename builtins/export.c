/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yessemna <yessemna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 17:53:16 by hchadili          #+#    #+#             */
/*   Updated: 2024/07/22 05:50:55 by yessemna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"
int ft_count_eq(char *str, int chek, int *append)
{
	int x = 0;
	if (chek)
	{
		while (str[x])
		{
			if (str[x] == '=')
				return x;
			x++;
		}
		return x;
	}
	else
	{
		while (str[x])
		{
			if (str[x] == '+' || str[x] == '=')
			{
				if(str[x] == '+')
				{
					if(str[x+1] == '=')
					{
						*append = 1;
						return x - 1;
					}
				}
				else
					return x;
			}
			x++;
		}
		return x;
	}
}
int ft_check_key(char *key)
{
	int x;
	x = 0;
	if ((key[x] >= 97 && key[x] <= 122) || (key[x] >= 65 && key[x] <= 90) || key[x] == 95)
	{
		x++;
		while (key[x])
		{
			if ((key[x] <= 96 || key[x] > 122) || (key[x] < 65 || key[x] > 90) || key[x] == 95 || (key[x] >= 48 && key[x] <= 57))
		}
		return 1;
	}
	return 0;
}

void ft_export(t_cmd *cmnd, t_env **env, t_export **export)
{
	(void)export;
	(void)env;
	int x = 0;
	// t_env *tmp = *env;
	t_export *tmp1 = *export;
	int start ;
	char *key;
	char *value;
	int append = 0;
	while (cmnd->cmds[x])
		x++;
	if (x == 1)
	{
		while (tmp1)
		{
			printf("declare -x %s=\"%s\"\n",tmp1->key, tmp1->value);
			tmp1 = tmp1->next;
		}
		
	}
	else
	{
		x = 1;
		while (cmnd->cmds[x])
		{
			start = ft_count_eq(cmnd->cmds[x], 1, &append) + 1;
			key = ft_substr_env(cmnd->cmds[x], 0, (ft_count_eq(cmnd->cmds[x], 0, &append)));
			value = ft_substr_env(cmnd->cmds[x], start, (ft_strlen(cmnd->cmds[x]) - start));
			if (ft_check_key(key) == 0)
			{
				print_error("export: not valid in this context:");
				return ;
			}
			printf("%d\n", append);
			if(value[0])
			{
				lst_add_back_env(env,lst_new_env(key, value));
				insert_end(export,key,value);
			}
			else
				insert_end(export, key, value);
			x++;
		}
		
	}
	
}
// lst_add_back_env(envi, lst_new_env(key, value));
// if ((key[x] < 'a' || key[x] > 'z') && key[x] != '_' && (key[x] < 'A' || key[x] > 'Z') && (key[x] < '0' && key[x] > '9'))
