/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_sector.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vomelchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 12:38:01 by vomelchu          #+#    #+#             */
/*   Updated: 2018/12/18 12:38:02 by vomelchu         ###   ########.fr       */
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

int		clockwise_3(t_sector *tmp_sect, double a)
{
	vector vect1;
	vector vect2;
	vector vect3;

	vect1.x = tmp_sect->next->x0 - tmp_sect->x0;
	vect1.y = tmp_sect->next->y0 - tmp_sect->y0;
	vect2.x = tmp_sect->next->next->x0 - tmp_sect->next->x0;
	vect2.y = tmp_sect->next->next->y0 - tmp_sect->next->y0;
	vect3.x = tmp_sect->x0 - tmp_sect->next->next->x0;
	vect3.y = tmp_sect->y0 - tmp_sect->next->next->y0;
	
	a = atan2(vect1.x*vect2.y - vect2.x * vect1.y,
		vect1.x* vect2.x + vect1.y * vect2.y);
	//printf("%f\n", a);	
	if (a < 0 && radians(a) < 0)
		return (1);
	a = atan2(vect2.x*vect3.y - vect3.x * vect2.y,
		vect2.x* vect3.x + vect2.y * vect3.y);
	//printf("%f\n", a);
	if (a < 0 && radians(a) < 0)
		return (1);
	a = atan2(vect3.x*vect1.y - vect1.x * vect3.y,
		vect3.x* vect1.x + vect3.y * vect1.y);
	//printf("%f\n", a);
	if (a < 0 && radians(a) < 0)
		return (1);
	
	return (0);
}

int		clockwise_4(t_sector *tmp_sect, double a)
{
	vector vect1;
	vector vect2;
	vector vect3;
	vector vect4;

	vect1.x = tmp_sect->next->x0 - tmp_sect->x0;
	vect1.y = tmp_sect->next->y0 - tmp_sect->y0;
	vect2.x = tmp_sect->next->next->x0 - tmp_sect->next->x0;
	vect2.y = tmp_sect->next->next->y0 - tmp_sect->next->y0;

	vect3.x = tmp_sect->next->next->next->x0 - tmp_sect->next->next->x0;
	vect3.y = tmp_sect->next->next->next->y0 - tmp_sect->next->next->y0;

	vect4.x = tmp_sect->x0 - tmp_sect->next->next->next->x0;
	vect4.y = tmp_sect->y0 - tmp_sect->next->next->next->y0;


	a = atan2(vect1.x*vect2.y - vect2.x * vect1.y,
		vect1.x* vect2.x + vect1.y * vect2.y);
	//printf("%f\n", a);	
	if (a < 0 && radians(a) < 0)
		return (1);
	a = atan2(vect2.x*vect3.y - vect3.x * vect2.y,
		vect2.x* vect3.x + vect2.y * vect3.y);
	//printf("%f\n", a);
	if (a < 0 && radians(a) < 0)
		return (1);
	a = atan2(vect3.x*vect4.y - vect4.x * vect3.y,
		vect3.x* vect4.x + vect3.y * vect4.y);
	//printf("%f\n", a);
	if (a < 0 && radians(a) < 0)
		return (1);

	a = atan2(vect4.x*vect1.y - vect1.x * vect4.y,
		vect4.x* vect1.x + vect4.y * vect1.y);
	//printf("%f\n", a);
	if (a < 0 && radians(a) < 0)
		return (1);

	return (0);
}

int		clockwise(t_data *data, int q)
{
	double a;

	a = 0.0;
	t_sector *tmp_sect;
	tmp_sect = &data->sectors[q];
	if (len_list(tmp_sect) == 3 && clockwise_3(tmp_sect, a) == 1)
		return (1);
	if (len_list(tmp_sect) == 4 && clockwise_4(tmp_sect, a) == 1)
		return (1);
	return (0);
}

int		clockwise1(t_data *data)
{
	double a;

	a = 0.0;
	t_sector *tmp_sect;
	tmp_sect = &data->sectors[data->current_sector];
	if (len_list(tmp_sect) == 3 && clockwise_3(tmp_sect, a) == 1)
		return (1);
	if (len_list(tmp_sect) == 4 && clockwise_4(tmp_sect, a) == 1)
		return (1);
	return (0);
}

void	change_dots(t_data *data, int q)
{
	vector vect1;
	vector vect2;

	if (len_list(&data->sectors[q]) == 3)
	{
		vect1.x = (double)data->sectors[q].x0;
		vect1.y = (double)data->sectors[q].y0;
		data->sectors[q].x0 = data->sectors[q].next->next->x0;
		data->sectors[q].y0 = data->sectors[q].next->next->y0;
		data->sectors[q].next->next->x0 = (int)vect1.x;
		data->sectors[q].next->next->y0 = (int)vect1.y;
	}
	if (len_list(&data->sectors[q]) == 4)
	{
		vect1.x = (double)data->sectors[q].x0;
		vect1.y = (double)data->sectors[q].y0;
		vect2.x = (double)data->sectors[q].next->x0;
		vect2.y = (double)data->sectors[q].next->y0;
		
		data->sectors[q].x0 = data->sectors[q].next->next->next->x0;
		data->sectors[q].y0 = data->sectors[q].next->next->next->y0;
		data->sectors[q].next->x0 = data->sectors[q].next->next->x0;
		data->sectors[q].next->y0 = data->sectors[q].next->next->y0;
		data->sectors[q].next->next->next->x0 = (int)vect1.x;
		data->sectors[q].next->next->next->y0 = (int)vect1.y;
		data->sectors[q].next->next->x0 = (int)vect2.x;
		data->sectors[q].next->next->y0 = (int)vect2.y;	
	}
}

void	sort_dots(t_data *data)
{
	int q;

	q = -1;
	if (data->sectors[data->current_sector].next == NULL)
		data->current_sector -= 1;
	while (++q <= data->current_sector)
	{
		if (clockwise(data, q) == 1)
			change_dots(data, q);
	}
}