/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenazing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yessemna <yessemna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 18:21:27 by yessemna          #+#    #+#             */
/*   Updated: 2024/05/19 19:05:39 by yessemna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void pipe_redirection(char *line, t_token **list, int *i)
{
    int d = *i;
    if (line[d] == '|')
            lst_add_back(list, lst_new(ft_substr(line, d++, 1), PIPE));
        else if (is_space(line[d]))
        {
            while (is_space(line[d + 1]))
                d = d + 1;
            lst_add_back(list, lst_new(ft_substr(line, d++, 1), SPACE));
        }
        else if (line[d] == '<')
        {
            if (line[d + 1] == '<')
                lst_add_back(list, lst_new(ft_substr(line, d++, 2), HEREDOC));
            else
                lst_add_back(list, lst_new(ft_substr(line, d, 1), IN));
            d = d + 1;
        }
        else if (line[d] == '>')
        {
            if (line[d + 1] == '>')
                lst_add_back(list, lst_new(ft_substr(line, d++, 2), APPEND));
            else
                lst_add_back(list, lst_new(ft_substr(line, d, 1), OUT));
            d = d + 1;
        }
        *i = d;
}
