/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmassarw <mmassarw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 10:12:26 by lde-alen          #+#    #+#             */
/*   Updated: 2023/05/28 14:50:28 by mmassarw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#ifdef __linux__
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

int				ft_check_color(int r, int g, int b);
void			ft_reset_opti(char **opti);
int				ft_error(char *error);
int				ft_init_struct(char *file);
char			*ft_init_mlx(t_env *env);
void			ft_america(t_env *env);
int				ft_convert_color(char *str);
char			*ft_parse(t_map *map_def, int *fd);
char			*ft_parse_color(t_map *init, char *line);
char			*ft_parse_resolution(t_map *init, char *line);
char			*ft_parse_texture(char *line, t_map *map_def);
char			*ft_parse_map(int fd, char *line, char **map, char *file, t_position *pos);
char			*ft_fill_map(char *file, char **map, int size);
char			*ft_fill_line(int fd, char *line, char **map, int size);
t_map			ft_init_map_struct(void);
char			**ft_init_map(int fd, char *file, int *size);
t_position		ft_init_position(void);
char			*ft_control_map(t_env *env);
int				ft_size_map(int fd);
int 			ft_orientation(char c);
void			ft_print_map(t_env *env);
void			ft_move(t_env *env);
t_position		ft_incr_pos(t_env *env, int incr);
int			ft_incr_ori(t_position pos, char dir);
void			ft_quit_mlx(t_env *env);
void			ft_init_img(t_env *env);
void			ft_put_img_to_window(t_env *env, int nb);
void			ft_print_perso(t_env *env, int size);
int				red_cross(int key, void *param);
int				deal_key(int key, void *param);
void			ft_adjust_resolution(t_env *s);
int				resize_request(void *env);
char			*ft_texture(t_env *s);
int				ft_mlx_get_color(t_texture text, int x, int y);
char			*ft_check_zero(char **map, int i, int j, t_env *env);
char			*control_map(char **map, t_env *env);
int				ft_create_image(t_env *env, int fd);
int				key_press(int key, void *param);
int				key_release(int key, void *param);
t_key			ft_init_key(void);
int				ft_init_struct2(t_env *env, char *error);
void			ft_print_square(t_env *env, int x, int y, int size);
int				ft_find_size_x(t_env *env);
void			pixel_put(t_env *data, t_vert pos, int color);
void			raycasting(t_env *data);
bool			check_hit(t_vert to_check, char **map);
void			render_ray(t_ray ray, t_env *data, int idx);
void			fill_area(t_env *data, t_vert top_left, t_vert bottom_right, int color);

#endif
