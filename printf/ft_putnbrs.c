/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbrs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorais- <amorais-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 09:51:35 by amorais-          #+#    #+#             */
/*   Updated: 2022/11/10 13:34:59 by amorais-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr_unsigned(unsigned int n, int fd)
{
	if (n > 9)
		ft_putnbr_fd(n / 10, fd);
	ft_putchar_fd('0' + n % 10, fd);
}

int	ft_putptr(unsigned long int n, int len, int check)
{
	char	*base;

	base = "0123456789abcdef";
	if (!n)
	{
		write(1, "(nil)", 5);
		return (len + 3);
	}
	if (check)
		write(1, "0x", 2);
	if (n > 15)
		len = ft_putptr(n / 16, len, 0);
	ft_putchar_fd(base[n % 16], 1);
	len++;
	return (len);
}

int	ft_puthexa(unsigned long int n, int len, int upper)
{
	char	*base;

	if (!upper)
		base = "0123456789abcdef";
	else
		base = "0123456789ABCDEF";
	if (n > 15)
		len = ft_puthexa(n / 16, len, upper);
	ft_putchar_fd(base[n % 16], 1);
	len++;
	return (len);
}
