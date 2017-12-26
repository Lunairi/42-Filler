/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_board.c                                       :+:      :+:    :+:   */
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
	map->row = 0;
	map->col = 0;
	map->j = 0;
	map->k = -1;
	map->valid = 0;
}

static void	truncate_spots(t_filler *game, t_coords *map)
{
	int z;

	z = 0;
	map->k++;
	if (map->k >= game->piece_col)
	{
		map->k = 0;
		map->j++;
	}
	if (map->j >= game->piece_row)
			z = 1;
	while (z == 0)
	{
		if (game->piece[map->j][map->k] == '.')
		{
			map->k++;
			if (map->k >= game->piece_col)
			{
				map->k = 0;
				map->j++;
			}
		}
		else
			z = 1;
		if (map->j >= game->piece_row)
			z = 1;
	}
}

static void	check_piece(t_filler *game, t_coords *map)
{
	if (game->track != 4)
		map->valid = fill_bottom(game, map);
	else if (game->track == 4)
	{
		while ((map->j < game->piece_row) && map->valid != 1)
		{
			truncate_spots(game, map);
		if (map->j < game->piece_row)
			map->valid = fill_bottom(game, map);
		}
	}
	if (map->valid == 1)
		place_piece(game, map);
	else
		map->valid = 0;
}

int		fill_board(t_filler *game, t_coords *map)
{
	reset_coords(game, map);
	truncate_spots(game, map);
	while (map->valid == 0)
	{
		if (game->map[map->row][map->col] == ft_toupper(game->player_number))
		{
			if (game->track == 4)
			{
				map->j = 0;
				map->k = -1;
			}
			check_piece(game, map);
		}
		if (++map->col >= game->map_col)
		{
			map->col = 0;
			map->row++;
		}
		if ((map->row >= game->map_row) && game->track == 4)
		{
			game->track = 5;
			ft_printf("0 0\n");
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
