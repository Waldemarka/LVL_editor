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

void	take_vect(t_data *data, t_sector *sect)
{
	int q;

	q = -1;
	while (++q < 4)
	{
		data->vect[q].x = sect->x0;
		data->vect[q].y = sect->y0;
		if (sect->next == NULL)
		{
			data->vect[3].x = -1;
			data->vect[3].y = -1;
			break;
		}
		sect = sect->next;
	}
}

void	sort_dots(t_data *data)
{
	t_sector *sect;
	int q;

	q = -1;
	if (data->sectors[data->current_sector].next == NULL)
		data->current_sector -= 1;
	while (++q <= data->current_sector)
	{
		sect =  &data->sectors[q];
		take_vect(data, sect);
		double a = atan2(data->vect[0].x * data->vect[1].y - data->vect[1].x * data->vect[0].y, 
			 data->vect[0].x *  data->vect[1].x +  data->vect[0].y *  data->vect[1].y);
		printf("%f\n",a);
//a = atan2( x1*y2-x2*y1, x1*x2+y1*y2 );

/*		printf("x0 : %f -- y0 : %f\n", data->vect[0].x, data->vect[0].y);
		printf("x1 : %f -- y1 : %f\n", data->vect[1].x, data->vect[1].y);
		printf("x2 : %f -- y2 : %f\n", data->vect[2].x, data->vect[2].y);
		printf("x3 : %f -- y3 : %f\n", data->vect[3].x, data->vect[3].y);*/
	}
}