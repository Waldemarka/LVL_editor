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

int		two_vertical(t_data *data)
{
	if((data->p1.x - data->p2.x == 0) && (data->p3.x - data->p4.x == 0)) {
 
    //если они лежат на одном X
    if(data->p1.x == data->p3.x) {
 
        //проверим пересекаются ли они, т.е. есть ли у них общий Y
        //для этого возьмём отрицание от случая, когда они НЕ пересекаются
        if (!((max(data->p1.y, data->p2.y) < min(data->p3.y, data->p4.y)) ||
                (min(data->p1.y, data->p2.y) > max(data->p3.y, data->p4.y)))) {
 
            return (1);
        }
    }
 
	}
    return (0);
}

int		one_vertical_2(t_data *data)
{
	if (data->p3.x - data->p4.x == 0) {
 
    //найдём Xa, Ya - точки пересечения двух прямых
    double Xa = (double)data->p3.x;
    double A1 = (double)(data->p1.y - data->p2.y) / (double)(data->p1.x - data->p2.x);
    double b1 = (double)data->p1.y - A1 * data->p1.x;
    double Ya = A1 * Xa + b1;
 
    if (data->p1.x <= Xa && data->p2.x >= Xa && min(data->p3.y, data->p4.y) <= Ya &&
            max(data->p3.y, data->p4.y) >= Ya) {
 
        return (1);
    }
}
    return (0);
}

int		one_vertical_1(t_data *data)
{
	//если первый отрезок вертикальный
	if (data->p1.x - data->p2.x == 0) {
 
    //найдём Xa, Ya - точки пересечения двух прямых
		double Xa = (double)data->p1.x;
		double A2 = (double)(data->p3.y - data->p4.y) / (double)(data->p3.x - data->p4.x);
		double b2 = (double)data->p3.y - A2 * (double)data->p3.x;
		double Ya = A2 * Xa + b2;
 
		if (data->p3.x <= Xa && data->p4.x >= Xa && min(data->p1.y, data->p2.y) <= Ya &&
            max(data->p1.y, data->p2.y) >= Ya)
        	return (1);
	}
    return (0);
}

int		without_vertical(t_data *data)
{
	double A1 = (double)(data->p1.y - data->p2.y) / (double)(data->p1.x - data->p2.x);
	double A2 = (double)(data->p3.y - data->p4.y) / (double)(data->p3.x - data->p4.x);
	double b1 = (double)data->p1.y - A1 * (double)data->p1.x;
	double b2 = (double)data->p3.y - A2 * (double)data->p3.x;
	//printf("%f\n", (double)(data->p1.y - data->p2.y) / (double)(data->p1.x - data->p2.x));
	if (A1 == A2) {
 	   return (0); //отрезки параллельны
	}
 
	//Xa - абсцисса точки пересечения двух прямых
	double Xa = (b2 - b1) / (A1 - A2);
 
	if ((Xa < max(data->p1.x, data->p3.x)) || (Xa > min( data->p2.x, data->p4.x))) {
	    return (0); //точка Xa находится вне пересечения проекций отрезков на ось X 
	}
	else {
    	return (1);
}
    return (0);
}
