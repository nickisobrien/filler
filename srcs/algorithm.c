#include "../includes/filler.h"

int		get_points(t_env *g, int x, int y)
{
	int i;
	int j;
	int tot;

	tot = 0;
	i = 0;
	while (i < g->piece.y)
	{
		j = 0;
		while (j < g->piece.x)
		{
			if (g->piece.shape[i][j] == '*')
				tot += g->hmap[i + y][j + x];
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

int		get_placement(t_env *g)
{
	g->bestx = -2147483648;
	g->besty = -2147483648;
	default_heatmap(g);
	calculate_heatmap(g);
	mappiecetodebugger(g);
	if (!(place_piece(g, &cmp)))
		return (0);
	return (1);
}