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

/*int		*numer(t_data *data)
  {
  if 
  return ();
  }*/

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
/*	if (event.key.keysym.sym == SDLK_BACKSPACE)
	{
		space_imitation(data, 2);
	}*/
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

	SDL_PumpEvents();
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
		if (*num > 99999999)
			*num = 99999999;
		/*if (data->flo_or_cei == 0 &&
			*num > data->ceil - 5)
			*num = data->ceil - 5;
		if (data->flo_or_cei == 1 &&
			*num < data->floor + 5)
			*num = data->ceil + 5;*/
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
			data->buf[q][i] = get_pixel_int(&data->dot[data->picture_menu % 3], i, q);
		}
	}
}

void	menu(t_data *data)
{
	SDL_Color       color;
	color.r = 255;
	color.g = 255;
	color.b = 255;

	picture(data);
	event_menu(data);
	if (data->picture_menu % 3 != 2)
	{
		draw_text(data, ft_itoa(data->floor), 175, 53, color, F_ARIAL, 27);
		draw_text(data, ft_itoa(data->ceil), 175, 150, color, F_ARIAL, 27);
		color.r = 128;
		color.g = 153;
		color.b = 84;
		draw_text(data, ">", 7, 53 + (data->flo_or_cei * 97), color, F_ARIAL, 27);
	}
}










