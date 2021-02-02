#include "../cube3D.h"

int	check_valide_value(t_object_on_scene *objects, char symbol)
{
	(void)objects;
	if (symbol == '1' || symbol == '0' ||
		symbol == '2' || symbol == 'N' ||
		symbol == 'W' || symbol == 'S' ||
		symbol == 'E')
		return (1);
	return (0);
}

void	quantity_strings(t_object_on_scene *objects)
{
	int i;

	i = 0;
	while (objects->map[i] != NULL)
		i++;
	objects->s_value_from_map.quantity_string = i;
}

void	check_vertical_edge(t_object_on_scene *objects)
{
	int j;

	j = 0;
	// printf("1) objects->s_value_from_map.valide_map: %d\n", objects->s_value_from_map.valide_map);
	while (objects->map[0][j] != '\0')
	{
		if (objects->map[0][j] != '1')
			objects->s_value_from_map.valide_map = -1;
		j++;
	}
	j = 0;
	// printf("2) objects->s_value_from_map.valide_map: %d\n", objects->s_value_from_map.valide_map);
	// printf("%s\n", objects->map[objects->s_value_from_map.quantity_string - 1]);
	while (objects->map[objects->s_value_from_map.quantity_string - 1][j] != '\0')
	{
		if (objects->map[objects->s_value_from_map.quantity_string - 1][j] != '1')
			objects->s_value_from_map.valide_map = -1;
			j++;
	}
	// write(1, "1", 1);
}

int	check_arround_fill(t_object_on_scene *objects, int i, int j)
{
	int sum;

	sum = 0;
	if (check_valide_value(objects, objects->map[i - 1][j - 1]) == 1)
		sum++;
	if (check_valide_value(objects, objects->map[i - 1][j]) == 1)
		sum++;
	if (check_valide_value(objects, objects->map[i - 1][j + 1]) == 1)
		sum++;
	if (check_valide_value(objects, objects->map[i][j - 1]) == 1)
		sum++;
	if (check_valide_value(objects, objects->map[i][j + 1]) == 1)
		sum++;
	if (check_valide_value(objects, objects->map[i + 1][j - 1]) == 1)
		sum++;
	if (check_valide_value(objects, objects->map[i + 1][j]) == 1)
		sum++;
	if (check_valide_value(objects, objects->map[i + 1][j + 1]) == 1)
		sum++;
	if (sum == 8)
		return (1);
	threatment_error(1, "Not valide map!", objects);
	return (-1);
}

void	check_valide_map(t_object_on_scene *objects)
{
	int i;
	int j;

	i = 0;
	j = 0;
	quantity_strings(objects);
	check_vertical_edge(objects);
	while (objects->map[i] != NULL && objects->s_value_from_map.valide_map != -1)
	{
		while (objects->map[i][j] != '\0')
		{
			if (objects->map[i][j] == '0' || objects->map[i][j] == '2' ||
				objects->map[i][j] == 'N' || objects->map[i][j] == 'S' ||
				objects->map[i][j] == 'W' || objects->map[i][j] == 'E')
				// printf("HI %c\n", objects->map[i][j]);
					objects->s_value_from_map.valide_map = check_arround_fill(objects, i, j);
				printf("%d\n", i);
			j++;
		}
		j = 0;
		i++;
	}
	// write(1, "2\n", 2);
}
