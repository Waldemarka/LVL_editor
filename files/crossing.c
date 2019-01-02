/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crossing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vomelchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 19:43:58 by vomelchu          #+#    #+#             */
/*   Updated: 2019/01/02 13:20:49 by vomelchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int		touch_dots(t_data *data)
{
	if (((int)data->p1.x == (int)data->p3.x && (int)data->p1.y ==
				(int)data->p3.y) || ((int)data->p2.x == (int)data->p3.x &&
					(int)data->p2.y == (int)data->p3.y))
		return (1);
	else if (((int)data->p1.x == (int)data->p4.x && (int)data->p1.y
				== (int)data->p4.y) || ((int)data->p2.x == (int)data->p4.x
				&& (int)data->p2.y == (int)data->p4.y))
		return (1);
	return (0);
}

int		two_vert(t_data *data)
{
	if ((data->p1.x - data->p2.x == 0) && (data->p3.x - data->p4.x == 0))
	{
		if (data->p1.x == data->p3.x)
		{
			if (!((max(data->p1.y, data->p2.y) < min(data->p3.y, data->p4.y))
				|| (min(data->p1.y, data->p2.y) > max(data->p3.y, data->p4.y))))
			{
				data->color = 0xff0000;
				return (1);
			}
		}
		return (0);
	}
	return (2);
}

int		intersection_of_two_line(t_data *data)
{
	data->color = 0x15eb43;
	if (touch_dots(data) == 1)
		return (0);
	if (normal_vec(data) == 0)
		return (0);
	if (two_vert(data) == 1)
		return (1);
	else if (two_vert(data) == 0)
		return (0);
	if (first_vert(data) == 1)
		return (1);
	else if (first_vert(data) == 0)
		return (0);
	if (second_vert(data) == 1)
		return (1);
	else if (second_vert(data) == 0)
		return (0);
	if (both_not_vert(data) == 1)
		return (1);
	else if (both_not_vert(data) == 0)
		return (0);
	return (0);
}

int		last(t_data *data, t_sector *sector)
{
	data->p1.x = (double)sector->x0;
	data->p1.y = (double)sector->y0;
	data->p2.x = (double)data->sectors[data->iter].x0;
	data->p2.y = (double)data->sectors[data->iter].y0;
	if (intersection_of_two_line(data) == 1)
		return (1);
	return (0);
}

int		bef_crossing(t_data *data, int check)
{
	t_sector *sector;

	data->iter = -1;
	if (check == 0 && init_vector(data) == 1)
		return (0);
	while (++data->iter != data->current_sector + 1)
	{
		sector = &data->sectors[data->iter];
		while (sector->next != NULL && sector->next->next != NULL)
		{
			if (data->current_sector == data->iter &&
				sector->next->next->next == NULL)
				break ;
			data->p1.x = (double)sector->x0;
			data->p1.y = (double)sector->y0;
			data->p2.x = (double)sector->next->x0;
			data->p2.y = (double)sector->next->y0;
			if (intersection_of_two_line(data) == 1)
				return (1);
			sector = sector->next;
		}
		if (data->iter != data->current_sector && last(data, sector) == 1)
			return (1);
	}
	return (0);
}
