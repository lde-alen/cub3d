/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 10:12:26 by lde-alen          #+#    #+#             */
/*   Updated: 2023/05/28 05:01:56 by lde-alen         ###   ########.fr       */
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
t_wall			*ft_distance_wall(t_env *env, float alpha);
t_wall			*ft_find_wall(t_env *env, float alpha, int x_r, int y_r);
t_wall			*ft_fill_wall_struct(char type, float x, float y, t_wall *w);
int 			ft_orientation(char c);
t_dist			*ft_init_dist(t_env *env, float alpha);
float			ft_init_pos(float pos);
void			ft_print_map(t_env *env);
void			ft_move(t_env *env);
t_position		ft_incr_pos(t_env *env, int incr);
float			ft_incr_ori(t_position pos, char dir);
void			ft_quit_mlx(t_env *env);
void			ft_mlx_pixel_put(t_img image, int x, int y, int color);
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
float			ft_dist(float x_w, float y_w, float x0, float y0);
int				ft_create_image(t_env *env, int fd);
int				key_press(int key, void *param);
int				key_release(int key, void *param);
t_key			ft_init_key(void);
int				ft_init_struct2(t_env *env, char *error);
void			ft_print_square(t_env *env, int x, int y, int size);
int				ft_find_size_x(t_env *env);

#endif
