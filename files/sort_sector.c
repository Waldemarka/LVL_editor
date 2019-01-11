/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_sector.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vomelchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 12:38:01 by vomelchu          #+#    #+#             */
/*   Updated: 2019/01/02 13:24:23 by vomelchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int		radians(double a)
{
	int x;

	x = (int)(a * 100);
	if (x == -314)
		return (1);
	return (-1);
}

int		for_atan(t_vector vect1, t_vector vect2)
{
	double a;

	a = atan2(vect1.x * vect2.y - vect2.x * vect1.y,
		vect1.x * vect2.x + vect1.y * vect2.y);
	if (a < 0 && radians(a) < 0)
		return (1);
	return (0);
}

int		clockwise_3(t_sector *tmp_sect)
{
	t_vector vect1;
	t_vector vect2;
	t_vector vect3;

	vect1.x = tmp_sect->next->x0 - tmp_sect->x0;
	vect1.y = tmp_sect->next->y0 - tmp_sect->y0;
	vect2.x = tmp_sect->next->next->x0 - tmp_sect->next->x0;
	vect2.y = tmp_sect->next->next->y0 - tmp_sect->next->y0;
	vect3.x = tmp_sect->x0 - tmp_sect->next->next->x0;
	vect3.y = tmp_sect->y0 - tmp_sect->next->next->y0;
	if (for_atan(vect1, vect2) == 1)
		return (1);
	if (for_atan(vect2, vect3) == 1)
		return (1);
	if (for_atan(vect3, vect1) == 1)
		return (1);
	return (0);
}

int		clockwise_4(t_sector *tmp_sect)
{
	t_vector vect1;
	t_vector vect2;
	t_vector vect3;
	t_vector vect4;

	vect1.x = tmp_sect->next->x0 - tmp_sect->x0;
	vect1.y = tmp_sect->next->y0 - tmp_sect->y0;
	vect2.x = tmp_sect->next->next->x0 - tmp_sect->next->x0;
	vect2.y = tmp_sect->next->next->y0 - tmp_sect->next->y0;
	vect3.x = tmp_sect->next->next->next->x0 - tmp_sect->next->next->x0;
	vect3.y = tmp_sect->next->next->next->y0 - tmp_sect->next->next->y0;
	vect4.x = tmp_sect->x0 - tmp_sect->next->next->next->x0;
	vect4.y = tmp_sect->y0 - tmp_sect->next->next->next->y0;
	if (for_atan(vect1, vect2) == 1)
		return (1);
	if (for_atan(vect2, vect3) == 1)
		return (1);
	if (for_atan(vect3, vect4) == 1)
		return (1);
	if (for_atan(vect4, vect1) == 1)
		return (1);
	return (0);
}

void	sort_sector(t_data *data)
{
	int			q;
	t_sector	*sector;
	t_vector	tmp;

	q = -1;
	while (++q <= data->current_sector)
	{
		sector = &data->sectors[q];
		tmp.x = (double)sector->next->x0;
		tmp.y = (double)sector->next->y0;
		if (len_list(sector) == 4 && clockwise_3(sector) == 1)
		{
			sector->next->x0 = sector->next->next->x0;
			sector->next->y0 = sector->next->next->y0;
			sector->next->next->x0 = (int)tmp.x;
			sector->next->next->y0 = (int)tmp.y;
		}
		if (len_list(sector) == 5 && clockwise_4(sector) == 1)
		{
			sector->next->x0 = sector->next->next->next->x0;
			sector->next->y0 = sector->next->next->next->y0;
			sector->next->next->next->x0 = (int)tmp.x;
			sector->next->next->next->y0 = (int)tmp.y;
		}
	}
}
