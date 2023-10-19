/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorais- <amorais-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 13:08:47 by amorais-          #+#    #+#             */
/*   Updated: 2023/01/30 11:14:57 by amorais-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	*moves_str(t_all *all)
{
	free(all->moves);
	all->moves = line_join("Number of movements: ", ft_itoa(all->counter), 0);
	return (all->moves);
}

int	colusion(t_object *master, t_object *enemy)
{
	while (enemy)
	{
		if (master->x == enemy->x && master->y == enemy->y)
			return (1);
		enemy = enemy->next;
	}
	return (0);
}

time_t	get_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}

void	put_str_win(t_all *all)
{
	int	x;
	int	y;

	y = 0;
	while (y < 18)
	{
		x = 0;
		while (x < all->map.width * 51)
			put_pixel_img(all->canva[1], x++, y, 0x00000000);
		y++;
	}
	mlx_put_image_to_window(all->mlx, all->win, all->canva[1].img, 0, 0);
	mlx_string_put(all->mlx, all->win, 0, 15, 0xFFFFFFFF, moves_str(all));
}
