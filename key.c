/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vomelchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 16:44:45 by vomelchu          #+#    #+#             */
/*   Updated: 2018/11/18 18:32:23 by vomelchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"
# define EXIT (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)

typedef	struct s_point
{
	double X;
	double Y;
}				point;

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
		{
			data->for_exit = 1;
			writting(data);
		}
		if (EXIT)
		{
			data->for_exit = 1;
			writting(data);
			//system("leaks doom");
		}
		if (event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_w))
		{
			/*coord_displ(data, data->sectors[data->current_sector].x0, data->sectors[data->current_sector].y0);
			fill_next(data, data->x0, data->y0);*/
			if (len_list(&data->sectors[data->current_sector]) >= 3)
			{
				data->current_sector++;
				data->for_realloc++;
				list_realloc(data);
				data->check_click = 0;
				data->sectors[data->current_sector].next = NULL;
			}
		}
		key_helper(data, event);
	}
}

int		near_round(int q)
{
	int i;

	i = q % 10;
	if (i < 5)
		return (q - i);
	else
		return((q - i) + 10);
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
			if (data->check_click == 0)
			{
				data->x1_line = x;
				data->y1_line = y;
				fill_next(data, x, y);
			}
			else if (bef_crossing(data) == 0)
			{
				data->x1_line = x;
				data->y1_line = y;
				fill_next(data, x, y);
			}
			tmp++;
			data->check_click = 1;
		}
	}
	else
	{
		if (tmp > 0)
			tmp = 0;
		data->x0_line = x;
		data->y0_line = y;
	}
	/*printf("0 :%d %d\n", data->x0_line, data->y0_line);
	printf("1 :%d %d\n", data->x1_line, data->y1_line);*/
	bef_crossing(data);
	near_lines(data);
}