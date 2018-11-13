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

void	key_event(t_data *data)
{
	SDL_Event	event;
	//const Uint8 *keys = SDL_GetKeyboardState(NULL);

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			data->for_exit = 1;
		if (EXIT)
		{
			//system("leaks doom_nukem");
			data->for_exit = 1;
		}
		if (event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_w))
		{
			data->current_sector++;
			data->for_realloc++;
			list_realloc(data);
			data->check_click = 0;
			data->sectors[data->current_sector].next = NULL;
		}
}
}
void	mouse_line(t_data *data)
{
	int x;
	int y;
	static int tmp;

	SDL_PumpEvents();
	if (SDL_GetMouseState(&x, &y) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
		if (tmp == 0)
		{
			data->x0 = data->x1;
			data->y0 = data->y1;
			data->x1 = x;
			data->y1 = y;
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
		data->x0 = x;
		data->y0 = y;
	}
	printf("--------\n");
	printf(" x0 : %d\n y0 : %d \n x1 : %d \n x1 : %d\n", data->x0, data->y0, data->x1, data->y1);


}


