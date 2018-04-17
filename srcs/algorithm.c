/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobrien <nobrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 18:10:10 by nobrien           #+#    #+#             */
/*   Updated: 2018/04/16 17:35:31 by nobrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

int			get_points(t_env *g, int x, int y)
{
	int i;
	int j;
	int tot;

	tot = 0;
	i = -1;
	while (++i < g->piece.y)
	{
		j = -1;
		while (++j < g->piece.x)
			if (g->piece.shape[i][j] == '*')
				tot += g->hmap[i + y][j + x];
	}
	return (tot);
}

int			cmp(t_env *g, int x, int y, int (get_points)(t_env *, int, int))
{
	if (g->bestx == -2147483648 && g->besty == -2147483648)
		return (1);
	if ((*get_points)(g, g->bestx, g->besty) > (*get_points)(g, x, y))
		return (1);
	return (0);
}

int			get_heat_number(t_env *g, int i, int j, int counter)
{
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

void		calculate_heatmap(t_env *g,
	int (get_heat_number)(t_env *, int, int, int))
{
	int i;
	int j;
	int counter;

	counter = -1;
	while (++counter < (g->wwidth * g->wheight))
	{
		i = -1;
		while (++i < g->wheight)
		{
			j = -1;
			while (++j < g->wwidth)
			{
				if (g->hmap[i][j] == -1)
				{
					if ((get_heat_number)(g, i, j, counter))
						g->hmap[i][j] = counter + 1;
				}
			}
		}
	}
}

void		default_heatmap(t_env *g)
{
	int i;
	int j;

	i = -1;
	while (++i < g->wheight)
	{
		j = -1;
		while (++j < g->wwidth)
		{
			if (ft_tolower(g->map[i][j]) == ft_tolower(g->opp))
				g->hmap[i][j] = 0;
			else if (ft_tolower(g->map[i][j]) == ft_tolower(g->letter))
				g->hmap[i][j] = g->wwidth * g->wheight;
			else
				g->hmap[i][j] = -1;
		}
	}
}
