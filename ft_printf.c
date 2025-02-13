/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsala <jsala@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 10:16:56 by jsala             #+#    #+#             */
/*   Updated: 2024/02/09 11:59:04 by jsala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	ft_print_basecase(char c, va_list ap)
{
	if (c == 'c')
		return (ft_putchar(va_arg(ap, int)));
	else if (c == 's')
		return (ft_putstr(va_arg(ap, char *)));
	else if (c == 'p')
		return (ft_putpointer(va_arg(ap, void *)));
	else if (c == 'd' || c == 'i')
		return (ft_putnbr(va_arg(ap, int)));
	else if (c == 'u')
		return (ft_putunbr(va_arg(ap, unsigned int)));
	else if (c == 'x' || c == 'X')
		return (ft_puthex(va_arg(ap, unsigned int), c));
	else if (c == '%')
		return (ft_putchar('%'));
	return (-1);
}

int	ft_printf(const char *str, ...)
{
	va_list	ap;
	int		i;
	int		print_count;
	int		len_print;

	va_start(ap, str);
	i = 0;
	print_count = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			len_print = -1;
			while (len_print == -1)
				len_print = ft_print_basecase(str[++i], ap);
			print_count += len_print;
			i++;
			continue ;
		}
		write(1, &str[i++], 1);
		print_count++;
	}
	va_end(ap);
	return (print_count);
}
