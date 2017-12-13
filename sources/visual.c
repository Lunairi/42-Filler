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

int		check_addr(t_visual *visual, t_vcord pt, char p)
{
	if (p == 'O' || p == 'X')
	{
		if (visual->pix[pt.y0 + (pt.x0 * visual->s_line / 4)] == 0x303030)
			return (1);
		if (visual->pix[pt.y0 + (pt.x0 * visual->s_line / 4)] == 0)
			return (1);
	}
	if (p == '.')
		if (visual->pix[pt.y0 + (pt.x0 * visual->s_line / 4)] == 0)
			return (1);
	return (0);
}

void	color_piece(t_visual *visual, int x, int y, char p)
{
	t_vcord	pt;

	pt.x0 = x * visual->x_size + visual->border + visual->x_offset;
	pt.x1 = (x + 1) * visual->x_size - visual->border + visual->x_offset;
	pt.y0 = y * visual->y_size + visual->border + visual->y_offset;
	pt.y1 = (y + 1) * visual->y_size - visual->border + visual->y_offset;
	while (pt.x0 < pt.x1)
	{
		if ((p == 'O') && check_addr(visual, pt, p))
			visual->pix[pt.y0 + (pt.x0 * visual->s_line / 4)] = 0xFF00FF;
		else if ((p == 'X') && check_addr(visual, pt, p))
			visual->pix[pt.y0 + (pt.x0 * visual->s_line / 4)] = 0x099FFF;
		else if ((p == '.') && check_addr(visual, pt, p))
			visual->pix[pt.y0 + (pt.x0 * visual->s_line / 4)] = 0x303030;
		if (++pt.y0 > pt.y1)
		{
			pt.y0 = y * visual->y_size + visual->border + visual->y_offset;
			pt.x0++;
		}
	}
}

void	visualizer(t_filler *game, t_coords *map, t_visual *visual, int i)
{
	int x;
	int y;
	int end;

	x = i * 20;
	end = ((i + 1) * 20);
	y = 0;
	while ((x < game->map_row) && (x < end))
	{
			color_piece(visual, x , y, game->map[x][y]);
			if (++y > game->map_col)
			{
				y = 0;
				x++;
			}
	}
}	

void	init_map(t_filler *game, t_coords *map, t_visual *visual, int *size)
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
}

static void	*threader(void *t)
{
	t_thread *image;

	image = (t_thread*)t;
	visualizer(image->game, image->map, image->visual, image->count);
	return ((void*)image);
}

void	initialize_visualizer(t_filler *game, t_coords *map, t_visual *visual, int size)
{
	pthread_t tid[size];
	t_thread	t[size];
	int i;

	i = -1;
	if (visual->init++ == 0)
		init_map(game, map, visual, &size);
	else
	{
		while (++i < size)
		{
			t[i].game = game;
			t[i].map = map;
			t[i].visual = visual;
			t[i].count = i;
			pthread_create(&tid[i], NULL, threader, &t[i]);
		}
		i = -1;
		while(++i < size)
		{
			pthread_join(tid[i], NULL);
		}
		mlx_put_image_to_window(visual->mlx, visual->win, visual->img, 0, 0);
	}
}