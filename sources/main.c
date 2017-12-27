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

void	hub(t_filler *game, t_coords *map, t_visual *visual, char *string)
{
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
	{
		initialize_visualizer(game, map, visual);
		mlx_do_sync(visual->mlx);
	}
}

int		main(void)
{
	char		*string;
	t_filler	*game;
	t_coords	*map;
	t_visual	*visual;

	visual = ft_memalloc(sizeof(t_visual));
	map = ft_memalloc(sizeof(t_coords));
	game = ft_memalloc(sizeof(t_filler));
	map->behave = 0;
	while (game->track != 5 && get_next_line(0, &string))
		hub(game, map, visual, string);
	free(string);
	free(map);
	free(game);
	free(visual);
	sleep(3);
	return (0);
}
