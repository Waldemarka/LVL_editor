/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crossing_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vomelchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 13:30:22 by vomelchu          #+#    #+#             */
/*   Updated: 2019/01/02 13:20:56 by vomelchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int		init_vector(t_data *data)
{
	if (data->sectors[0].next == NULL ||
			data->sectors[0].next->next == NULL
			|| data->sectors[0].next->next->next == NULL)
		return (1);
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
	t_vector tmp;

	if (data->p2.x < data->p1.x)
	{
		tmp = data->p1;
		data->p1 = data->p2;
		data->p2 = tmp;
	}
	if (data->p4.x < data->p3.x)
	{
		tmp = data->p3;
		data->p3 = data->p4;
		data->p4 = tmp;
	}
	if (data->p2.x < data->p3.x)
		return (0);
	return (1);
}

int		first_vert(t_data *data)
{
	double x_a;
	double a_2;
	double b2;
	double y_a;

	if (data->p1.x - data->p2.x == 0)
	{
		x_a = data->p1.x;
		a_2 = (data->p3.y - data->p4.y) / (data->p3.x - data->p4.x);
		b2 = data->p3.y - a_2 * data->p3.x;
		y_a = a_2 * x_a + b2;
		if (data->p3.x <= x_a && data->p4.x >= x_a &&
			min(data->p1.y, data->p2.y) <= y_a &&
				max(data->p1.y, data->p2.y) >= y_a)
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
	double x_a;
	double a_1;
	double b1;
	double y_a;

	if (data->p3.x - data->p4.x == 0)
	{
		x_a = data->p3.x;
		a_1 = (data->p1.y - data->p2.y) / (data->p1.x - data->p2.x);
		b1 = data->p1.y - a_1 * data->p1.x;
		y_a = a_1 * x_a + b1;
		if (data->p1.x <= x_a && data->p2.x >= x_a &&
				min(data->p3.y, data->p4.y) <= y_a &&
				max(data->p3.y, data->p4.y) >= y_a)
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
	double a_1;
	double a_2;
	double b1;
	double b2;
	double x_a;

	a_1 = (data->p1.y - data->p2.y) / (data->p1.x - data->p2.x);
	a_2 = (data->p3.y - data->p4.y) / (data->p3.x - data->p4.x);
	b1 = data->p1.y - a_1 * data->p1.x;
	b2 = data->p3.y - a_2 * data->p3.x;
	if (a_1 == a_2)
		return (0);
	x_a = (b2 - b1) / (a_1 - a_2);
	if ((x_a < max(data->p1.x, data->p3.x)) ||
		(x_a > min(data->p2.x, data->p4.x)))
		return (0);
	else
	{
		data->color = 0xff0000;
		return (1);
	}
}
