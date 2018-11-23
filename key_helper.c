/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vomelchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 12:39:28 by vomelchu          #+#    #+#             */
/*   Updated: 2018/11/21 17:27:26 by vomelchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int		check_zoom(t_data *data, char c)
{
	if (c == '+')
	{
		if ((data->max_canv_x - data->start_coord_x) > 1000)
			return (1);
		if ((data->max_canv_y - data->start_coord_y) > 1000)
			return (1);
	}
	if (c == '-')
	{
		if ((data->max_canv_x - data->start_coord_x) < 100)
			return (1);
		if ((data->max_canv_y - data->start_coord_y) < 100)
			return (1);
	}
	return (0);
}

void	zoom(t_data *data, char c)
{
	int tmp[2];

	tmp[0] = data->start_coord_x;
	tmp[1] = data->start_coord_y;
	if (c == '+' && check_zoom(data, '+') == 0)
	{
		data->start_coord_x -= ((data->max_canv_x - data->start_coord_x) / 22);
		data->start_coord_y -= ((data->max_canv_y - data->start_coord_y) / 22);
		data->max_canv_x += ((data->max_canv_x - tmp[0]) / 22);
		data->max_canv_y += ((data->max_canv_y - tmp[1]) / 22);
	}
	if (c == '-' && check_zoom(data, '-') == 0)
	{
		data->start_coord_x += ((data->max_canv_x - data->start_coord_x) / 22);
		data->start_coord_y += ((data->max_canv_y - data->start_coord_y) / 22);
		data->max_canv_x -= ((data->max_canv_x - tmp[0]) / 22);
		data->max_canv_y -= ((data->max_canv_y - tmp[1]) / 22);
	}
}

void	key_helper(t_data *data, SDL_Event	event)
{
	int tmp[2];

	tmp[0] = data->start_coord_x;
	tmp[1] = data->start_coord_y;
	if (event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_p) && data->check_click == 0)
		zoom(data, '+');
	if (event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_o) && data->check_click == 0)
		zoom(data, '-');
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
	if (event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_RIGHT)
		&& data->start_coord_x < 1000 && data->check_click == 0)
	{
		data->start_coord_x += ((data->max_canv_x - data->start_coord_x) / 22);
		data->max_canv_x += ((data->max_canv_x - tmp[0]) / 22);
	}
	if (event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_LEFT)
		&& data->start_coord_x > -1000 && data->check_click == 0)
	{
		data->start_coord_x -= ((data->max_canv_x - data->start_coord_x) / 22);
		data->max_canv_x -= ((data->max_canv_x - tmp[0]) / 22);
	}
}

