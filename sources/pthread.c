/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlu <mlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 20:59:44 by mlu               #+#    #+#             */
/*   Updated: 2017/11/28 17:43:16 by mlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static void	*threader(void *t)
{
	t_thread *image;

	image = (t_thread*)t;
	if (image->count == 0)
		visualizer(image->game, image->map, image->visual);
	else
		check_spot(image->game, image->map);
	return ((void*)image);
}

void		initialize_visualizer(t_filler *game,
				t_coords *map, t_visual *visual)
{
	pthread_t	tid[2];
	t_thread	t[2];
	int			i;

	i = -1;
	if (visual->init++ == 0)
		init_map(game, map, visual);
	while (++i < 2)
	{
		t[i].game = game;
		t[i].map = map;
		t[i].visual = visual;
		t[i].count = i;
		pthread_create(&tid[i], NULL, threader, &t[i]);
	}
	i = -1;
	while (++i < 2)
		pthread_join(tid[i], NULL);
	mlx_put_image_to_window(visual->mlx, visual->win, visual->img, 0, 0);
}
