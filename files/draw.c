/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vomelchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 16:06:36 by vomelchu          #+#    #+#             */
/*   Updated: 2019/01/02 13:21:03 by vomelchu         ###   ########.fr       */
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
	tmp_sect->texture = 0;
	if (tmp_sect->x0 == data->sectors[data->current_sector].x0
			&& tmp_sect->y0 == data->sectors[data->current_sector].y0)
		space_imitation(data);
	if (!(tmp_sect->next = (t_sector *)malloc(sizeof(t_sector))))
		ft_error("Bad malloc in fill_next");
	tmp_sect->next->next = NULL;
	tmp_sect = tmp_sect->next;
}

int		draw_switch_sector(t_data *data, int i)
{
	t_sector *tmp_sect;

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
	return (1);
}

void	draw_lines(t_data *data)
{
	int i;

	i = -1;
	data->color = 0x15eb43;
	while (++i < data->current_sector + 1)
		draw_switch_sector(data, i);
	data->color = 0xffffff;
	if (data->q_texture > -1)
		draw_switch_sector(data, data->q_texture);
}

int		normalize_line(int q)
{
	if (q % 10 == 0)
		return (q);
	while (q % 10 != 0)
		q++;
	return (q);
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
