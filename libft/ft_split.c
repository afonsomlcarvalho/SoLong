/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorais- <amorais-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 10:23:28 by amorais-          #+#    #+#             */
/*   Updated: 2022/11/03 15:39:28 by amorais-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	nbwords(char const *s, char c)
{
	int	counter;
	int	i;

	if (s[0] == '\0')
		return (0);
	counter = 0;
	i = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] == c && s[i - 1] != c)
			counter++;
		i++;
	}
	if (s[i - 1] == c)
		return (counter);
	return (counter + 1);
}

int	wordlen(char const *s, char c, int i)
{
	int	counter;

	counter = 0;
	while (s[i])
	{
		if (s[i] == c)
			break ;
		counter++;
		i++;
	}
	return (counter);
}

void	split2(char const *s, char c, char **array, int a)
{
	int		i;
	int		x;

	i = 0;
	if (nbwords(s, c) > 0)
	{
		while (s[i])
		{
			while (wordlen(s, c, i) == 0)
				i++;
			array[a] = malloc(sizeof(char) * (wordlen(s, c, i) + 1));
			x = 0;
			while (wordlen(s, c, i) != 0)
			{
				array[a][x] = s[i];
				i++;
				x++;
			}
			array[a][x] = '\0';
			while (wordlen(s, c, i) == 0 && s[i])
				i++;
			a++;
		}
	}
	array[a] = 0;
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	int		a;

	if (!s)
		return (NULL);
	a = 0;
	array = malloc(sizeof(char *) * (nbwords(s, c) + 1));
	if (!array)
		return (NULL);
	split2(s, c, array, a);
	return (array);
}
