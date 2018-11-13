/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_nukem.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vomelchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 14:15:45 by vomelchu          #+#    #+#             */
/*   Updated: 2018/10/20 14:19:55 by vomelchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_NUKEM_H
# define DOOM_NUKEM_H

# include <unistd.h>
# include "../source/libft/includes/libft.h"
# include "../includes/get_next_line.h"
# include <SDL.h>
# include <SDL_image.h>
# include <SDL_ttf.h>
# include <SDL_mixer.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>

#define WIDTH 608
#define HEIGHT 480

typedef struct  s_sector
{
                int x0;
                int y0;
                struct s_sector *next;
               // struct s_sector *previous; 
}               t_sector;

typedef struct  s_data
{
    SDL_Window      *win;
    SDL_Renderer    *ren;
    SDL_Texture     *screen;
    char            *name;
    int             buf[HEIGHT][WIDTH];
    int             for_exit;

    int             x0;
    int             y0;
    int             x1;
    int             y1;
    int             deltax;
    int             deltay;
    int             x_step;
    int             y_step;
    int             color;
    int             step_for_x;
    int             step_for_y;
    int             for_realloc;
    int             current_sector;
    int             check_click;

    t_sector        *sectors;
    t_sector        *tmp;
}                   t_data;

void                ft_error(char *str);
void                key_event(t_data *data);
void                bresenham_line(t_data *data);
void                mouse_line(t_data *data);
void                list_realloc(t_data *data);
void                list_malloc(t_sector **list, int size);
void                fill_next(t_data *data, int x, int y);
void                draw_lines(t_data *data);

#endif