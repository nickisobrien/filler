#include "../includes/filler.h"

void	get_piece(t_piece *p)
{
	char *str;
	int i;
	char *ptr;

	str = NULL;
	ft_get_next_line(0, &str);
	p->y = ft_atoi(str + 5);
	ptr = ft_strchr(str + 6, ' ');
	p->x = ft_atoi(ptr);
	if (str != NULL)
		ft_strdel(&str);
	i = 0;
	while (i < p->y)
	{
		ft_get_next_line(0, &str);
		strncpy(p->shape[i], str, (size_t)p->x);
		ft_strdel(&str);
		i++;
	}
}

void	default_map(t_env *g)
{
	int i;
	char *str;

	i = 0;
	str = NULL;
	ft_get_next_line(0, &str);
	if (str != NULL)
		ft_strdel(&str);//MALLOC ERROR SOURCE 1
	while (i < g->wheight)
	{
		str = NULL;
		ft_get_next_line(0, &str);
		ft_strncpy(g->map[i], str + 4, (size_t)g->wwidth);
		if (str != NULL)
			ft_strdel(&str);
		i++;
	}
}

void	get_dim(t_env *g)
{
	char	*line;
	int		n;

	n = 0;
	ft_get_next_line(0, &line);
	g->wheight = ft_atoi(line + 8);
	while (ft_isdigit(*(line + 8 + n)))
		n++;
	g->wwidth = ft_atoi(line + 9 + n);
	ft_strdel(&line);
}