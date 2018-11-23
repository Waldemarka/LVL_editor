/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crossing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vomelchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 19:43:58 by vomelchu          #+#    #+#             */
/*   Updated: 2018/11/21 12:40:11 by vomelchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int		cros_dots(t_data *data)
{
/*	int p1_x = (int)data->p1.x;
	int p1_y = (int)data->p1.y;
	int p2_x = (int)data->p2.x;
	int p2_y = (int)data->p2.y;
	int p3_x = (int)data->p3.x;
	int p3_y = (int)data->p3.y;
	printf("p1_x : %d -- p1_y : %d\n", p1_x, p1_y);
	printf("p2_x : %d -- p2_y : %d\n", p2_x, p2_y);
	printf("p3_x : %d -- p3_y : %d\n", p3_x, p3_y);
	if (p3_x == p1_x && p3_y == p1_y)
	{
		printf("+++++%d\n", p1_x);
		return (1);
	}
	if (p3_x == p2_x && p3_y == p2_y)
	{
		printf("-----%d\n", p2_y);
		return (1);
	}*/
	return (1);
}

int		crossing(t_data *data)
{
	data->color = 0x15eb43;
	if (data->p2.x < data->p1.x)
	{
   	vector tmp = data->p1;
    data->p1 = data->p2;
    data->p2 = tmp;
	}
	if (data->p4.x < data->p3.x) {
 
  	  vector tmp = data->p3;
 	   data->p3 = data->p4;
 	   data->p4 = tmp;
	}
	if (data->p2.x < data->p3.x)
    	return (0);
    data->color = 0xff0000;
    if (two_vertical(data) == 1)
    	return (1);
    //if (one_vertical_1(data) == 1 ||
    //	one_vertical_2(data) == 1)
    //	return (1);
    if (without_vertical(data) == 1)
    	return (1);
    data->color = 0x15eb43;
	return (0);
}

int		init_vector(t_data *data)
{
	if (data->sectors[0].next == NULL ||
		data->sectors[0].next->next == NULL
		|| data->sectors[0].next->next->next == NULL)
		return(1);
	coord_canvas(data, data->x0_line, data->y0_line);
	data->p3.x = (double)near_round(data->x_canv);
	data->p3.y = (double)near_round(data->y_canv);
	coord_canvas(data, data->x1_line, data->y1_line);
	data->p4.x = (double)near_round(data->x_canv);
	data->p4.y = (double)near_round(data->y_canv);
	return (0);	
}
/*
int		before_crossing(t_data *data)
{
	t_sector *sector;
	int q;

	q = 0;
	if (init_vector(data) == 1)
		return (0);
	while (q != data->for_realloc)
	{
		sector = &data->sector[q];
		while (sector->next != NULL)
		{
			if ()
			sector = sector->next;
		}
		q++;
	}

}*/

int		bef_crossing(t_data *data)
{
	t_sector *sector;
	int i;

	i = -1;
	if (init_vector(data) == 1)
		return (0);
	while (++i != data->for_realloc)
	{
		sector = &data->sectors[i];
		while (sector->next != NULL && sector->next->next != NULL)
		{
			if (data->current_sector == i && sector->next->next->next == NULL)
				break;
			data->p1.x = (double)sector->x0;
			data->p1.y = (double)sector->y0;
			data->p2.x = (double)sector->next->x0;
			data->p2.y = (double)sector->next->y0;
			if (crossing(data) == 1)
				//if (cros_dots(data) == 0)
					return (1);
			sector = sector->next;
		}
	}
	return (0);
}






