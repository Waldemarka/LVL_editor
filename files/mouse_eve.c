/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_eve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vomelchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 19:23:22 by vomelchu          #+#    #+#             */
/*   Updated: 2018/12/09 17:45:12 by vomelchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int		check_first_cross(t_data *data, int x1, int y1)
{
	t_sector *tmp_sec;
	int i;
	int x;
	int y;

	if (data->current_sector == 0)
		return (1);
	if (data->check_click == 1)
		return (1);
	i = -1;
	coord_canvas(data, x1, y1);
	x = near_round(data->x_canv);
	y = near_round(data->y_canv);
	while (++i != data->current_sector)
	{
		tmp_sec = &data->sectors[i];
		while (tmp_sec->next != NULL)
		{
			if (x == tmp_sec->x0 && y == tmp_sec->y0)
				return (1);
			tmp_sec = tmp_sec->next;
		}
	}
	return (0);
}

void	mouse_help(t_data *data, int x, int y)
{
	if (data->tmp_count == 0)
	{
		if (data->check_click == 0 &&
			check_first_cross(data, x, y) == 1)
		{
			data->check_click = 1;
			data->x1_line = x;
			data->y1_line = y;
			fill_next(data, x, y);
		}
		else if (bef_crossing(data, 0) == 0 &&
			check_first_cross(data, x, y) == 1
			&& len_list(&data->sectors[data->current_sector]) <= 4)
		{
			data->x1_line = x;
			data->y1_line = y;
			fill_next(data, x, y);
		}
		data->tmp_count++;
	}
}
