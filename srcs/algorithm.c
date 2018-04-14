/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobrien <nobrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 18:10:10 by nobrien           #+#    #+#             */
/*   Updated: 2018/04/14 11:23:45 by nobrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

int		get_points(t_env *g, int x, int y)
{
	int i;
	int j;
	int tot;
	int yadd;
	int xadd;

	tot = 0;
	i = 0;
	while (i < g->piece.y)
	{
		j = 0;
		while (j < g->piece.x)
		{
			yadd = 0;
			xadd = 0;
			if (g->piece.shape[i][j] == '*')
			{
				if (i + y < 0)
					yadd = g->wheight;
				if (j + x < 0)
					xadd = g->wwidth;
				tot += g->hmap[i + y + yadd][j + x + xadd];
			}
			j++;
		}
		i++;
	}
	return (tot);
}

int		cmp(t_env *g, int x, int y)
{
	if (g->bestx == -2147483648 && g->besty == -2147483648)
		return (1);
	if (get_points(g, g->bestx, g->besty) > get_points(g, x, y))
		return (1);
	return (0);
}

int		get_heat_number(t_env *g, int i, int j, int counter)
{
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

void	calculate_heatmap(t_env *g)
{
	int i;
	int j;
	int counter;

	counter = 0;
	while (counter < (g->wwidth * g->wheight))
	{
		i = 0;
		while (i < g->wheight)
		{
			j = 0;
			while (j < g->wwidth)
			{
				if (g->hmap[i][j] == -1)
				{
					if (get_heat_number(g, i, j, counter))
						g->hmap[i][j] = counter + 1;
				}
				j++;
			}
			i++;
		}
		counter++;
	}
}

void	default_heatmap(t_env *g)
{
	int i;
	int j;

	i = 0;
	while (i < g->wheight)
	{
		j = 0;
		while (j < g->wwidth)
		{
			if (ft_tolower(g->map[i][j]) == ft_tolower(g->opp))
				g->hmap[i][j] = 0;
			else if (ft_tolower(g->map[i][j]) == ft_tolower(g->letter))
				g->hmap[i][j] = -2;
			else
				g->hmap[i][j] = -1;
			j++;
		}
		i++;
	}
}

//try to encourage closing edges
// void	secret_heatmap_power(t_env *g)
// {
// 	int i;
// 	int j;

// 	i = 0;
// 	while (i < g->wheight)
// 	{
// 		j = 0;
// 		while(j < g->wwidth)
// 		{
// 			if (g->hmap[i][j] == 0)
// 			{
// 				if (i >= g->wheight -3)// || i < 3 || j >= g->wwidth - 3 || j < 3)
// 				{
// 					if (g->hmap[g->wheight - 1][j] == -1)
// 						g->hmap[g->wheight - 1][j] = 1;
// 				}
// 				if (i < 3)
// 				{
// 					if (g->hmap[0][j] == -1)
// 						g->hmap[0][j] = 1;
// 				}
// 				if (j >= g->wwidth - 3)
// 				{
// 					if (g->hmap[i][g->wwidth - 1] == -1)
// 						g->hmap[i][g->wwidth - 1] = 1;
// 				}
// 				if (j < 3)
// 				{
// 					if (g->hmap[i][0] == -1)
// 						g->hmap[i][0] = 1;
// 				}
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// }

int		get_placement(t_env *g)
{
	g->bestx = -2147483648;
	g->besty = -2147483648;
	default_heatmap(g);
	// secret_heatmap_power(g);
	calculate_heatmap(g);
	mappiecetodebugger(g);
	if (!(place_piece(g, &cmp)))
		return (0);
	return (1);
}