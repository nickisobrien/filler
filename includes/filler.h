/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobrien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 14:56:56 by nobrien           #+#    #+#             */
/*   Updated: 2018/04/03 14:57:43 by nobrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __FILLER_H__
# define __FILLER_H__

# include "../libft/libft.h"
# include <unistd.h>

typedef struct s_piece
{
	int		x;
	int		y;
	char	**shape;
}				t_piece;


typedef struct	s_env
{
	char	letter;
	char	opp;
	int		wwidth;
	int		wheight;
	char	**map;
	int		**hmap;
	t_piece	piece;
	int		tx;
	int		ty;
	int		bestx;
	int		besty;

	FILE	*fd;//for debugging
}				t_env;

int		get_points(t_env *g, int x, int y);
int		cmp(t_env *g, int x, int y);
int		get_heat_number(t_env *g, int i, int j, int counter);
void	calculate_heatmap(t_env *g);
void	default_heatmap(t_env *g);
int		get_placement(t_env *g);

int		overflows(t_env *g, int y, int x);
int		can_place(t_env *g, int y, int x);
int		place_piece(t_env *g, int (cmp)(t_env *g, int x, int y));

void	mappiecetodebugger(t_env *g);
FILE	*debugger(void);

int		malloc_piece(t_env *g);
int		malloc_heatmap(t_env *g);
int		malloc_map(t_env *g);

void	get_piece(t_piece *p);
void	default_map(t_env *g);
void	get_dim(t_env *g);

#endif
