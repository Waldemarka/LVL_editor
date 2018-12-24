/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vomelchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 18:18:35 by vomelchu          #+#    #+#             */
/*   Updated: 2018/12/09 19:17:32 by vomelchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	picture_icon(t_data *data, int st_x, int st_y, SDL_Surface *icon)
{
	int q;
	int i;

	q = st_y - 1;
	while (++q < st_y + data->pixel_pict)
	{
		if (q < data->min_coord_icon || q > HEIGHT - 1)
			continue;
		i = st_x - 1;
		while (++i < st_x + data->pixel_pict)
		{
			if (i < 0 || i > WIDTH - 1)
				continue;
			if (get_pixel_int(icon, i - st_x, q - st_y) != 0)
				data->buf[q][i] = get_pixel_int(icon, i - st_x, q - st_y);
		}
	}
}

void	picture(t_data *data)
{
	int q;
	int i;

	q = -1;
	while (++q < 223)
	{
		i = -1;
		while (++i < 720)
			data->buf[q][i] = get_pixel_int(data->dot[data->picture_menu % 3], i, q);
	}
}

void	mouse_icons(t_data *data)
{
	int x;
	int y;

	SDL_PumpEvents();
	if (SDL_GetMouseState(&x, &y) & SDL_BUTTON(SDL_BUTTON_LEFT) && y > 32
		&& y < 64 && x > 250 && x < 282)
		data->num_icon = 0;
	if (SDL_GetMouseState(&x, &y) & SDL_BUTTON(SDL_BUTTON_LEFT)
		&& y > 32 && y < 64 && x > 282 && x < 314 && data->num_icon == -1)
		data->num_icon = 1;
	else if (SDL_GetMouseState(&x, &y) & SDL_BUTTON(SDL_BUTTON_LEFT)
		&& y > 64 && y < 96 && x > 250 && x < 282 && data->num_icon == -1)
		data->num_icon = 2;
	else if (SDL_GetMouseState(&x, &y) & SDL_BUTTON(SDL_BUTTON_LEFT)
		&& y > 64 && y < 96 && x > 282 && x < 314 && data->num_icon == -1)
		data->num_icon = 3;
	else if (SDL_GetMouseState(&x, &y) & SDL_BUTTON(SDL_BUTTON_LEFT)
		&& y > 96 && y < 128 && x > 250 && x < 282 && data->num_icon == -1)
		data->num_icon = 4;
	else if (SDL_GetMouseState(&x, &y) & SDL_BUTTON(SDL_BUTTON_LEFT)
		&& y > 96 && y < 128 && x > 282 && x < 314 && data->num_icon == -1)
		data->num_icon = 5;
	else
		help_mouse_icons(data);
}

void	set_icon(t_data *data, int x, int y)
{
	if (y > 223 && data->object < 150 && check_in_sector(data, x, y) == 0)
	{
		coord_canvas(data, x, y);
		if (data->num_icon == 0 || data->num_icon == 1
			|| data->num_icon == 6 || data->num_icon == 4 || data->num_icon == 2)
			special_icons(data);
		else
		{
			writte_icons_to_struct(data, data->object);
			data->object++;
		}
	}
	data->num_icon = -1;
}

void	move_icons(t_data *data)
{
	int x, y;

	SDL_PumpEvents();
	if (SDL_GetMouseState(&x, &y)
		& SDL_BUTTON(SDL_BUTTON_LEFT) && data->num_icon >= 0)
	{
		data->pixel_pict = 64;
		picture_icon(data, x - 32,  y - 32, data->icon64[data->num_icon]);
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
			picture_icon(data, data->x0 - 16,  data->y0 - 16,
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
	while (++q <= 7)
	{
		picture_icon(data, 250 + (32 * (q % 2)),  32 + (32 * (q / 2)),
			data->icon[q]);
	}
	if (data->check_menu == 1)
	{
		mouse_icons(data);
		move_icons(data);
	}
}

void	menu(t_data *data, int i)
{
	SDL_Color       color;
	color.r = 255;
	color.g = 255;
	color.b = 255;

	picture(data);
	if (i == 0 && data->show_text != 1)
		event_menu(data);
	if (data->picture_menu % 3 != 2)
	{
		if (i == 0 && data->flo_or_cei == 0 && data->floor > data->ceil - 5)
			data->floor = data->ceil - 5;
		if (i == 0 && data->flo_or_cei == 1 && data->ceil < data->floor + 5)
			data->ceil = data->floor + 5;
		//system("leaks lvl_editor");
		//draw_text(data, ft_itoa(data->floor), 175, 53, color, F_ARIAL, 27);
		//draw_text(data, ft_itoa(data->ceil), 175, 150, color, F_ARIAL, 27);
		color.r = 128;
		color.g = 153;
		color.b = 84;
		//draw_text(data, ">", 7, 53 + (data->flo_or_cei * 97), color, F_ARIAL, 27);
		icons(data);
		textures_menu(data);
	}
}

/* how to lift up */









