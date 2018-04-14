/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piece_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobrien <nobrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 14:47:23 by nobrien           #+#    #+#             */
/*   Updated: 2018/04/14 11:23:41 by nobrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

int		can_place(t_env *g, int y, int x)
{
	int i;
	int j;
	int overlaps;
	int xadd;
	int yadd;

	i = 0;
	overlaps = 0;
	while (i < g->piece.y)
	{
		j = 0;
		while (j < g->piece.x)
		{
			xadd = 0;
			yadd = 0;
			if (g->piece.shape[i][j] == '*')
			{
				if (j + x >= g->wwidth || i + y >= g->wheight)
					return (0);
				if (i + y < 0)
					yadd = g->wheight;
				if (j + x < 0)
					xadd = g->wwidth;
				if (g->map[i + y + yadd][j + x + xadd] == g->letter)
				{
					overlaps++;
					if (overlaps > 1)
						return (0);
				}
				else if (g->piece.shape[i][j] == '*' && g->map[i + y + yadd][j + x + xadd] != '.')
					return (0);
			}
			j++;
		}
		i++;
	}
	if (overlaps == 1) 
		return (1);
	return (0);
}

int		place_piece(t_env *g, int (cmp)(t_env *g, int x, int y))
{
	int x;
	int y;
	int found;

	found = 0;
	y = 0 - g->piece.y;
	while (y < g->wheight)
	{
		x = 0 - g->piece.x;
		while (x < g->wwidth)
		{
			if (can_place(g, y, x))
			{
				found = 1;
				if ((*cmp)(g, x, y))
				{
					g->bestx = x;
					g->besty = y;
				}
			}
			x++;
		}
		y++;
	}
	if (found)
	{
		ft_printf("%d %d\n", g->besty, g->bestx);
		return (1);
	}
	return (0);
}
