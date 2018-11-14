/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vomelchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 15:41:12 by vomelchu          #+#    #+#             */
/*   Updated: 2018/11/14 15:41:14 by vomelchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	coord_canvas(t_data *data, int x, int y)
{
	data->x_canv = ((float)data->max_canv_x / (float)WIDTH * x) + data->start_coord_x;
	data->y_canv = ((float)data->max_canv_y / (float)HEIGHT * y) + data->start_coord_y;
}

void	coord_displ(t_data *data, int x, int y)
{
	data->x0 = (float)WIDTH / (float)data->max_canv_x * x + data->start_coord_x;
	data->y0 = (float)HEIGHT / (float)data->max_canv_y * y + data->start_coord_y;
}

void	limit_coord(t_data *data, int x, int y)
{
	if (y < HEIGHT - 1 && y >= 0 &&
		x < WIDTH - 1 && x >= 0)
		data->buf[y][x] = data->color;
}