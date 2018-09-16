/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akotilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 16:35:25 by akotilie          #+#    #+#             */
/*   Updated: 2018/08/11 19:15:55 by akotilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		main(int argc, char **argv)
{
  t_i       ti;

//  read_map(&ti, argv[1], -1);
  if (argc != 2)
  {
      argv[0] = NULL;
  }
    // return (0);
   printf("validation result: %i\n",read_map(&ti, argv[1], -1));


  ti.mlx_ptr = mlx_init();
	choose_distance(&ti);
	ti.win_ptr = mlx_new_window(ti.mlx_ptr, ti.dc, ti.dc, "fdf");
  ti.img_ptr = mlx_new_image(ti.mlx_ptr, ti.dc, ti.dc);
  ti.d = mlx_get_data_addr(ti.img_ptr, &(ti.bpp), &(ti.sl), &(ti.ei));
  fill_dt(&ti);
  printf("%d, %d, %d\n", ti.bpp, ti.sl, ti.ei);
  mlx_put_image_to_window(ti.mlx_ptr,ti.win_ptr, ti.img_ptr, 0, 0);
	mlx_loop(ti.mlx_ptr);
  // while (1);
  free_type(&ti);
	return (0);
}

