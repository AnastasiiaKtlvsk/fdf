/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akotilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/16 18:24:19 by akotilie          #+#    #+#             */
/*   Updated: 2018/09/16 18:24:21 by akotilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	mnp_key(int key, t_i *ti)
{
    mlx_destroy_image(ti->mlx_ptr, ti->img_ptr);
    write(1, " >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n", 45);
    key++;
    ti->a = 0.9;
      ti->d = mlx_get_data_addr(ti->img_ptr, &(ti->bpp), &(ti->sl), &(ti->ei));
    process(ti);
	/*if (key == 53)
		exit(0);
	if (key == 75 || key == 81)
		ft_change_color(key, fdf);
	if (key == 15)
	{
		fdf->angle.z += 15;
		rotate_z_cv(fdf, 15);
	}
	if (key == 69 || key == 78 || key == 6 || key == 7 || ARROW_KEY)
		scale_map(key, fdf);
	if (key == 32)
		fdf->usage = (fdf->usage) ? 0 : 1;
	if (key == 13 || key == 0 || key == 1 || key == 2)
		move_map(key, fdf);
	if (key == 8)
		move_def(fdf);
	if (key == 4)
		fdf->height_mode = (fdf->height_mode) ? 0 : 1;
	if (key == 11)
		fdf->bg_curr_color = (fdf->bg_curr_color == 15) ? 12 :
			fdf->bg_curr_color + 1;*/
            	mlx_put_image_to_window(ti->mlx_ptr, ti->win_ptr, ti->img_ptr, 0, 0);
            return (0);
}

void	hook(t_i *ti)
{
	ti->img_ptr = mlx_new_image(ti->mlx_ptr, ti->dc, ti->dc);
	//fill_image(fdf);

	mlx_hook(ti->win_ptr, 2, 5, mnp_key, ti);

}
