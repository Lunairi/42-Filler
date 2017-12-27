/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place_top.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlu <mlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 20:59:44 by mlu               #+#    #+#             */
/*   Updated: 2017/11/28 17:43:16 by mlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static void	set_scan_value(t_filler *game, t_coords *map)
{
	map->x = game->piece_row - 1;
	map->y = game->piece_col - 1;
	map->valid = 0;
	map->place = 0;
}

static void	check_overflow(t_filler *game, t_coords *map)
{
	if (--map->y < 0)
	{
		map->y = game->piece_col - 1;
		map->x--;
	}
}

static int	validate_spot(t_filler *game, t_coords *map)
{
	if (game->map[map->row + map->x - map->j]
			[map->col + map->y - map->k] == '.')
		check_overflow(game, map);
	else if (map->place == 0)
	{
		check_overflow(game, map);
		map->place = 1;
	}
	else
		return (0);
	return (1);
}

int			fill_top(t_filler *game, t_coords *map)
{
	set_scan_value(game, map);
	while (map->x >= 0)
	{
		if (game->piece[map->x][map->y] == '*')
		{
			if (((map->row + map->x - map->j) < game->map_row) &&
				((map->row + map->x - map->j) >= 0))
			{
				if (!(validate_spot(game, map)))
					return (2);
			}
			else
				return (2);
		}
		else
			check_overflow(game, map);
	}
	return (1);
}
