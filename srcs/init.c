#include "../includes/filler.h"

int		malloc_piece(t_env *g)
{
	int i;

	i = 0;
	if (!(g->piece.shape = malloc(sizeof(char *) * (g->wheight + 1))))
		return (-1);
	g->piece.shape[g->wheight] = NULL;
	while (i < g->wheight)
	{
		if (!((g->piece.shape)[i] = ft_strnew(g->wwidth)))
			return (-1);
		i++;
	}
	return (0);
}

int		malloc_heatmap(t_env *g)
{
	int i;

	i = 0;
	if (!(g->hmap = malloc(sizeof(int *) * g->wheight)))
		return (-1);
	while (i < g->wheight)
	{
		if (!(g->hmap[i] = malloc(sizeof(int) * g->wwidth)))
			return (-1);
		i++;
	}
	return (0);
}

int		malloc_map(t_env *g)
{
	int i;

	i = 0;
	if (!(g->map = malloc(sizeof(char *) * (g->wheight + 1))))
		return (-1);
	g->map[g->wheight] = NULL;
	while (i < g->wheight)
	{
		if (!((g->map)[i] = ft_strnew(g->wwidth)))
			return (-1);
		i++;
	}
	return (0);
}