/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorais- <amorais-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:15:04 by amorais-          #+#    #+#             */
/*   Updated: 2023/01/30 12:40:36 by amorais-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	display_img(t_img canva, t_img object, int j, int i)
{
	int	x;
	int	y;

	y = 0;
	while (y < 51)
	{
		x = 0;
		while (x < 51)
		{
			put_pixel_img(canva, x + j * 51, \
			y + i * 51, get_color(object, x, y));
			x++;
		}
		y++;
	}
}

void	display_floor(t_img canva, t_img floor, t_map map)
{
	int	y;
	int	x;

	y = 0;
	while (y < map.height)
	{
		x = 0;
		while (x < map.width)
			display_img(canva, floor, x++, y);
		y++;
	}
}

void	display_map(t_all all)
{
	int	y;
	int	x;

	display_floor(all.canva[0], all.floor, all.map);
	y = 0;
	while (y < all.map.height)
	{
		x = 0;
		while (x < all.map.width)
		{
			if (all.map.map[y][x] == '1')
				display_img(all.canva[0], all.wall, x, y);
			else if (all.map.map[y][x] == 'C')
				display_img(all.canva[0], all.coll, x, y);
			else if (all.map.map[y][x] == 'E')
				display_img(all.canva[0], \
				all.exit->img[all.exit->status], x, y);
			x++;
		}
		y++;
	}
}

void	display_master(t_all all)
{
	display_map(all);
	put_enemies(all.weapons, all.canva[0]);
	if (all.master->img[1].img)
		display_img(all.canva[0], all.master->img[all.master->status], \
		all.master->x, all.master->y);
	put_enemies(all.enemies, all.canva[0]);
}

void	put_enemies(t_object *enemies, t_img canva)
{
	while (enemies)
	{
		display_img(canva, enemies->img[enemies->status], \
		enemies->x, enemies->y);
		enemies = enemies->next;
	}
}
