/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expandtest.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahamoun <lahamoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 07:25:46 by lahamoun          #+#    #+#             */
/*   Updated: 2023/06/08 07:58:30 by lahamoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*replace_var_wrongname(char *tok, int *i)
{
	
	char	*tmp = ft_substr(tok, *i + 2, ft_strlen(tok) - *i - 2);
	char	*new_tok = ft_strjoin_char(ft_substr(tok, 0, *i), tmp, ' ');
	free(tok);
	free(tmp);
	*i = ft_strlen(new_tok);
	return (new_tok);
}

char	*replace_var_exitcode(char *tok, int *i)
{
	int len = ft_strlen(tok);
	char	*tmp = ft_substr(tok, *i + 2, len - (*i + 2));
	char	*itoa_exitcode = ft_itoa(exit_status);
	char	*new_tok = ft_strjoin_many(3, ft_substr(tok, 0, *i), itoa_exitcode, tmp);
	free(tok);
	free(tmp);
	free(itoa_exitcode);
	*i = ft_strlen(new_tok);
	return (new_tok);
}

static char	*replace_var(char *token, int *i, t_env *env)
{
	t_env	*search;
	char	*tmp;
	char	*tmp2;
	char	*var_name;
	int		end_var_name;

	end_var_name = (*i) + 1;
	while ((token[end_var_name] && ft_isalnum(token[end_var_name])) || (token[end_var_name] && token[end_var_name] == '_'))
		end_var_name++;
	var_name = ft_substr(token, (*i) + 1, end_var_name - (*i) - 1);
	search = ft_list_search(env, var_name);
	tmp = ft_substr(token, 0, *i);
	if (search && search->value)
		tmp2 = ft_strjoin(tmp, search->value);
	else
		tmp2 = ft_strjoin(tmp, "");
	free (tmp);
	tmp = ft_substr(token, end_var_name, 1000);
	free (token);
	token = ft_strjoin(tmp2, tmp);
	*i = ft_strlen(tmp2);
    free(tmp);
    free(tmp2);
    free(var_name);
	return (token);
}

static char	*apply_expansion_bis(char *tok, int *i, int state, t_env *env)
{
	if ((tok[*i] == '$' && state != 1 && ft_isalpha(tok[*i + 1]))
		|| (tok[*i] == '$' && state != 1 && tok[*i + 1] == '_'))
	{
		tok = replace_var(tok, i, env);
		if (tok[*i] == '$' || tok[*i] == '"' || tok[*i] == '\'')
			*i -= 1;
		else if (tok[*i] == 0)
			*i = -2;
	}
	else if (tok[*i] == '$' && state != 1)
	{
		tok = replace_var_wrongname(tok, i);
		if (tok[*i] == '$' || tok[*i] == '"' || tok[*i] == '\'')
			*i -= 1;
		else if (tok[*i] == 0)
			*i = -2;
	}
	return (tok);
}

static char	*apply_expansion(char *tok, t_env *env)
{
	int		i;
	int		state;

	i = 0;
	state = 0;
	while (i != -1 && tok[i])
	{
		change_value_state(&state, tok[i]);
		if (tok[i] == '$' && state != 1 && tok[i + 1] == '?')
		{
			tok = replace_var_exitcode(tok, &i);
			if (tok[i] == '$' || tok[i] == '"' || tok[i] == '\'')
				continue ;
			else if (tok[i] == 0)
				break ;
		}
		else if (tok[i] == '$' && state != 1 && (tok[i + 1] == ' '
				|| tok[i + 1] == '\'' || tok[i + 1] == '"' || tok[i + 1] == '$'
				|| !tok[i + 1]))
		;
		else
			tok = apply_expansion_bis(tok, &i, state, env);
		i++;
	}
	return (tok);
}


void	expand_env_vars(char **cmd, int *tokens, t_env *env)
{
	int	i;
	int	j;

	i = 0;
	while (cmd[i])
	{
		if (ft_strchr(cmd[i], '$'))
			cmd[i] = apply_expansion(cmd[i], env);
		j = 0;
		while (cmd[i][j])
			if (cmd[i][j] != ' ' || !(cmd[i][j] >= 9 && cmd[i][j] <= 13))
				break ;
		if (!cmd[i][j])
			tokens[i] = NULL_TOKEN;
		i++;
	}
}
