/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_nukem.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vomelchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 14:15:45 by vomelchu          #+#    #+#             */
/*   Updated: 2019/01/03 13:21:44 by vomelchu         ###   ########.fr       */
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
# include <math.h>
# define WIDTH 720
# define HEIGHT 870
# define EXIT (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
# define F_ARIAL 	"fonts/ARIAL.TTF"
# define F_MOR 	"fonts/MORPHEUS.TTF"
# define MF 	data->fonts
# define F_ICE  "fonts/LadyIceRevisited.ttf"
# define F_AG  "fonts/OpenSans-Semibold.ttf"
# define VEC t_vector
# define SRF SDL_Surface
# define EVE SDL_Event
# define DT2X (int)dot_2.x == sector->next->x0
# define DT2Y (int)dot_2.y == sector->y0
# define DT1X (int)dot_1.x == sector->next->x0
# define DTX (int)dot_1.x == sector->x0
# define DTY (int)dot_2.x == data->sectors[q].x0
# define DT (int)dot_1.x == data->sectors[q].x0

typedef struct		s_font_data
{
	SDL_Surface		*font_surf;
	SDL_Texture		*font_textr;
	TTF_Font		*font_ttf;
	SDL_Rect		font_rect;
}					t_font_data;

typedef struct		s_vector
{
	double			x;
	double			y;
}					t_vector;

typedef struct		s_vertex
{
	int				x_vert;
	int				y_vert;
	struct s_vertex	*next;
}					t_vertex;

typedef struct		s_icons
{
	int				x;
	int				y;
	int				obj;
	int				sector;
	int				flag;
}					t_icons;

typedef struct		s_sector
{
	int				x0;
	int				y0;
	int				floor;
	int				ceil;
	int				texture;
	struct s_sector	*next;
}					t_sector;

typedef struct		s_data
{
	SDL_Window		*win;
	SDL_Renderer	*ren;
	SDL_Texture		*screen;
	SDL_Surface		*navig[3];
	SDL_Surface		*pict[7];
	SDL_Surface		*dot[4];
	SDL_Surface		*icon[12];
	SDL_Surface		*icon64[12];
	SDL_Surface		*text_menu;
	char			*name;
	int				buf[HEIGHT][WIDTH];
	int				for_exit;
	int				fd;
	int				x0;
	int				y0;
	int				x1;
	int				y1;
	int				x0_line;
	int				y0_line;
	int				x1_line;
	int				y1_line;
	int				deltax;
	int				deltay;
	int				x_step;
	int				y_step;
	int				color;
	int				step_for_x;
	int				step_for_y;
	int				current_sector;
	int				check_click;
	int				max_canv_x;
	int				max_canv_y;
	int				start_coord_x;
	int				start_coord_y;
	float			x_canv;
	float			y_canv;
	int				iter;
	int				tmp_count;
	int				check_menu;
	int				picture_menu;
	int				floor;
	int				ceil;
	int				flo_or_cei;
	int				tmp_x;
	int				tmp_y;
	int				pixel_pict;
	int				num_icon;
	int				num_sector;
	int				object;
	int				min_coord_icon;
	int				show_text;
	int				num_text;
	int				q_texture;
	int				time;
	int				key;
	int				font_size;
	t_sector		sectors[100];
	t_icons			icons[150];
	t_sector		*tmp;
	t_font_data		fonts;
	t_vertex		vertex;
	t_vector		p1;
	t_vector		p2;
	t_vector		p3;
	t_vector		p4;
	t_vector		vect[4];
	SDL_Color		rgb;
}					t_data;

void				ft_error(char *str);
void				init_all(t_data *data);
int					len_list(t_sector *sectors);
int					near_round(int q);
void				near_lines(t_data *data);
void				key_event(t_data *data);
void				key_helper(t_data *data, SDL_Event event);
void				bresenham_line(t_data *data);
void				mouse_line(t_data *data);
void				fill_next(t_data *data, int x, int y);
void				draw_lines(t_data *data);
void				draw_grid(t_data *data);
void				dots_to_bres(t_data *data);
void				coord_canvas(t_data *data, int x, int y);
void				coord_displ(t_data *data, int x, int y);
void				limit_coord(t_data *data, int x, int y);
int					bef_crossing(t_data *data, int check);
int					intersection_of_two_line(t_data *data);
int					first_vert(t_data *data);
int					second_vert(t_data *data);
int					normal_vec(t_data *data);
int					both_not_vert(t_data *data);
void				space_imitation(t_data *data);
int					find_wall(t_data *data, VEC dot_1, VEC dot_2, int check);
void				mouse_help(t_data *data, int x, int y);
double				min(double x, double y);
double				max(double x, double y);
int					init_vector(t_data *data);
void				ft_swap(int *a, int *b);
void				writting(t_data *data);
void				writte_walls(t_data *data, FILE *fp, int q);
int					find_wall(t_data *data, VEC dot_1, VEC dot_2, int check);
void				make_vertex_list(t_data *data);
int					num_ele(t_data *data, int x, int y);
void				del_list(t_data *data, int q);
void				backspace_imitation(t_data *data);
void				help_mouse_icons(t_data *data);
void				event_menu(t_data *data);
void				menu(t_data *data, int i);
int					modif_obj(t_data *data, int x);
int					check_in_sector(t_data *data, int x, int y);
void				special_icons(t_data *data);
void				writte_icons_to_struct(t_data *data, int q);
void				textures_menu(t_data *data);
void				picture_icon(t_data *data, int st_x, int st_y, SRF *icon);
int					draw_switch_sector(t_data *data, int q);
void				numer(SDL_Event	event, int *num);
void				numer_helper(EVE event, int *num, t_data *data, int q);
void				icons(t_data *data);
int					draw_text(t_data *data, char *text, int x, int y);
unsigned int		get_pixel_int(SDL_Surface *surface, int x, int y);
SDL_Surface			*load_image(char *path);
int					check_flag(t_data *data);
void				multi_key(t_data *data);
void				sort_sector(t_data *data);
int					normalize_line(int q);
void				solid_rect(t_data *data);
void				next_sect(t_data *data);
void				fwri(FILE *fp, char *str);
void				fwri1(FILE *fp, int q);
void				fwrite_icons(t_data *data, FILE *fp);
void				fwrite_textures(t_data *data, FILE *fp);
void				free_vertex(t_data *data);
void				malloc_vertex(t_vertex *new_vertex);

#endif
