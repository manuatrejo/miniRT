#include "miniRT.h"

int	main(int ac, char **av)
{
	t_scene	*scene;

	if (ac != 2)
		return (ft_putendl_fd("Error\nIncorrect args number\n", 2), 0);
	scene = parse_file(av[1]);
}