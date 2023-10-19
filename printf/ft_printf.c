/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorais- <amorais-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 09:51:28 by amorais-          #+#    #+#             */
/*   Updated: 2022/12/02 10:03:03 by amorais-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_type3(char c, va_list valist, int len)
{
	if (c == 'p')
		len = 2 + ft_putptr(va_arg(valist, unsigned long int), len, 1);
	else if (c == 'x')
		len = ft_puthexa(va_arg(valist, unsigned int), len, 0);
	else if (c == 'X')
		len = ft_puthexa(va_arg(valist, unsigned int), len, 1);
	return (len);
}

int	ft_type2(char c, va_list valist, int len)
{
	unsigned int	u;
	int				i;

	if (c == '%')
	{
		ft_putchar_fd('%', 1);
		len++;
	}
	else if (c == 'd' || c == 'i')
	{
		i = va_arg(valist, int);
		ft_putnbr_fd(i, 1);
		len = len + nbrlen((long int)i);
	}
	else if (c == 'u')
	{
		u = va_arg(valist, unsigned int);
		ft_putnbr_unsigned(u, 1);
		len = len + nbrlen((long)u);
	}
	else
		return (ft_type3(c, valist, len));
	return (len);
}

int	ft_type(char c, va_list valist, int len)
{
	char	*s;

	if (c == 's')
	{
		s = va_arg(valist, char *);
		if (!s)
		{
			write(1, "(null)", 6);
			len = len + 6;
		}
		else
		{
			ft_putstr_fd(s, 1);
			len = len + ft_strlen(s);
		}
	}
	else if (c == 'c')
	{
		ft_putchar_fd(va_arg(valist, int), 1);
		len++;
	}
	else
		return (ft_type2(c, valist, len));
	return (len);
}

int	ft_printf(const char *s, ...)
{
	int		i;
	int		len;
	va_list	valist;

	va_start(valist, s);
	i = 0;
	len = 0;
	while (s[i])
	{
		if (s[i] == '%')
		{
			len = ft_type(s[i + 1], valist, len);
			i++;
		}
		else
		{
			ft_putchar_fd(s[i], 1);
			len++;
		}
		i++;
	}
	va_end(valist);
	return (len);
}
