/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vomelchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 12:39:28 by vomelchu          #+#    #+#             */
/*   Updated: 2019/01/02 13:22:14 by vomelchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

#define ST_X data->start_coord_x

int		check_zoom(t_data *data, char c)
{
	if (c == '+')
	{
		if ((data->max_canv_x - ST_X) > 1000)
			return (1);
		if ((data->max_canv_y - data->start_coord_y) > 1000)
			return (1);
	}
	if (c == '-')
	{
		if ((data->max_canv_x - ST_X) < 100)
			return (1);
		if ((data->max_canv_y - data->start_coord_y) < 100)
			return (1);
	}
	return (0);
}

void	zoom(t_data *data, char c)
{
	int tmp[2];

	tmp[0] = ST_X;
	tmp[1] = data->start_coord_y;
	if (c == '+' && check_zoom(data, '+') == 0)
	{
		ST_X -= ((data->max_canv_x - ST_X) / 22);
		data->start_coord_y -= ((data->max_canv_y - data->start_coord_y) / 22);
		data->max_canv_x += ((data->max_canv_x - tmp[0]) / 22);
		data->max_canv_y += ((data->max_canv_y - tmp[1]) / 22);
	}
	if (c == '-' && check_zoom(data, '-') == 0)
	{
		ST_X += ((data->max_canv_x - ST_X) / 22);
		data->start_coord_y += ((data->max_canv_y - data->start_coord_y) / 22);
		data->max_canv_x -= ((data->max_canv_x - tmp[0]) / 22);
		data->max_canv_y -= ((data->max_canv_y - tmp[1]) / 22);
	}
}

void	left_right(t_data *data, SDL_Event event, int tmp[2])
{
	if (event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_RIGHT)
			&& ST_X < 1000 && data->check_click == 0)
	{
		ST_X += ((data->max_canv_x - ST_X) / 22);
		data->max_canv_x += ((data->max_canv_x - tmp[0]) / 22);
	}
	if (event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_LEFT)
			&& ST_X > -1000 && data->check_click == 0)
	{
		ST_X -= ((data->max_canv_x - ST_X) / 22);
		data->max_canv_x -= ((data->max_canv_x - tmp[0]) / 22);
	}
}

void	key_helper_2(t_data *data, SDL_Event event, int tmp[2])
{
	if (event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_UP)
			&& data->start_coord_y > -1000 && data->check_click == 0)
	{
		data->start_coord_y -= ((data->max_canv_y - data->start_coord_y) / 22);
		data->max_canv_y -= ((data->max_canv_y - tmp[1]) / 22);
	}
	if (event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_DOWN)
			&& data->start_coord_y < 1000 && data->check_click == 0)
	{
		data->start_coord_y += ((data->max_canv_y - data->start_coord_y) / 22);
		data->max_canv_y += ((data->max_canv_y - tmp[1]) / 22);
	}
	if (event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_BACKSPACE)
			&& (data->current_sector > 0 ||
				(data->current_sector == 0 && data->sectors[0].next != NULL)))
		backspace_imitation(data);
	left_right(data, event, tmp);
}

void	key_helper(t_data *data, SDL_Event event)
{
	int tmp[2];

	tmp[0] = ST_X;
	tmp[1] = data->start_coord_y;
	if (event.type == SDL_MOUSEWHEEL)
	{
		if (event.wheel.y > 0 && data->check_click == 0)
			zoom(data, '+');
		else if (event.wheel.y < 0 && data->check_click == 0)
			zoom(data, '-');
		if (event.wheel.x > 0 && ST_X < 1000 && data->check_click == 0)
		{
			ST_X += ((data->max_canv_x -
						ST_X) / 22);
			data->max_canv_x += ((data->max_canv_x - tmp[0]) / 22);
		}
		else if (event.wheel.x < 0 && ST_X > -1000
				&& data->check_click == 0)
		{
			ST_X -= ((data->max_canv_x - ST_X) / 22);
			data->max_canv_x -= ((data->max_canv_x - tmp[0]) / 22);
		}
	}
	key_helper_2(data, event, tmp);
}
