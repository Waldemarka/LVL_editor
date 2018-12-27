/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crossing_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vomelchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 13:30:22 by vomelchu          #+#    #+#             */
/*   Updated: 2018/11/25 16:27:16 by vomelchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

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

int		normal_vec(t_data *data)
{
	if (data->p2.x < data->p1.x) {
		vector tmp = data->p1;
		data->p1 = data->p2;
		data->p2 = tmp;
	}
	if (data->p4.x < data->p3.x) {
		vector tmp = data->p3;
		data->p3 = data->p4;
		data->p4 = tmp;
	}
	if (data->p2.x < data->p3.x) {
		return (0);
	}
	return (1);
}

int		first_vert(t_data *data)
{
	double Xa;
	double A2;
	double b2;
	double Ya;

	if (data->p1.x - data->p2.x == 0) {
		Xa = data->p1.x;
		A2 = (data->p3.y - data->p4.y) / (data->p3.x - data->p4.x);
		b2 = data->p3.y - A2 * data->p3.x;
		Ya = A2 * Xa + b2;
		if (data->p3.x <= Xa && data->p4.x >= Xa && min(data->p1.y, data->p2.y) <= Ya &&
				max(data->p1.y, data->p2.y) >= Ya)
		{
			data->color = 0xff0000;
			return (1);
		}
		return (0);
	}
	return (2);
}

int		second_vert(t_data *data)
{
	double Xa;
	double A1;
	double b1;
	double Ya;

	if (data->p3.x - data->p4.x == 0)
	{
		Xa = data->p3.x;
		A1 = (data->p1.y - data->p2.y) / (data->p1.x - data->p2.x);
		b1 = data->p1.y - A1 * data->p1.x;
		Ya = A1 * Xa + b1;
		if (data->p1.x <= Xa && data->p2.x >= Xa &&
				min(data->p3.y, data->p4.y) <= Ya && max(data->p3.y, data->p4.y) >= Ya)
		{
			data->color = 0xff0000;
			return (1);
		}
		return (0);
	}
	return (2);
}

int		both_not_vert(t_data *data)
{
	double A1;
	double A2;
	double b1;
	double b2;
	double Xa;

	A1 = (data->p1.y - data->p2.y) / (data->p1.x - data->p2.x);
	A2 = (data->p3.y - data->p4.y) / (data->p3.x - data->p4.x);
	b1 = data->p1.y - A1 * data->p1.x;
	b2 = data->p3.y - A2 * data->p3.x;
	if (A1 == A2)
		return (0);
	Xa = (b2 - b1) / (A1 - A2);
	if ((Xa < max(data->p1.x, data->p3.x)) || (Xa > min( data->p2.x, data->p4.x)))
		return (0);
	else {
		data->color = 0xff0000;
		return (1);
	}
}

