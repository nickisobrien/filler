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
	// int		mx;
	// int		my;
	// int		xinc;
	// int		yinc;
	int			bestx;
	int			besty;

	FILE	*fd;//for debugging only
}				t_env;

#endif
