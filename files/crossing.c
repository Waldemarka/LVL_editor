/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crossing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vomelchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 19:43:58 by vomelchu          #+#    #+#             */
/*   Updated: 2018/12/03 19:11:41 by vomelchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int		touch_dots(t_data *data)
{

	if (((int)data->p1.x == (int)data->p3.x && (int)data->p1.y == (int)data->p3.y) ||
			((int)data->p2.x == (int)data->p3.x && (int)data->p2.y == (int)data->p3.y))
		return (1);
	else if (((int)data->p1.x == (int)data->p4.x && (int)data->p1.y == (int)data->p4.y) ||
			((int)data->p2.x == (int)data->p4.x && (int)data->p2.y == (int)data->p4.y))
		return (1);
	return (0);
}

int		two_vert(t_data *data)
{
	if((data->p1.x - data->p2.x == 0) && (data->p3.x - data->p4.x == 0))
	{
		if(data->p1.x == data->p3.x)
		{
			if (!((max(data->p1.y, data->p2.y) < min(data->p3.y, data->p4.y)) ||
						(min(data->p1.y, data->p2.y) > max(data->p3.y, data->p4.y))))
			{
				data->color = 0xff0000;
				return (1);
			}
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

int		IntersectionOfTwoLine(t_data *data) 
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

/*int		dot_on_line(t_data *data)
{
	printf("+__+__+%f\n", ((data->p3.x - data->p1.x)*(data->p2.y - data->p1.y) -
				(data->p2.x - data->p1.x)*(data->p3.y - data->p1.y)));
	if (((data->p3.x - data->p1.x) * (data->p2.y - data->p1.y) - (data->p2.x - data->p1.x) * (data->p3.y - data->p1.y)) == 0)
		return (1);
	return (0);
}*/

double 	thc(double x, double y, double z, double w, double a, double b)
{
    double k, c;

    if (z == x) {
        return (a == x && b >= min(y, w) && x <= max(y, w));
    }

    k = (w - y) / (z - x);
    c = y - k * x;
    printf("a[%f] * k[%f] + c[%f]\n", a, k, c);
    printf("b == %f\n", b = a * k + c);
    return b = a * k + c;
}

int		bef_crossing(t_data *data, int check)
{
	t_sector *sector;

	data->iter = -1;
	if (check == 0 && init_vector(data) == 1)
		return (0);
	while (++data->iter != data->for_realloc)
	{
		sector = &data->sectors[data->iter];
		if (data->sectors[data->current_sector].floor != sector->floor)
			continue;
		while (sector->next != NULL && sector->next->next != NULL)
		{
			if (data->current_sector == data->iter && sector->next->next->next == NULL)
				break;
			data->p1.x = (double)sector->x0;
			data->p1.y = (double)sector->y0;
			data->p2.x = (double)sector->next->x0;
			data->p2.y = (double)sector->next->y0;
			if (IntersectionOfTwoLine(data) == 1)
				return (1);
			/*if (thc(10, 10, 45, 10, 35, 10) == 0)
				printf("%f------%f\n", data->p2.x, data->p2.y);*/
			sector = sector->next;
		}
			/*if (data->iter == data->current_sector && sector->next->next == NULL)
			{
				//printf("%f\n", thc(data->p1.x, data->p1.y, data->p2.x, data->p2.y, data->p3.x, data->p3.y));
					return (1);
			}*/
		if (data->iter != data->current_sector)
		{
			data->p1.x = (double)sector->x0;
			data->p1.y = (double)sector->y0;
			data->p2.x = (double)data->sectors[data->iter].x0;
			data->p2.y = (double)data->sectors[data->iter].y0;
			if (IntersectionOfTwoLine(data) == 1)
				return (1);
		}
	}
	return (0);
}

