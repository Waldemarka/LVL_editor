/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vomelchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 11:45:29 by vomelchu          #+#    #+#             */
/*   Updated: 2019/01/09 11:45:30 by vomelchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	draw_grid_help(t_data *data)
{
	int q;

	q = normalize_line(data->start_coord_y);
	while (q <= data->max_canv_y)
	{
		data->color = 0x001b3d;
		if (q % 50 == 0)
			data->color = 0x122b68;
		if (q % 250 == 0)
			data->color = 0xc1a3c93;
		coord_displ(data, data->max_canv_x, q);
		data->x1 = data->x0;
		data->y1 = data->y0;
		coord_displ(data, data->start_coord_x, q);
		q += 10;
		bresenham_line(data);
	}
}

void	draw_grid(t_data *data)
{
	int q;

	q = normalize_line(data->start_coord_x);
	while (q <= data->max_canv_x)
	{
		data->color = 0x001b3d;
		if (q % 50 == 0)
			data->color = 0x122b68;
		if (q % 250 == 0)
			data->color = 0xc1a3c93;
		coord_displ(data, q, data->max_canv_y);
		data->x1 = data->x0;
		data->y1 = data->y0;
		coord_displ(data, q, data->start_coord_y);
		q += 10;
		bresenham_line(data);
	}
	draw_grid_help(data);
}
