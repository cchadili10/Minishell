/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_er.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yessemna <yessemna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 20:41:16 by hchadili          #+#    #+#             */
/*   Updated: 2024/08/25 02:20:10 by yessemna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_display_erorr_export(char *str, int *check)
{
	ft_printf("Minishell: export: '%s'", str);
	ft_printf(": not a valid identifier\n");
	ft_exit_status(1, SET);
	*check = 1;
}
