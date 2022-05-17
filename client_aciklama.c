/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcetin <kcetin@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 11:59:51 by kcetin            #+#    #+#             */
/*   Updated: 2022/03/02 12:11:19 by kcetin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_kill(int pid, char *str)
{
	int		i;
	char	c;
/* str boyunca işlem devam ediyor */
	while (*str)
	{
		i = 8;
		/*8 bitlik bir işlem yapacağımız için i değerine 8 veriyoruz*/
		c = *str++;
		/*
		c değerimiz ise mesajın char değerlerini tutuyor
		örnek:
		string = "selam"
		c = 's'
		*/
		while (i--)
		{
			/*eğer c'nin i. biti ötelenip ve işlemi ile 1 olursa
			1 & 1 = 1
			1 & 0 = 0
			0 & 0 = 1
			SIGUSR1 ile 1 değerini gönder diyoruz
			değilse SIGUSR2 ile 0 döndürüyor*/
			if (c >> i & 1)
			/*kill fonksiyonu verilen pid numarasına 
			SIGUSR ile 0 veya 1 gönderiyor*/
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			/*araya 50 mikrosaniye koyuyoruz ki sinyaller çakışmasın*/
			usleep(50);
			/*bunu her harfe uyguladığımız zaman bütün stringi server'e göndermiş oluyoruz*/
		}
	}
	/*
	bu kısımda string sonunu belli etmek için \0 yolluyoruz
	00000000 = '\0'
	*/
	i = 8;
	while (i--)
	{
		kill(pid, SIGUSR2);
		usleep(50);
	}
}
/*
main'den başlıyoruz
eğer 3 argüman girilmezse if'e giriyor ve hata verip çıkıyor
girilmesi gereken 3 değer var
1- ./client
2-  pid numarası
3-  gönderilecek mesaj
girilen pid numarasını int olarak okunmasını sağlıyoruz
yukarıdaki fonksiyonumuza pid numarasını ve mesajı gönderiyoruz.
alttaki \n ise onun ascii değerini bulamadık o yüzden direkt onu gönderdik
alt satıra geçmesi senin terihin dokümanda yazmıyor
*/
int	main(int argc, char **argv)
{
	if (argc != 3)
	{
		ft_printf("en az iki arguman girmelisiniz\n");
		return (0);
	}
	ft_kill(ft_atoi(argv[1]), argv[2]);
	ft_kill(ft_atoi(argv[1]), "\n");
}
