/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crossing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vomelchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 19:43:58 by vomelchu          #+#    #+#             */
/*   Updated: 2018/11/18 19:43:59 by vomelchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int		crossing(t_data *data)
{
	data->color = 0x15eb43;
	/*if (data->sectors[0].next == NULL ||
		data->sectors[0].next->next == NULL
		|| data->sectors[0].next->next->next == NULL)
		return(0);*/
	int x1;
	int	y1;

	int x2;
	int	y2;

	int x3;
	int	y3;

	int x4;
	int	y4;

	x1 = data->tmp_x1;
	y1 = data->tmp_y1;
	x2 = data->tmp_x2;
	y2 = data->tmp_y2;

	coord_canvas(data, data->x0_line, data->y0_line);
	x3 = near_round(data->x_canv);
	y3 = near_round(data->y_canv);

	coord_canvas(data, data->x1_line, data->y1_line);
	x4 = near_round(data->x_canv);
	y4 = near_round(data->y_canv);

	int	dx1 = x2 - x1;
	int	dy1 = y2 - y1;
	int	dx2 = x4 - x3;
	int	dy2 = y4 - y3;

	float x = (float)dy1 * (float)dx2 - (float)dy2 * (float)dx1;
	if(!x || !dx2)
		return (0);
	long y = x3 * y4 - y3 * x4;
	x = ((x1 * y2 - y1 * x2) * dx2 - y * dx1) / x;
	y = (dy2 * x - y) / dx2;
	if (((x1 <= x && x2 >= x) || (x2 <= x && x1 >= x))
		&& ((x3 <= x && x4 >= x) || (x4 <= x && x3 >= x)))
	{
		data->color = 0xff0000;
		printf("x1 %d --- y1 %d +++ x2 %d ---- y2 %d\n", x1, y1, x2, y2);
		printf("x3 %d --- y3 %d +++ x4 %d ---- y4 %d\n", x3, y3, x4, y4);
		return (1);
	}
	return (0);
}

int		bef_crossing(t_data *data)
{
	t_sector *sector;
	int i;

	i = -1;
	if (data->sectors[0].next == NULL ||
		data->sectors[0].next->next == NULL
		|| data->sectors[0].next->next->next == NULL)
		return(0);
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
			data->tmp_x1 = sector->x0;
			data->tmp_y1 = sector->y0;
			data->tmp_x2 = sector->next->x0;
			data->tmp_y2 = sector->next->y0;
			if (crossing(data) == 1)
				return (1);
			sector = sector->next;
		}
	}
	return (0);
}
