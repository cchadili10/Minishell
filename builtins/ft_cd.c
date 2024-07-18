/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 15:40:16 by hchadili          #+#    #+#             */
/*   Updated: 2024/07/18 14:22:05 by hchadili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_cd(t_cmd *cmnd)
{
	if(!cmnd->cmds[2])
	{	
		if(chdir(cmnd->cmds[1]))
		{
			perror("chdir erorr");
		}
	}
	else
		perror("chdir erorr");
	
}
// int main() 
// { 
//     char s[100]; 
 
//     // printing current working directory 
//     printf("%s\n", getcwd(s, 100)); 
 
//     // using the command 
//     // chdir("parsing"); 
 
// 	ft_cd("parsing");
//     // printing current working directory 
//     printf("%s\n", getcwd(s, 100)); 
 
//     // after chdir is executed 
//     return 0; 
// } 
