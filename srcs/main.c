/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobrien <nobrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 14:50:44 by nobrien           #+#    #+#             */
/*   Updated: 2018/04/14 13:59:54 by nobrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

int		get_placement(t_env *g)
{
	g->bestx = -2147483648;
	g->besty = -2147483648;
	default_heatmap(g);
	calculate_heatmap(g, &get_heat_number);
	mapheatmaptodebugger(g);
	if (!(place_piece(g, &cmp)) && !(o_place_piece(g, &cmp)))
		return (0);
	ft_printf("%d %d\n", g->besty, g->bestx);
	return (1);
}

int		main(void)
{
	char	*line;
	t_env	global;

	global.fd = start_debugger();
	ft_get_next_line(0, &line);
	global.letter = (ft_atoi(line + 10) == 1) ? 'O' : 'X';
	ft_strdel(&line);
	global.opp = (global.letter == 'X') ? 'O' : 'X';
	get_dim(&global);
	if (malloc_map(&global) || malloc_heatmap(&global) || malloc_piece(&global))
		return (-1);
	while (1)
	{
		default_map(&global);
		get_piece(&(global.piece));
		if (!(get_placement(&global)))
			break ;
		line = NULL;
		ft_get_next_line(0, &line);
		if (line != NULL)
			ft_strdel(&line);
	}
	ft_printf("0 0\n");
	fclose(global.fd);
	return (0);
}
