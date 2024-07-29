/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 17:53:16 by hchadili          #+#    #+#             */
/*   Updated: 2024/07/29 10:53:50 by hchadili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

char	*ft_strjoin_(char const *s1, char const *s2)
{
	int		x;
	int		y;
	char	*array;
	int		size;

	x = 0;
	y = 0;
	if (!s1 && !s2)
		return (0);
	size = (ft_strlen(s1) + ft_strlen(s2));
	array = (char *) malloc((sizeof(char) * size) + 1);
	if (!array)
		return (0);
	while (s1[x])
	{
		array[x] = s1[x];
		x++;
	}
	while (s2[y])
		array[x++] = s2[y++];
	array[size] = '\0';
	return (array);
}

int ft_count_eq(char *str, int chek, int *append, int *update)
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
						*update = 1;
						*append = 1;
						return x;
					}
				}
				else
				{
					*update = 1;
					return x;
				}
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
			if ((key[x] >= 'a' && key[x] <= 'z') || key[x] == '_' || (key[x] >= 'A' && key[x] <= 'Z') || (key[x] >= '0' && key[x] <= '9'))
				x++;
			else
				return 0;
		}
		return 1;
	}
	return 0;
}

int ft_find_key(t_export **export, char *key)
{
	t_export *tmp;
	
	tmp = *export;
	
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
void	ft_add_to_env_export(t_export **export, t_env **env, char *key, char *value)
{
	t_export *tmp = *export;
	t_env *tmp_env = *env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
			break;
		tmp = tmp->next;
	}
	while (tmp_env)
	{
		if (ft_strcmp(tmp_env->key, key) == 0)
			break;
		tmp_env = tmp_env->next;
	}
	if (tmp)
		tmp->value = ft_strjoin_(tmp->value, value);
	if (tmp_env)
		tmp_env->value = ft_strjoin_(tmp_env->value, value);
}
void	ft_replace_value_for_env(t_env **env, char *key, char *value, int check)
{
	t_env *tmp = *env;
	
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
			break;
		tmp = tmp->next;
	}
	if (tmp && check)
		tmp->value = ft_strdup_env(value);
}
void	ft_replace_value_for_export(t_export **export, char *key, char *value, int check)
{
	t_export *tmp = *export;	
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
			break;
		tmp = tmp->next;
	}
	if (tmp && check)
		tmp->value = ft_strdup_env(value);
	
}
void ft_export(t_cmd *cmnd, t_env **env, t_export **export)
{
	int x = 0;
	t_export *tmp1 = *export;
	int start ;
	char *key;
	char *value;
	int append = 0;
	int update_ = 0;
	while (cmnd->cmds[x])
		x++;
	if (x == 1)
	{
		while (tmp1)
		{
			printf("declare -x %s=\"%s\"\n",tmp1->key, tmp1->value);
			tmp1 = tmp1->next;
		}
		ft_exit_status(0, SET);
	}
	else
	{
		x = 1;
		while (cmnd->cmds[x])
		{
			start = ft_count_eq(cmnd->cmds[x], 1, &append, &update_) + 1;
			key = ft_substr_env(cmnd->cmds[x], 0, (ft_count_eq(cmnd->cmds[x], 0, &append, &update_)));
			value = ft_substr_env(cmnd->cmds[x], start, (ft_strlen(cmnd->cmds[x]) - start));
			if (ft_check_key(key) == 0)
			{
				print_error("export: not valid in this context:");
				ft_exit_status(1, SET);
				return ;
			}
			if (append == 0)
			{
				if (ft_find_key(export, key) == 0)// when find 0 add to export || env
				{
					if(value[0] || update_ == 1)
					{
						lst_add_back_env(env, lst_new_env(key, value));
						insert_end(export, key, value);
					}
					else 
						insert_end(export, key, value);
				}
				else //// other update value of export || env
				{
					ft_replace_value_for_export(export, key, value, update_);
					ft_replace_value_for_env(env, key, value, update_);
				}
				
			}
			else
			{
				if(ft_find_key(export, key))//if you find var update if updat_ = 1
					ft_add_to_env_export(export, env, key, value);
				else
				{
					if(value[0] || update_ == 1)
					{
						lst_add_back_env(env,lst_new_env(key, value));
						insert_end(export, key, value);
					}
					else
						insert_end(export, key, value);
				}
			}
			append = 0;
			update_ = 0;
			x++;
		}
		ft_exit_status(0, SET);
	}
	
}
// lst_add_back_env(envi, lst_new_env(key, value));
// if ((key[x] < 'a' || key[x] > 'z') && key[x] != '_' && (key[x] < 'A' || key[x] > 'Z') && (key[x] < '0' && key[x] > '9'))
