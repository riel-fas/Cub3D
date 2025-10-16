/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_anim_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 21:40:47 by riel-fas          #+#    #+#             */
/*   Updated: 2025/10/16 21:43:48 by riel-fas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	calculate_hands_dimensions(int *hands_width, int *hands_height)
{
    *hands_width = WINDOW_WIDTH * FP_HANDS_WIDTH_SCALE;
    *hands_height = WINDOW_HEIGHT * FP_HANDS_HEIGHT_SCALE;
}

static void	calculate_hands_position(int hands_width, int hands_height, 
                                int *hands_x, int *hands_y)
{
    *hands_x = (WINDOW_WIDTH - hands_width) / 2;
    *hands_y = WINDOW_HEIGHT - hands_height + FP_HANDS_Y_OFFSET;
}

static int	is_valid_pixel_position(int tex_x, int tex_y, int screen_x, int screen_y,
                                t_texture *texture)
{
    return (tex_x >= 0 && tex_x < texture->width && 
            tex_y >= 0 && tex_y < texture->height &&
            screen_x < WINDOW_WIDTH && screen_y < WINDOW_HEIGHT &&
            screen_x >= 0 && screen_y >= 0);
}

static void	render_hands_pixel(t_data *data, t_texture *current_frame,
                            int x, int y, int hands_x, int hands_y,
                            int hands_width, int hands_height)
{
    int			tex_x;
    int			tex_y;
    uint32_t	color;

    tex_x = (x * current_frame->width) / hands_width;
    tex_y = (y * current_frame->height) / hands_height;
    
    if (is_valid_pixel_position(tex_x, tex_y, hands_x + x, hands_y + y, current_frame))
    {
        color = get_pixel_color(current_frame, tex_x, tex_y);
        if ((color & 0xFF) != 0)
            mlx_put_pixel(data->image, hands_x + x, hands_y + y, color);
    }
}

void	render_first_person_zombie_hands(t_data *data)
{
    t_texture	*current_frame;
    int			hands_width;
    int			hands_height;
    int			hands_x;
    int			hands_y;
    int			x;
    int			y;

    current_frame = get_current_frame(&data->zombie_anim);
    if (!current_frame)
        return ;
    calculate_hands_dimensions(&hands_width, &hands_height);
    calculate_hands_position(hands_width, hands_height, &hands_x, &hands_y);
    y = 0;
    while (y < hands_height)
    {
        x = 0;
        while (x < hands_width)
        {
            render_hands_pixel(data, current_frame, x, y, hands_x, hands_y,
                            hands_width, hands_height);
            x++;
        }
        y++;
    }
}
