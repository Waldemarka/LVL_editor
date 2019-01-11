/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vomelchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 14:54:54 by vomelchu          #+#    #+#             */
/*   Updated: 2019/01/06 11:37:02 by vomelchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	return_imitation(t_data *data)
{
	if (data->picture_menu % 4 == 2)
	{
		data->for_exit = 1;
		writting(data);
	}
	if (data->picture_menu % 4 == 3)
	{
		data->show_text = 1;
	}
}

void	next_sect(t_data *data)
{
	data->check_menu = 0;
	data->sectors[data->current_sector].floor = data->floor;
	data->sectors[data->current_sector].ceil = data->ceil;
}

void	numer_helper(SDL_Event event, int *num, t_data *data, int q)
{
	if (event.key.keysym.sym == SDLK_BACKSPACE)
		*num = *num / 10;
	if (q == 0)
	{
		if (event.key.keysym.sym == SDLK_LEFT)
		{
			data->picture_menu = 0;
			data->flo_or_cei = 0;
		}
		if (event.key.keysym.sym == SDLK_RIGHT)
		{
			data->picture_menu = 1;
			data->flo_or_cei = 1;
		}
		if (event.key.keysym.sym == SDLK_UP)
			data->picture_menu = 2;
		if (event.key.keysym.sym == SDLK_DOWN)
			data->picture_menu = 3;
		if (event.key.keysym.sym == SDLK_RETURN)
			return_imitation(data);
	}
}

void	numer(SDL_Event event, int *num)
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
}

void	event_menu(t_data *data)
{
	SDL_Event	event;
	int			*num;

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
		if (event.type == SDL_KEYDOWN)
		{
			numer(event, num);
			numer_helper(event, num, data, 0);
		}
		if (*num > 99)
			*num = 99;
	}
}
