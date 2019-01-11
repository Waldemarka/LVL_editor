/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vomelchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2218/11/07 16:44:45 by vomelchu          #+#    #+#             */
/*   Updated: 2019/01/02 13:22:09 by vomelchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int		is_crossing_last_line(t_data *data)
{
	t_sector *sector;

	data->p3.x = (double)data->sectors[data->current_sector].x0;
	data->p3.y = (double)data->sectors[data->current_sector].y0;
	sector = &data->sectors[data->current_sector];
	while (sector->next->next != NULL)
		sector = sector->next;
	data->p4.x = (double)sector->x0;
	data->p4.y = (double)sector->y0;
	if (bef_crossing(data, 1) == 1)
		return (1);
	return (0);
}

void	space_imitation(t_data *data)
{
	if (len_list(&data->sectors[data->current_sector]) >= 3
			&& is_crossing_last_line(data) == 0)
	{
		data->current_sector++;
		data->check_click = 0;
		data->sectors[data->current_sector].next = NULL;
		data->check_menu = 1;
	}
}

void	key_event(t_data *data)
{
	SDL_Event	event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			data->for_exit = 1;
		if (EXIT)
			data->for_exit = 1;
		key_helper(data, event);
	}
}

void	mouse_line(t_data *data)
{
	int	x;
	int	y;

	SDL_PumpEvents();
	if (SDL_GetMouseState(&x, &y) & SDL_BUTTON(SDL_BUTTON_LEFT) && y < 223
			&& data->check_click == 0)
		data->check_menu = 1;
	if (data->current_sector < 32)
	{
		if (SDL_GetMouseState(&x, &y) & SDL_BUTTON(SDL_BUTTON_LEFT) && y > 223)
			mouse_help(data, x, y);
		else
		{
			if (data->tmp_count > 0)
				data->tmp_count = 0;
			data->x0_line = x;
			data->y0_line = y;
		}
		bef_crossing(data, 0);
		near_lines(data);
	}
}
