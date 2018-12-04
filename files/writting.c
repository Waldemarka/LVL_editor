/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vomelchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 14:02:18 by vomelchu          #+#    #+#             */
/*   Updated: 2018/11/16 14:02:20 by vomelchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	wri_vert(t_data *data, FILE *fp)
{
	int q;
	size_t count;
	char const *vertex = "vertex    ";
	char *num;
	t_sector *sector;

	q = -1;
	while (++q != data->current_sector + 1)
	{
		sector = &data->sectors[q];
		if (sector->next == NULL)
			break;
		while (sector->next != NULL)
		{
			count = fwrite(vertex, ft_strlen(vertex), 1, fp);
			num = ft_itoa(sector->y0);
			count = fwrite(num, ft_strlen(num), 1, fp);
			count = fwrite(" ", 1, 1, fp);
			num = ft_itoa(sector->x0);
			count = fwrite(num, ft_strlen(num), 1, fp);
			count = fwrite(" \n", 1, 2, fp);
			sector = sector->next;
		}
	}
}

void	malloc_vertex(vertex *new_vertex)
{
	if (!(new_vertex = (vertex *)malloc(sizeof(vertex) * 1)))
 		ft_error("Bad realloc in vertex");
}

void	sort_list(t_data *data)
{
	vertex *orig;
	vertex *tmp;

	orig = &data->vertex;
	tmp = &data->vertex;
	while (orig->next != NULL)
	{
		if ((orig->y_vert > orig->next->y_vert) && orig->next->next != NULL)
		{
			ft_swap(&orig->x_vert, &orig->next->x_vert);
			ft_swap(&orig->y_vert, &orig->next->y_vert);
			orig = tmp;
		}
		else
			orig = orig->next;
	}
	/*while (data->vertex.next != NULL)
 	{
 		printf("x : %d ----- y : %d\n", data->vertex.x_vert, data->vertex.y_vert);
 		data->vertex = *data->vertex.next;
 	}*/
}

void	make_vertex_list(t_data *data)
{
	int q;
	t_sector *sector;
	vertex *vert;

	q = -1;
	malloc_vertex(&data->vertex);
	vert = &data->vertex;
	if (data->sectors[data->current_sector].next == NULL)
		data->current_sector -= 1;
 	while (++q <= data->current_sector)
 	{
 		sector = &data->sectors[q];
 		while (sector->next != NULL)
 		{
 			vert->x_vert = sector->x0;
 			vert->y_vert = sector->y0;
 			//malloc_vertex(&vert->next);
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
 /*	while (data->vertex.next != NULL)
 	{
 		printf("x : %d ----- y : %d\n", data->vertex.x_vert, data->vertex.y_vert);
 		data->vertex = *data->vertex.next;
 	}*/
}

/*num = ft_itoa(sector->y0);
			count = fwrite(num, ft_strlen(num), 1, fp);
			count = fwrite(" \n", 1, 2, fp);*/


void	write_vertex(t_data *data, FILE *fp)
{
	int num;
	vertex *tmp;

	tmp = &data->vertex;
	num = tmp->y_vert;
	while (tmp->next != NULL)
	{
		fwrite("vertex ", 7, 1, fp);
		fwrite(ft_itoa(num), ft_strlen(ft_itoa(num)), 1, fp);
		fwrite("  ", 2, 1, fp);
		while (tmp->y_vert == num && tmp->next != NULL)
		{
			fwrite(ft_itoa(tmp->x_vert), ft_strlen(ft_itoa(tmp->x_vert)), 1, fp);
			fwrite(" ", 1, 1, fp);
			tmp = tmp->next;
		}
		printf("%d\n", tmp->y_vert);
		if (tmp->next == NULL)
			break;
		num = tmp->y_vert;
		fwrite("\n", 1, 1, fp);
		//tmp = tmp->next;
	}
}

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
}

void	write_sector(t_data *data, FILE *fp)
{
	t_sector *sector;
	int q;

	q = -1;
	while (++q != data->current_sector)
	{
		sector = &data->sectors[q];
		fwrite("sector  0  20    ", 7, 1, fp);
		while (sector->next != NULL)
		{
			fwrite(ft_itoa(num_ele(data, sector->x0, sector->y0)),
				ft_strlen(ft_itoa(num_ele(data, sector->x0, sector->y0))), 1, fp);
fwrite("  ", 2, 1, fp);
			sector = sector->next;
		}
	}
}

void	sorting_list(t_data *data, FILE *fp)
{
	make_vertex_list(data);
 	sort_list(data);
 	write_vertex(data, fp);
 	write_sector(data, fp);
}

void	writting(t_data *data)
{
	FILE *fp;

    fp = fopen(data->name, "wb");
    if(fp == NULL) {
        ft_error("Not FILE");
    }
    //wri_vert(data, fp);
    //fwrite(" \n", 1, 2, fp);
    //fwrite(" \n", 1, 2, fp);
    //wri_sect(data, fp);
    sorting_list(data, fp);
    if (fclose(fp) != 0)
    	ft_error("bad writting");
    fclose(fp);
}
