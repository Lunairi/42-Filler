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

void	initialize_visualizer(t_visual *visual)
{
	visual->mlx = mlx_init();
	visual->map = mlx_new_window(map->mlx, 1100, 1100, "Kill me please");
	visual->img = mlx_new_image(map->mlx, 1100, 1100);
	visual->pix = (int*)mlx_get_data_addr(visual->img,
		&(visual->bits), &(visual->s_line), &(visual->endian));
}

int		main(void)
{
	char *string;
	t_filler *game;
	t_coords *map;
	t_visual *visual;

	visual = ft_memalloc(sizeof(t_visual));
	map = ft_memalloc(sizeof(t_coords));
	game = ft_memalloc(sizeof(t_filler));
	initialize_visualizer(visual);
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