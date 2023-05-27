/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42za>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 16:50:56 by lde-alen          #+#    #+#             */
/*   Updated: 2023/05/28 00:28:04 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# define PI 3.14159

#ifdef __linux__
#  include "../miniLibx_linux/mlx.h"
# else
#  include "../minilibx_opengl/mlx.h"
# endif

/*
	KEY Macraaazzzz for the keyboard and mouse both linux and macos
*/

# ifdef __linux__
#  define MLB			1
#  define MRB			3
#  define MMB			2
#  define MWU			4
#  define MWD			5
#  define KEY_W			119
#  define KEY_A			0x1f
#  define KEY_D			0x21
#  define KEY_S			115
#  define KEY_Z			122
#  define KEY_X			120
#  define KEY_C			99
#  define KEY_V			118
#  define KEY_L         0x27
#  define KEY_R			114
#  define KEY_ESC		65307
#  define ARROW_UP		65362
#  define ARROW_DOWN	65364
#  define ARROW_LEFT	65361
#  define ARROW_RIGHT	65363
# else
#  define MLB			0x01
#  define MRB			0x02
#  define MMB			0x03
#  define MWU			0x04
#  define MWD			0x05
#  define KEY_W			0x0D
#  define KEY_A			0
#  define KEY_D			2
#  define KEY_S			0x01
#  define KEY_Z			0x06
#  define KEY_X			0x07
#  define KEY_C			0x08
#  define KEY_V			0x09
#  define KEY_R			0x0F
#  define KEY_L			37
#  define KEY_ESC		0x35
#  define ARROW_UP		0x7E
#  define ARROW_DOWN	0x7D
#  define ARROW_LEFT	0x7B
#  define ARROW_RIGHT	0x7C

# endif