/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vomelchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 14:02:18 by vomelchu          #+#    #+#             */
/*   Updated: 2018/11/16 14:02:20 by vomelchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	wri_vert(t_data *data, FILE *fp)
{
	int q;
	size_t count;
	char const *vertex = "vertex    ";
	char *num;
	t_sector *sector;

	q = -1;
	while (++q != data->current_sector + 1)
	{
		sector = &data->sectors[q];
		if (sector->next == NULL)
			break;
		while (sector->next != NULL)
		{
			count = fwrite(vertex, ft_strlen(vertex), 1, fp);
			num = ft_itoa(sector->x0);
			count = fwrite(num, ft_strlen(num), 1, fp);
			count = fwrite(" ", 1, 1, fp);
			num = ft_itoa(sector->y0);
			count = fwrite(num, ft_strlen(num), 1, fp);
			count = fwrite(" \n", 1, 2, fp);
			sector = sector->next;
		}
	}
}

void	writting(t_data *data)
{
	FILE *fp;

    fp = fopen(data->name, "wb");
    if(fp == NULL) {
        ft_error("Not FILE");
    }
    wri_vert(data, fp);
    fwrite(" \n", 1, 2, fp);
    fwrite(" \n", 1, 2, fp);
    wri_sect(data, fp);
    if (fclose(fp) != 0)
    	ft_error("bad writting");
    fclose(fp);
}
