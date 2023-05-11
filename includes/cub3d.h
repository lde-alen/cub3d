/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myvh <myvh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 10:12:26 by lde-alen          #+#    #+#             */
/*   Updated: 2023/05/11 05:33:46 by myvh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <string.h>
# include "mlx.h"
# include "structs.h"
# include "macros.h"
# include <stdbool.h>


/**
 *  Prototypes
 * 
 **/
int	ft_check_map(char *str);
float			angle(float alpha, float beta);
int				ft_check_color(int r, int g, int b);
int				field_of_view(t_env *env, float alpha);
void			ft_mlx_pixel_put_sprite(t_img image, int x, int y, int color);
void			ft_reset_opti(char **opti);
int				ft_error(char *error);
int				ft_size_mini_map(t_env *env);
int				ft_init_struct(char *file);
char			*ft_init_mlx(t_env *env);
void			ft_free(t_env *env);
int				ft_convert_color(char *str);
char			*ft_parse(t_map *map_def, int *fd);
char			*ft_parse_color(t_map *init, char *line);
char			*ft_parse_resolution(t_map *init, char *line);
char			*ft_parse_texture(char *line, t_map *map_def);
char			*ft_parse_map(int fd, char *line, char **map, char *file,
					t_position *pos);
char			*ft_fill_map(char *file, char **map, int size);
char			*ft_fill_line(int fd, char *line, char **map, int size);
t_map			ft_init_map_struct();
char			**ft_init_map(int fd, char *file, int *size);
t_position		ft_init_position(void);
char			*ft_control_map(t_env *env);
int				ft_size_map(int fd);
void			ft_surface_color(t_env *env);
float			*ft_printf_wall(t_env *env);
void			ft_print_column(t_wall *w, int x, t_env *env, float alpha);
int				ft_find_color(t_wall *w);
t_wall			*ft_distance_wall(t_env *env, float alpha);
t_wall			*ft_find_wall(t_env *env, float alpha, int x_r, int y_r);
t_wall			*ft_fill_wall_struct(char type, float x, float y, t_wall *w);
t_wall			*ft_init_wall(void);
float			ft_orientation(char c);
int				it_is_a_wall(float x, float y, t_env *env);
t_wall			*find_next_wall(t_env *env, t_wall *w, float delta_x,
					float delta_y);
t_dist			*ft_init_dist(t_env *env, float alpha);
float			ft_init_pos(float pos);
char			ft_orient_wall(float alpha, char c);
void			ft_print_map(t_env *env);
void			ft_move(t_env *env);
t_position		ft_incr_pos(t_env *env, int incr);
float			ft_incr_ori(t_position pos, char dir);
void			ft_quit_mlx(t_env *env);
void			ft_print_mini_map(t_env *env);
t_wall			*ft_find_wall_dist(t_env *env, float alpha);
t_wall			*check_vertical(t_env *env, float alpha);
t_wall			*check_horizontal(t_env *env, float alpha);
void			ft_mlx_pixel_put(t_img image, int x, int y, int color);
void			ft_init_img(t_env *env);
void			ft_put_img_to_window(t_env *env, int nb);
void			ft_print_perso(t_env *env, int size);
int				ft_find_color_mini_map(char c);
int				red_cross(int key, void *param);
int				deal_key(int key, void *param);
void			ft_adjust_resolution(t_env *s);
int				resize_request(void *env);
char			*ft_texture(t_env *s);
int				ft_mlx_get_color(t_texture text, int x, int y);
int				ft_find_x_text(t_env *env, t_wall *w, int or);

char			*ft_check_zero(char **map, int i, int j, t_env *env);
char			*control_map(char **map, t_env *env);
float			ft_lim_alpha(float alpha);
float			ft_dist(float x_w, float y_w, float x0, float y0);


void			ft_save_bitmap(t_env *env);
void			ft_fill_bmp(t_env *env, int fd);
int				ft_create_image(t_env *env, int fd);



int				key_press(int key, void *param);
void			key_press_bonus(int key, t_env *env);
int				key_release(int key, void *param);
void			ft_arme(t_env *env, t_weapon weapon);
t_weapon		ft_weapon(int a);
t_weapon		ft_tir(int a);
int				ft_which_weapons(int m);
void			ft_print_all(t_env *env);
t_key			ft_init_key(void);
void			ft_up_down(t_env *env, int key);
void			ft_jetpack(t_env *env);
int				ft_init_struct2(t_env *env, char *error);
void			ft_print_square(t_env *env, int x, int y, int size);
void			ft_print_life(t_env *env);
int				ft_find_size_x(t_env *env);
#endif
