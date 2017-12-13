/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlu <mlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 20:59:44 by mlu               #+#    #+#             */
/*   Updated: 2017/11/28 17:43:16 by mlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	thread_count_set(t_filler *game, t_coords *map, t_visual *visual, int *size)
{
	if (game->map_row < 20)
		*size = 2;
	else if (game->map_row < 80)
		*size = 3;
	else
		*size = 10;
}

int		main(void)
{
	char *string;
	t_filler *game;
	t_coords *map;
	t_visual *visual;
	int	size;

	visual = ft_memalloc(sizeof(t_visual));
	map = ft_memalloc(sizeof(t_coords));
	game = ft_memalloc(sizeof(t_filler));
	while (game->track != 4 && get_next_line(0, &string))
	{
		if (ft_strstr(string, "exec"))
			parse_player_number(game, 0, string);
		else if (ft_strstr(string, "Plateau"))
			parse_map_size(game, 0, string);
		else if ((!(ft_strstr(string, "Piece")))
			&& (!(ft_strstr(string, "012345"))) && game->track == 1)
			parse_map_detail(game, 0, string);
		else if (ft_strstr(string, "Piece"))
		{
			thread_count_set(game, map, visual, &size);
			initialize_visualizer(game, map, visual, size);
			mlx_do_sync(visual->mlx);
			parse_piece_size(game, 0, string);
		}
		else if (game->track == 2)
			parse_piece_detail(game, string);
		if (game->track == 3)
			check_spot(game, map);
	}
	free(string);
	free(map);
	free(game);
	free(visual);
	sleep(10);
	return (0);
}

// $$$ exec p1 : [user1]
// Plateau 14 30:
// 012345678901234567890123456789
// 000 ..............................
// 001 ..............................
// 002 ..............................
// 003 ..............................
// 004 ......X.......................
// 005 ..............................
// 006 ..............................
// 007 ..........................O...
// 008 ..............................
// 009 ..............................
// 010 ..............................
// 011 ..............................
// 012 ..............................
// 013 ..............................
// Piece 3 6:
// .****.
// **....
// *.....

// ./resources/filler_vm -f ./resources/maps/map00 -p1 ./mlu.filler -p2 ./resources/players/