/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_eve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vomelchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 19:23:22 by vomelchu          #+#    #+#             */
/*   Updated: 2019/01/02 13:23:15 by vomelchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	help_mouse_icons(t_data *data)
{
	int x;
	int y;

	SDL_PumpEvents();
	if (SDL_GetMouseState(&x, &y) & SDL_BUTTON(SDL_BUTTON_LEFT)
			&& y > 133 && y < 180 && x > 465 && x < 530 && data->num_icon == -1)
		data->num_icon = 5;
	else if (SDL_GetMouseState(&x, &y) & SDL_BUTTON(SDL_BUTTON_LEFT)
			&& y > 133 && y < 180 && x > 535 && x < 600 && data->num_icon == -1)
		data->num_icon = 6;
	else if (SDL_GetMouseState(&x, &y) & SDL_BUTTON(SDL_BUTTON_LEFT)
			&& y > 133 && y < 180 && x > 605 && x < 670 && data->num_icon == -1)
		data->num_icon = 7;
	else if (SDL_GetMouseState(&x, &y) & SDL_BUTTON(SDL_BUTTON_LEFT)
			&& y > 190 && y < 220 && x > 550 && x < 670 && data->num_icon == -1
			&& data->show_text == 0)
	{
		data->show_text = 1;
		data->picture_menu = 3;
	}
	else if (SDL_GetMouseState(&x, &y) & SDL_BUTTON(SDL_BUTTON_LEFT)
			&& y > 223 && y < HEIGHT - 1 && x > 0 && x < WIDTH - 1
			&& data->num_icon == -1 && data->show_text != 1)
		next_sect(data);
}

int		check_first_cross(t_data *data, int x1, int y1)
{
	t_sector	*tmp_sec;
	int			i;
	int			x;
	int			y;

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
