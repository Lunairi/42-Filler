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
	int		t;
	// char *ret;
	game = ft_memalloc(sizeof(t_filler));
	game->i = 0;
	game->map = ft_memalloc(sizeof(char) * 100);
	string = ft_memalloc(sizeof(char));
	while (get_next_line(0, &string) && string != NULL)
	{
		if (game->p == 0)
		{
			// game->p_number = ft_memalloc(sizeof(char) * ft_strlen(string));
			game->p_number = string;
			fprintf(stderr, "PLAYER NUMBER %s\n", game->p_number);
			game->p++;
		}
		else if (game->p == 1)
		{
			// game->m_info = ft_memalloc(sizeof(char) * ft_strlen(string));
			game->m_info = string;
			fprintf(stderr, "MAP INFO %s\n", game->m_info);
			game->p++;
		}
		else if ((!(ft_strstr(string, "Plateau"))) &&
				(!(ft_strstr(string, "Piece"))) && game->p == 2)
		{
			// game->map[game->i] = ft_memalloc(sizeof(char) * ft_strlen(string));
			game->map[game->i] = string;
			fprintf(stderr, "MAP [%i] %s\n", game->i, game->map[game->i]);
			game->i++;
		}
		else if (ft_strstr(string, "Piece"))
		{
			// game->p_info = ft_memalloc(sizeof(char) * ft_strlen(string));
			game->p_info = string;
			fprintf(stderr, "PIECE INFO %s\n", game->p_info);
			game->piece = ft_memalloc(sizeof(char*) * 100);
			game->p++;
		}
		else if (game->p == 3)
		{
			game->piece[game->j] = string;
			fprintf(stderr, "PIECE [%i] %s\n", game->j, game->piece[game->j]);
			game->i++;
		}
	}
	// string = ft_fdtostr(0);
	// fprintf(stderr, "MAP %s\n", string);
	free(string);
	free(game);
	fprintf(stdout, "8 1\n");

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