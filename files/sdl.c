/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vomelchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/19 15:55:15 by vomelchu          #+#    #+#             */
/*   Updated: 2019/01/02 13:24:14 by vomelchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define SUR SDL_Surface *destination

#include "doom_nukem.h"

SDL_Surface		*load_image(char *path)
{
	SDL_Surface	*texture;

	texture = IMG_Load(path);
	if (texture == NULL)
		ft_error("Bad load image");
	return (texture);
}

unsigned int	get_pixel_int(SDL_Surface *surface, int x, int y)
{
	unsigned int	*pixels;

	pixels = (unsigned int*)surface->pixels;
	return (pixels[(y * surface->w) + x]);
}

int				init_fonts(t_data *data, char *font_path, int font_size)
{
	TTF_Init();
	MF.font_ttf = TTF_OpenFont(font_path, font_size);
	if (!MF.font_ttf)
	{
		ft_putendl(SDL_GetError());
		return (0);
	}
	return (1);
}

int				draw_text(t_data *data, char *text, int x, int y)
{
	int tw;
	int th;

	if (text == NULL)
		return (0);
	if (data->font_size < 1 || data->font_size > 999)
		return (0);
	if (!init_fonts(data, F_AG, data->font_size))
		return (0);
	MF.font_surf = TTF_RenderText_Solid(MF.font_ttf, text, data->rgb);
	MF.font_textr = SDL_CreateTextureFromSurface(data->ren, MF.font_surf);
	SDL_QueryTexture(MF.font_textr, NULL, NULL, &tw, &th);
	MF.font_rect.x = x;
	MF.font_rect.y = y;
	MF.font_rect.w = tw;
	MF.font_rect.h = th;
	SDL_RenderCopy(data->ren, MF.font_textr, NULL, &MF.font_rect);
	SDL_DestroyTexture(MF.font_textr);
	SDL_FreeSurface(MF.font_surf);
	TTF_CloseFont(MF.font_ttf);
	return (1);
}
