/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmassarw <mmassarw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 10:16:46 by lde-alen          #+#    #+#             */
/*   Updated: 2023/05/28 03:05:32 by mmassarw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRUCTURE_H
# define FT_STRUCTURE_H

typedef struct	s_map
{
	char	*texture[4];
	int		x_res;
	int		y_res;
	int		floor;
	int		ceiling;
}				t_map;

typedef struct	s_position
{
	float	x;
	float	y;
	float	dir;
	float	speed;
	int		z;
	float	life;
	int		mk;
}				t_position;

typedef struct	s_wall
{
	int		wall;
	float	x_wall;
	float	y_wall;
	char	orientation;
	float	dist;
}				t_wall;

typedef struct	s_print_wall
{
	float	alpha;
	int		x;
	int		x_ecart;
}				t_print_wall;

typedef struct	s_text
{
	float	y;
	int		x;
	float	pos;
	float	d_y;
}				t_text;

typedef struct	s_dist
{
	float	x;
	float	y;
	float	delta_x;
	float	delta_y;
}				t_dist;

typedef struct	s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		end;
	char	**opti;
}				t_img;

typedef struct	s_texture
{
	void	*img;
	int		width;
	int		height;
	t_img	data;
	int		color;
}				t_texture;

typedef struct	s_mlx_ptr
{
	void	*mlx;
	void	*win;
	t_img	img;
}				t_mlx_ptr;

typedef struct	s_sp
{
	float	x;
	float	y;
	float	d;
	float	ang;
}				t_sp;

typedef struct	s_key
{
	short		w;
	short		s;
	short		d;
	short		a;
	short		l;
	short		r;
}				t_key;

typedef struct s_vert
{
	int			x;
	int			y;
}	t_vert;

typedef struct s_player
{
	t_vert	player_pos;
	t_vert	map_pos;
	double	angle;
}	t_player;

enum e_texture
{
	NO,
	SO,
	WE,
	EA,
};

typedef struct s_ray
{
	enum e_texture	texture;
	double			texture_x;
	double			depth;
	double			proj_height;
}	t_ray;

typedef struct s_rayutils
{
	double	angle;
	double	sin_angle;
	double	cos_angle;
	double	horizental_depth;
	double	vertical_depth;
	double	horizental_wall;
	double	vertical_wall;
	double	edge;
	double	delta_x;
	double	delta_y;
	double	delta_depth;
	t_vert	check_vert;
}	t_rayutils;

typedef struct	s_env
{
	t_mlx_ptr	mlx;
	t_position	pos;
	t_map		init;
	char		**map;
	int			size_x;
	int			size_y;
	int			*size_line;
	t_texture	tex[4];
	t_key		key;
}				t_env;


#endif