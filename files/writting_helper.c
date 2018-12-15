/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writting_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vomelchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 17:46:35 by vomelchu          #+#    #+#             */
/*   Updated: 2018/12/03 17:46:37 by vomelchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int 	num_ele(t_data *data, int x, int y)
{
	vertex *vert;
	int q;

	q = 0;
	vert = &data->vertex;
	while (vert->next != NULL)
	{
		if (vert->x_vert == x && vert->y_vert == y)
			return (q);
		q++;
		vert = vert->next;
	}
	return (0); // may wil be problem
}

vector	last_vect(t_data *data, int q)
{
	t_sector *sect;
	vector dot_1;

	sect = &data->sectors[q];
	while (sect->next->next != NULL)
		sect = sect->next;
	dot_1.x = (double)sect->x0;
	dot_1.y = (double)sect->y0;
	return (dot_1);
}


int		find_wall(t_data *data, vector dot_1, vector dot_2, int check)
{
	t_sector *sector;
	int q;

	q = -1;
	while (++q != data->current_sector)
	{
		sector = &data->sectors[q];
		while (sector->next != NULL && q != check)
		{
			if (((int)dot_1.x == sector->x0 && (int)dot_1.y == sector->y0 &&
				(int)dot_2.x == sector->next->x0 && (int)dot_2.y == sector->next->y0)
				|| ((int)dot_2.x == sector->x0 && (int)dot_2.y == sector->y0 &&
				(int)dot_1.x == sector->next->x0 && (int)dot_1.y == sector->next->y0))
				return (q);
			if (sector->next->next == NULL)
				if (((int)dot_1.x == sector->x0 && (int)dot_1.y == sector->y0 &&
				(int)dot_2.x == data->sectors[q].x0 && (int)dot_2.y == data->sectors[q].y0)
				|| ((int)dot_2.x == sector->x0 && (int)dot_2.y == sector->y0 &&
				(int)dot_1.x == data->sectors[q].x0 && (int)dot_1.y == data->sectors[q].y0))
					return (q);
			sector = sector->next;
		}
	}
	return (-1);
}

void	writte_walls(t_data *data, FILE *fp, int q)
{
	t_sector *sector;
	vector dot_1;
	vector dot_2;
	char *wall;

	sector = &data->sectors[q];
	dot_1 = last_vect(data, q);
	dot_2.x = (double)sector->x0;
	dot_2.y = (double)sector->y0;
	wall = ft_itoa(find_wall(data, dot_1, dot_2, q));
		fwrite(wall, ft_strlen(wall), 1, fp);
		fwrite(" ", 1, 1, fp);
	while (sector->next->next != NULL)
	{
		dot_1.x = (double)sector->x0;
		dot_1.y = (double)sector->y0;
		/*if (sector->next->next == NULL)
		{
			sector->next->x0 = data->sectors[q].x0;
			sector->next->y0 = data->sectors[q].y0;
		}*/
		dot_2.x = (double)sector->next->x0;
		dot_2.y = (double)sector->next->y0;
		wall = ft_itoa(find_wall(data, dot_1, dot_2, q));
		fwrite(wall, ft_strlen(wall), 1, fp);
		fwrite(" ", 1, 1, fp);
		sector = sector->next;
	}
}
/*

vector	last_vect(t_data *data, int q)
{
	t_sector *sect;
	vector dot_1;

	sect = &data->sectors[q];
	while (sect->next->next != NULL)
		sect = sect->next;
	dot_1.x = (double)sect->x0;
	dot_1.y = (double)sect->y0;
	return (dot_1);
}

int 	is_one_vector(vector vect_1, vector vect_2, vector vect_3, vector vect_4)
{
	if (vect_1.x == vect_3.x && vect_1.y == vect_3.y && vect_2.x == vect_4.x
		&& vect_2.y == vect_4.y)
		return (1);
	if (vect_1.x == vect_4.x && vect_1.y == vect_4.y && vect_2.x == vect_3.x
		&& vect_2.y == vect_3.y)
		return (1);
	return (0);
}

int		find_num_sector(t_data *data, vector vect_1, vector vect_2, int q)
{
	t_sector *sect;
	vector vect_3;
	vector vect_4;
	int i;

	i = -1;
	while (i <= data->current_sector)
	{
		i++;
		if (i > data->current_sector)
			break;
		sect = &data->sectors[i];
		if (i == q)
				continue;
		while (sect->next->next != NULL && sect->next != NULL)
		{
			vect_3.x = (double)sect->x0;
			vect_3.y = (double)sect->y0;
			vect_4.x = (double)sect->next->x0;
			vect_4.y = (double)sect->next->y0;
			if (is_one_vector(vect_1, vect_2, vect_3, vect_4) == 1)
				return (i);
			sect = sect->next;
		}
	}
	return (-1);
}

int 	num_last_walls(t_data *data, vector vect_1, vector vect_2, int q)
{
		t_sector *sect;
	vector vect_3;
	vector vect_4;
	int i;

	i = -1;
	while (i <= data->current_sector)
	{
		i++;
		if (i > data->current_sector)
			break;
		if (i == q)
				continue;
		sect = &data->sectors[i];
		vect_4.x = (double)sect->x0;
		vect_4.y = (double)sect->y0;
		while (sect->next->next != NULL)
			sect = sect->next;
		vect_3.x = (double)sect->x0;
		vect_3.y = (double)sect->y0;
		if (is_one_vector(vect_1, vect_2, vect_3, vect_4) == 1)
			return (i);
	}
	return (-1);

}


void	writte_walls(t_data *data, FILE *fp, int q)
{
	t_sector *sect;
	vector vect_1;
	vector vect_2;
	char *num;

	sect = &data->sectors[q];
	vect_1 = last_vect(data, q);
	vect_2.x = (double)sect->x0;
	vect_2.y = (double)sect->y0;
	num = ft_itoa(find_num_sector(data, vect_1, vect_2, q));
	fwrite(num, ft_strlen(num), 1, fp);
}
*/

