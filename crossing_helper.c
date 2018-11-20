/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crossing_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vomelchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 13:30:22 by vomelchu          #+#    #+#             */
/*   Updated: 2018/11/20 13:30:24 by vomelchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

typedef struct 	s_vector
{
		double x;
		double y;
}				vector;

int		min(int	x, int y)
{
	if (x < y)
		return (x);
	else
		return (y);
	return (x);
}

int		max(int	x, int y)
{
	if (x > y)
		return (x);
	else
		return (y);
	return (x);
}

int		two_vertical(vector p1, vector p2, vector p3, vector p4)
{
	if((p1.x - p2.x == 0) && (p3.x - p4.x == 0)) {
 
    //если они лежат на одном X
    if(p1.x == p3.x) {
 
        //проверим пересекаются ли они, т.е. есть ли у них общий Y
        //для этого возьмём отрицание от случая, когда они НЕ пересекаются
        if (!((max(p1.y, p2.y) < min(p3.y, p4.y)) ||
                (min(p1.y, p2.y) > max(p3.y, p4.y)))) {
 
            return (1);
        }
    }
 
	}
    return (0);
}

int		one_vertical(vector p1, vector p2, vector p3, vector p4)
{
	//если первый отрезок вертикальный
	if (p1.x - p2.x == 0) {
 
    //найдём Xa, Ya - точки пересечения двух прямых
		double Xa = (double)p1.x;
		double A2 = (double)(p3.y - p4.y) / (double)(p3.x - p4.x);
		double b2 = (double)p3.y - A2 * (double)p3.x;
		double Ya = A2 * Xa + b2;
 
		if (p3.x <= Xa && p4.x >= Xa && min(p1.y, p2.y) <= Ya &&
            max(p1.y, p2.y) >= Ya)
        	return (1);
	}
    return (0);
}

int		without_vertical(vector p1, vector p2, vector p3, vector p4)
{
	double A1 = (double)(p1.y - p2.y) / (double)(p1.x - p2.x);
	double A2 = (double)(p3.y - p4.y) / (double)(p3.x - p4.x);
	double b1 = (double)p1.y - A1 * (double)p1.x;
	double b2 = (double)p3.y - A2 * (double)p3.x;
	//printf("%f\n", (double)(p1.y - p2.y) / (double)(p1.x - p2.x));
	if (A1 == A2) {
 	   return (0); //отрезки параллельны
	}
 
	//Xa - абсцисса точки пересечения двух прямых
	double Xa = (b2 - b1) / (A1 - A2);
 
	if ((Xa < max(p1.x, p3.x)) || (Xa > min( p2.x, p4.x))) {
	    return (0); //точка Xa находится вне пересечения проекций отрезков на ось X 
	}
	else {
    	return (1);
    return (0);
}
}

int		crossing(vector p1, vector p2, vector p3, vector p4)
{
	if (p2.x < p1.x) {
 
    vector tmp = p1;
    p1 = p2;
    p2 = tmp;
	}
	if (p4.x < p3.x) {
 
  	  vector tmp = p3;
 	   p3 = p4;
 	   p4 = tmp;
	}
	if (p2.x < p3.x)
    	return (0);
    if (two_vertical(p1, p2, p3, p4) == 1)
    	return (1);
    if (one_vertical(p1, p2, p3, p4) == 1 ||
    	one_vertical(p3, p4, p1, p2) == 1)
    	return (1);
    if (without_vertical(p1, p2, p3, p4) == 1)
    	return (1);
	return (0);
}

int		bef_crossing(t_data *data)
{
	t_sector *sector;
	vector p1;
	vector p2;
	vector p3;
	vector p4;
	int i;

	i = -1;
	if (data->sectors[0].next == NULL ||
		data->sectors[0].next->next == NULL
		|| data->sectors[0].next->next->next == NULL)
		return(0);
	coord_canvas(data, data->x0_line, data->y0_line);
	p3.x = (double)near_round(data->x_canv);
	p3.y = (double)near_round(data->y_canv);
	coord_canvas(data, data->x1_line, data->y1_line);
	p4.x = (double)near_round(data->x_canv);
	p4.y = (double)near_round(data->y_canv);
	/*sector = &data->sectors[0];
	data->tmp_x1 = sector->x0;
	data->tmp_y1 = sector->y0;
	data->tmp_x2 = sector->next->x0;
	data->tmp_y2 = sector->next->y0;
	if (crossing(data) == 1)
				return (1);*/
	while (++i != data->for_realloc)
	{
		sector = &data->sectors[i];
		while (sector->next != NULL && sector->next->next != NULL)
		{
			if (data->current_sector == i
				&& (sector->next == NULL ||
					sector->next->next == NULL
					|| sector->next->next->next == NULL))
				break;
			/*data->tmp_x1 = sector->x0;
			data->tmp_y1 = sector->y0;
			data->tmp_x2 = sector->next->x0;
			data->tmp_y2 = sector->next->y0;*/
			p1.x = (double)sector->x0;
			p1.y = (double)sector->y0;
			p2.x = (double)sector->next->x0;
			p2.y = (double)sector->next->y0;
		//	printf("%d\n", crossing(p1, p2, p3, p4));
		//	printf("%d\n", crossing(p1, p2, p3, p4));
			if (crossing(p1, p2, p3, p4) == 1)
			{
				data->color = 0xff0000;
				return (1);
			}
			sector = sector->next;
		}
	}
	data->color = 0x15eb43;
	return (0);
}