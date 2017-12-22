/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_stdin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlu <mlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 20:59:44 by mlu               #+#    #+#             */
/*   Updated: 2017/11/28 17:43:16 by mlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	parse_player_number(t_filler *game, int t, char *string)
{
	while (string[t] != 'p')
		t++;
	if (string[++t] == '1')
		game->player_number = 'o';
	else
		game->player_number = 'x';
}

void	parse_map_size(t_filler *game, int t, char *string)
{
	game->map_row = 0;
	game->map_col = 0;
	while (string[t] != ' ')
		t++;
	while (string[++t] != ' ')
		game->map_row = game->map_row * 10 + (string[t] - '0');
	while (string[++t] != ':')
		game->map_col = game->map_col * 10 + (string[t] - '0');
	game->map = ft_memalloc(sizeof(char*) * (game->map_row));
	game->track = 1;
	game->i = 0;
}

void	parse_map_detail(t_filler *game, char *tmp, char *string)
{
	tmp = string;
	tmp += 4;
	game->map[game->i] = tmp;
	game->i++;
}

void	parse_piece_size(t_filler *game, int t, char *string)
{
	game->piece_row = 0;
	game->piece_col = 0;
	free(game->piece);
	while (string[t] != ' ')
		t++;
	while (string[++t] != ' ')
		game->piece_row = game->piece_row * 10 + (string[t] - '0');
	while (string[++t] != ':')
		game->piece_col = game->piece_col * 10 + (string[t] - '0');
	game->piece = ft_memalloc(sizeof(char*) * (game->piece_row));
	game->track = 2;
}

void	parse_piece_detail(t_filler *game, char *string)
{
	game->piece[game->j] = string;
	game->j++;
	game->parse_loop++;
	if (game->parse_loop == game->piece_row)
	{
		game->j = 0;
		game->parse_loop = 0;
		game->track = 3;
	}
}
