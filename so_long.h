/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshawish <sshawish@student.42amman.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 12:05:34 by sshawish          #+#    #+#             */
/*   Updated: 2024/11/20 12:06:25 by sshawish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# define MAX_LINES 1000
# define TILE_SIZE 32
# define ESC 65307
# define KEY_W 119
# define KEY_S 115
# define KEY_A 97
# define KEY_D 100
# define A_UP 65362
# define A_DOWN 65364
# define A_LEFT 65361
# define A_RIGHT 65363

# include <stdlib.h>
# include <mlx.h>
# include <fcntl.h>
# include <unistd.h>
# include <errno.h>
# include "libft/libft.h"

typedef struct s_flood_fill_info
{
	int	collectibles;
	int	exit_found;

}	t_flood_fill_info;

typedef struct s_count_info
{
	int	count_p;
	int	count_e;
	int	count_c;
	int	count_k;
}	t_count_info;

typedef struct s_data
{
	t_flood_fill_info		*flood_fill_info;
	void					*mlx;
	void					*window;
	void					*wall_img;
	void					*floor_img;
	void					*collectible_img;
	void					*exit_img;
	void					*enemy_img;
	void					*player_img1;
	int						img_width;
	int						img_height;
	int						player_x;
	int						player_y;
	int						move_count;
	int						window_width;
	int						window_height;
	char					**map;
}	t_data;

char	**read_map(const char *filename);
char	**copy_map(char **map);
int		find_start(char **map, int *start_x, int *start_y);
int		find_start_s(t_data *data, int *start_x, int *start_y);
int		find_start_and_check(char **map, int *start_x,
			int *start_y, t_flood_fill_info *info);
int		count_collectibles(char **map);
int		process_map_line(int fd, char ***map);
int		valid_ber(const char *filename);
int		validate_map(t_data *data, int ac, char **av);
int		check_walls(char *line);
int		allocate_flood_fill_info(t_flood_fill_info **info);
int		validate_and_count(char c, t_count_info *count_info);
int		is_rectangular(char **map);
int		has_valid_elements(char **map, t_count_info *count_info);
int		is_enclosed_in_walls(char **map);
int		is_accessible(char **map, t_data *data);
int		parse_map(t_data *data, char *filename, t_count_info *count_info);
int		close_window(t_data *data);
int		handle_symbols(t_data *data, int new_x, int new_y);
int		change_player_position(int keycode, t_data *data,
			int *new_x, int *new_y);
int		move_player(t_data *data, int keycode);
int		handle_keypress(int keycode, t_data	*data);
int		load_sprites(t_data *data);
int		game_loop(t_data *data);
int		handle_info_error(t_flood_fill_info *info);
void	flood_fill(char **map, int x, int y, t_flood_fill_info *info);
void	free_map(char **map);
void	free_struct(t_data *data);
void	cleanup_sprites(t_data *data);
void	draw_tile(t_data *data, int x, int y, char tile);
void	render_map(t_data *data, char **map);
void	render_player(t_data *data);
void	window_size(t_data *data);
void	cleanup_game(t_data *data);

#endif
