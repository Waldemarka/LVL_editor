/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vomelchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/19 15:55:15 by vomelchu          #+#    #+#             */
/*   Updated: 2018/08/19 15:55:17 by vomelchu         ###   ########.fr       */
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

int    init_fonts(t_data *data, char *font_path, int font_size)
{
    TTF_Init();
    MF.font_ttf = TTF_OpenFont(font_path, font_size);
    if (!MF.font_ttf)
    {
        ft_putendl(SDL_GetError());
        // prog_quit(0, main);
        return (0);
    }
    return (1);
}

int    draw_text(t_data *data, char *text, int x, int y, SDL_Color color, char *font_path, int font_size)
{
    int         tw;
    int         th;

    if (text == NULL)
        return (0);
    if (font_size < 1 || font_size > 999)
        return (0);
    if (!init_fonts(data, font_path, font_size))
        return (0);
    MF.font_surf = TTF_RenderText_Solid(MF.font_ttf, text, color);
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

/*Mix_Music		*load_music(char *path)
{
	Mix_Music *music;

	if (!(music = Mix_LoadMUS(path)))
		ft_error(4);
	return (music);
}

void			apply_surface(int x, int y, SDL_Surface *sour, SUR)
{
	SDL_Rect offset;

	offset.x = x;
	offset.y = y;
	SDL_BlitSurface(sour, NULL, destination, &offset);
}*/
