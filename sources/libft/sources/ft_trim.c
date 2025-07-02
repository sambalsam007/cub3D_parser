#include "../libft.h"

char	*ft_trim(const char *str)
{
	int		start;
	int		end;
	int		len;
	char	*result;

	if (!str)
		return (NULL);
	// Find start of non-whitespace
	start = 0;
	while (str[start] && ft_isspace(str[start]))
		start++;
	// Find end of non-whitespace
	end = ft_strlen(str) - 1;
	while (end >= start && ft_isspace(str[end]))
		end--;
	// Calculate length of trimmed string
	len = end - start + 1;
	// Allocate and copy
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	ft_strlcpy(result, str + start, len + 1);
	return (result);
}
