/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writting_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vomelchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 17:46:35 by vomelchu          #+#    #+#             */
/*   Updated: 2019/01/02 13:25:09 by vomelchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int			num_ele(t_data *data, int x, int y)
{
	t_vertex	*vert;
	int			q;

	q = 0;
	vert = &data->vertex;
	while (vert->next != NULL)
	{
		if (vert->x_vert == x && vert->y_vert == y)
			return (q);
		q++;
		vert = vert->next;
	}
	if (vert->x_vert == x && vert->y_vert == y)
		return (q);
	return (0);
}

t_vector	last_vect(t_data *data, int q)
{
	t_sector *sect;
	t_vector dot_1;

	sect = &data->sectors[q];
	while (sect->next->next != NULL)
		sect = sect->next;
	dot_1.x = (double)sect->x0;
	dot_1.y = (double)sect->y0;
	return (dot_1);
}

int			find_wall(t_data *data, t_vector dot_1, t_vector dot_2, int check)
{
	t_sector	*sector;
	int			q;

	q = -1;
	while (++q <= data->current_sector)
	{
		sector = &data->sectors[q];
		while (sector->next != NULL && q != check)
		{
			if (((int)dot_1.x == sector->x0 && (int)dot_1.y == sector->y0 &&
			DT2X && (int)dot_2.y == sector->next->y0)
			|| ((int)dot_2.x == sector->x0 && DT2Y &&
			DT1X && (int)dot_1.y == sector->next->y0))
				return (q);
			if (sector->next->next == NULL)
				if ((DTX && (int)dot_1.y == sector->y0 &&
				DTY && (int)dot_2.y == data->sectors[q].y0)
				|| ((int)dot_2.x == sector->x0 && (int)dot_2.y == sector->y0 &&
				DT && (int)dot_1.y == data->sectors[q].y0))
					return (q);
			sector = sector->next;
		}
	}
	return (-1);
}

void		writte_walls(t_data *data, FILE *fp, int q)
{
	t_sector	*sector;
	t_vector	dot_1;
	t_vector	dot_2;
	char		*wall;

	sector = &data->sectors[q];
	dot_1 = last_vect(data, q);
	dot_2.x = (double)sector->x0;
	dot_2.y = (double)sector->y0;
	wall = ft_itoa(find_wall(data, dot_1, dot_2, q));
	fwrite(wall, ft_strlen(wall), 1, fp);
	fwrite(" ", 1, 1, fp);
	free(wall);
	while (sector->next->next != NULL)
	{
		dot_1.x = (double)sector->x0;
		dot_1.y = (double)sector->y0;
		dot_2.x = (double)sector->next->x0;
		dot_2.y = (double)sector->next->y0;
		wall = ft_itoa(find_wall(data, dot_1, dot_2, q));
		fwrite(wall, ft_strlen(wall), 1, fp);
		fwrite(" ", 1, 1, fp);
		free(wall);
		sector = sector->next;
	}
}

void		make_vertex_list(t_data *data)
{
	int			q;
	t_sector	*sector;
	t_vertex	*vert;

	q = -1;
	vert = &data->vertex;
	vert->next = NULL;
	while (++q <= data->current_sector)
	{
		sector = &data->sectors[q];
		while (sector->next != NULL)
		{
			vert->x_vert = sector->x0;
			vert->y_vert = sector->y0;
			if (sector->next != NULL)
			{
				if (!(vert->next = (t_vertex *)malloc(sizeof(t_vertex))))
					ft_error("Bad malloc in vertex");
				vert = vert->next;
			}
			sector = sector->next;
		}
	}
	vert->next = NULL;
}
