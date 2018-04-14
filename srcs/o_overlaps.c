/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_overlaps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobrien <nobrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 11:35:20 by nobrien           #+#    #+#             */
/*   Updated: 2018/04/14 14:14:49 by nobrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

int			o_get_points(t_env *g, int x, int y)
{
	int i;
	int j;
	int tot;
	int yadd;
	int xadd;

	tot = 0;
	i = -1;
	while (++i < g->piece.y)
	{
		j = -1;
		while (++j < g->piece.x)
		{
			if (g->piece.shape[i][j] == '*')
			{
				yadd = (i + y < 0) ? g->wheight : 0;
				xadd = (j + x < 0) ? g->wwidth : 0;
				tot += g->hmap[i + y + yadd][j + x + xadd];
			}
		}
	}
	return (tot);
}

static int	o_get_heat_number(t_env *g, int i, int j, int counter)
{
	if (j == g->wwidth - 1 && (g->hmap[i][0]) == counter)
		return (1);
	if (i == g->wheight - 1 && (g->hmap[0][j] == counter))
		return (1);
	if (i == 0 && g->hmap[g->wheight - 1][j] == counter)
		return (1);
	if (j == 0 && g->hmap[i][g->wwidth - 1] == counter)
		return (1);
	if (i > 0 && (g->hmap[i - 1][j] == counter))
		return (1);
	if (j > 0 && (g->hmap[i][j - 1] == counter))
		return (1);
	if (j != g->wwidth - 1 && (g->hmap[i][j + 1] == counter))
		return (1);
	if (i != g->wheight - 1 && (g->hmap[i + 1][j] == counter))
		return (1);
	return (0);
}

static int	o_can_place(t_env *g, int y, int x)
{
	int i;
	int j;
	int overlaps;
	int xadd;
	int yadd;

	i = -1;
	overlaps = 0;
	while (++i < g->piece.y)
	{
		j = -1;
		while (++j < g->piece.x)
		{
			if (g->piece.shape[i][j] == '*')
			{
				yadd = (i + y < 0) ? g->wheight : 0;
				xadd = (j + x < 0) ? g->wwidth : 0;
				if (check_loc(g, i + y + yadd, j + x + xadd, &overlaps) < 0)
					return (0);
			}
		}
	}
	return (overlaps);
}

int			o_place_piece(t_env *g, int (*cmp)(t_env *g, int x,
	int y, int (get_points)(t_env *, int, int)))
{
	int x;
	int y;
	int found;

	default_heatmap(g);
	calculate_heatmap(g, &o_get_heat_number);
	found = 0;
	y = -1 - g->piece.y;
	while (++y < g->wheight)
	{
		x = -1 - g->piece.x;
		while (++x < g->wwidth)
		{
			if (o_can_place(g, y, x))
			{
				found = 1;
				if ((*cmp)(g, x, y, o_get_points))
				{
					g->bestx = x;
					g->besty = y;
				}
			}
		}
	}
	return (found);
}
