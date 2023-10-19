/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorais- <amorais-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 13:27:55 by amorais-          #+#    #+#             */
/*   Updated: 2023/01/31 10:07:44 by amorais-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	weapon_creator(int keycode, t_all *all)
{
	t_object	*new;

	if (keycode == 32)
	{
		new = malloc(sizeof(t_object));
		if (!new)
			error_management(3, all);
		new->dir = all->master->status;
		new->x = all->master->x;
		new->y = all->master->y;
		new->img[0] = image_creator(all->mlx, "Textures/Weapon0.xpm");
		new->img[1] = image_creator(all->mlx, "Textures/Weapon1.xpm");
		new->img[2] = image_creator(all->mlx, "Textures/Weapon2.xpm");
		new->img[3] = image_creator(all->mlx, "Textures/Weapon3.xpm");
		new->img[4] = image_creator(all->mlx, "Textures/Weapon4.xpm");
		new->status = 1;
		new->next = NULL;
		new->t[0] = get_time();
		new->t[1] = get_time();
		add_back(&(all->weapons), new);
	}
	return (0);
}

void	weapon_mover(t_object **weapon)
{
	t_object	*current;

	current = *weapon;
	while (current)
	{
		if (get_time() > current->t[1])
		{
			if (current->dir == 1)
				current->x--;
			if (current->dir == 2)
				current->y--;
			if (current->dir == 3)
				current->x++;
			if (current->dir == 4)
				current->y++;
			current->t[1] = get_time() + 50;
		}
		current = current->next;
	}
}

int	check_enemy(t_object *w, t_object **e, void *mlx)
{
	int			i;
	t_object	*cur;
	t_object	*temp;

	i = 0;
	if (*e && (*e)->x == w->x && (*e)->y == w->y)
	{
		temp = *e;
		*e = (*e)->next;
		object_clear(temp, mlx);
		i = 1;
	}
	cur = (*e);
	while (cur && cur->next)
	{
		if (cur->next->x == w->x && cur->next->y == w->y)
		{
			temp = cur->next;
			cur->next = temp->next;
			object_clear(temp, mlx);
			i = 1;
		}
		cur = cur->next;
	}
	return (i);
}

void	check_weapons(t_object **w, t_object **e, char **map, void *mlx)
{
	t_object	*cur;
	t_object	*temp;

	while (*w && (map[(*w)->y][(*w)->x] == '1' || check_enemy(*w, e, mlx)))
	{
		temp = *w;
		*w = (*w)->next;
		object_clear(temp, mlx);
	}
	cur = (*w);
	while (cur && cur->next)
	{
		if (map[cur->next->y][cur->next->x] == '1' || \
		check_enemy(cur->next, e, mlx))
		{
			temp = cur->next;
			cur->next = temp->next;
			object_clear(temp, mlx);
		}
		cur = cur->next;
	}
}
