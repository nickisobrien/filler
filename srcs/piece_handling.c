/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piece_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobrien <nobrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 14:47:23 by nobrien           #+#    #+#             */
/*   Updated: 2018/04/14 14:16:11 by nobrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

int			check_loc(t_env *g, int y, int x, int *overlaps)
{
	if (x >= g->wwidth || y >= g->wheight)
		return (-1);
	if (g->map[y][x] == g->letter)
	{
		(*overlaps)++;
		if (*overlaps > 1)
			return (-1);
	}
	else if (g->map[y][x] != '.')
		return (-1);
	return (0);
}

static int	can_place(t_env *g, int y, int x)
{
	int i;
	int j;
	int overlaps;

	i = -1;
	overlaps = 0;
	while (++i < g->piece.y)
	{
		j = -1;
		while (++j < g->piece.x)
		{
			if (y < 0 || x < 0)
				return (0);
			if (g->piece.shape[i][j] == '*')
				if (check_loc(g, i + y, j + x, &overlaps) < 0)
					return (0);
		}
	}
	return (overlaps);
}

int			place_piece(t_env *g, int (*cmp)(t_env *, int, int,
	int (get_points)(t_env *, int, int)))
{
	int x;
	int y;
	int found;

	found = 0;
	y = -1 - g->piece.y;
	while (++y < g->wheight)
	{
		x = -1 - g->piece.x;
		while (++x < g->wwidth)
		{
			if (can_place(g, y, x))
			{
				found = 1;
				if ((*cmp)(g, x, y, get_points))
				{
					g->bestx = x;
					g->besty = y;
				}
			}
		}
	}
	return (found);
}
