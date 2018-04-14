/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugger.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobrien <nobrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 14:38:58 by nobrien           #+#    #+#             */
/*   Updated: 2018/04/14 11:23:46 by nobrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

FILE	*debugger(void)
{
	FILE	*fd;

	if (!(fd = fopen("file.txt", "w")))
		return (NULL);
	return (fd);
}

void	mappiecetodebugger(t_env *g)
{
	int i;
	int j;

	i = 0;
	while (g->map[i])
	{
		fprintf(g->fd, "%s\n", g->map[i]);
		i++;
	}
	i = 0;
	while (i < g->piece.y)
	{
		fprintf(g->fd, "%s\n", g->piece.shape[i]);
		i++;
	}
	fprintf(g->fd, "Heatmap:\n");
	i = 0;
	while (i < g->wheight)
	{
		j = 0;
		while (j < g->wwidth)
		{
			fprintf(g->fd, "%3d", g->hmap[i][j]);
			j++;
		}
		fprintf(g->fd,"\n");
		i++;
	}
}