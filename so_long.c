/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorais- <amorais-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 10:57:18 by amorais-          #+#    #+#             */
/*   Updated: 2023/01/31 10:08:55 by amorais-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	all_setup(char **argv, t_all *all)
{
	all->map = map_creator(argv[1]);
	if (!map_validator(all->map))
		error_management(1, all);
	all->mlx = mlx_init();
	all->win = mlx_new_window(all->mlx, all->map.width * 51, \
	all->map.height * 51 + 20, "So_Long");
	all->canva[0].img = mlx_new_image(all->mlx, all->map.width * 51, \
	all->map.height * 51);
	all->canva[0].addr = mlx_get_data_addr(all->canva[0].img, \
	&all->canva[0].bpp, &all->canva[0].ll, &all->canva[0].endian);
	all->canva[1].img = mlx_new_image(all->mlx, all->map.width * 51, 17);
	all->canva[1].addr = mlx_get_data_addr(all->canva[0].img, \
	&all->canva[1].bpp, &all->canva[1].ll, &all->canva[1].endian);
	all->floor = image_creator(all->mlx, "Textures/Floor.xpm");
	all->wall = image_creator(all->mlx, "Textures/Wall.xpm");
	all->coll = image_creator(all->mlx, "Textures/Collectible.xpm");
	master_setup(all);
	all->enemies = enemy_creator(all->map.map, all->mlx);
	all->counter = 0;
	all->moves = line_join("Number of moves: ", ft_itoa(all->counter), 0);
	all->weapons = NULL;
}

int	master_move(int keycode, t_all *all)
{
	if (keycode > 65360 && keycode < 65365 && all->master->status != 0)
		all->master->status = keycode - 65360;
	if (keycode == 65361 && is_walkable(all, -1, 0))
		all->master->x--;
	else if (keycode == 65362 && is_walkable(all, 0, -1))
		all->master->y--;
	else if (keycode == 65363 && is_walkable(all, 1, 0))
		all->master->x++;
	else if (keycode == 65364 && is_walkable(all, 0, 1))
		all->master->y++;
	else if (keycode == 65307)
		end(all);
	if (all->map.map[all->master->y][all->master->x] == 'C')
		all->map.map[all->master->y][all->master->x] = '0';
	if (count_chars(all->map.map, 'C') == 0)
		all->exit->status = 1;
	put_str_win(all);
	return (0);
}

int	render(t_all *all)
{
	enemy_mover(&(all->enemies), all->map);
	status_changer(&(all->enemies), 75);
	weapon_mover(&(all->weapons));
	status_changer(&(all->weapons), 25);
	if (colusion(all->master, all->enemies))
	{
		all->master->status = 0;
		all->master->t[0] = get_time() + 750;
	}
	display_master(*all);
	mlx_put_image_to_window(all->mlx, all->win, all->canva[0].img, 0, 20);
	check_weapons(&(all->weapons), &(all->enemies), all->map.map, all->mlx);
	finish(all);
	return (0);
}

int	main(int argc, char **argv)
{
	t_all	all;

	if (argc != 2)
		error_management(2, (t_all *) NULL);
	all_setup(argv, &all);
	put_str_win(&all);
	mlx_loop_hook(all.mlx, render, &all);
	mlx_hook(all.win, 2, 1l << 0, master_move, &all);
	mlx_hook(all.win, 3, 1l << 1, weapon_creator, &all);
	mlx_hook(all.win, 17, 0, end, &all);
	mlx_loop(all.mlx);
}
