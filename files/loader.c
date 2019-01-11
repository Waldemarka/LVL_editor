/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vomelchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 12:59:43 by vomelchu          #+#    #+#             */
/*   Updated: 2019/01/02 13:22:28 by vomelchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	init_sdl(t_data *data)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		ft_error("BAD INIT SDL2\n");
	if (!(data->win = SDL_CreateWindow("Doom_nukem", 400, 400, WIDTH,
					HEIGHT, SDL_WINDOW_SHOWN)))
		ft_error("BAD INIT SDL2\n");
	if (!(data->ren = SDL_CreateRenderer(data->win, -1,
					SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)))
		ft_error("BAD INIT SDL2\n");
	if (!(data->screen = SDL_CreateTexture(data->ren,
		SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, WIDTH, HEIGHT)))
		ft_error("BAD INIT SDL2\n");
}

void	init_variable(t_data *data)
{
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
	data->num_text = 0;
	data->picture_menu = 0;
	data->num_icon = -1;
	data->object = 0;
	data->min_coord_icon = 0;
	data->q_texture = -1;
	data->rgb.r = 255;
	data->rgb.g = 255;
	data->rgb.b = 255;
}

void	load_surf(t_data *data)
{
	data->icon[0] = load_image("./media/32/3.png");
	data->icon[1] = load_image("./media/32/3_bl.png");
	data->icon[2] = load_image("./media/32/door.png");
	data->icon[3] = load_image("./media/32/2.png");
	data->icon[4] = load_image("./media/32/lift.png");
	data->icon[5] = load_image("./media/32/5.png");
	data->icon[6] = load_image("./media/32/enemy.png");
	data->icon[7] = load_image("./media/32/7.png");
	data->icon[8] = load_image("./media/32/key.png");
	data->icon[9] = load_image("./media/32/green.png");
	data->icon[10] = load_image("./media/32/red.png");
	data->icon[11] = load_image("./media/32/yellow.png");
	data->icon64[0] = load_image("./media/64/3.png");
	data->icon64[1] = load_image("./media/64/3_bl.png");
	data->icon64[2] = load_image("./media/64/door.png");
	data->icon64[3] = load_image("./media/64/2.png");
	data->icon64[4] = load_image("./media/64/lift.png");
	data->icon64[5] = load_image("./media/64/5.png");
	data->icon64[6] = load_image("./media/64/enemy.png");
	data->icon64[7] = load_image("./media/64/7.png");
	data->icon64[8] = load_image("./media/64/key.png");
	data->icon64[9] = load_image("./media/64/green.png");
	data->icon64[10] = load_image("./media/64/red.png");
	data->icon64[11] = load_image("./media/64/yellow.png");
}

void	load_surf_1(t_data *data)
{
	data->dot[0] = load_image("./media/for_menu/menu_0.png");
	data->dot[1] = load_image("./media/for_menu/menu_1.png");
	data->dot[2] = load_image("./media/for_menu/menu_2.png");
	data->dot[3] = load_image("./media/for_menu/menu_3.png");
	data->navig[0] = load_image("./media/for_menu/navigat.png");
	data->navig[1] = load_image("./media/for_menu/left.png");
	data->navig[2] = load_image("./media/for_menu/right.png");
	data->pict[0] = load_image("./media/for_menu/Brick_Big_White.png");
	data->pict[1] = load_image("./media/for_menu/iron_diffuse.png");
	data->pict[2] = load_image("./media/for_menu/brick_1.png");
	data->pict[3] = load_image("./media/for_menu/Door_1.png");
	data->pict[4] = load_image("./media/for_menu/Window_compressed.png");
	data->pict[5] = load_image("./media/for_menu/red_hex.png");
	data->pict[6] = load_image("./media/for_menu/gren_hex.png");
	data->text_menu = load_image("./media/for_menu/text_menu.png");
}

void	init_all(t_data *data)
{
	init_sdl(data);
	init_variable(data);
	load_surf(data);
	load_surf_1(data);
}
