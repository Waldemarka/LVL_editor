/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_menu.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vomelchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 12:03:17 by vomelchu          #+#    #+#             */
/*   Updated: 2018/12/24 12:03:19 by vomelchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	solid_rect(t_data *data)
{
	int x;
	int y;

	x = 494;
	while (++x != WIDTH -1)
	{
		y = 223;
		while (++y != HEIGHT - 1)
		{
			data->buf[y][x] = 0x001433;
		}
	}
}

int		draw_switch_sector(t_data *data, int i)
{
	t_sector *tmp_sect;

	tmp_sect = &data->sectors[i];	
		while (tmp_sect->next != NULL)
		{
			if (tmp_sect->next->next != NULL && tmp_sect->next != NULL)
			{
				coord_displ(data, tmp_sect->next->x0, tmp_sect->next->y0);
				data->x1 = data->x0;
				data->y1 = data->y0;
				coord_displ(data, tmp_sect->x0, tmp_sect->y0);
				bresenham_line(data);
			}
			tmp_sect = tmp_sect->next;
		}
		if (i != data->current_sector)
		{
			//if (i == data->q_texture)
			//		data->color = 0xffffff;
			coord_displ(data, data->sectors[i].x0, data->sectors[i].y0);
			bresenham_line(data);
		}
	return (1);
}

void	hepl_for_events_text(t_data *data, SDL_Event event, int tmp_time)
{

		if (event.key.keysym.sym == SDLK_1)
			data->num_text = 0;
		if (event.key.keysym.sym == SDLK_2)
			data->num_text = 1;
		if (event.key.keysym.sym == SDLK_3)
			data->num_text = 2;
		if (event.key.keysym.sym == SDLK_RIGHT && (tmp_time - 100) > data->time && data->q_texture < data->current_sector - 1)
		{
			data->time = tmp_time;
			data->q_texture++;
			if (data->sectors[data->q_texture].texture > -1)
				data->num_text = data->sectors[data->q_texture].texture;
		}
		if (event.key.keysym.sym == SDLK_LEFT && data->q_texture > 0 && (tmp_time - 100) > data->time)
		{
			data->time = tmp_time;
			data->q_texture--;
			if (data->sectors[data->q_texture].texture > -1)
				data->num_text = data->sectors[data->q_texture].texture;
		}
		if (event.key.keysym.sym == SDLK_UP && (tmp_time - 100) > data->time && data->num_text < 2)
		{
			data->time = tmp_time;
			data->num_text++;
		}
		if (event.key.keysym.sym == SDLK_DOWN && (tmp_time - 100) > data->time && data->num_text > 0)
		{
			data->time = tmp_time;
			data->num_text--;
		}
}

void	event_for_texture(t_data *data)
{
	int tmp_time;

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
	}
}

void	textures_menu(t_data *data)
{
	data->pixel_pict = 64;
	picture_icon(data, 515,  155, data->cube[0]);
	if (data->show_text == 1)
	{
		solid_rect(data);
		picture_icon(data, 515,  155, data->cube[1]);
		data->pixel_pict = 200;
		picture_icon(data, 505,  670, data->navig[0]);
		picture_icon(data, 515,  470, data->set);
		data->pixel_pict = 64;
		picture_icon(data, 485,  300, data->navig[1]);
		picture_icon(data, 665,  300, data->navig[2]);
		data->pixel_pict = 140;
		picture_icon(data, 538,  265, data->pict[data->num_text]);
		event_for_texture(data);
	}

}