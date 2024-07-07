/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yessemna <yessemna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 10:15:54 by yessemna          #+#    #+#             */
/*   Updated: 2024/07/07 10:16:05 by yessemna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *ft_strdup(const char *s)
{
    int i = 0;
    char *out = malloc(ft_strlen(s) + 1);
    while (s[i])
    {
        out[i] = s[i];
        i++;
    }
    out[i] = '\0';
    return (out);
}
