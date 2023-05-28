#include "cub3d.h"

bool	check_hit(t_vert to_check, char **map)
{
	size_t	len;

	len = 0;
	while (map[len])
		len++;
	if (to_check.y >= 0 && (size_t) to_check.y < len)
		if (to_check.x >= 0 && (size_t) to_check.x < ft_strlen(map[to_check.y]))
			if (map[to_check.y][to_check.x] == '1')
				return (true);
	return (false);
}

void	render_ray(t_ray ray, t_data data, t_map map, int idx)
{
	int y_start = ((HEIGHT / 2) - ray.proj_height/2); 
	int y_end = ((HEIGHT / 2) + ray.proj_height/2); 

	while(y_start <= y_end)
	{
		if (y_start < 0 || y_start > HEIGHT)
			pixel_put(data, (t_vert) {WIDTH - idx, y_start}, );
			// map.texture[ray.texture].texture[(int) ray.texture_x * MAP_SCALE / map.texture.width][y_start * (int) ray.proj_height / map.texture.height]);
		y_start++;
	}
}

void fill_area(t_data data, t_vert top_left, t_vert bottom_right, int color)
{
	int x;
	int y;

	y = top_left.y;
	while (y <= bottom_right.y)
	{
		x = top_left.x;
		while (x <= bottom_right.x)
		{
			t_vert pos = {x, y};
			pixel_put(data, pos, color);
			x++;
		}
		y++;
	}
}

void	draw_walls(t_data data, int edge_length, char ** map) {
	int 	row;
	int		col;
	t_vert	top_left;
	t_vert	bottom_right;
	size_t	len;

	len = 0;
	while (map[len])
		len++;
	for (row = 0; (size_t) row < len; row++)
		for (col = 0; (size_t) col < ft_strlen(map[row]); col++)
			if (map[row][col] == '1')
			{
				top_left.x = col * edge_length;
				top_left.y = row * edge_length;
				bottom_right.x = (col + 1) * edge_length - 1;
				bottom_right.y = (row + 1) * edge_length - 1;
				fill_area(data, top_left, bottom_right, 0xff0000); // Assuming color 1 represents walls
			}
}

