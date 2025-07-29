/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_to_window.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshawish <sshawish@student.42amman.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 12:21:02 by sshawish          #+#    #+#             */
/*   Updated: 2024/11/26 12:21:04 by sshawish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	load_sprites(t_data *data)
{
	data->wall_img = mlx_xpm_file_to_image(data->mlx, "textures/wall.xpm",
			&data->img_width, &data->img_height);
	if (!data->wall_img)
		return (0);
	data->floor_img = mlx_xpm_file_to_image(data->mlx, "textures/floor.xpm",
			&data->img_width, &data->img_height);
	if (!data->floor_img)
		return (0);
	data->collectible_img = mlx_xpm_file_to_image(data->mlx,
			"textures/mashroom.xpm", &data->img_width, &data->img_height);
	if (!data->collectible_img)
		return (0);
	data->exit_img = mlx_xpm_file_to_image(data->mlx, "textures/exit.xpm",
			&data->img_width, &data->img_height);
	if (!data->exit_img)
		return (0);
	data->player_img1 = mlx_xpm_file_to_image(data->mlx, "textures/player.xpm",
			&data->img_width, &data->img_height);
	if (!data->player_img1)
		return (0);
	data->enemy_img = mlx_xpm_file_to_image(data->mlx, "textures/enemy.xpm",
			&data->img_width, &data->img_height);
	if (!data->enemy_img)
		return (0);
	return (1);
}

void	draw_tile(t_data *data, int x, int y, char tile)
{
	void	*img;

	img = NULL;
	if (tile == '1')
		img = data->wall_img;
	else if (tile == 'C')
		img = data->collectible_img;
	else if (tile == 'E')
		img = data->exit_img;
	else if (tile == 'K')
		img = data->enemy_img;
	else
		img = data->floor_img;
	mlx_put_image_to_window(data->mlx, data->window, img,
		x * TILE_SIZE, y * TILE_SIZE);
}

void	render_map(t_data *data, char **map)
{
	int	x;
	int	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			draw_tile(data, x, y, map[y][x]);
			x++;
		}
		y++;
	}
}

void	render_player(t_data *data)
{
	mlx_put_image_to_window(data->mlx, data->window, data->player_img1,
		data->player_x * TILE_SIZE, data->player_y * TILE_SIZE);
}

int	game_loop(t_data *data)
{
	render_map(data, data->map);
	render_player(data);
	return (0);
}
