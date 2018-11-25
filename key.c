/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vomelchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2218/11/07 16:44:45 by vomelchu          #+#    #+#             */
/*   Updated: 2218/11/18 18:32:23 by vomelchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"
# define EXIT (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)

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
			if (len_list(&data->sectors[data->current_sector]) >= 3
				&& bef_crossing(data) == 0)
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

int		check_first_cross(t_data *data, int x1, int y1)
{
	t_sector *tmp_sec;
	int i;
	int x;
	int y;

	if (data->current_sector == 0)
		return (1);
	if (data->check_click == 1)
		return (1);
	i = -1;
	coord_canvas(data, x1, y1);
	x = near_round(data->x_canv);
	y = near_round(data->y_canv);
	while (++i != data->current_sector)
	{
		tmp_sec = &data->sectors[i];
		while (tmp_sec->next != NULL)
		{
			if (x == tmp_sec->x0 && y == tmp_sec->y0)
				return (1);
			tmp_sec = tmp_sec->next;
		}
	}
	return (0);
}

void	mouse_line(t_data *data)
{
	int 		x;
	int			y;
	static int	tmp;

	SDL_PumpEvents();
	if (SDL_GetMouseState(&x, &y) & SDL_BUTTON(SDL_BUTTON_LEFT))
	{
		if (tmp == 0)
		{
			if (data->check_click == 0 &&
				check_first_cross(data, x, y) == 1)
			{
				data->x1_line = x;
				data->y1_line = y;
				fill_next(data, x, y);
			}
			else if (bef_crossing(data) == 0 &&
				check_first_cross(data, x, y) == 1)
			{
				data->x1_line = x;
				data->y1_line = y;
				fill_next(data, x, y);
			}
			tmp++;
			if (check_first_cross(data, x, y) == 1)
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
	bef_crossing(data);
	near_lines(data);
}