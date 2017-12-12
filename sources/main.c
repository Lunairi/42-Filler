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

int		main(void)
{
	char *string;
	t_filler *game;
	t_coords *map;
	int		t;
	// char *ret;
	t = 0;
	map = ft_memalloc(sizeof(t_coords));
	game = ft_memalloc(sizeof(t_filler));
	while (game->track != 4 && get_next_line(0, &string))
	{
		// fprintf(stderr, "COCK game->track[%i]\n", game->track);
		if (ft_strstr(string, "exec"))
			parse_player_number(game, 0, string);
		else if (ft_strstr(string, "Plateau"))
			parse_map_size(game, 0, string);
		else if ((!(ft_strstr(string, "Piece")))
			&& (!(ft_strstr(string, "012345"))) && game->track == 1)
			parse_map_detail(game, 0, string);
		else if (ft_strstr(string, "Piece"))
			parse_piece_size(game, 0, string);
		else if (game->track == 2)
			parse_piece_detail(game, string);
		if (game->track == 3)
			check_spot(game, map);
	}
	free(string);
	free(map);
	free(game);
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

// ./resources/filler_vm -f ./resources/maps/map00 -p1 ./mlu.filler