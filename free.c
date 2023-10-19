/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorais- <amorais-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 11:01:51 by amorais-          #+#    #+#             */
/*   Updated: 2023/01/31 10:02:32 by amorais-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	array_clear(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	array = NULL;
}

void	object_clear(t_object *obj, void *mlx)
{
	obj_image_destroyer(&obj->img[0], mlx);
	obj_image_destroyer(&obj->img[1], mlx);
	obj_image_destroyer(&obj->img[2], mlx);
	obj_image_destroyer(&obj->img[3], mlx);
	obj_image_destroyer(&obj->img[4], mlx);
	free(obj);
}

void	clear_enemies(t_object **enemies, void *mlx)
{
	t_object	*temp;

	while (*enemies)
	{
		temp = (*enemies)->next;
		object_clear(*enemies, mlx);
		(*enemies) = temp;
	}
}

void	clear_all(t_all *all)
{
	array_clear(all->map.map);
	close(all->map.fd);
	mlx_destroy_image(all->mlx, all->coll.img);
	mlx_destroy_image(all->mlx, all->wall.img);
	mlx_destroy_image(all->mlx, all->floor.img);
	mlx_destroy_image(all->mlx, all->canva[0].img);
	mlx_destroy_image(all->mlx, all->canva[1].img);
	object_clear(all->master, all->mlx);
	object_clear(all->exit, all->mlx);
	clear_enemies(&(all->enemies), all->mlx);
	clear_enemies(&(all->weapons), all->mlx);
	mlx_destroy_window(all->mlx, all->win);
	mlx_destroy_display(all->mlx);
	free(all->moves);
	free(all->mlx);
}
