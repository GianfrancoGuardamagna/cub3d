#include "cub3d.h"

unsigned long createRGB(int r, int g, int b)
{
	if(r > 255 || g > 255 || b > 255)
		return 0;
	return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}

void	pixel_put(t_img *img, int x, int y, int color)
{
	int	offset;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return;

	offset = (y * img->line_len) + (x * (img->bpp / 8));
	*(unsigned int *)(img->pixels_ptr + offset) = color;
}

int abs(int n)
{
	if(n > 0)
		return n;
	else
		return n * -1;
}

double calcular_angulo_grados(double x0, double y0, double x1, double y1)
{
	// 1. Calcular la diferencia en los ejes (vector de dirección)
	double delta_y = y1 - y0;
	double delta_x = x1 - x0;

	// 2. Obtener el ángulo en radianes
	// Nota: atan2 siempre recibe 'y' primero y luego 'x'
	double radianes = atan2(delta_y, delta_x);

	// 3. Convertir a grados
	double grados = radianes * (180.0 / M_PI);

	return grados;
}