/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 14:54:31 by lde-alen          #+#    #+#             */
/*   Updated: 2023/05/28 17:39:18 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# ifdef __linux__
#  include "../miniLibx_linux/mlx.h"
# else
#  include "../minilibx_opengl/mlx.h"
# endif

# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <string.h>
# include "structs.h"
# include "macros.h"
# include <stdbool.h>

/**
 *  Prototypes
 * 
 **/

int				check_color(int r, int g, int b);
void			reset_opti(char **opti);
int				ft_error(char *error);
int				init(char *file);
char			*init_mlx(t_env *env);
void			america(t_env *env);
int				convert_color(char *str);
char			*parse(t_map *map_def, int *fd);
char			*parse_color(t_map *init, char *line);
char			*parse_texture(char *line, t_map *map_def);
char			*fill_map(char *file, char **map, int size);
char			*fill_line(int fd, char *line, char **map, int size);
t_map			init_map_struct(void);
char			**init_map(int fd, char *file, int *size);
t_position		init_position(void);
char			*ft_control_map(t_env *env);
int				size_map(int fd);
int				orientation(char c);
void			move(t_env *env);
t_position		incr_pos(t_env *env, int incr);
int				incr_ori(t_position pos, char dir);
void			quit_mlx(t_env *env);
void			init_img(t_env *env);
int				red_cross(int key, void *param);
char			*texture(t_env *s);
int				ft_mlx_get_color(t_texture text, int x, int y);
char			*check_zero(char **map, int i, int j, t_env *env);
char			*control_map(char **map, t_env *env);
int				key_press(int key, void *param);
int				key_release(int key, void *param);
t_key			init_key(void);
int				init2(t_env *env, char *error);
int				find_x(t_env *env);
void			pixel_put(t_env *data, t_vert pos, int color);
void			raycasting(t_env *data);
bool			check_hit(t_vert to_check, char **map);
void			render_ray(t_ray ray, t_env *data, int idx);
void			fill_area(t_env *data, t_vert top_left,
					t_vert bottom_right, int color);

#endif
