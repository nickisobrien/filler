/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobrien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 14:50:44 by nobrien           #+#    #+#             */
/*   Updated: 2018/04/10 13:26:43 by nobrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

int		main(void)
{
	char	*line;
	t_env	global;

	global.fd = debugger();
	ft_get_next_line(0, &line);
	global.letter = (ft_atoi(line + 10) == 1) ? 'O' : 'X';
	ft_strdel(&line);
	global.opp = (global.letter == 'X') ? 'O' : 'X';
	get_dim(&global);
	if (malloc_map(&global))
		return (-1);
	if (malloc_heatmap(&global))
		return (-1);
	if (malloc_piece(&global))
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
