#include "../includes/filler.h"

int		overflows(t_env *g, int y, int x)
{
	int i;
	int j;

	i = 0;
	while (i < g->piece.y)
	{
		j = 0;
		while (j < g->piece.x)
		{
			if (g->piece.shape[i][j] == '*')
			{
				if (i + y >= g->wheight || i + y < 0)
					return (1);
				else if (j + x >= g->wwidth || j + x < 0)
					return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int		can_place(t_env *g, int y, int x)
{
	int i;
	int j;
	int overlaps;

	i = 0;
	overlaps = 0;
	while (i < g->piece.y)
	{
		j = 0;
		while (j < g->piece.x)
		{
			if (g->piece.shape[i][j] == '*')
			{
				if (i + y < 0 || i + y >= g->wheight || j + x < 0 || j + x >= g->wwidth)//might need abs?
					return (0);
				if (g->map[i + y][j + x] == g->letter)
				{
					overlaps++;
					if (overlaps > 1)
						return (0);
				}
				else if (g->piece.shape[i][j] == '*' && g->map[i + y][j + x] != '.')
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
