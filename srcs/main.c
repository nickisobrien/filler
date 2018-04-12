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
#include <fcntl.h>

//count exposed edges on their shape to decide where to place the piece (less exposed edges = better pick)?
//if no difference, can also count their free area 1 away from each, then 2 away from each, then 3...?

/* * * * * * * * * * * * * * * * * * * * * * * * * */
/*               FILE DEBUGGING                    */
/* * * * * * * * * * * * * * * * * * * * * * * * * */

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

/* * * * * * * * * * * * * * * * * * * * * * * * * */
/*                 PIECE HANDLING                  */
/* * * * * * * * * * * * * * * * * * * * * * * * * */

int		overflows(t_env *g, int y, int x)
{
	int i;
	int j;

	i = 0;
	while (g->piece.shape[i])
	{
		j = 0;
		while (g->piece.shape[i][j])
		{
			if (g->piece.shape[i][j] == '*')
			{
				if (i + y >= g->wheight || i + y < 0)
					return (1);
				else if (j + x >= g->wwidth || j + y < 0)
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
	while (g->piece.shape[i])
	{
		j = 0;
		while (g->piece.shape[i][j])
		{
			if (overflows(g, y, x))
				return (0);
			if (g->piece.shape[i][j] == '*' && g->map[i + y][j + x] == g->letter)
			{
				overlaps++;
				if (overlaps > 1)
					return (0);
			}
			else if (g->piece.shape[i][j] == '*' && g->map[i + y][j + x] != '.')
				return (0);
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

/* * * * * * * * * * * * * * * * * * * * * * * * * */
/*                   ALGORITHM                     */
/* * * * * * * * * * * * * * * * * * * * * * * * * */

int		get_points(t_env *g, int x, int y)
{
	int i;
	int j;
	int tot;

	tot = 0;
	i = 0;
	while (g->piece.shape[i])
	{
		j = 0;
		while (g->piece.shape[i][j])
		{
			if (g->piece.shape[i][j] == '*')
			{
				tot += g->hmap[i + y][j + x];	
			}
			j++;
		}
		i++;
	}
	return (tot);
}

int		cmp(t_env *g, int x, int y)
{
	if (!g->bestx && !g->besty)
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
	g->bestx = 0;
	g->besty = 0;
	default_heatmap(g);
	calculate_heatmap(g);
	mappiecetodebugger(g);
	if (!(place_piece(g, &cmp)))
		return (0);
	return (1);

}

/* * * * * * * * * * * * * * * * * * * * * * * * * */
/*                    READERS                      */
/* * * * * * * * * * * * * * * * * * * * * * * * * */

void	get_piece(t_piece *p)
{
	char *str;
	int i;

	ft_get_next_line(0, &str);
	p->y = ft_atoi(str + 5);
	p->x = ft_atoi(str + 7);
	if (!(p->shape = malloc(sizeof(char *) * (p->y + 1))))
		return ;
	p->shape[p->y] = NULL;
	i = 0;
	while (i < p->y)
	{
		ft_get_next_line(0, &p->shape[i]);
		i++;
	}
}

void	set_map(t_env *g)//change this to simply initializing int map
{
	int i;
	char *str;

	i = 0;
	ft_get_next_line(0, &str);
	ft_strdel(&str);//PROBABLY MALLOC ERROR SOURCE
	while (i < g->wheight)
	{
		ft_get_next_line(0, &str);
		strncpy(g->map[i], str + 4, (size_t)g->wwidth);
		ft_strdel(&str);//PROBABLY MALLOC ERROR SOURCE
		i++;
	}
}

/* * * * * * * * * * * * * * * * * * * * * * * * * */
/*                     INIT                        */
/* * * * * * * * * * * * * * * * * * * * * * * * * */

void	init_heatmap(t_env *g)
{
	int i;
	int j;

	i = 0;
	if (!(g->hmap = malloc(sizeof(int *) * g->wheight)))
		return ;
	while (i < g->wheight)
	{
		if (!(g->hmap[i] = malloc(sizeof(int) * g->wwidth)))
			return ;
		i++;
	}
}

void	malloc_map(t_env *g)
{
	int i;

	i = 0;
	g->map = malloc(sizeof(char *) * (g->wheight + 1));
	g->map[g->wheight] = NULL;
	while (i < g->wheight)
	{
		(g->map)[i] = ft_strnew(g->wwidth);
		i++;
	}
}

void	get_dim(t_env *g)
{
	char *line;

	ft_get_next_line(0, &line);
	g->wheight = ft_atoi(line + 8);
	g->wwidth = ft_atoi(line + 11);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * */
/*                     MAINS                       */
/* * * * * * * * * * * * * * * * * * * * * * * * * */

int		main(void)
{
	char	*line;
	t_env	global;

	global.fd = debugger();
	ft_get_next_line(0, &line);
	global.letter = (ft_atoi(line + 10) == 1) ? 'O' : 'X';
	global.opp = (global.letter == 'X') ? 'O' : 'X';
	get_dim(&global);
	malloc_map(&global);
	init_heatmap(&global);
	while (1)
	{
		set_map(&global);
		get_piece(&(global.piece));
		if (!(get_placement(&global))) //need to check leaks? get rid of the break
			break ;
		ft_get_next_line(0, &line);//reading "Plateau", don't need it, just reading it
	}
	ft_printf("0 0\n");//might not need, just so it doesnt end on error
	fclose(global.fd);
	return (0);
}
