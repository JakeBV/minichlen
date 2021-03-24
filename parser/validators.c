#include "minishell.h"
#include "parseader.h"

int	twinks_validator(char *line)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(line);
	while (line[i] != '\0')
	{
		if ((line[i] == '|' && line[i + 1] == '|') || (line[i] == ';' && \
			line[i + 1] == ';') || (i + 2 <= len && line[i] == '>' && \
			line[i + 1] == '>' && line[i + 2] == '>') || (line[i] == '<' \
			&& line[i + 1] == '<'))
		{
			if ((i > 0 && line[i - 1] != '\\') || (i == 0 && i + 1 == 1))
				display_error("minishell", "syntax error", "unexpected token");
			return (-1);
		}
		i++;
	}
	return (0);
}

int quotes_validator(char *line)
{
	int		i;
	int		double_quotes;
	int		single_quotes;

	i = 0;
	double_quotes = 0;
	single_quotes = 0;
	while (line[i] != '\0')
	{
		if ((line[i] == '\'' && i > 0 && line[i - 1] != '\\') || \
				(!i && line[i] == '\''))
			single_quotes++;
		if ((line[i] == '"' && i > 0 && line[i - 1] != '\\') || \
				(!i && line[i] == '"'))
			double_quotes++;
		i++;
	}
	if (single_quotes % 2 || double_quotes % 2)
	{
		display_error("minishell", "syntax error", "unexpected token");
		return (-1);
	}
	return (0);
}

int ultimate_validator(char *line)
{
	int ret;

	ret = quotes_validator(line);
	if (ret == -1)
		return (-1);
	ret = twinks_validator(line);
	if (ret == -1)
		return (-1);
	return (0);
}