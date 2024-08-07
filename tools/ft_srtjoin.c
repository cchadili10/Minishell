/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_srtjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yessemna <yessemna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 22:38:59 by yessemna          #+#    #+#             */
/*   Updated: 2024/07/11 02:21:53 by yessemna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ft_srtjoin.c

#include "../minishell.h"

char *ft_srtjoin(char *s1, char *s2)
{
    char *out;
    int i;
    int j;

    i = 0;
    j = 0;
    out = g_malloc(ft_strlen(s1) + ft_strlen(s2) + 1 , MALLOC);
    while (s1 && s1[i])
    {
        out[i] = s1[i];
        i++;
    }
    while (s2 && s2[j])
    {
        out[i] = s2[j];
        i++;
        j++;
    }
    out[i] = '\0';
    return (out);
}
