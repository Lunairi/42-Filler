/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlu <mlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 20:59:44 by mlu               #+#    #+#             */
/*   Updated: 2017/11/28 17:43:16 by mlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		color_value(t_visual *visual, t_vcord pt)
{
	if (visual->pix[pt.y0 + (pt.x0 * visual->s_line / 4)] != 0x303030
			&& pt.p == 'O')
		return (0x0062FF);
	if (visual->pix[pt.y0 + (pt.x0 * visual->s_line / 4)] != 0x303030
			&& pt.p == 'X')
		return (0xCC00FF);
	return (0xFFFFFF);
}

void	color_piece(t_filler *game, t_coords *map,
				t_visual *visual, t_vcord pt)
{
	pt.x0 = pt.x * visual->x_size + visual->border + visual->x_offset;
	pt.x1 = (pt.x + 1) * visual->x_size - visual->border + visual->x_offset;
	pt.y0 = pt.y * visual->y_size + visual->border + visual->y_offset;
	pt.y1 = (pt.y + 1) * visual->y_size - visual->border + visual->y_offset;
	if (pt.p == 'O')
		pt.color = color_value(visual, pt);
	else if (pt.p == 'X')
		pt.color = color_value(visual, pt);
	while (pt.x0 < pt.x1)
	{
		if (pt.p == 'O')
			visual->pix[pt.y0 + (pt.x0 * visual->s_line / 4)] = pt.color;
		else if (pt.p == 'X')
			visual->pix[pt.y0 + (pt.x0 * visual->s_line / 4)] = pt.color;
		if (visual->init == 1)
			visual->pix[pt.y0 + (pt.x0 * visual->s_line / 4)] = 0x303030;
		if (++pt.y0 > pt.y1)
		{
			pt.y0 = pt.y * visual->y_size + visual->border + visual->y_offset;
			pt.x0++;
		}
	}
}

void		visualizer(t_filler *game, t_coords *map, t_visual *visual)
{
	t_vcord	pt;

	while (pt.x < game->map_row)
	{
		if (game->map[pt.x][pt.y] == 'O' || game->map[pt.x][pt.y] == 'X')
		{
			pt.p = game->map[pt.x][pt.y];
			color_piece(game, map, visual, pt);
		}
		if (visual->init == 1 && game->map[pt.x][pt.y] == '.')
			color_piece(game, map, visual, pt);
		if (++pt.y > game->map_col)
		{
			pt.y = 0;
			pt.x++;
		}
	}
}

void		init_map(t_filler *game, t_coords *map, t_visual *visual)
{
	visual->mlx = mlx_init();
	visual->win = mlx_new_window(visual->mlx, 1000, 1000, "Kill me please");
	visual->img = mlx_new_image(visual->mlx, 1000, 1000);
	visual->pix = (int*)mlx_get_data_addr(visual->img,
		&(visual->bits), &(visual->s_line), &(visual->endian));
	visual->x_size = (1000 / game->map_row);
	visual->y_size = (1000 / game->map_col);
	visual->x_offset = (1000 - (visual->x_size * game->map_row)) / 2;
	visual->y_offset = (1000 - (visual->y_size * game->map_col)) / 2;
	if (game->map_row < 20)
		visual->border = 6;
	else if (game->map_row < 80)
		visual->border = 4;
	else
		visual->border = 2;
	if (visual->init == 1)
		visualizer(game, map, visual);
}
