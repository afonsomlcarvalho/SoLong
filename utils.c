/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorais- <amorais-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 10:52:34 by amorais-          #+#    #+#             */
/*   Updated: 2023/01/31 10:07:19 by amorais-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	put_pixel_img(t_img img, int x, int y, int color)
{
	char	*dst;

	if (color != 0x00ffe4)
	{
		dst = img.addr + (y * img.ll + x * (img.bpp / 8));
		*(unsigned int *) dst = color;
	}
}

unsigned int	get_color(t_img img, int x, int y)
{
	char	*dst;

	dst = img.addr + (y * img.ll + x * (img.bpp / 8));
	return (*(unsigned int *) dst);
}

int	is_walkable(t_all *all, int x, int y)
{
	if (all->master->status == 0)
		return (0);
	if (all->map.map[all->master->y + y][all->master->x + x] == '1' || \
	(all->map.map[all->master->y + y][all->master->x + x] == 'E' && \
	all->exit->status == 0))
		return (0);
	if (all->master->img[1].img)
		all->counter++;
	return (1);
}

int	count_chars(char **map, char c)
{
	int	x;
	int	y;
	int	counter;

	y = 0;
	counter = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
			if (map[y][x++] == c)
				counter++;
		y++;
	}
	return (counter);
}

char	**array_dup(char **array)
{
	char	**new;
	int		i;

	i = 0;
	while (array[i])
		i++;
	new = malloc(sizeof(char *) * (i + 1));
	if (!new)
		error_management(3, (t_all *) NULL);
	i = 0;
	while (array[i])
	{
		new[i] = ft_strdup(array[i]);
		i++;
	}
	new[i] = 0;
	return (new);
}