void	raycasting(t_data data, t_map map, t_player *player)
{
	t_ray		rays[WIDTH];
	int			i[2];
	t_rayutils	rayutils;

//	----------------------------------------------------------------------------
	(void) data;
	(void) rays;
	char	string[11][11] = {{"1111111111"},
							  {"1000000001"},
							  {"1111101101"},
							  {"  10000011"},
							  {"  1000001 "},
							  {"  1000001 "},
							  {"  100s111 "},
							  {"1110101   "},
							  {"1000001   "},
							  {"1111111   "}};
	map.map = (char **) ft_calloc(11, sizeof(char *));
	for (int j = 0; j < 10; j++) {
		map.map[j] = ft_strdup(string[j]);
	}
	// draw_walls(data, 64, map.map);
//	----------------------------------------------------------------------------


	rayutils.angle = player->angle - (FOV / 2) + 1e-6;
	ft_bzero(i, sizeof(int) * 2);
	i[0] = -1;
	while(++i[0] < WIDTH)
	{
		printf("%f\n", rayutils.angle);
		rayutils.sin_angle = sin(rayutils.angle * DTOR) * -1;
		rayutils.cos_angle = cos(rayutils.angle * DTOR);

		if (rayutils.sin_angle > 0)
		{
			rayutils.edge = player->map_pos.y + 1;
			rayutils.edge *= MAP_SCALE;
			rayutils.delta_y = MAP_SCALE;
		}
		else
		{
			rayutils.edge = player->map_pos.y - 1e-6;
			rayutils.edge *= MAP_SCALE;
			rayutils.delta_y = -MAP_SCALE;
		}
		int map_edge = (int) rayutils.edge / 64;
		rayutils.horizental_depth = (rayutils.edge - player->player_pos.y - player->map_pos.y * MAP_SCALE) / rayutils.sin_angle;
		rayutils.horizental_wall = player->player_pos.x + player->map_pos.x * MAP_SCALE + rayutils.horizental_depth * rayutils.cos_angle;
		rayutils.delta_depth = rayutils.delta_y / rayutils.sin_angle;
		rayutils.delta_x = rayutils.delta_depth * rayutils.cos_angle;
		i[1] = 0;
		while(i[1]++ < MAX_DEPTH)
		{
			rayutils.check_vert = (t_vert) {(int)  rayutils.horizental_wall / MAP_SCALE, (int) rayutils.edge / MAP_SCALE};
			if (check_hit(rayutils.check_vert, map.map))
				break;
			rayutils.horizental_wall += rayutils.delta_x;
			rayutils.edge += rayutils.delta_y;
			rayutils.horizental_depth += rayutils.delta_depth;
		}

		if (rayutils.cos_angle > 0)
		{
			rayutils.edge = player->map_pos.x + 1;
			rayutils.edge *= MAP_SCALE;
			rayutils.delta_x = MAP_SCALE;
		}
		else
		{
			rayutils.edge = player->map_pos.x - 1e-6;
			rayutils.edge *= MAP_SCALE;
			rayutils.delta_x = -MAP_SCALE;
		}
		map_edge = (int) rayutils.edge / 64;
		rayutils.vertical_depth = (rayutils.edge - player->player_pos.x - player->map_pos.x * MAP_SCALE) / rayutils.cos_angle;
		rayutils.vertical_wall = player->player_pos.y + player->map_pos.y * MAP_SCALE + rayutils.vertical_depth * rayutils.sin_angle;
		rayutils.delta_depth = rayutils.delta_x / rayutils.cos_angle;
		rayutils.delta_y = rayutils.delta_depth * rayutils.sin_angle;
		i[1] = 0;
		while(i[1]++ < MAX_DEPTH )
		{
			rayutils.check_vert = (t_vert) {(int)  rayutils.edge / MAP_SCALE, (int) rayutils.vertical_wall / MAP_SCALE};
			if (check_hit(rayutils.check_vert, map.map))
				break;
			rayutils.vertical_wall += rayutils.delta_y;
			rayutils.edge += rayutils.delta_x;
			rayutils.vertical_depth += rayutils.delta_depth;
		}

		if (rayutils.vertical_depth < rayutils.horizental_depth)
		{
			rays[i[0]].depth = rayutils.vertical_depth;
			if (rayutils.cos_angle < 0)
			{
				rays[i[0]].texture = EA;
				rays[i[0]].texture_x = MAP_SCALE - ((int) rayutils.vertical_wall % MAP_SCALE);
			}
			else
			{
				rays[i[0]].texture = WE;
				rays[i[0]].texture_x = (int) rayutils.vertical_wall % MAP_SCALE;
			}
		}
		else
		{
			rays[i[0]].depth = rayutils.horizental_depth;
			if (rayutils.sin_angle > 0)
			{
				rays[i[0]].texture = NO;
				rays[i[0]].texture_x = MAP_SCALE - ((int) rayutils.horizental_wall % MAP_SCALE);
			}
			else
			{
				rays[i[0]].texture = SO;
				rays[i[0]].texture_x = (int) rayutils.horizental_wall % MAP_SCALE;
			}
		}
		rays[i[0]].depth *= cos((player->angle - rayutils.angle) * DTOR);
		rays[i[0]].proj_height = ((double) (WIDTH / 2) / (tan((double) FOV * DTOR / 2))) / ((rays[i[0]].depth + 1e-6)/MAP_SCALE);

//	----------------------------------------------------------------------------		
		// int finalX =  player->player_pos.x + player->map_pos.x * MAP_SCALE + round(rays[i[0]].depth * rayutils.cos_angle);
		// int finalY =  player->player_pos.y + player->map_pos.y * MAP_SCALE + round(rays[i[0]].depth * rayutils.sin_angle);
		// t_vert start = {player->player_pos.x + player->map_pos.x * MAP_SCALE, player->player_pos.y + player->map_pos.y * MAP_SCALE };
		// t_vert finalpoint = {finalX, finalY};
		// drawline(start, finalpoint, data, 0xFFFFFF);
		drawline((t_vert) {WIDTH - i[0], (((HEIGHT / 2) + rays[i[0]].proj_height/2))}, (t_vert) {WIDTH - i[0], (((HEIGHT / 2) - rays[i[0]].proj_height/2))}, data, 0xFFFFFF);
//	----------------------------------------------------------------------------		
		rayutils.angle += ((double) FOV / (double) WIDTH);
	}
}