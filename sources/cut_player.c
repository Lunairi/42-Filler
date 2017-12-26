/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_player.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlu <mlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 20:59:44 by mlu               #+#    #+#             */
/*   Updated: 2017/11/28 17:43:16 by mlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static void	reset_coords(t_filler *game, t_coords *map)
{
	map->row = map->current;
	map->col = game->map_col - 1;
	map->j = game->piece_row - 1;
	map->k = game->piece_col - 1;
	map->valid = 0;
}

static void	find_spot_last(t_filler *game, t_coords *map)
{
	int z;

	z = 0;
	map->k--;
	if (map->k < 0)
	{
		map->k = game->piece_col - 1;
		map->j--;
	}
	if (map->j < 0)
		z = 1;
	while (z == 0)
	{
		if (game->piece[map->j][map->k] == '.')
		{
			map->k--;
			if (map->k < 0)
			{
				map->k = game->piece_col - 1;
				map->j--;
			}
		}
		else
			z = 1;
		if (map->j < 0)
			z = 1;
	}
}

static void	check_piece(t_filler *game, t_coords *map)
{
	// if (game->track != 4)
	// 	map->valid = fill_top(game, map);
	// else if (game->track == 4)
	// {
		while ((map->j >= 0) && map->valid != 1)
		{
			find_spot_last(game, map);
		if (map->j >= 0)
			map->valid = fill_bottom(game, map);
		}
	// }
	if (map->valid == 1)
		place_piece(game, map);
	else
		map->valid = 0;
}



int		cut_player(t_filler *game, t_coords *map)
{
	static int i;

	i = 0;
	reset_coords(game, map);
	// find_spot_last(game, map);
	while (map->valid == 0)
	{
		if (game->map[map->row][map->col] == ft_toupper(game->player_number))
		{
			if (i == 0)
			{
				i++;
				map->current = map->row;
			}
			// if (game->track == 4)
			// {
				map->j = game->piece_row - 1;
				map->k = game->piece_col - 1;
			// }
			check_piece(game, map);
		}
		if (--map->col < (game->map_col * (1/2)))
		{
			map->col = game->map_col - 1;
			map->row++;
		}
		if ((map->row >= game->map_row) && game->track == 4)
		{
			game->track = 3;
			map->behave = 1;
			return (0);
		}
		if ((map->row >= game->map_row) && game->track == 3)
		{
			reset_coords(game, map);
			game->track = 4;
		}
	}
	return (0);
}