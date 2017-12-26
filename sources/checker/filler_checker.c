/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlu <mlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 20:59:44 by mlu               #+#    #+#             */
/*   Updated: 2017/11/28 17:43:16 by mlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

//champely
//abanlin
//carli
//hcao
//grati
//superjeannot

int main()
{
	char *checker;
	char ret[99999];
	int hcao = 0;
	int mlu = 0;
	int i = 0;
	while (i < 5)
	{
		system("./resources/filler_vm -f ./resources/maps/map00 -p1 ./mlu.filler -p2 ./resources/players/hcao.filler");
		checker = read_input(open("./filler.trace", O_RDONLY));
		if (!strcmp(checker, "mlu"))
			mlu++;
		else
			hcao++;
		if (mlu >= 3 || hcao >= 3)
			i = 5;
		else
			i++;
	}
	snprintf(ret, sizeof(char), "MAP00: P1-MLU %i P2-HCAO %i\n", mlu, hcao);
	i = 0;
	mlu = 0;
	hcao = 0;
	while (i < 5)
	{
		system("./resources/filler_vm -f ./resources/maps/map00 -p2 ./mlu.filler -p1 ./resources/players/hcao.filler");
		checker = read_input(open("./filler.trace", O_RDONLY));
		if (!strcmp(checker, "mlu"))
			mlu++;
		else
			hcao++;
		if (mlu >= 3 || hcao >= 3)
			i = 5;
		else
			i++;
	}
	snprintf(ret, sizeof(char), "MAP00: P1-HCAO %i P2-MLU %i\n", hcao, mlu);
	printf("%s\n", ret);
	return (0);
}