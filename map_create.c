#include "map.h"
#include "get_next_line.h"

void throw_error();

void map_create(t_map* map)
{
    map->data = NULL;
    map->hight_capacity = 0;
    map->hight = 0;
    map->width = 0;
}

void line_create(t_line* vec)
{
    vec->data = NULL;
    vec->width_capacity = 0;
    vec->width = 0;
}

void* reallocate(void *data, size_t* capacity, size_t elem_size)
{
    size_t new_capacity = *capacity;
    new_capacity += (new_capacity + 2) / 2;

    void *new_data = malloc(new_capacity * elem_size);
    if(!new_data)
    {
        return NULL;
    }

    size_t old_mem_size = *capacity * elem_size;
    memcpy(new_data, data, old_mem_size);

    free(data);

    *capacity = new_capacity;

    return new_data;
}

int line_add(t_line* line, int x, int y, int z)
{
    if ( line->width >= line->width_capacity )
    {
        t_point *new_data = (t_point*) reallocate(line->data, &line->width_capacity, sizeof(t_point));
        if ( !new_data )
        {
            return -1;
        }
        line->data = new_data;
    }

    t_point point = {x, y, z};
    line->data[line->width++] = point;
    return 0;
}

int map_add(t_map* map, t_point* data, size_t width)
{
    if(!map->width)
    {
        map->width = width;
    }
    else if(map->width != width)
    {
        return -1;
    }

    if (map->hight >= map->hight_capacity)
    {
        t_point **new_data = (t_point**)reallocate(map->data, &map->hight_capacity, sizeof(t_point*));
        if (!new_data)
        {
            return -1;
        }
        map->data = new_data;
    }

    map->data[map->hight++] = data;
    return 0;
}

static void parse_line(char **split_line, t_map *map)
{
    t_line line;
    int i;

    line_create(&line);
    i = 0;
    while (*split_line)
    {
        line_add(&line, i * X_UNIT, map->hight * Y_UNIT,  ft_atoi(*split_line)*10);
        *split_line++;
        i++;
    }
    map_add(map, line.data, line.width);
}

int read_map(const int fd, t_map *map)
{
    char *line;
    char **split_lines;

    while (get_next_line(fd, &line))
    {
        if (!(split_lines = ft_strsplit(line, ' ')))
            throw_error();
        parse_line(split_lines, map);
    }
    return 0;
}

