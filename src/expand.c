/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahamoun < lahamoun@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 02:17:00 by lahamoun          #+#    #+#             */
/*   Updated: 2023/05/30 17:06:47 by lahamoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*replace_var(char *token, int *start_idx, t_env *env)
{
	t_env	*env_var;
	char	*prefix;
	char	*value;
	char	*suffix;
	char	*name;
	int		end_var_name = *start_idx + 1;

	while ((token[end_var_name] && ft_isalnum(token[end_var_name])) || (token[end_var_name] && token[end_var_name] == '_'))
		end_var_name++;

	name = ft_substr(token, *start_idx + 1, end_var_name - *start_idx - 1);
	env_var = ft_list_search(env, name);
	prefix = ft_substr(token, 0, *start_idx);
	
	if (env_var && env_var->value) 
	{
		value = ft_strdup(env_var->value);
	} 
	else 
	{
		value = ft_strdup("");
	}
	suffix = ft_substr(token, end_var_name, 1000);
	free(token);

	token = ft_strjoin_many(3, prefix, value, suffix);
	*start_idx = ft_strlen(prefix) + ft_strlen(value);

	free(prefix);
	free(value);
	free(suffix);
	free(name);
	
	return (token);
}

char	*replace_var_wrongname(char *tok, int *i)
{
	char	*tmp = ft_substr(tok, *i + 2, ft_strlen(tok) - *i - 2);
	char	*new_tok = ft_strjoin_char(ft_substr(tok, 0, *i), tmp, ' ');
	free(tok);
	free(tmp);
	*i = ft_strlen(new_tok);
	return new_tok;
}

char	*replace_var_exitcode(char *tok, int *i)
{
	char	*tmp = ft_substr(tok, *i + 2, ft_strlen(tok) - *i - 2);
	char	*itoa_exitcode = ft_itoa(exit_status);
	char	*new_tok = ft_strjoin_many(3, ft_substr(tok, 0, *i), itoa_exitcode, tmp);
	free(tok);
	free(tmp);
	free(itoa_exitcode);
	*i = ft_strlen(new_tok);
	return new_tok;
}

static char	*replace_env_var(char *token, t_env *env)
{
	int		state = 0;
	int		i = 0;
	while (token[i])
	{
		change_value_state(&state, token[i]);
		if (token[i] == '$' && state != 1 && token[i + 1] != 0) 
		{
			if (ft_isalpha(token[i + 1]) || token[i + 1] == '_') 
			{
				token = replace_var(token, &i, env);
				if (!token[i] || token[i] == '$' || token[i] == '"' || token[i] == '\'')
					i--;
			}
			else if (!ft_isalnum(token[i + 1]) && token[i + 1] != '_')
				token = replace_var_wrongname(token, &i);
		}
		i++;
	}
	return (token);
}

void	expand_env_vars(char **cmd, int *tokens, t_env *env)
{
	int i = 0;
	while (cmd[i])
	{
		if (ft_strchr(cmd[i], '$'))
			cmd[i] = replace_env_var(cmd[i], env);
		if (!cmd[i][0] || cmd[i][0] == ' ')
			tokens[i] = NULL_TOKEN;
		i++;
	}
}