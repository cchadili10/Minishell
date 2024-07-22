/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yessemna <yessemna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 17:53:16 by hchadili          #+#    #+#             */
/*   Updated: 2024/07/21 07:35:25 by yessemna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"
int ft_count_eq(char *str, int chek)
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
				return x;
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
			;
		}
		
	}
	return 1;
}

void ft_export(t_cmd *cmnd, t_env **env)
{
	(void)env;
	int x = 0;
	t_env *tmp = *env;
	int start ;
	char *key;
	char *value;
	while (cmnd->cmds[x])
	{
		// printf("%s\n",cmnd->cmds[x]);
		x++;
	}
	if (x == 1)
	{
		while (tmp)
		{
			printf("declare -x %s=\"%s\"\n",tmp->key, tmp->value);
			tmp = tmp->next;
		}
		
	}
	else
	{
		x = 1;
		while (cmnd->cmds[x])
		{
			// printf("%d\n",ft_count_eq(cmnd->cmds[x]));
			start = ft_count_eq(cmnd->cmds[x], 1) + 1;
			key = ft_substr_env(cmnd->cmds[x], 0, (ft_count_eq(cmnd->cmds[x], 0)));
			value = ft_substr_env(cmnd->cmds[x], start, (ft_strlen(cmnd->cmds[x]) - start));
			printf("%s\n",key);
			printf("%s\n",value);
			// if (ft_check_key(key))
			// {
				
			// }
			x++;
		}
		
	}
	
}
// lst_add_back_env(envi, lst_new_env(key, value));