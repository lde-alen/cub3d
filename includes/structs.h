/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 14:54:36 by lde-alen          #+#    #+#             */
/*   Updated: 2023/05/28 14:54:38 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_map
{
	char	*texture[4];
	int		fov;
	int		floor;
	int		ceiling;
}				t_map;

typedef struct s_position
{
	float	x;
	float	y;
	int		dir;
	float	speed;
	int		mk;
}				t_position;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		end;
	char	**opti;
}				t_img;

typedef struct s_texture
{
	void	*img;
	int		width;
	int		height;
	t_img	data;
	int		color;
}				t_texture;

typedef struct s_mlx_ptr
{
	void	*mlx;
	void	*win;
	t_img	img;
}				t_mlx_ptr;

typedef struct s_key
{
	short		w;
	short		s;
	short		d;
	short		a;
	short		l;
	short		r;
	short		u;
	short		v;
}				t_key;

typedef struct s_vert
{
	int			x;
	int			y;
}	t_vert;

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

typedef struct s_utlpls
{
	double	edge;
	double	dmain;
}	t_utlpls;

typedef struct s_rutl
{
	double		a;
	double		sin_a;
	double		cos_a;
	double		hor_depth;
	double		ver_depth;
	double		hor_wl;
	double		ver_wl;
	double		dothr;
	double		ddepth;
	t_vert		chk;
	t_utlpls	xtra;
}	t_rutl;

typedef struct s_env
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