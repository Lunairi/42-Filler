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

void	color_piece(t_visual *visual, int x, int y, char p)
{
	t_vcord	pt;

	pt.x0 = x * visual->x_size + visual->border + visual->x_offset;
	pt.x1 = (x + 1) * visual->x_size - visual->border + visual->x_offset;
	pt.y0 = y * visual->y_size + visual->border + visual->y_offset;
	pt.y1 = (y + 1) * visual->y_size - visual->border + visual->y_offset;
	while (pt.x0 < pt.x1)
	{
		if ((p == 'O') &&
			(visual->pix[pt.y0 + (pt.x0 * visual->s_line / 4)] == 0x303030 ||
			visual->pix[pt.y0 + (pt.x0 * visual->s_line / 4)] == 0))
			visual->pix[pt.y0 + (pt.x0 * visual->s_line / 4)] = 0xFF00FF;
		else if ((p == 'X') &&
			(visual->pix[pt.y0 + (pt.x0 * visual->s_line / 4)] == 0x303030 ||
			visual->pix[pt.y0 + (pt.x0 * visual->s_line / 4)] == 0))
			visual->pix[pt.y0 + (pt.x0 * visual->s_line / 4)] = 0x099FFF;
		else if ((p == '.') &&
			(visual->pix[pt.y0 + (pt.x0 * visual->s_line / 4)] == 0))
			visual->pix[pt.y0 + (pt.x0 * visual->s_line / 4)] = 0x303030;
		if (++pt.y0 > pt.y1)
		{
			pt.y0 = y * visual->y_size + visual->border + visual->y_offset;
			pt.x0++;
		}
	}
}

void	check_vis_overflow(t_filler *game, int *x, int *y)
{
	*y = *y + 1;
	if (*y > game->map_col)
	{
		*y = 0;
		*x = *x + 1;
	}
}

void	visualizer(t_filler *game, t_coords *map, t_visual *visual)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (x < game->map_row)
	{
		// if (game->map[x][y] == 'O' || game->map[x][y] == 'X')
		// {
			color_piece(visual, x , y, game->map[x][y]);
			check_vis_overflow(game, &x, &y);
		// }
		// else
		// 	check_vis_overflow(game, &x, &y);
	}
	mlx_put_image_to_window(visual->mlx, visual->win, visual->img, 0, 0);
}	

void	init_map(t_visual *visual)
{
	visual->mlx = mlx_init();
	visual->win = mlx_new_window(visual->mlx, 1000, 1000, "Kill me please");
	visual->img = mlx_new_image(visual->mlx, 1000, 1000);
	visual->pix = (int*)mlx_get_data_addr(visual->img,
		&(visual->bits), &(visual->s_line), &(visual->endian));
}

void	initialize_visualizer(t_filler *game, t_coords *map, t_visual *visual)
{
	if (visual->init == 0)
	{
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
		init_map(visual);
		visual->init = 1;
	}
	else
		visualizer(game, map, visual);
}