/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobrien <nobrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 14:56:56 by nobrien           #+#    #+#             */
/*   Updated: 2018/04/14 15:46:24 by nobrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __FILLER_H
# define __FILLER_H

# include "../libft/libft.h"
# include <unistd.h>
# include <fcntl.h>

typedef struct	s_piece
{
	int			x;
	int			y;
	char		**shape;
}				t_piece;

typedef struct	s_env
{
	char		letter;
	char		opp;
	int			wwidth;
	int			wheight;
	char		**map;
	int			**hmap;
	t_piece		piece;
	int			tx;
	int			ty;
	int			bestx;
	int			besty;

	FILE		*fd;
}				t_env;

int				cmp(t_env *g, int x, int y,
		int (get_points)(t_env *, int, int));
int				get_points(t_env *g, int x, int y);
int				get_heat_number(t_env *g, int i, int j, int counter);
void			default_heatmap(t_env *g);
int				get_placement(t_env *g);
void			calculate_heatmap(t_env *g,
		int (get_heat_number)(t_env *, int, int, int));

int				overflows(t_env *g, int y, int x);
int				place_piece(t_env *g, int (*cmp)(t_env *, int, int,
			int (get_points)(t_env *, int, int)));
int				check_loc(t_env *g, int y, int x, int *overlaps);

void			mapheatmaptodebugger(t_env *g);
FILE			*start_debugger(void);

int				malloc_piece(t_env *g);
int				malloc_heatmap(t_env *g);
int				malloc_map(t_env *g);

void			get_piece(t_piece *p);
void			default_map(t_env *g);
void			get_dim(t_env *g);

int				o_place_piece(t_env *g, int (*cmp)(t_env *g, int x, int y,
			int (get_points)(t_env *, int, int)));
int				o_cmp(t_env *g, int x, int y);
int				o_get_points(t_env *g, int x, int y);

#endif
