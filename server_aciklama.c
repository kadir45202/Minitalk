/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcetin <kcetin@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 12:00:04 by kcetin            #+#    #+#             */
/*   Updated: 2022/03/02 12:20:03 by kcetin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	sig_usr(int sig)
{
/*
static kullanmamızın nedeni sürekli yeni veri geldiği için
ve fonksiyon kendini sürekli sıfırladığı için sonraki sefer
bu veriyi kaybetmemesi ve üzerine yazması.
*/
	static char	str = 0;
	static int	get_byte = 0;

	if (sig == SIGUSR1)
	/*
	or kapısı kullanarak gelen veri eğer 1 ise
	static str'nin bitine 0 veriyoruz
	*/
		str = str | 1;
	/*eğer 8 bit bize ulaşırsa char değerimizi ekrana basıyoruz
	++getbyte kullanmamızın sebebi eğer get_byte++ yazarsak bu değeri arttırmıyor*/
	if (++get_byte == 8)
	{
		get_byte = 0;
		ft_printf("%c", str);
		str = 0;
	}
	/*eğer bize gelen değer 1 değilse bir bit öteliyor
	ötelenen değere default olarak 0 verilir*/
	else
		str <<= 1;
}

int	main(void)
{
/*
ft_printf ile serverimizin pid numarasını ekrana yazdırıyoruz
bunu da getpid fonksiyonunu kullarak yapıyoruz
getpid fonksiyonu çalıştığı işlemin pid numarasını verir
*/
	ft_printf("pid = %d\n", getpid());
	signal(SIGUSR1, sig_usr);
	/*signal fonksiyonuları program bitmediği sürece sürekli çalışır ve kanalları dinler*/
	signal(SIGUSR2, sig_usr);
	/*programın bitmemesi için sürekli pause verip bekletiyoruz*/
	while (1)
	{
		pause();
	}
	return (0);
}
