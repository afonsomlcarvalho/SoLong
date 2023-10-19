/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorais- <amorais-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 19:25:18 by amorais-          #+#    #+#             */
/*   Updated: 2023/01/30 12:07:31 by amorais-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	len(long int n)
{
	size_t	c;

	c = 1;
	if (n < 0)
	{
		n = -n;
		c++;
	}
	while (n > 9)
	{
		n = n / 10;
		c++;
	}
	return (c);
}

char	*case_0(void)
{
	char	*s;

	s = (char *)malloc(sizeof(char) * 2);
	s[0] = '0';
	s[1] = '\0';
	return (s);
}

char	*ft_itoa(int n)
{
	char		*s;
	int			i;
	long int	nbr;

	nbr = n;
	if (n == 0)
		return (case_0());
	s = malloc(sizeof(char) * (len(nbr) + 1));
	if (!s)
		return (NULL);
	i = len(nbr) - 1;
	s[i + 1] = '\0';
	if (nbr < 0)
	{
		s[0] = '-';
		nbr = -nbr;
	}
	while (nbr > 0)
	{
		s[i] = (nbr % 10) + '0';
		nbr = nbr / 10;
		i--;
	}
	return (s);
}
