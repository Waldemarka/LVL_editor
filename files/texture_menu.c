/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_menu.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vomelchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 12:03:17 by vomelchu          #+#    #+#             */
/*   Updated: 2019/01/02 13:24:36 by vomelchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	other_help(t_data *data, SDL_Event event, int tmp_time)
{
	if (event.key.keysym.sym == SDLK_UP && (tmp_time - 100) > data->time
			&& data->num_text < 6)
	{
		data->time = tmp_time;
		data->num_text++;
	}
	if (event.key.keysym.sym == SDLK_DOWN && (tmp_time - 100) > data->time
			&& data->num_text > 0)
	{
		data->time = tmp_time;
		data->num_text--;
	}
}

void	hepl_for_events_text(t_data *data, SDL_Event event, int tmp_time)
{
	if (event.key.keysym.sym == SDLK_1)
		data->num_text = 0;
	if (event.key.keysym.sym == SDLK_2)
		data->num_text = 1;
	if (event.key.keysym.sym == SDLK_3)
		data->num_text = 2;
	if (event.key.keysym.sym == SDLK_RIGHT && (tmp_time - 100) > data->time
			&& data->q_texture < data->current_sector - 1)
	{
		data->time = tmp_time;
		data->q_texture++;
		if (data->sectors[data->q_texture].texture > -1)
			data->num_text = data->sectors[data->q_texture].texture;
	}
	if (event.key.keysym.sym == SDLK_LEFT && data->q_texture > 0 &&
			(tmp_time - 100) > data->time)
	{
		data->time = tmp_time;
		data->q_texture--;
		if (data->sectors[data->q_texture].texture > -1)
			data->num_text = data->sectors[data->q_texture].texture;
	}
}

void	event_for_texture(t_data *data)
{
	int			tmp_time;
	SDL_Event	event;

	SDL_PumpEvents();
	tmp_time = SDL_GetTicks();
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			data->for_exit = 1;
		if (EXIT)
		{
			data->show_text = 0;
			data->q_texture = -1;
		}
		if (event.key.keysym.sym == SDLK_RETURN && data->q_texture != -1)
			data->sectors[data->q_texture].texture = data->num_text;
		hepl_for_events_text(data, event, tmp_time);
		other_help(data, event, tmp_time);
	}
}

void	info_about_texture(t_data *data)
{
	char *str;

	data->font_size = 27;
	draw_text(data, "FLOOR : ", 520, 525);
	draw_text(data, "CEIL : ", 520, 555);
	draw_text(data, "SECTOR : ", 520, 585);
	str = ft_itoa(data->sectors[data->q_texture].floor);
	draw_text(data, str, 650, 525);
	free(str);
	str = ft_itoa(data->sectors[data->q_texture].ceil);
	draw_text(data, str, 650, 555);
	free(str);
	str = ft_itoa(data->q_texture);
	draw_text(data, str, 650, 585);
	free(str);
}

void	textures_menu(t_data *data)
{
	if (data->show_text == 1)
	{
		solid_rect(data);
		data->pixel_pict = 200;
		picture_icon(data, 505, 670, data->navig[0]);
		data->pixel_pict = 64;
		picture_icon(data, 492, 335, data->navig[1]);
		picture_icon(data, 660, 335, data->navig[2]);
		data->pixel_pict = 140;
		picture_icon(data, 538, 290, data->pict[data->num_text]);
		if (data->q_texture != -1)
			info_about_texture(data);
		event_for_texture(data);
	}
}
