/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorais- <amorais-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 13:11:38 by amorais-          #+#    #+#             */
/*   Updated: 2023/01/31 10:07:58 by amorais-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	add_back(t_object **enemies, t_object *new)
{
	t_object	*current;

	if (!(*enemies))
	{
		*enemies = new;
		return ;
	}
	current = *enemies;
	while (current->next)
		current = current->next;
	current->next = new;
}

void	enemy_setup(t_object *enemy, void *mlx, int x, int y)
{
	enemy->img[0] = image_creator(mlx, "Textures/Enemy0.xpm");
	enemy->img[1] = image_creator(mlx, "Textures/Enemy1.xpm");
	enemy->img[2] = image_creator(mlx, "Textures/Enemy2.xpm");
	enemy->img[3] = image_creator(mlx, "Textures/Enemy3.xpm");
	enemy->img[4] = image_creator(mlx, "Textures/Enemy4.xpm");
	enemy->x = x;
	enemy->y = y;
	enemy->next = NULL;
	enemy->status = rand() % 5;
	enemy->t[0] = get_time();
	enemy->t[1] = get_time();
}

t_object	*enemy_creator(char **map, void *mlx)
{
	t_object	*enemies;
	t_object	*new;
	int			x;
	int			y;

	enemies = NULL;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'X')
			{
				new = malloc(sizeof(t_object));
				if (!new)
					error_management(3, (t_all *) NULL);
				enemy_setup(new, mlx, x, y);
				add_back(&enemies, new);
			}
			x++;
		}
		y++;
	}
	return (enemies);
}

void	status_changer(t_object **enemies, int i)
{
	t_object	*current;

	current = *enemies;
	while (current)
	{
		if (get_time() > current->t[0])
		{
			if (current->status != 4)
				current->status++;
			else
				current->status = 0;
			current->t[0] = get_time() + i;
		}
		current = current->next;
	}
}

void	enemy_mover(t_object **enemies, t_map map)
{
	t_object	*current;

	current = *enemies;
	while (current)
	{
		if (get_time() > current->t[1])
		{
			current->dir = rand() % 4;
			if (current->dir == 0 && map.map[current->y][current->x + 1] != '1')
				current->x++;
			if (current->dir == 1 && map.map[current->y][current->x - 1] != '1')
				current->x--;
			if (current->dir == 2 && map.map[current->y + 1][current->x] != '1')
				current->y++;
			if (current->dir == 3 && map.map[current->y - 1][current->x] != '1')
				current->y--;
			current->t[1] = get_time() + 400;
		}
		current = current->next;
	}
}
