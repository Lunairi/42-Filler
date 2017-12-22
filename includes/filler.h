/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftls.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlu <mizukori250@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/25 09:00:00 by mlu               #+#    #+#             */
/*   Updated: 2017/08/25 09:00:00 by mlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <sys/stat.h>
# include <sys/xattr.h>
# include <sys/acl.h>
# include <dirent.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <errno.h>
# include <string.h>
# include <pthread.h>

# include "libft.h"
# include "mlx.h"

typedef	struct	s_filler
{
	int			i;
	int			track;
	int			j;
	char		**map;
	char		**prev_map;
	char		*piece_info;
	char		**piece;
	char		player_number;
	int			map_row;
	int			map_col;
	int			piece_row;
	int			piece_col;
	int			parse_loop;
}				t_filler;

typedef struct	s_coords
{
	int			row;
	int			col;
	int			x;
	int			y;
	int			valid;
	int			illegal;
	int			j;
	int			k;
	int			place;
}				t_coords;

typedef struct	s_visual
{
	void		*mlx;
	void		*win;
	void		*img;
	int			*pix;
	int			bits;
	int			s_line;
	int			endian;
	int			x_size;
	int			y_size;
	int			init;
	int			height;
	int			width;
	int			y_offset;
	int			x_offset;
	int			border;
}				t_visual;

typedef struct	s_vcord
{
	int			x0;
	int			x1;
	int			y0;
	int			y1;
	int			x;
	int			y;
	char		p;
	int			color;
}				t_vcord;

typedef struct	s_thread
{
	t_visual	*visual;
	t_coords	*map;
	t_filler	*game;
	int			count;
}				t_thread;

/*
** parse_stdin
*/
void			parse_player_number(t_filler *game, int t, char *string);
void			parse_map_size(t_filler *game, int t, char *string);
void			parse_map_detail(t_filler *game, char *tmp, char *string);
void			parse_piece_size(t_filler *game, int t, char *string);
void			parse_piece_detail(t_filler *game, char *string);

/*
** fill_board.c
*/
int				check_spot(t_filler *game, t_coords *map);

/*
** visual.c
*/
void			visualizer(t_filler *game, t_coords *map, t_visual *visual);
void			init_map(t_filler *game, t_coords *map, t_visual *visual);
int				color_value(t_visual *visual, t_vcord pt);
void			color_piece(t_filler *game, t_coords *map,
					t_visual *visual, t_vcord pt);

/*
** pthread.c
*/
void			initialize_visualizer(t_filler *game,
					t_coords *map, t_visual *visual);

/*
** place_bottom.c
*/
int				fill_bottom(t_filler *game, t_coords *map);

/*
** place_top.c
*/
int				fill_top(t_filler *game, t_coords *map);

#endif
