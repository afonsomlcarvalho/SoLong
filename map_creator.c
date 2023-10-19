/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_creator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorais- <amorais-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 13:07:38 by amorais-          #+#    #+#             */
/*   Updated: 2023/01/31 10:05:20 by amorais-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	*line_join(char	*line, char	*gnl, int f)
{
	char	*new_line;
	int		i;
	int		j;

	if (!line)
		return (gnl);
	new_line = malloc(ft_strlen(line) + ft_strlen(gnl) + 1);
	if (!new_line)
		error_management(3, (t_all *) NULL);
	i = -1;
	j = -1;
	while (line[++i])
		new_line[i] = line[i];
	while (gnl[++j])
		new_line[i + j] = gnl[j];
	new_line[i + j] = '\0';
	if (f && line)
		free(line);
	free(gnl);
	return (new_line);
}

void	coords(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->map[y][x] == 'P')
			{
				map->master.x = x;
				map->master.y = y;
			}
			else if (map->map[y][x] == 'E')
			{
				map->exit.x = x;
				map->exit.y = y;
			}
			x++;
		}
		y++;
	}
}

t_map	map_creator(char *map_name)
{
	t_map	map;
	char	*line;
	char	*gnl;

	map.fd = open(map_name, O_RDONLY);
	if (map.fd == -1)
		error_management(2, (t_all *) NULL);
	gnl = get_next_line(map.fd);
	line = NULL;
	map.height = 0;
	while (gnl)
	{
		line = line_join(line, gnl, 1);
		gnl = get_next_line(map.fd);
		map.height++;
	}
	map.map = ft_split(line, '\n');
	map.width = ft_strlen(map.map[0]);
	coords(&map);
	free(line);
	return (map);
}

int	can_p(char **map, int x, int y, int dir)
{
	char	**map_dup;

	if (dir == 0)
	{
		map_dup = array_dup(map);
		dir = can_p(map_dup, x, y, 5);
		array_clear(map_dup);
		return (dir);
	}
	if (x < 0 || y < 0 || !map[y][x] || map[y][x] == '1' || \
	(map[y][x] == 'E' && dir != 5))
		return (0);
	if (map[y][x] == 'P')
		return (1);
	map[y][x] = '1';
	if (dir != 2 && can_p(map, x + 1, y, 1))
		return (1);
	if (dir != 1 && can_p(map, x - 1, y, 2))
		return (1);
	if (dir != 4 && can_p(map, x, y + 1, 3))
		return (1);
	if (dir != 3 && can_p(map, x, y - 1, 4))
		return (1);
	return (0);
}

int	map_validator(t_map map)
{
	int	x;
	int	y;

	y = 0;
	while (map.map[y])
	{
		x = 0;
		while (map.map[y][x])
		{
			if (map.map[y][x] != '1' && map.map[y][x] != '0' && map.map[y][x] \
			!= 'C' && map.map[y][x] != 'P' && map.map[y][x] != 'E' \
			&& map.map[y][x] != 'X')
				return (0);
			if ((x == 0 || y == 0 || x == map.width - 1 || y == map.height - 1) \
			&& map.map[y][x] != '1')
				return (0);
			if (map.map[y][x++] == 'C' && !can_p(map.map, x - 1, y, 0))
				return (0);
		}
		if (x != map.width)
			return (0);
		y++;
	}
	return (can_p(map.map, map.exit.x, map.exit.y, 0) && \
	count_chars(map.map, 'P') == 1 && count_chars(map.map, 'E') == 1);
}
