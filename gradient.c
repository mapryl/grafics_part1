#include "map.h"

double percent(int start, int end, int current)
{
    double placement;
    double distance;

    placement = current - start;
    distance = end - start;
    return ((distance == 0) ? 1.0 : (placement / distance));
}


t_color	get_default_color(int z, t_map *map)
{
    double	percentage;

    percentage = percent(map->min_z, map->max_z, z);
    t_color color;
    color.a = 0;
    if (percentage < 0.2)
    {
        color.b = 255;
        color.g = 0;
        color.r = 0;
    }
    else if (percentage < 0.4)
    {
        color.b = 254;
        color.g = 117;
        color.r = 31;
    }
    else if (percentage < 0.6)
    {
        color.b = 255;
        color.g = 144;
        color.r = 30;
    }
    else if (percentage < 0.8)
    {
        color.b = 255;
        color.g = 191;
        color.r = 0;
    }
    else
    {
        color.b = 255;
        color.g = 255;
        color.r = 0;
    }
    return color;
}

short	get_light(int start, int end, double percentage)
{
    return ((short)((1 - percentage) * start + percentage * end));
}

t_color	get_color(t_point current, t_point start, t_point end, t_point delta)
{
    t_color new_color;
    double	percentage;

    if (current.color.r == end.color.r && current.color.b == end.color.b && current.color.g == end.color.g)
        return (current.color);
    if (delta.x > delta.y)
        percentage = percent(start.x, end.x, current.x);
    else
        percentage = percent(start.y, end.y, current.y);
    new_color.r = get_light(start.color.a, end.color.a, percentage);
    new_color.g = get_light(start.color.g, end.color.g, percentage);
    new_color.b = get_light(start.color.b, end.color.b, percentage);
    return new_color;
}

