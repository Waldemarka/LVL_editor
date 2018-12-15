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
}

void	write_sector(t_data *data, FILE *fp)
{
	t_sector *sector;
	int q;

	q = -1;
	while (++q != data->current_sector + 1)
	{
		sector = &data->sectors[q];
		fwrite("sector  ", 8, 1, fp);
		fwrite(ft_itoa(data->sectors[q].floor), ft_strlen(ft_itoa(data->sectors[q].floor)), 1, fp);
		fwrite("  ", 2, 1, fp);
		fwrite(ft_itoa(data->sectors[q].ceil), ft_strlen(ft_itoa(data->sectors[q].ceil)), 1, fp);
		fwrite("  ", 2, 1, fp);
		while (sector->next != NULL)
		{
			fwrite(ft_itoa(num_ele(data, sector->x0, sector->y0)),
				ft_strlen(ft_itoa(num_ele(data, sector->x0, sector->y0))), 1, fp);
			fwrite(" ", 1, 1, fp);
			sector = sector->next;
		}
		fwrite("    ", 4, 1, fp);
		writte_walls(data, fp, q);
		fwrite("\n", 1, 1, fp);
	}
}

void	free_vertex(t_data *data)
{
	vertex *vert;
	vertex *tmp;
	int q;

	q = 0;
	vert = &data->vertex;
	tmp = &data->vertex;
	while (vert->next != NULL)
	{
		printf("%d-----\n", vert->x_vert);
		
		if (vert->next->next == NULL)
		{
			free(vert->next);
			vert->next = NULL;
			vert = tmp;
		}
		else
			vert = vert->next;
	}
/*	while (vert->next != NULL)
	{
		tmp = vert->next;
		if (q != 0)
			free(vert);
		vert = tmp;
		q++;
	}*/
}

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
		if (tmp->next == NULL)
			break;
		num = tmp->y_vert;
		fwrite("\n", 1, 1, fp);
	}
}

void	sorting_list(t_data *data, FILE *fp)
{
	make_vertex_list(data);
 	sort_list(data);
 	write_vertex(data, fp);
	free_vertex(data);
    //system("leaks lvl_editor");
 	fwrite("\n\n", 2, 1, fp);
 	write_sector(data, fp);
}

void	writting(t_data *data)
{
	FILE *fp;

    fp = fopen(data->name, "wb");
    if(fp == NULL) {
        ft_error("Not FILE");
    }
    sorting_list(data, fp);
    if (fclose(fp) != 0)
    	ft_error("bad writting");
    fclose(fp);
}
