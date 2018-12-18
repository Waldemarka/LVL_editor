/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vomelchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 16:06:36 by vomelchu          #+#    #+#             */
/*   Updated: 2018/11/08 16:06:39 by vomelchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int		clockwise(t_data *data)
{
	double a;
	t_sector *tmp_sect;
	tmp_sect = &data->sectors[data->current_sector];
	while (tmp_sect->next != NULL)
	{
		a = atan2((double)tmp_sect->x0 * (double)tmp_sect->next->y0 -
			(double)tmp_sect->next->x0 * (double)tmp_sect->y0,
			(double)tmp_sect->x0 * (double)tmp_sect->next->x0 +
			(double)tmp_sect->y0 * (double)tmp_sect->next->y0);
		printf("%f\n", a);
		//if (a < 0)
		//	return (1);
		tmp_sect = tmp_sect->next;
	}
	a = atan2((double)data->sectors[data->current_sector].x0 
		* (double)tmp_sect->y0 - (double)tmp_sect->x0
		* (double)data->sectors[data->current_sector].y0,
		(double)data->sectors[data->current_sector].x0
		* (double)tmp_sect->x0 + (double)data->sectors[data->current_sector].y0
		* (double)tmp_sect->y0);
	printf("%f\n", a);
	//if (a < 0)
	//	return (1);
	return (0);
	//printf("%f\n", a);
}

void	fill_next(t_data *data, int x, int y)
{
	t_sector *tmp_sect;

	tmp_sect = &data->sectors[data->current_sector];
	//printf("%d\n", len_list(tmp_sect));
	while (tmp_sect->next != NULL)
		tmp_sect = tmp_sect->next;
	coord_canvas(data, x, y);
	tmp_sect->x0 = near_round(data->x_canv);
	tmp_sect->y0 = near_round(data->y_canv);
	//clockwise(data);
	if (tmp_sect->x0 == data->sectors[data->current_sector].x0
		&& tmp_sect->y0 == data->sectors[data->current_sector].y0)
		space_imitation(data);
	if (!(tmp_sect->next = (t_sector *)malloc(sizeof(t_sector))))
		ft_error("Bad malloc in fill_next");
	tmp_sect->next->next = NULL;
	tmp_sect = tmp_sect->next;
}


void	draw_lines(t_data *data)
{
	t_sector *tmp_sect;
	int i;

	i = -1;
	data->color = 0x15eb43;
	while (++i < data->current_sector + 1)
	{
		tmp_sect = &data->sectors[i];	
		while (tmp_sect->next != NULL)
		{
			if (tmp_sect->next->next != NULL && tmp_sect->next != NULL)
			{
				coord_displ(data, tmp_sect->next->x0, tmp_sect->next->y0);
				data->x1 = data->x0;
				data->y1 = data->y0;
				coord_displ(data, tmp_sect->x0, tmp_sect->y0);
				bresenham_line(data);
			}
			tmp_sect = tmp_sect->next;
		}
		if (i != data->current_sector)
		{
			coord_displ(data, data->sectors[i].x0, data->sectors[i].y0);
			bresenham_line(data);
		}
	}
	
}

int		normalize_line(int q)
{
	if (q % 10 == 0)
		return (q);
	while (q % 10 != 0)
		q++;
	return (q);
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

void	near_lines(t_data *data)
{
	coord_canvas(data, data->x1_line, data->y1_line);
	coord_displ(data, near_round(data->x_canv), near_round(data->y_canv));
	data->x1 = data->x0;
	data->y1 = data->y0;
	coord_canvas(data, data->x0_line, data->y0_line);
	coord_displ(data, near_round(data->x_canv), near_round(data->y_canv));
}
