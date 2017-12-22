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
	map->row = 0;
	map->col = game->col - 1;
	map->j = 0;
	map->k = -1;
	map->valid = 0;
}

void	find_spot_last(t_filler *game, t_coords *map)
{
	int z;

	z = 0;
	while (z == 0)
	{
		if (game->piece[map->j][map->k] == '.')
		{
			map->k--;
			if (map->k >= game->piece_col)
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


int		check_spot(t_filler *game, t_coords *map)
{
	reset_coords(game, map);
	find_spot_last(game, map);
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
		if (--map->col < 0)
		{
			map->col = game->col - 1;
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