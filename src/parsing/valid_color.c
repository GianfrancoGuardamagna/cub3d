#include "../../cub3d.h"

int	valid_rgb_format(char *line)
{
	int	i;

	if (count_commas(line) != 2)
	{
		ft_fprintf(2, "Error: No valid data ceiling or floor\n");
		return (1);
	}
	i = 0;
	while (line[i])
	{
		if (!ft_isdigit(line[i]) && line[i] != ',' && !ft_isspace(line[i]))
		{
			ft_fprintf(2, "Error: Invalid character in color\n");
			return (1);
		}
		else
			i++;
	}
	return (0);
}

int	extract_color_numbers(char *line, uint32_t *dest_color)
{
	char	**rgb;
	int		r;
	int		g;
	int		b;

	if (valid_rgb_format(line) == 1)
		return (1);
	rgb = ft_split(line, ',');
	if (!rgb)
	{
		ft_fprintf(2, "Error allocated memory\n");
		return (1);
	}
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	ft_free_matrix(rgb);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		ft_fprintf(2, "Error: invalid color\n");
		return (1);
	}
	*dest_color = ((r << 24) | (g << 16) | (b << 8) | 255);
	return (0);
}
