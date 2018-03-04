/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/03 19:51:07 by asyed             #+#    #+#             */
/*   Updated: 2018/03/03 20:18:29 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/if_ether.h>
#include <netinet/ip_icmp.h>
#include <unistd.h>

// Xor swap
int	main(void)
{
	void		*packet;
	struct icmp	*icmppacket;
	struct ip	*ipreply;
	char		*str;
	char test[] = "\x00\x00\x01\x00\x00\x01\x00\x10\x94\x00\x00\x02\x08\x00\x45\x00\x00\x3D\x00\x0E\x00\x00\x0A\x11\x2F\x4A\xC0\x55\x01\x02\xC0\x00\x00\x01\x04\x00\x0E\xC8\x00\x29\x72\x31\x20\x44\x05\x21\x00\x00\x00\x01\x00\x00\x00\x00\x00\x0F\x42\x40\x00\x0F\x42\x40\x00\x00\x00\x00\x01\x09\x02\x73\x65\x63\x72\x65\x74\xFA\x7B\x79\x1C";

	ipreply = (struct ip *)(test + sizeof(struct ether_header));
	str = inet_ntoa(ipreply->ip_src);
	printf("Before IP_SRC: %s", str);
	str = inet_ntoa(ipreply->ip_dst);
	printf(" IP_DST: %s\n", str);

	ipreply->ip_src.s_addr = (ipreply->ip_src.s_addr ^ ipreply->ip_dst.s_addr);
	ipreply->ip_dst.s_addr = (ipreply->ip_src.s_addr ^ ipreply->ip_dst.s_addr);
	ipreply->ip_src.s_addr = (ipreply->ip_src.s_addr ^ ipreply->ip_dst.s_addr);

	str = inet_ntoa(ipreply->ip_src);
	printf("After IP_SRC: %s", str);
	str = inet_ntoa(ipreply->ip_dst);
	printf(" IP_DST: %s\n", str);
}