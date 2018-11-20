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

/*int		len_list(t_data *data, int q)
{
	int len;
	t_sectors *sectors;

	len = 0;
	sectors = *data->sectors[q];
	while (sectors.next != NULL)
	{

	}
}*/

void	wri_sectors(t_data *data, FILE *fp)
{
	int q;
	 size_t count;
	char const *str = "SECTOR\n";
	char *num;
	int y = 0;

	q = -1;
	while (++q != data->current_sector + 1)
	{
		count = fwrite(str, ft_strlen(str), 1, fp);
		if (data->sectors[q].next == NULL)
			exit(1);
		while (data->sectors[q].next != NULL)
		{
			num = ft_itoa(data->sectors[q].x0);
			count = fwrite(num, ft_strlen(num), 1, fp);
			count = fwrite(" ", 1, 1, fp);
			num = ft_itoa(data->sectors[q].y0);
			count = fwrite(num, ft_strlen(num), 1, fp);
			count = fwrite(" \n", 1, 2, fp);
			data->sectors[q] = *data->sectors[q].next;
		}
		printf("%d\n", ++y);
	}

}

void	writting(t_data *data)
{
	FILE *fp;
    //char const *str = "привет\n";

    fp = fopen(data->name, "wb");
    if(fp == NULL) {
        ft_error("Not FILE");
    }
    wri_sectors(data, fp);
    //count = fwrite(str, ft_strlen(str), 1, fp);
   // count = fwrite(str, ft_strlen(str), 1, fp);
    if (fclose(fp) != 0)
    	ft_error("bad writting");
    fclose(fp);
}

/*int main(void)
{
    FILE *fp;
    size_t count;
    char const *str = "привет\n";

    fp = fopen("пример.txt", "wb");
    if(fp == NULL) {
        perror("ошибка открытия пример.txt");
        return EXIT_FAILURE;
    }
    count = fwrite(str, strlen(str), 1, fp);
    printf("Записано %lu байт. fclose(fp) %s.\n", (unsigned long)count, fclose(fp) == 0 ? "успешно" : "с ошибкой");

    fclose(fp);
    return 0;
}*/