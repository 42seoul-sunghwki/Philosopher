/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 13:38:21 by sunghwki          #+#    #+#             */
/*   Updated: 2024/03/24 15:36:21 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	check_atol(const char *input, long *output)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (!ft_isdigit(input[i++]))
		{
			printf("NOT INTEGER!\n");
			return (FUN_FAIL);
		}
	}
	*output = ft_atol(input);
	if (*output < 0)
	{
		printf("NOT POSITIVE NUMBER!\n");
		return (FUN_FAIL);
	}
	if (*output > INT_MAX || i > 12)
	{
		printf("INVALID INT SIZE!\n");
		return (FUN_FAIL);
	}
	return (FUN_SUC);
}

int	ft_init_info(t_info *info, int argc, char **argv)
{
	int		i;
	long	tmp[6];

	if (argc < 5 || argc > 6)
	{
		printf("WRONG NUMBER OF ARGUMENTS!\n");
		return (FUN_FAIL);
	}
	i = 1;
	while (i < argc)
	{
		if (check_atol(argv[i], &tmp[i]))
			return (FUN_FAIL);
		i++;
	}
	info->philo_num = tmp[1];
	info->time_to_die = tmp[2] * THOUSAND;
	info->time_to_eat = tmp[3] * THOUSAND;
	info->time_to_sleep = tmp[4] * THOUSAND;
	if (argc == 6)
		info->num_must_eat = tmp[5];
	else
		info->num_must_eat = -1;
	return (0);
}

t_sem	*ft_init_sem(t_info *info)
{
	t_sem	*sem;

	sem = (t_sem *)malloc(sizeof(t_sem));
	if (!sem)
		return (NULL);
	sem_unlink(FORK);
	sem_unlink(PRINT);
	sem_unlink(COUNT);
	sem_unlink(FLAG);
	sem_unlink(BE_FORK);
	sem->fork = sem_open(FORK, O_CREAT, 0644, info->philo_num);
	sem->print = sem_open(PRINT, O_CREAT, 0644, 1);
	sem->flag = sem_open(FLAG, O_CREAT, 0644, 1);
	sem->be_fork = sem_open(BE_FORK, O_CREAT, 0644, 1);
	if (info->num_must_eat != -1)
		sem->count = sem_open(COUNT, O_CREAT, 0644, info->num_must_eat);
	else
		sem->count = NULL;
	if (sem->fork == SEM_FAILED || sem->print == SEM_FAILED
		|| sem->count == SEM_FAILED || sem->flag == SEM_FAILED)
	{
		free(sem);
		return (NULL);
	}
	return (sem);
}

void	ft_unlink_sem(t_sem **sem)
{
	sem_close((*sem)->fork);
	sem_close((*sem)->print);
	sem_close((*sem)->count);
	sem_close((*sem)->flag);
	sem_close((*sem)->be_fork);
	free(*sem);
	sem_unlink(FORK);
	sem_unlink(PRINT);
	sem_unlink(COUNT);
	sem_unlink(FLAG);
	sem_unlink(BE_FORK);
}
