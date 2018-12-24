/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_nukem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vomelchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 14:13:01 by vomelchu          #+#    #+#             */
/*   Updated: 2018/11/26 18:02:27 by vomelchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void    ft_error(char *str)
{
	ft_putstr(str);
	exit(0);
}

void    init_all(t_data *data)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		ft_error("BAD INIT SDL2\n");
	if (!(data->win = SDL_CreateWindow("Doom_nukem", 400, 400, WIDTH,
					HEIGHT, SDL_WINDOW_SHOWN)))
		ft_error("BAD INIT SDL2\n");
	if (!(data->ren = SDL_CreateRenderer(data->win, -1, SDL_RENDERER_ACCELERATED
					| SDL_RENDERER_PRESENTVSYNC)))
		ft_error("BAD INIT SDL2\n");
	if (!(data->screen = SDL_CreateTexture(data->ren,
					SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, WIDTH, HEIGHT)))
		ft_error("BAD INIT SDL2\n");
	data->current_sector = 0;
	data->sectors[0].next = NULL;
	data->check_click = 0;
	data->max_canv_x = 360;
	data->max_canv_y = 360;
	data->start_coord_x = 0;
	data->start_coord_y = 0;
	data->check_menu = 1;
	data->floor = 0;
	data->ceil = 20;
	data->flo_or_cei = 0;
	data->dot[0] = load_image("./media/menu_0.jpg");
	data->dot[1] = load_image("./media/menu_1.jpg");
	data->dot[2] = load_image("./media/menu_2.jpeg");
	data->icon[0] = load_image("./media/32/3.png");
	data->icon[1] = load_image("./media/32/3_bl.png");
	data->icon[2] = load_image("./media/32/door.png");
	data->icon[3] = load_image("./media/32/2.png");
	data->icon[4] = load_image("./media/32/lift.png");
	data->icon[5] = load_image("./media/32/5.png");
	data->icon[6] = load_image("./media/32/8.png");
	data->icon[7] = load_image("./media/32/7.png");
	data->icon64[0] = load_image("./media/64/3.png");
	data->icon64[1] = load_image("./media/64/3_bl.png");
	data->icon64[2] = load_image("./media/64/door.png");
	data->icon64[3] = load_image("./media/64/2.png");
	data->icon64[4] = load_image("./media/64/lift.png");
	data->icon64[5] = load_image("./media/64/5.png");
	data->icon64[6] = load_image("./media/64/8.png");
	data->icon64[7] = load_image("./media/64/7.png");
	data->cube[0] = load_image("./media/cube.png");
	data->cube[1] = load_image("./media/cube1.png");
	data->navig[0] = load_image("./media/navigat.png");
	data->navig[1] = load_image("./media/left.png");
	data->navig[2] = load_image("./media/right.png");
	data->set = load_image("./media/set.png");
	data->pict[0] = load_image("./media/brick_1.png");
	data->pict[1] = load_image("./media/Brick_Big_White.png");
	data->pict[2] = load_image("./media/iron_diffuse.png");
	data->lift_info = load_image("./media/lift_info.png");

	data->num_text = 0;
	data->picture_menu = 0;
	data->num_icon = -1;
	data->object = 0;
	data->min_coord_icon = 0;
	data->q_texture = -1;
}

void	draw_back(t_data *data)
{
	int i = -1;
		while (++i != HEIGHT)
		{
			int x = -1;
			while(++x != WIDTH)
			{
				data->buf[i][x] = 0;
			}
		}

	i = 223;
	while (++i != HEIGHT)
	{
		int x = -1;
		while(++x != WIDTH)
		{
			if (data->buf[i][x] == 0)
				data->buf[i][x] = 0x3c3c3c;
		}
	}
}

void	game_render(t_data *data)
{
		int i = -1;
		while (++i != HEIGHT)
		{
			int x = -1;
			while(++x != WIDTH)
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
		//system("leaks lvl_editor");
}

void    game(t_data *data)
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

int     main(int argc, char **argv)
{
	t_data *data;

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
		int q = -1;
		//writting(data);
		while(++q != 3)
			SDL_FreeSurface(data->dot[q]);
		q = -1;

	}
	else
		ft_error("BAD NUM ARGC\n");
	return (0);
}
