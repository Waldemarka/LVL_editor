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

void	fill_next(t_data *data, int x, int y)
{
	t_sector *tmp_sect;

	tmp_sect = &data->sectors[data->current_sector];
	while (tmp_sect->next != NULL)
		tmp_sect = tmp_sect->next;
	coord_canvas(data, x, y);
	tmp_sect->x0 = near_round(data->x_canv);
	tmp_sect->y0 = near_round(data->y_canv);
	if (!(tmp_sect->next = (t_sector *)malloc(sizeof(t_sector))))
		ft_error("Bad malloc in fill_next");
	tmp_sect->next->next = NULL;
	tmp_sect = tmp_sect->next;
}


void	draw_lines(t_data *data)
{
	t_sector *tmp_sect;
	int i;
	int len;

	i = -1;
	data->color = 0x15eb43;
	if (data->check_click != 0)
		len = data->for_realloc;
	else
		len = data->for_realloc -1;
	while (++i < data->for_realloc)
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
		data->color = 0x2d4d49;
		if (q % 50 == 0)
			data->color = 0x021c5d;
		if (q % 250 == 0)
			data->color = 0xc1845d;
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
		data->color = 0x2d4d49;
		if (q % 50 == 0)
			data->color = 0x021c5d;
		if (q % 250 == 0)
			data->color = 0xc1845d;
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
