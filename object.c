/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorais- <amorais-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 11:02:46 by amorais-          #+#    #+#             */
/*   Updated: 2023/01/31 10:06:40 by amorais-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	exit_setup(t_all *all)
{
	all->exit = malloc(sizeof(t_object));
	if (!all->exit)
		error_management(3, all);
	all->exit->status = 0;
	all->exit->x = all->map.exit.x;
	all->exit->y = all->map.exit.y;
	all->exit->img[0] = image_creator(all->mlx, "Textures/Exit_0.xpm");
	all->exit->img[1] = image_creator(all->mlx, "Textures/Exit_1.xpm");
	all->exit->img[2].img = NULL;
	all->exit->img[3].img = NULL;
	all->exit->img[4].img = NULL;
}

void	master_setup(t_all *all)
{
	all->master = malloc(sizeof(t_object));
	if (!all->master)
		error_management(3, all);
	all->master->status = 4;
	all->master->x = all->map.master.x;
	all->master->y = all->map.master.y;
	all->master->img[0] = image_creator(all->mlx, "Textures/Dead.xpm");
	all->master->img[1] = image_creator(all->mlx, "Textures/Walk_left.xpm");
	all->master->img[2] = image_creator(all->mlx, "Textures/Walk_up.xpm");
	all->master->img[3] = image_creator(all->mlx, "Textures/Walk_right.xpm");
	all->master->img[4] = image_creator(all->mlx, "Textures/Walk_down.xpm");
	all->master->t[0] = get_time();
	exit_setup(all);
}

t_img	image_creator(void *mlx, char *path)
{
	t_img	img;

	img.img = mlx_xpm_file_to_image(mlx, path, &img.width, &img.height);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.ll, &img.endian);
	return (img);
}

void	obj_image_destroyer(t_img *img, void *mlx)
{
	if (img->img)
		mlx_destroy_image(mlx, img->img);
	img->img = NULL;
}