/*void	writte_walls(t_data *data, FILE *fp, int q)
{
	t_sector *sector;
	vector dot_1;
	vector dot_2;
	char *wall;

	sector = &data->sectors[q];
	dot_1 = last_vect(data, q);
	dot_2.x = (double)sector->x0;
	dot_2.y = (double)sector->y0;
	wall = ft_itoa(find_wall(data, dot_1, dot_2, q));
	fwrite(wall, ft_strlen(wall), 1, fp);
	fwrite(" ", 1, 1, fp);
	while (sector->next != NULL)
	{
		dot_1.x = (double)sector->x0;
		dot_1.y = (double)sector->y0;
		dot_2.x = (double)sector->next->x0;
		dot_2.y = (double)sector->next->y0;
		wall = ft_itoa(find_wall(data, dot_1, dot_2, q));
		fwrite(wall, ft_strlen(wall), 1, fp);
		fwrite(" ", 1, 1, fp);
		sector = sector->next;
	}
}*/

void	malloc_vertex(vertex *new_vertex)
{
	if (!(new_vertex = (vertex *)malloc(sizeof(vertex) * 1)))
 		ft_error("Bad realloc in vertex");
}

void	make_vertex_list(t_data *data)
{
	int q;
	t_sector *sector;
	vertex *vert;

	q = -1;
	//malloc_vertex(&data->vertex);
	vert = &data->vertex;
	vert->next = NULL;
	if (data->sectors[data->current_sector].next == NULL)
		data->current_sector -= 1;
 	while (++q <= data->current_sector)
 	{
 		sector = &data->sectors[q];
 		while (sector->next != NULL)
 		{
 			vert->x_vert = sector->x0;
 			vert->y_vert = sector->y0;
 			if (sector->next != NULL)
 			{
 				if (!(vert->next = (vertex *)malloc(sizeof(vertex))))
					ft_error("Bad malloc in vertex");
 				vert = vert->next;
 			}
 			sector = sector->next;
 		}
 	}
 	vert->next = NULL;
}
