/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_part.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 17:28:34 by hchadili          #+#    #+#             */
/*   Updated: 2024/08/10 17:30:31 by hchadili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*cpy_part(char *src, int start, int end)
{
    char	*out;
    int		lenght;
    int		i;

	i = -1;
	lenght =  (end - start);
	out = g_malloc(lenght + 2, MALLOC);
    if(!out)
        return (NULL); 
    while (++i <= lenght)
        out[i] = src[i];
    out[i] = '\0';
    return (out);
}
