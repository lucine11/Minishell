#include "../inc/minishell.h"

// int	main(int argc, char **argv, char **envp)
// {
// 	char	*line;


// 	line = readline("say something: ");
// 	// ft_printf("%s\n", line);
	
// }

int	main(int argc, char **argv, char **envp)
{
	t_command	command_string;

	(void)argc;
	(void)argv;
	(void)envp;

	command_string = (t_command){0};
	if (parsing(&command_string))
		return (1);
	// print_overview(command_string);
}