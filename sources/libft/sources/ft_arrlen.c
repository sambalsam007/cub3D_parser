#include "../libft.h"

int	ft_arrlen (char **arr)
{
	int	len;

	len = 0;
	if (!arr)
		return (0);
	while(arr[len])
		len++;
	return (len);
}
