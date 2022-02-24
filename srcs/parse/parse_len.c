#include "../../incls/mini_rt.h"

int	get_int_len(char *line, int i)
{
	int int_len;

	int_len = 0;
	if (ft_isdigit(line[i]))
	{
		while (ft_isdigit(line[i]))
		{
			i++;
			int_len++;
		}
	}
	else
	{
		printf("ERROR GET INT LEN\n");
		return (-100);
	}
	return (int_len);
}

int	get_float_len(char *line, int i)
{
	int float_len;
	int dot;
	
	dot = 0;
	float_len = 0;
	if (line[i] == '-')
	{
		i++;
		float_len++;
	}
	if (ft_isdigit(line[i]))
	{
		while (ft_isdigit(line[i]) || line[i] == '.')
		{
			if (line[i] == '.')
				dot++;
			i++;
			float_len++;
		}
	}
	else
		return (-1);
	if (dot > 1)
		return (-1);
	return(float_len);
}
