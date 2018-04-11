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

int		xplace_piece(t_env *g, int sy, int sx)
{
	int x;
	int y;
	int px;
	int py;

	y = sy;
	while (y != 0 - g->piece.y - 1 && y != g->wheight + 1)
	{
		x = sx;
		while (x != 0 - g->piece.x - 1 && x != g->wwidth + 1)
		{
			if (can_place(g, y, x))
			{
				ft_printf("%d %d\n", y, x);
				return (1);
			}
			x += g->xinc;
		}
		y += g->yinc;
	}
	return (0);
}

int		yplace_piece(t_env *g, int sy, int sx)
{
	int x;
	int y;
	int px;
	int py;

	x = sx;
	while (x != 0 - g->piece.x - 1 && x != g->wwidth + 1)
	{
		y = sy;
		while (y != 0 - g->piece.y - 1 && x != g->wheight + 1)
		{
			if (can_place(g, y, x))
			{
				ft_printf("%d %d\n", y, x);
				return (1);
			}
			y += g->yinc;
		}
		x += g->xinc;
	}
	return (0);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * */
/*                   ALGORITHM                     */
/* * * * * * * * * * * * * * * * * * * * * * * * * */

//what would be considered better placement than the other?

void	get_opp_last_placement(t_env *g)
{
	int i;
	int j;

	i = 0;
	while (g->map[i])
	{
		j = 0;
		while (g->map[i][j])
		{
			if (g->map[i][j] == ft_tolower(g->opponent))
			{
				g->tx = j;
				g->ty = i;
				return ;
			}
			else if (g->map[i][j] == ft_toupper(g->opponent))
			{
				g->tx = j;
				g->ty = i;
			}
			j++;
		}
		i++;
	}
}

void	get_my_last_placement(t_env *g)
{
	int i;
	int j;

	i = 0;
	while (g->map[i])
	{
		j = 0;
		while (g->map[i][j])
		{
			if (g->map[i][j] == ft_tolower(g->letter))
			{
				g->mx = j;
				g->my = i;
				return ;
			}
			else if (g->map[i][j] == ft_toupper(g->letter))
			{
				g->mx = j;
				g->my = i;
			}
			j++;
		}
		i++;
	}
}

int		get_placement(t_env *g)
{
	int x;
	int y;

	get_opp_last_placement(g);
	get_my_last_placement(g);
	y = (g->my > g->ty) ? 0 - g->piece.y : g->wheight;
	g->yinc = (g->my > g->ty) ? 1 : -1;
	x = (g->mx > g->tx) ? 0 - g->piece.x : g->wwidth;
	g->xinc = (g->mx > g->tx) ? 1 : -1;
	fprintf(g->fd, "g->xinc:%d g->yinc:%d x:%d y:%d\n", g->xinc, g->yinc, x, y);
	if (ft_abs(g->my - g->ty) > ft_abs(g->mx - g->tx))
	{
		if (!(yplace_piece(g, y, x)))
			return (0);
	}
	else
	{
		if (!(xplace_piece(g, y, x)))
			return (0);
	}
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

void	set_map(t_env *g)
{
	int i;
	char *str;

	i = 0;
	ft_get_next_line(0, &str);
	ft_strdel(&str);
	while (i < g->wheight)
	{
		ft_get_next_line(0, &str);
		strncpy(g->map[i], str + 4, (size_t)g->wwidth);
		ft_strdel(&str);
		i++;
	}
}

/* * * * * * * * * * * * * * * * * * * * * * * * * */
/*                     INIT                        */
/* * * * * * * * * * * * * * * * * * * * * * * * * */

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
	global.opponent = (global.letter == 'X') ? 'O' : 'X';
	get_dim(&global);
	malloc_map(&global);
	while (1)
	{
		set_map(&global);
		get_piece(&(global.piece));
		mappiecetodebugger(&global);
		if (!(get_placement(&global))) //need to check leaks? get rid of the break
			break ;
		ft_get_next_line(0, &line);//reading "Plateau", don't need it, just reading it
	}
	ft_printf("0 0\n");//might not need, just so it doesnt end on error
	fclose(global.fd);
	return (0);
}
