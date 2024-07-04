/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 15:40:16 by hchadili          #+#    #+#             */
/*   Updated: 2024/07/04 16:30:07 by hchadili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_cd(char *path)
{
	if(chdir(path))
	{
		perror("chdir erorr");
	}
	
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
