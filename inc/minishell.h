#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
//# include <readline/readline.h>

typedef struct s_simple_command
{
	int	no_avail_args;
	int	no_args;
	char **arguments;
	
}				t_simple_command;

typedef struct s_command
{
	int						no_avail_commands;
	int						no_commands;
	t_simple_command		**simple_commands;
	char					*outfile;
	char					*infile;
	char					*errfile;
	int						background;
	t_simple_command	*current_s_command;
}				t_command;

#endif
