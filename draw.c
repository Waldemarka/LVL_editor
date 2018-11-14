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
	tmp_sect->x0 = data->x_canv;
	tmp_sect->y0 = data->y_canv;
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
	}
	
}
/*
void	draw_grid(t_data *data)
{
	int q;

	q = 0;
	data->y0 = 0;	
	data->color = 0x2d4d49;
	while (q < WIDTH)
	{
		data->x0 = q;
		data->x1 = q;
		data->y1 = HEIGHT;
		q += data->scale;
		bresenham_line(data);
	}
	q = 0;
	data->x0 = 0;
	while (q < HEIGHT)
	{
		data->y0 = q;
		data->x1 = WIDTH;
		data->y1 = q;
		q += data->scale;
		bresenham_line(data);
	}
}
*/