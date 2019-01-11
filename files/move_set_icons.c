/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_set_icons.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vomelchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 12:53:26 by vomelchu          #+#    #+#             */
/*   Updated: 2019/01/02 13:23:28 by vomelchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	mouse_icons(t_data *data)
{
	int x;
	int y;

	SDL_PumpEvents();
	if (SDL_GetMouseState(&x, &y) & SDL_BUTTON(SDL_BUTTON_LEFT)
			&& y > 133 && y < 180 && x > 45 && x < 110)
		data->num_icon = 0;
	if (SDL_GetMouseState(&x, &y) & SDL_BUTTON(SDL_BUTTON_LEFT)
			&& y > 133 && y < 180 && x > 115 && x < 180 && data->num_icon == -1)
		data->num_icon = 1;
	else if (SDL_GetMouseState(&x, &y) & SDL_BUTTON(SDL_BUTTON_LEFT)
			&& y > 133 && y < 180 && x > 185 && x < 250 && data->num_icon == -1)
		data->num_icon = 2;
	else if (SDL_GetMouseState(&x, &y) & SDL_BUTTON(SDL_BUTTON_LEFT)
			&& y > 133 && y < 180 && x > 255 && x < 320 && data->num_icon == -1)
		data->num_icon = 3;
	else if (SDL_GetMouseState(&x, &y) & SDL_BUTTON(SDL_BUTTON_LEFT)
			&& y > 133 && y < 180 && x > 325 && x < 390 && data->num_icon == -1)
		data->num_icon = 8;
	else if (SDL_GetMouseState(&x, &y) & SDL_BUTTON(SDL_BUTTON_LEFT)
			&& y > 133 && y < 180 && x > 395 && x < 460 && data->num_icon == -1)
		data->num_icon = 4;
	else
		help_mouse_icons(data);
}

void	set_icon(t_data *data, int x, int y)
{
	if (y > 223 && data->object < 150 && check_in_sector(data, x, y) == 0)
	{
		coord_canvas(data, x, y);
		if (data->num_icon == 0 || data->num_icon == 1
				|| data->num_icon == 4 || data->num_icon == 2)
			special_icons(data);
		else
		{
			writte_icons_to_struct(data, data->object);
			if (data->num_icon == 8)
			{
				data->key = 1;
				data->tmp_x = x;
				data->tmp_y = y;
			}
			data->object++;
		}
	}
	data->num_icon = -1;
}

void	move_icons(t_data *data)
{
	int x;
	int y;

	SDL_PumpEvents();
	if (SDL_GetMouseState(&x, &y)
			& SDL_BUTTON(SDL_BUTTON_LEFT) && data->num_icon >= 0)
	{
		data->pixel_pict = 64;
		picture_icon(data, x - 32, y - 32, data->icon64[data->num_icon]);
	}
	else if (data->num_icon != -1)
		set_icon(data, x, y);
}

void	draw_icons(t_data *data)
{
	int q;

	data->min_coord_icon = 223;
	if (data->object > 0)
	{
		q = -1;
		data->pixel_pict = 32;
		while (++q <= data->object - 1)
		{
			if (data->icons[q].flag == 0)
				continue;
			coord_displ(data, data->icons[q].x, data->icons[q].y);
			if (data->y0 < 207)
				continue;
			picture_icon(data, data->x0 - 16, data->y0 - 16,
					data->icon[data->icons[q].obj]);
		}
	}
	data->min_coord_icon = 0;
}

void	icons(t_data *data)
{
	int q;

	q = -1;
	data->pixel_pict = 32;
	draw_icons(data);
	while (++q <= 8)
	{
		if (q == 4)
			picture_icon(data, 60 + (q * 71), 145, data->icon[8]);
		else if (q < 4)
			picture_icon(data, 60 + (q * 71), 145, data->icon[q]);
		else
			picture_icon(data, 60 + (q * 71), 145, data->icon[q - 1]);
	}
	if (data->check_menu == 1 && data->key != 1)
	{
		mouse_icons(data);
		move_icons(data);
	}
	if (data->key == 1)
		multi_key(data);
}
