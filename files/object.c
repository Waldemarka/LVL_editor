/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vomelchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 19:32:18 by vomelchu          #+#    #+#             */
/*   Updated: 2018/12/15 19:32:20 by vomelchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"


int		init_obj(t_data *data, int x, int y)
{
	if (data->sectors[0].next == NULL)
		return(1);
	coord_canvas(data, x, y);
	data->p3.x = (double)near_round(data->x_canv);
	data->p3.y = (double)near_round(data->y_canv);
	coord_canvas(data, 50000, 50000);
	data->p4.x = (double)near_round(data->x_canv);
	data->p4.y = (double)near_round(data->y_canv);
	return (0);	
}

int		no_more_5(t_data *data)
{
	int q;
	int count;

	q = -1;
	count = 0; 
	while (++q != data->object)
	{
		if (data->icons[q].sector == data->num_sector)
			count++;
		if (count > 4)
			return (1);
	}
	return (0);
}

int 	help_check(t_data *data, t_sector *sector, int obj)
{
	while (sector->next != NULL && sector->next->next != NULL)
	{
		data->p1.x = (double)sector->x0;
		data->p1.y = (double)sector->y0;
		data->p2.x = (double)sector->next->x0;
		data->p2.y = (double)sector->next->y0;
		if (IntersectionOfTwoLine(data) == 1)
			obj++;
		sector = sector->next;
	}
	data->p1.x = (double)sector->x0;
	data->p1.y = (double)sector->y0;
	data->p2.x = (double)data->sectors[data->iter].x0;
	data->p2.y = (double)data->sectors[data->iter].y0;
	if (IntersectionOfTwoLine(data) == 1)
		obj++;
	if (obj == 1)
	{
		data->num_sector = data->iter;
		if (no_more_5(data) == 0)
			return (0);
	}
	return (1);
}


int		check_in_sector(t_data *data, int x, int y)
{
	int obj;
	t_sector *sector;

	if (init_obj(data, x, y) == 1)
		return (1);
	data->iter = -1;
	while (++data->iter != data->current_sector)
	{
		sector = &data->sectors[data->iter];
		obj = 0;
		if (help_check(data, sector, obj) == 0)
			return (0);
	}
	return (1);
}

int		end_start_marker(t_data *data)
{
	int q;

	if (data->num_icon == 6)
		return (0);
	q = -1;
	while (++q != data->object)
	{
		if (data->num_icon == 0 && data->icons[q].obj == 1
			&& data->icons[q].sector == data->num_sector)
			return (1);
		if (data->num_icon == 1 && data->icons[q].obj == 0
			&& data->icons[q].sector == data->num_sector)
			return (1);
	}
	return (0);
}

void	special_icons(t_data *data)
{
	int q;

	if (end_start_marker(data) == 0)
	{
		q = modif_obj(data, data->num_icon);
		if (q == data->object)
		{
			writte_icons_to_struct(data, data->object);
			data->object++;
		}
		else
			writte_icons_to_struct(data, q);
	}
}






