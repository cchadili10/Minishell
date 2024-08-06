/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 19:41:31 by hchadili          #+#    #+#             */
/*   Updated: 2024/08/06 14:22:06 by hchadili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_arg_idupx(const char format, unsigned long long num, int *count)
{
	char	c;

	if (format == 'u')
		ft_put_u_nbr((unsigned int)num, count);
	else if (format == 'x' || format == 'X')
	{
		if (format == 'x')
			ft_hexa((unsigned int)num, count, HEXA);
		else
			ft_hexa((unsigned int)num, count, HEXA_MAJ);
	}
	else if (format == 'p')
	{
		ft_putstr("0x", count);
		ft_hexap(num, count, HEXA);
	}
	else if (format == 'i' || format == 'd')
		ft_putnbr((int)num, count);
	else if (format == 'c')
	{
		c = (int)num;
		ft_putchar(c, count);
	}
}

void	ft_format_check(const char format, va_list arg, int *count)
{
	char	*str;

	if (format == 'd' || format == 'i' || format == 'u')
		ft_arg_idupx(format, va_arg(arg, int), count);
	else if (format == 'x' || format == 'X')
		ft_arg_idupx(format, va_arg(arg, int), count);
	else if (format == 'p')
		ft_arg_idupx(format, va_arg(arg, unsigned long long), count);
	else if (format == 'c')
		ft_arg_idupx(format, va_arg(arg, int), count);
	else if (format == '%')
		ft_putchar('%', count);
	else if (format == 's')
	{
		str = va_arg(arg, char *);
		if (str == NULL)
			ft_putstr("(null)", count);
		else
			ft_putstr(str, count);
	}
	else
		ft_putchar(format, count);
}

int	ft_printf(const char *format, ...)
{
	va_list	arg;
	int		count;

	va_start(arg, format);
	count = 0;
	if (write(1, "", 0) == -1)
		return (-1);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (*format == '\0')
				break ;
			ft_format_check(*format, arg, &count);
			format++;
		}
		else
		{
			ft_putchar(*format, &count);
			format++;
		}
	}
	va_end(arg);
	return (count);
}
