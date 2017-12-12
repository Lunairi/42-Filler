/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_board.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlu <mlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 20:59:44 by mlu               #+#    #+#             */
/*   Updated: 2017/11/28 17:43:16 by mlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

// parse map
// parse difference from top left corner of piece -> actual pieces
// determine distance from p1 to p2 and vice versa
// find first point to check if shape pieces can match
// if true, place piece, set pars eloop to 0


void	reset_coords(t_coords *map)
{
	map->row = 0;
	map->col = 0;
	map->p_row = 0;
	map->p_col = 0;
	map->valid = 0;
}

void	set_scan_value(t_coords *map)
{
	map->x = 0;
	map->y = 0;
	map->valid = 0;
	map->place = 0;
}

void	check_overflow(t_filler *game, t_coords *map)
{
	if ((++map->y + map->p_col) >= game->piece_col)
	{
		map->y = 0 - map->p_col;
		map->x++;
	}
}

/*
** By the time place_piece is called, you know which spot the map is on due to
** map->row and map->col, and we know where the piece is based off
** map->p_row and map->p_col, so we need to check all valid pieces
*/

int		validate_spot(t_filler *game, t_coords *map)
{
	if (game->map[map->row + map->x - map->j][map->col + map->y - map->k] == '.')
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

int		fill_bottom_right(t_filler *game, t_coords *map)
{
	set_scan_value(map);
	while((map->p_row + map->x) < game->piece_row)
	{
		if (game->piece[map->p_row + map->x][map->p_col + map->y] == '*')
		{
			if ((map->row + map->x - map->j) < game->map_row)
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

void	truncate_spots(t_filler *game, t_coords *map)
{
	int z;

	z = 0;
	map->j = 0;
	map->k = 0;
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

void	place_piece(t_filler *game, t_coords *map)
{
	ft_printf("%i %i\n", (map->row - map->j), (map->col - map->k));
	game->track = 0;
}

void	check_piece(t_filler *game, t_coords *map)
{
	map->valid = fill_bottom_right(game, map);
	if (map->valid == 1)
		place_piece(game, map);
	else
		map->valid = 0;
}

int		check_spot(t_filler *game, t_coords *map)
{
	reset_coords(map);
	truncate_spots(game, map);
	while ((map->row < game->map_row) && map->valid == 0)
	{
		if (game->map[map->row][map->col] == ft_toupper(game->player_number))
			check_piece(game, map);
		if (++map->col >= game->map_col)
		{
			map->col = 0;
			map->row++;
		}
		if (map->row >= game->map_row)
		{
			game->track = 4;
			ft_printf("0 0\n");
			return (0);
		}
	}
	return (0);
}

void	visualizer(t_filler *game, t_coords *map, t_visual *visual)
{

}
