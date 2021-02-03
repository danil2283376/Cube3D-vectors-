/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_file_cub.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 20:19:20 by scolen            #+#    #+#             */
/*   Updated: 2021/02/03 21:01:21 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3D.h"

void	validate_save(char *line, t_object_on_scene *objects)
{
	if (line[0] != '-' || line[1] != '-' ||
		line[2] != 's' || line[3] != 'a' ||
		line[4] != 'v' || line[5] != 'e' || line[6] != '\0')
			threatment_error(1, "The correct 2 argument is: --save", objects);
}

void validate_arguments(char *line, t_object_on_scene *objects, int argc, char **argv)
{
	int i;

	i = 0;
	if (line == NULL)
		threatment_error(1, "Few arguments!", objects);
	while (line[i] != '.' && line[i] != '\0')
		i++;
	printf("file: %s\n", &line[i]);
	if (line[i] == '.')
	{
		if (line[i + 1] != 'c' || line[i + 2] != 'u' ||
			line[i + 3] != 'b' || line[i + 4] != '\0')
				threatment_error(1, "Incorrect file!", objects);
		if (argc == 3)
			validate_save(argv[2], objects);
		if (argc > 3)
			threatment_error(1, "Many arguments!", objects);
	}
	else
		threatment_error(1, "File not cube!", objects);
}
