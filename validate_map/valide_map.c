#include "../cube3D.h"

int	check_valide_value(t_object_on_scene *objects, char symbol)
{
	(void)objects;
	if (symbol != '1' || symbol != '0' ||
		symbol != '2' || symbol != 'N' ||
		symbol != 'W' || symbol != 'S' ||
		symbol != 'E')
		return (0);
	return (1);
}

int	check_arround_fill(t_object_on_scene *objects, int i, int j)
{
	if (check_valide_value(objects, objects->map[i - 1][j - 1]) == 1)
		return (1);
	if (check_valide_value(objects, objects->map[i - 1][j]) == 1)
		return (1);
	if (check_valide_value(objects, objects->map[i - 1][j + 1]) == 1)
		return (1);
	if (check_valide_value(objects, objects->map[i][j - 1]) == 1)
		return (1);
	if (check_valide_value(objects, objects->map[i][j + 1]) == 1)
		return (1);
	if (check_valide_value(objects, objects->map[i + 1][j - 1]) == 1)
		return (1);
	if (check_valide_value(objects, objects->map[i + 1][j]) == 1)
		return (1);
	if (check_valide_value(objects, objects->map[i + 1][j + 1]) == 1)
		return (1);
	return (-1);
}

void	check_valide_map(t_object_on_scene *objects)
{
	// printf("1");
	int i;
	int j;

	i = 0;
	j = 0;
	while (objects->map[i] != NULL)
	{
		while (objects->map[i][j] != '\0')
		{
			if (objects->map[i][j] == '0' || objects->map[i][j] == '2' ||
				objects->map[i][j] == 'N' || objects->map[i][j] == 'S' ||
				objects->map[i][j] == 'W' || objects->map[i][j] == 'E')
					objects->s_value_from_map.valide_map = check_arround_fill(objects, i, j);
			j++;
		}
		j = 0;
		i++;
	}
}
