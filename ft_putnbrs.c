/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbrs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsala <jsala@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 20:28:59 by jsala             #+#    #+#             */
/*   Updated: 2024/02/09 12:02:33 by jsala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	ft_putnbr(int nb)
{
	int	count;

	count = 0;
	if (nb == -2147483648)
		return (ft_putstr("-2147483648"));
	else
	{
		if (nb < 0)
		{
			count += ft_putchar('-');
			nb = -nb;
		}
		if (nb >= 10)
		{
			count += ft_putnbr(nb / 10);
			nb = nb % 10;
		}
		if (nb < 10)
			count += ft_putchar(nb + '0');
		return (count);
	}
}

int	ft_putunbr(int n)
{
	unsigned int	nb;
	int				count;

	count = 0;
	nb = (unsigned int) n;
	if (nb >= 10)
	{
		count += ft_putnbr(nb / 10);
		nb = nb % 10;
	}
	if (nb < 10)
	{
		ft_putchar(nb + '0');
		count++;
	}
	return (count);
}

int	ft_puthex(unsigned int nbr, char x)
{
	int	count;

	count = 0;
	if (nbr >= 16)
	{
		count += ft_puthex(nbr / 16, x);
		nbr = nbr % 16;
	}
	if (nbr < 16)
	{
		if (x == 'x')
			ft_putchar("0123456789abcdef"[nbr]);
		else
			ft_putchar("0123456789ABCDEF"[nbr]);
		count++;
	}
	return (count);
}

int	ft_putlonghex(unsigned long int nbr, char x)
{
	int	count;

	count = 0;
	if (nbr >= 16)
	{
		count += ft_putlonghex(nbr / 16, x);
		nbr = nbr % 16;
	}
	if (nbr < 16)
	{
		if (x == 'x')
			ft_putchar("0123456789abcdef"[nbr]);
		else
			ft_putchar("0123456789ABCDEF"[nbr]);
		count++;
	}
	return (count);
}

int	ft_putpointer(void *p)
{
	unsigned long int	i;
	unsigned int		count;

	i = (unsigned long int)p;
	count = ft_putstr("0x") + ft_putlonghex(i, 'x');
	return (count);
}
