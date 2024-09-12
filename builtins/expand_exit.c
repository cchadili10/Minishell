/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yessemna <yessemna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 14:19:29 by yessemna          #+#    #+#             */
/*   Updated: 2024/09/12 15:45:19 by yessemna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

void ft_expand_exit_status(char **str)
{
    int x;
    int y;
    char *s;
    char *hold;
    
    y = 0;
    x = 0;
    hold = NULL;
    while (str[x])
    {
        while (str[x][y])
        {
            if(str[x][y] == '$' && str[x][y + 1] == '?')
            {
                s = ft_itoa(ft_exit_status(0, GET));
                hold =  ft_srtjoin(hold, s);
                y+=2;
            }else
            {
                hold = join_char(hold, str[x][y]);
                y++;
            }
            
        }
        str[x] = hold;
        x++;
        y = 0;
        hold = NULL;    
    }
    
}
