#include "cub3d.h"

int check_extension(char *str)
{
	int		ext;
	char	*aux;

	ext = ft_strlen(str);
	if (ext <= 4)
	{
		ft_fprintf(2, "Error: Invalid name map\n ");
		return (1);
	}
	aux = ft_strrchr(str, ".");
	if (aux == NULL)
		return (1);
	if (ft_strncmp(aux, ".cub", 4) != 0)
	{
		ft_fprintf(2, "Error: Invalid file extension. Have to be .cub\n");
		return (1);
	}
	return (0);
}
