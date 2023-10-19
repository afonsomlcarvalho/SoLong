/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorais- <amorais-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 14:00:54 by amorais-          #+#    #+#             */
/*   Updated: 2023/10/19 18:00:01 by amorais-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "mlx_linux1/mlx.h"
# include "getnextline/get_next_line.h"
# include "printf/ft_printf.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_coords
{
	int	x;
	int	y;
}				t_coords;

typedef struct s_img
{
	void	*img;
	int		width;
	int		height;
	char	*path;
	char	*addr;
	int		bpp;
	int		ll;
	int		endian;
}				t_img;

typedef struct s_object
{
	int				x;
	int				y;
	int				status;
	t_img			img[5];
	struct s_object	*next;
	int				dir;
	time_t			t[2];
}				t_object;

typedef struct s_map
{
	char		**map;
	int			height;
	int			width;
	int			fd;
	t_coords	exit;
	t_coords	master;
}				t_map;

typedef struct s_all
{
	void		*mlx;
	void		*win;
	t_map		map;
	t_object	*master;
	t_object	*exit;
	t_img		canva[2];
	t_img		floor;
	t_img		wall;
	t_img		coll;
	int			counter;
	char		*moves;
	t_object	*enemies;
	t_object	*weapons;
}				t_all;

t_map			map_creator(char *map_name);
void			array_clear(char **map);
t_img			image_creator(void *mlx, char *path);
void			master_setup(t_all *all);
void			display_floor(t_img canva, t_img floor, t_map map);
void			display_map(t_all all);
void			display_master(t_all all);
unsigned int	get_color(t_img img, int x, int y);
void			put_pixel_img(t_img img, int x, int y, int color);
void			clear_all(t_all *all);
int				is_walkable(t_all *all, int x, int y);
int				count_chars(char **map, char c);
void			object_clear(t_object *obj, void *mlx);
void			obj_image_destroyer(t_img *img, void *mlx);
char			**array_dup(char **array);
int				map_validator(t_map map);
void			obj_image_destroyer(t_img *img, void *mlx);
char			*line_join(char	*line, char	*gnl, int f);
char			*moves_str(t_all *all);
char			*moves_str(t_all *all);
t_object		*enemy_creator(char **map, void *mlx);
void			put_enemies(t_object *enemies, t_img canva);
int				colusion(t_object *master, t_object *enemy);
time_t			get_time(void);
void			status_changer(t_object **enemies, int i);
void			enemy_mover(t_object **enemies, t_map map);
void			put_str_win(t_all *all);
void			add_back(t_object **enemies, t_object *new);
int				weapon_creator(int keycode, t_all *all);
void			weapon_mover(t_object **weapon);
void			object_clear(t_object *obj, void *mlx);
void			check_weapons(t_object **w, t_object **e, \
char **map, void *mlx);
int				end(t_all *all);
void			error_management(int code, t_all *all);
void			finish(t_all *all);

#endif