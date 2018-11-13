/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vomelchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 16:06:36 by vomelchu          #+#    #+#             */
/*   Updated: 2018/11/08 16:06:39 by vomelchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	fill_next(t_data *data, int x, int y)
{
	t_sector *tmp_sect;

	tmp_sect = &data->sectors[data->current_sector];
	while (tmp_sect->next != NULL)
		tmp_sect = tmp_sect->next;
	tmp_sect->x0 = x;
	tmp_sect->y0 = y;
	if (!(tmp_sect->next = (t_sector *)malloc(sizeof(t_sector))))
		ft_error("Bad malloc in fill_next");
	tmp_sect->next->next = NULL;
	tmp_sect = tmp_sect->next;
}

void	draw_lines(t_data *data)
{
	t_sector *tmp_sect;
	int i;
	int len;

	i = -1;
	if (data->check_click != 0)
		len = data->for_realloc;
	else
		len = data->for_realloc -1;
		while (++i < data->for_realloc)
		{
		tmp_sect = &data->sectors[i];
			
		while (tmp_sect->next != NULL)
		{
			if (tmp_sect->next->next != NULL && tmp_sect->next != NULL)
			{
				data->x0 = tmp_sect->x0;
				data->x1 = tmp_sect->next->x0;
				data->y0 = tmp_sect->y0;
				data->y1 = tmp_sect->next->y0;
				bresenham_line(data);
			}
		tmp_sect = tmp_sect->next;
		}
	}
	
}
