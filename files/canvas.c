/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vomelchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 15:41:12 by vomelchu          #+#    #+#             */
/*   Updated: 2019/01/02 13:20:39 by vomelchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	coord_canvas(t_data *data, int x, int y)
{
	data->x_canv = data->start_coord_x + (float)(data->max_canv_x
		- data->start_coord_x) * (x / (float)WIDTH);
	data->y_canv = data->start_coord_y + (float)(data->max_canv_y
		- data->start_coord_y) * (y / (float)HEIGHT);
}

void	coord_displ(t_data *data, int x, int y)
{
	data->x0 = ((x - data->start_coord_x) * (float)WIDTH) /
	((float)(data->max_canv_x - data->start_coord_x));
	data->y0 = ((y - data->start_coord_y) * (float)HEIGHT) /
	((float)(data->max_canv_y - data->start_coord_y));
}

void	limit_coord(t_data *data, int x, int y)
{
	if (y < HEIGHT - 1 && y >= 223 &&
			x < WIDTH - 1 && x >= 0)
		data->buf[y][x] = data->color;
}
