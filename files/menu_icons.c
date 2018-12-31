/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_icons.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vomelchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 14:53:19 by vomelchu          #+#    #+#             */
/*   Updated: 2018/12/17 14:53:20 by vomelchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int		init_obj(t_data *data, int x, int y)
{
	if (data->sectors[0].next == NULL)
		return(1);
	coord_canvas(data, x, y);
	data->p3.x = (double)near_round(data->x_canv);
	data->p3.y = (double)near_round(data->y_canv);
	coord_canvas(data, 50000, 50000);
	data->p4.x = (double)near_round(data->x_canv);
	data->p4.y = (double)near_round(data->y_canv);
	return (0);
}

int		no_more_5(t_data *data)
{
	int q;
	int count;

	q = -1;
	count = 0; 
	while (++q != data->object)
	{
		if (data->icons[q].flag == 0)
			continue;
		if (data->icons[q].sector == data->num_sector)
			count++;
		if (count > 4)
			return (1);
	}
	return (0);
}

int 	help_check(t_data *data, t_sector *sector, int obj)
{
	while (sector->next != NULL && sector->next->next != NULL)
	{
		data->p1.x = (double)sector->x0;
		data->p1.y = (double)sector->y0;
		data->p2.x = (double)sector->next->x0;
		data->p2.y = (double)sector->next->y0;
		if (IntersectionOfTwoLine(data) == 1)
			obj++;
		sector = sector->next;
	}
	data->p1.x = (double)sector->x0;
	data->p1.y = (double)sector->y0;
	data->p2.x = (double)data->sectors[data->iter].x0;
	data->p2.y = (double)data->sectors[data->iter].y0;
	if (IntersectionOfTwoLine(data) == 1)
		obj++;
	if (obj == 1)
	{
		data->num_sector = data->iter;
		if (no_more_5(data) == 0)
			return (0);
	}
	return (1);
}

int		check_in_sector(t_data *data, int x, int y)
{
	int obj;
	t_sector *sector;

	if (init_obj(data, x, y) == 1)
		return (1);
	data->iter = -1;
	while (++data->iter != data->current_sector)
	{
		sector = &data->sectors[data->iter];
		obj = 0;
		if (help_check(data, sector, obj) == 0)
			return (0);
	}
	return (1);
}


void	multi_key(t_data *data)
{
	SDL_Event	event;
	static int tmp;

	data->pixel_pict = 64;
	picture_icon(data, data->tmp_x, data->tmp_y, data->icon64[9 + tmp]);
	while (SDL_PollEvent(&event))
	{
		if (event.key.keysym.sym == SDLK_RETURN)
		{
			data->icons[data->object - 1].obj = 9 + tmp;
			data->key = 0;
		}
		if (event.key.keysym.sym == SDLK_1)
			tmp = 0;
		if (event.key.keysym.sym == SDLK_2)
			tmp = 1;
		if (event.key.keysym.sym == SDLK_3)
			tmp = 2;
	}
}

void	lift(t_data *data)
{
	static int lift_up;
	SDL_Event	event;
	char *str;

	data->pixel_pict = 300;
	picture_icon(data, 194 - (100 * data->show_text),  300, data->lift_info);
	SDL_PumpEvents();
	while (SDL_PollEvent(&event))
	{
		if (event.key.keysym.sym == SDLK_RETURN)
		{
			data->lift = 0;
			data->sectors[data->icons[data->tmp_obj].sector].ceil += lift_up;
			lift_up = 0;
		}
		if (event.type == SDL_KEYDOWN)
		{
			numer(event, &lift_up);
			numer_helper(event, &lift_up, data, 1);
			if (lift_up > 100)
				lift_up = 100;
		}
	}
	draw_text(data, "How to lift up ?", 215 - (100 * data->show_text), 300, data->rgb, F_ARIAL, 40);
	str = ft_itoa(lift_up);
	draw_text(data, str, 345 - (ft_strlen(str) * 20) - (100 * data->show_text), 520, data->rgb, F_ARIAL, 80);
	free(str);
}

