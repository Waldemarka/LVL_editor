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
		if (q < 0 || q > HEIGHT - 1)
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

void	numer_helper(SDL_Event	event, int *num, t_data *data)
{
	if (event.key.keysym.sym == SDLK_BACKSPACE)
		*num = *num / 10;
	if (event.key.keysym.sym == SDLK_UP)
		data->flo_or_cei = 0;
	if (event.key.keysym.sym == SDLK_DOWN)
		data->flo_or_cei = 1;
	if (event.key.keysym.sym == SDLK_RIGHT)
		data->picture_menu += 1;
	if (event.key.keysym.sym == SDLK_LEFT)
	{
		data->picture_menu -= 1;
		if (data->picture_menu < 0)
			data->picture_menu = 2;
	}
	if (event.key.keysym.sym == SDLK_z)
		data->check_menu = 0;
	if (event.key.keysym.sym == SDLK_RETURN)
	{
		if (data->picture_menu % 3 == 0)
		{
			data->check_menu = 0;
			data->sectors[data->current_sector].floor = data->floor;
			data->sectors[data->current_sector].ceil = data->ceil;
		}
		if (data->picture_menu % 3 == 1)
		{
			data->for_exit = 1;
			writting(data);
		}
		if (data->picture_menu % 3 == 1)
		{
			data->for_exit = 1;
			writting(data);
		}
	}
}

void	numer(SDL_Event	event, int *num, t_data *data)
{
	if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_1)
				*num = *num * 10 + 1;
			if (event.key.keysym.sym == SDLK_2)
				*num = *num * 10 + 2;
			if (event.key.keysym.sym == SDLK_3)
				*num = *num * 10 + 3;
			if (event.key.keysym.sym == SDLK_4)
				*num = *num * 10 + 4;
			if (event.key.keysym.sym == SDLK_5)
				*num = *num * 10 + 5;
			if (event.key.keysym.sym == SDLK_6)
				*num = *num * 10 + 6;
			if (event.key.keysym.sym == SDLK_7)
				*num = *num * 10 + 7;
			if (event.key.keysym.sym == SDLK_8)
				*num = *num * 10 + 8;
			if (event.key.keysym.sym == SDLK_9)
				*num = *num * 10 + 9;
			if (event.key.keysym.sym == SDLK_0)
				*num = *num * 10 + 0;
			numer_helper(event, num, data);
		}
}

void	event_menu(t_data *data)
{
	SDL_Event	event;
	int 		*num;
	if (data->flo_or_cei == 0)
		num = &data->floor;
	else
		num = &data->ceil;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			data->for_exit = 1;
		if (EXIT)
			data->for_exit = 1;
		numer(event, num, data);
		if (*num > 999)
			*num = 999;
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
		{
			data->buf[q][i] = get_pixel_int(data->dot[data->picture_menu % 3], i, q);
		}
	}
}

void	mouse_icons(t_data *data)
{
	int x, y;

	SDL_PumpEvents();
	if (SDL_GetMouseState(&x, &y) & SDL_BUTTON(SDL_BUTTON_LEFT) && y > 32 && y < 64 && x > 250 && x < 282)
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
	else if (SDL_GetMouseState(&x, &y) & SDL_BUTTON(SDL_BUTTON_LEFT)
		&& y > 128 && y < 160 && x > 250 && x < 282 && data->num_icon == -1)
		data->num_icon = 6;
	else if (SDL_GetMouseState(&x, &y) & SDL_BUTTON(SDL_BUTTON_LEFT)
		&& y > 128 && y < 160 && x > 282 && x < 314 && data->num_icon == -1)
		data->num_icon = 7;
	else if (SDL_GetMouseState(&x, &y) & SDL_BUTTON(SDL_BUTTON_LEFT)
		&& y > 160 && y < 192 && x > 250 && x < 282 && data->num_icon == -1)
		data->num_icon = 8;
	else if (SDL_GetMouseState(&x, &y) & SDL_BUTTON(SDL_BUTTON_LEFT)
		&& y > 160 && y < 192 && x > 282 && x < 314 && data->num_icon == -1)
		data->num_icon = 9;
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
	{
		if (y > 223 && data->object < 50)
		{
			coord_canvas(data, x, y);
			data->icons[data->object].x = data->x_canv;
			data->icons[data->object].y = data->y_canv;
			data->icons[data->object].obj = data->num_icon;
			data->object++;
		}
		data->num_icon = -1;
	}
}

void	icons(t_data *data)
{
	int q;

	q = -1;
	data->pixel_pict = 32;
	while (++q <= 9)
	{
		picture_icon(data, 250 + (32 * (q % 2)),  32 + (32 * (q / 2)), data->icon[q]);
	}
	if (data->check_menu == 1)
	{
		mouse_icons(data);
		move_icons(data);
	}
	if (data->object > 0)
	{
		q = -1;
		data->pixel_pict = 32;
		while (++q <= data->object - 1)
		{
			coord_displ(data, data->icons[q].x, data->icons[q].y);
			if (data->y0 < 207)
				continue;
			picture_icon(data, data->x0 - 16,  data->y0 - 16, data->icon[data->icons[q].obj]);
		}
	}
}

void	menu(t_data *data, int i)
{
	SDL_Color       color;
	color.r = 255;
	color.g = 255;
	color.b = 255;

	picture(data);
	if (i == 0)
		event_menu(data);
	if (data->picture_menu % 3 != 2)
	{
		if (i == 0 && data->flo_or_cei == 0 && data->floor > data->ceil - 5)
			data->floor = data->ceil - 5;
		if (i == 0 && data->flo_or_cei == 1 && data->ceil < data->floor + 5)
			data->ceil = data->floor + 5;
		draw_text(data, ft_itoa(data->floor), 175, 53, color, F_ARIAL, 27);
		draw_text(data, ft_itoa(data->ceil), 175, 150, color, F_ARIAL, 27);
		color.r = 128;
		color.g = 153;
		color.b = 84;
		draw_text(data, ">", 7, 53 + (data->flo_or_cei * 97), color, F_ARIAL, 27);
		icons(data);
	}
}










