/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugger.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobrien <nobrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 14:38:58 by nobrien           #+#    #+#             */
/*   Updated: 2018/04/14 14:10:24 by nobrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

FILE	*start_debugger(void)
{
	FILE	*fd;

	if (!(fd = fopen("debugger.log", "w")))
		return (NULL);
	return (fd);
}

void	mapheatmaptodebugger(t_env *g)
{
	int i;
	int j;

	fprintf(g->fd, "Heatmap:\n");
	i = -1;
	while (++i < g->wheight)
	{
		j = -1;
		while (++j < g->wwidth)
			fprintf(g->fd, "%3d", g->hmap[i][j]);
		fprintf(g->fd, "\n");
	}
}
