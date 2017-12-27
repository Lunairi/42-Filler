/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlu <mlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 20:59:44 by mlu               #+#    #+#             */
/*   Updated: 2017/11/28 17:43:16 by mlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	place_piece(t_filler *game, t_coords *map)
{
	game->track = 3;
	ft_printf("%i %i\n", (map->row - map->j), (map->col - map->k));
	game->track = 0;
}

void	check_cut(t_coords *map, t_filler *game)
{
	if (map->k < 0)
	{
		map->k = game->piece_col - 1;
		map->j--;
	}
}

void	check_fill(t_coords *map, t_filler *game)
{
	if (map->k >= game->piece_col)
	{
		map->k = 0;
		map->j++;
	}
}

int		control_cut(t_filler *game, t_coords *map)
{
	if (--map->col < (game->map_col * (1 / 2)))
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
	return (1);
}

int		control_fill(t_filler *game, t_coords *map)
{
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
	return (1);
}
