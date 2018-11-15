/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vomelchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 16:44:45 by vomelchu          #+#    #+#             */
/*   Updated: 2018/11/07 16:44:48 by vomelchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"
# define EXIT (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)

void	key_helper(t_data *data, SDL_Event	event)
{
		if (event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_p))
		{
			data->max_canv_x += 7;
			data->max_canv_y += 7;
		}		
		if (event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_o))
		{
			data->max_canv_x -= 7;
			data->max_canv_y -= 7;
		}
		if (event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_UP))
		{
			data->start_coord_y = data->start_coord_y - 7;
			data->max_canv_y = data->max_canv_y - 7;
		}
		if (event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_DOWN))
		{
			data->start_coord_y = data->start_coord_y + 7;
			data->max_canv_y = data->max_canv_y + 7;
		}
		if (event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_RIGHT))
		{
			data->start_coord_x = data->start_coord_x + 7;
			data->max_canv_x = data->max_canv_x + 7;
		}
		if (event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_LEFT))
		{
			data->start_coord_x = data->start_coord_x - 7;
			data->max_canv_x = data->max_canv_x - 7;
		}
}

void	key_event(t_data *data)
{
	SDL_Event	event;
	//const Uint8 *keys = SDL_GetKeyboardState(NULL);

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			data->for_exit = 1;
		if (EXIT)
			data->for_exit = 1;
		if (event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_w))
		{
			data->current_sector++;
			data->for_realloc++;
			list_realloc(data);
			data->check_click = 0;
			data->sectors[data->current_sector].next = NULL;
		}
		key_helper(data, event);
	}
}

void	dots_to_bres(t_data *data)
{
	data->color = 0x15eb43;
	data->x0 = data->x0_line;
	data->y0 = data->y0_line;
	data->x1 = data->x1_line;
	data->y1 = data->y1_line;	
}

int		for_round(int q)
{
	int r;

	r = q % 10;
	if (r < 5)
		return (q - r);
	else
		return ((q - r) + 10);
	return (q);
}

void	mouse_line(t_data *data)
{
	int 		x;
	int			y;
	static int	tmp;

	SDL_PumpEvents();
	if (SDL_GetMouseState(&x, &y) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
		if (tmp == 0)
		{
			data->x0_line = data->x1_line;
			data->y0_line = data->y1_line;
			data->x1_line = x;
			data->y1_line = y;
			fill_next(data, x, y);
		}
		tmp++;
		data->check_click = 1;
	}
	else
	{
		if (tmp > 0)
		{
			tmp = 0;
		}
		data->x0_line = x;
		data->y0_line = y;
	}
	dots_to_bres(data);
}


