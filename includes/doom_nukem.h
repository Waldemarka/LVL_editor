/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_nukem.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vomelchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 14:15:45 by vomelchu          #+#    #+#             */
/*   Updated: 2018/12/04 15:51:53 by vomelchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_NUKEM_H
# define DOOM_NUKEM_H

# include <unistd.h>
# include "../source/libft/includes/libft.h"
# include <SDL.h>
# include <SDL_image.h>
# include <SDL_ttf.h>
# include <SDL_mixer.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>

#define WIDTH 720
#define HEIGHT 870
#define EXIT (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
#define F_ARIAL 	"fonts/ARIAL.TTF"
#define F_MORPHEUS 	"fonts/MORPHEUS.TTF"
# define MF 	data->fonts


typedef struct 	s_font_data
{
	SDL_Surface 	*font_surf;
	SDL_Texture 	*font_textr;
	TTF_Font		*font_ttf;
	SDL_Rect 		font_rect;
}				t_font_data;

typedef struct  s_vector
{
	double x;
	double y;
}               vector;

typedef struct s_vertex
{
	int     x_vert;
    int     y_vert;
	struct  s_vertex *next;
}               vertex;

typedef struct s_icons
{
	int		x;
	int		y;
	int		obj;
	int		sector;
	int		flag;
}			t_icons;

typedef struct  s_sector
{
	int x0;
	int y0;
	int floor;
	int ceil;
	struct s_sector *next;
}               t_sector;

typedef struct  s_data
{
	SDL_Window      *win;
	SDL_Renderer    *ren;
	SDL_Texture     *screen;
	SDL_Surface     *dot[3];
	SDL_Surface		*icon[10];
	SDL_Surface		*icon64[10];
	char            *name;
	int             buf[HEIGHT][WIDTH];
	int             for_exit;
	int             fd;
	int             x0;
	int             y0;
	int             x1;
	int             y1;
	int             x0_line;
	int             y0_line;
	int             x1_line;
	int             y1_line;
	int             deltax;
	int             deltay;
	int             x_step;
	int             y_step;
	int             color;
	int             step_for_x;
	int             step_for_y;
	int             current_sector;
	int             check_click;
	int             max_canv_x;
	int             max_canv_y;
	int             start_coord_x;
	int             start_coord_y;
	float           x_canv;
	float           y_canv;
	int             iter;
	int             tmp_count;

	int				check_menu;
	int				picture_menu;
	int				floor;
	int				ceil;
	int				flo_or_cei;

	int				pixel_pict;
	int 			num_icon;
	int				num_sector;
	int				object;
	int				min_coord_icon;

	t_sector        sectors[100];
	t_icons			icons[150];			
	t_sector        *tmp;
	t_font_data 	fonts;
	vertex          vertex;
	vector          p1;
	vector          p2;
	vector          p3;
	vector          p4;
	vector			vect[4];
}                   t_data;

void                ft_error(char *str);
void                key_event(t_data *data);
void                key_helper(t_data *data, SDL_Event  event);
void                bresenham_line(t_data *data);
void                mouse_line(t_data *data);
void                list_realloc(t_data *data);
void                list_malloc(t_sector **list, int size);
void                fill_next(t_data *data, int x, int y);
void                draw_lines(t_data *data);
void                draw_grid(t_data *data);
void                dots_to_bres(t_data *data);
void                coord_canvas(t_data *data, int x, int y);
void                coord_displ(t_data *data, int x, int y);
void                limit_coord(t_data *data, int x, int y);
void                writting(t_data *data);
int                 near_round(int q);
void                near_lines(t_data *data);
int                 bef_crossing(t_data *data, int check);
int                 len_list(t_sector *sectors);
int                 normal_vec(t_data *data);
int					IntersectionOfTwoLine(t_data *data);
int                 first_vert(t_data *data);
int                 second_vert(t_data *data);
void                space_imitation(t_data *data);
int                 touch_dots(t_data *data);
SDL_Surface         *load_image(char *path);
unsigned int        get_pixel_int(SDL_Surface *surface, int x, int y);
int                 find_wall(t_data *data, vector dot_1, vector dot_2, int check);
void                mouse_help(t_data *data, int x, int y);
void                change_position(t_data *data);
int                 is_in_sectror(t_data *data, int x1, int y1);
int                 check_first_cross(t_data *data, int x1, int y1);
double              min(double x, double y);
double              max(double x, double y);
int                 init_vector(t_data *data);
void                ft_swap(int *a, int *b);
int    				draw_text(t_data *data, char *text, int x, int y, SDL_Color color, char *font_path, int font_size);

void				writte_walls(t_data *data, FILE *fp, int q);
int					find_wall(t_data *data, vector dot_1, vector dot_2, int check);
void				make_vertex_list(t_data *data);
int 				num_ele(t_data *data, int x, int y);
void				menu(t_data *data, int i);

void				del_list(t_data *data, int q, int i);
int					modif_obj(t_data *data, int x);
int					check_in_sector(t_data *data, int x, int y);
void				special_icons(t_data *data);
void				writte_icons_to_struct(t_data *data, int q);
void				event_menu(t_data *data);
void				help_mouse_icons(t_data *data);
void				sort_dots(t_data *data);
int					clockwise(t_data *data);

#endif
