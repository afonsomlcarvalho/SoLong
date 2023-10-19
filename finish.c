/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorais- <amorais-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 12:14:40 by amorais-          #+#    #+#             */
/*   Updated: 2023/01/31 10:03:37 by amorais-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	error_management(int code, t_all *all)
{
	if (code == 1)
	{
		printf("Error.\nInvalid map.\n");
		array_clear(all->map.map);
	}
	else if (code == 2)
		printf("Error.\nMap not found.\n");
	else if (code == 3)
		printf("Error\nMalloc failure.\n");
	exit(0);
}

int	end(t_all *all)
{
	clear_all(all);
	exit (0);
	return (0);
}

void	finish(t_all *all)
{
	if (get_time() < all->master->t[0])
		return ;
	if (all->master->status == 0)
		printf("You died.\n");
	else if (all->master->x == all->exit->x && all->master->y == all->exit->y)
		printf("You won with %d movements.\n", all->counter);
	else
		return ;
	end(all);
}
