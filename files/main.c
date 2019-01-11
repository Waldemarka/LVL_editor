/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_nukem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vomelchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 14:13:01 by vomelchu          #+#    #+#             */
/*   Updated: 2019/01/02 13:22:36 by vomelchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	draw_back(t_data *data)
{
	int x;
	int i;

	i = -1;
	while (++i != HEIGHT)
	{
		x = -1;
		while (++x != WIDTH)
		{
			data->buf[i][x] = 0;
		}
	}
	i = 223;
	while (++i != HEIGHT)
	{
		x = -1;
		while (++x != WIDTH)
		{
			if (data->buf[i][x] == 0)
				data->buf[i][x] = 0x3c3c3c;
		}
	}
}

void	game_render(t_data *data)
{
	int x;
	int i;

	i = -1;
	while (++i != HEIGHT)
	{
		x = -1;
		while (++x != WIDTH)
		{
			data->buf[i][x] = 0;
		}
	}
	key_event(data);
	draw_grid(data);
	data->color = 0x15eb43;
	mouse_line(data);
	if (data->check_click != 0)
	{
		bresenham_line(data);
		draw_lines(data);
	}
	else
		draw_lines(data);
}

void	game(t_data *data)
{
	while (data->for_exit != 1)
	{
		SDL_UpdateTexture(data->screen, NULL, data->buf, WIDTH << 2);
		SDL_RenderCopy(data->ren, data->screen, NULL, NULL);
		draw_back(data);
		if (data->check_menu == 1)
		{
			draw_grid(data);
			draw_lines(data);
			menu(data, 0);
		}
		else
		{
			game_render(data);
			menu(data, 1);
		}
		SDL_RenderPresent(data->ren);
	}
}

int		main(int argc, char **argv)
{
	t_data	*data;

	if (argc == 2)
	{
		if (!(data = (t_data *)malloc(sizeof(t_data))))
			ft_error("BAD MALLOC FOR STRUCT\n");
		data->name = argv[1];
		data->fd = open(data->name, O_DIRECTORY);
		if (data->fd >= 0)
			ft_error("NOT DIRECTORY\n");
		data->sectors[0].next = NULL;
		init_all(data);
		draw_grid(data);
		game(data);
	}
	else
		ft_error("BAD NUM ARGC\n");
	system("leaks lvl_editor");
	return (0);
}
