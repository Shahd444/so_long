/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshawish <sshawish@student.42amman.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 10:54:40 by sshawish          #+#    #+#             */
/*   Updated: 2024/11/20 10:55:05 by sshawish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	init_mlx(t_data *data, int ac, char **av)
{
	(*data).mlx = mlx_init();
	if ((*data).mlx == NULL)
		return (EXIT_FAILURE);
	if (validate_map(data, ac, av) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (load_sprites(data) == 0)
	{
		ft_putstr_fd("Error: fail to load sprites\n", 2);
		free(data->flood_fill_info);
		cleanup_sprites(data);
		free_struct(data);
		return (EXIT_FAILURE);
	}
	if (find_start_s(data, &(*data).player_x, &(*data).player_y) == 0)
	{
		free_struct(data);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	init_window(t_data *data)
{
	window_size(data);
	(*data).window = mlx_new_window((*data).mlx, (*data).window_width,
			(*data).window_height, "so_long_game!");
	if ((*data).window == NULL)
	{
		cleanup_sprites(data);
		free((*data).mlx);
		free_struct(data);
		return (EXIT_FAILURE);
	}
	render_map(data, (*data).map);
	mlx_hook((*data).window, 2, 1L << 0, handle_keypress, data);
	mlx_hook((*data).window, 17, 0, close_window, data);
	return (EXIT_SUCCESS);
}

int	main(int ac, char **av)
{
	t_data	data;

	data.move_count = 0;
	data.map = NULL;
	if (init_mlx(&data, ac, av) == EXIT_FAILURE)
	{
		mlx_destroy_display(data.mlx);
		free(data.mlx);
		return (EXIT_FAILURE);
	}
	if (init_window(&data) == EXIT_FAILURE)
	{
		mlx_destroy_display(data.mlx);
		free_struct(&data);
		return (EXIT_FAILURE);
	}
	mlx_loop_hook(data.mlx, game_loop, &data);
	mlx_loop(data.mlx);
	return (EXIT_SUCCESS);
}
