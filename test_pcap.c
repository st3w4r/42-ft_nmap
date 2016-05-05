#include <stdio.h>
#include <pcap.h>
#include <netinet/in.h>
#include <netinet/if_ether.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>

//#define SIZE_ETHERNET 14

/* Ethernet addresses are 6 bytes */
//#define ETHER_ADDR_LEN	6

/* Ethernet header */
struct sniff_ethernet {
	u_char ether_dhost[ETHER_ADDR_LEN]; /* Destination host address */
	u_char ether_shost[ETHER_ADDR_LEN]; /* Source host address */
	u_short ether_type; /* IP? ARP? RARP? etc */
};

/* IP header */
struct sniff_ip {
	u_char ip_vhl;		/* version << 4 | header length >> 2 */
	u_char ip_tos;		/* type of service */
	u_short ip_len;		/* total length */
	u_short ip_id;		/* identification */
	u_short ip_off;		/* fragment offset field */
#define IP_RF 0x8000		/* reserved fragment flag */
#define IP_DF 0x4000		/* dont fragment flag */
#define IP_MF 0x2000		/* more fragments flag */
#define IP_OFFMASK 0x1fff	/* mask for fragmenting bits */
	u_char ip_ttl;		/* time to live */
	u_char ip_p;		/* protocol */
	u_short ip_sum;		/* checksum */
	struct in_addr ip_src, ip_dst; /* source and dest address */
};
//#define IP_HL(ip)		(((ip)->ip_vhl) & 0x0f)
//#define IP_V(ip)		(((ip)->ip_vhl) >> 4)

/* TCP header */
typedef u_int tcp_seq;

struct sniff_tcp {
	u_short th_sport;	/* source port */
	u_short th_dport;	/* destination port */
	tcp_seq th_seq;		/* sequence number */
	tcp_seq th_ack;		/* acknowledgement number */
	u_char th_offx2;	/* data offset, rsvd */
#define TH_OFF(th)	(((th)->th_offx2 & 0xf0) >> 4)
	u_char th_flags;
#define TH_FIN 0x01
#define TH_SYN 0x02
#define TH_RST 0x04
#define TH_PUSH 0x08
#define TH_ACK 0x10
#define TH_URG 0x20
#define TH_ECE 0x40
#define TH_CWR 0x80
#define TH_FLAGS (TH_FIN|TH_SYN|TH_RST|TH_ACK|TH_URG|TH_ECE|TH_CWR)
	u_short th_win;		/* window */
	u_short th_sum;		/* checksum */
	u_short th_urp;		/* urgent pointer */
};

#define IP_HL(ip)		(((ip)->ip_v) & 0x0f)
#define IP_V(ip)		(((ip)->ip_v) >> 4)

void capture_packet(u_char *user, const struct pcap_pkthdr *h, const u_char *packet)
{
	const struct ethhdr *ethernet;
	const struct ip *ip;
	//const struct tcphdr *tcp;
	const struct tcphdr *tcp;
	const char *payload;
	u_int size_ip;
	u_int size_tcp;


	ethernet = (struct ethhdr*)(packet);
	printf("Ethernet: %u\n", ethernet->h_proto);

	ip = (struct ip*)(packet + ETH_HLEN);
	
	size_ip = ip->ip_hl * 4;
	if (size_ip < 20) {
		printf("   * Invalid IP header length: %u bytes\n", size_ip);
		return ;
	}
	
	printf("IP SRC sniffed: %s\n", inet_ntoa(ip->ip_src));
	printf("IP DST sniffed: %s\n", inet_ntoa(ip->ip_dst));

	tcp = (struct tcphdr*)(packet + ETH_HLEN + size_ip);
//	printf("TCP size: %u\n", tcp->doff);
//	printf("TCP size: %u\n", TH_OFF(tcp)*4);
//	size_tcp = TH_OFF(tcp)*4;
	size_tcp = tcp->doff * 4;
	if (size_tcp < 20) {
		printf("   * Invalid TCP header length: %u bytes\n", size_tcp);
		return ;
	}
	payload = (u_char *)(packet + ETH_HLEN + size_ip + size_tcp);
	printf("TCP SRC port: %u\n", ntohs(tcp->source));
	printf("TCP DST port: %u\n", ntohs(tcp->dest));
//	printf("FLAGS: %u\n", tcp->th_flags);
	printf("FLAGS:\n");
	
	(tcp->fin & 0x01) ? printf("FIN on\n") : printf("FIN off\n");
	(tcp->syn & 0x1) ? printf("SYN on\n") : printf("SYN off\n");
	(tcp->rst & 0x1) ? printf("RST on\n") : printf("RST off\n");
	(tcp->psh & 0x1) ? printf("PUSH on\n") : printf("PUSH off\n");
	(tcp->ack & 0x1) ? printf("ACK on\n") : printf("ACK off\n");
	(tcp->urg & 0x1) ? printf("URG on\n") : printf("URG off\n");
//	(tcp->ece & TH_ECE) ? printf("ECE on\n") : printf("ECE off\n");
//	(tcp->th_flags & TH_CWR) ? printf("CWR on\n") : printf("CWR off\n");

}
/*
void capture_packet(u_char *user, const struct pcap_pkthdr *h, const u_char *packet)
{
	
	const struct sniff_ethernet *ethernet;
	const struct sniff_ip *ip;
	const struct sniff_tcp *tcp;
	const char *payload;
	u_int size_ip;
	u_int size_tcp;


	ethernet = (struct sniff_ethernet*)(packet);
	printf("Ethernet: %u\n", ethernet->ether_type);

	ip = (struct sniff_ip*)(packet + SIZE_ETHERNET);
	size_ip = IP_HL(ip)*4;
	if (size_ip < 20) {
		printf("   * Invalid IP header length: %u bytes\n", size_ip);
		return ;
	}
	printf("IP SRC sniffed: %s\n", inet_ntoa(ip->ip_src));
	printf("IP DST sniffed: %s\n", inet_ntoa(ip->ip_dst));

	tcp = (struct sniff_tcp*)(packet + SIZE_ETHERNET + size_ip);
	size_tcp = TH_OFF(tcp)*4;
	if (size_tcp < 20) {
		printf("   * Invalid TCP header length: %u bytes\n", size_tcp);
		return ;
	}
	payload = (u_char *)(packet + SIZE_ETHERNET + size_ip + size_tcp);
	printf("TCP SRC port: %u\n", ntohs(tcp->th_sport));
	printf("TCP DST port: %u\n", ntohs(tcp->th_dport));
	printf("FLAGS: %u\n", tcp->th_flags);
	
	(tcp->th_flags & TH_FIN) ? printf("FIN on\n") : printf("FIN off\n");
	(tcp->th_flags & TH_SYN) ? printf("SYN on\n") : printf("SYN off\n");
	(tcp->th_flags & TH_RST) ? printf("RST on\n") : printf("RST off\n");
	(tcp->th_flags & TH_PUSH) ? printf("PUSH on\n") : printf("PUSH off\n");
	(tcp->th_flags & TH_ACK) ? printf("ACK on\n") : printf("ACK off\n");
	(tcp->th_flags & TH_URG) ? printf("URG on\n") : printf("URG off\n");
	(tcp->th_flags & TH_ECE) ? printf("ECE on\n") : printf("ECE off\n");
	(tcp->th_flags & TH_CWR) ? printf("CWR on\n") : printf("CWR off\n");
}
*/
int main(int argc, char *argv[])
{
	char dev[] = "eth0";
	char errbuf[PCAP_ERRBUF_SIZE];
	pcap_t *handle;
	struct bpf_program fp;
	char filter_exp[] = "tcp";
	bpf_u_int32 mask;
	bpf_u_int32 net;
	struct pcap_pkthdr header;
	const u_char *packet;

/*
	const struct sniff_ethernet *ethernet;
	const struct sniff_ip *ip;
	const struct sniff_tcp *tcp;
	const char *payload;

	u_int size_ip;
	u_int size_tcp;
*/

	/*
	   dev = pcap_lookupdev(errbuf);
	   if (dev == NULL) {
	   fprintf(stderr, "Couldn't find default device: %s\n", errbuf);
	   return(2);
	   }
	   printf("Device: %s\n", dev);
	   */
	if (pcap_lookupnet(dev, &net, &mask, errbuf) == -1)
	{
		fprintf(stderr, "Can't get netmask: %s:%s\n", dev, errbuf);
		net = 0;
		mask = 0;
	}

	handle = pcap_open_live(dev, BUFSIZ, 1, 10000, errbuf);
	if (handle == NULL)
	{
		fprintf(stderr, "Couldn't open device: %s:%s\n", dev, errbuf);
		return (2);
	}

	if (pcap_compile(handle, &fp, filter_exp, 1, net) == -1)
	{
		fprintf(stderr, "Couldn't compile filter: %s:%s\n", filter_exp, pcap_geterr(handle));
		return (2);
	}

	if (pcap_setfilter(handle, &fp) == -1)
	{
		fprintf(stderr, "Couldn't set filter: %s:%s\n", filter_exp, pcap_geterr(handle));
		return (2);
	}
	
	while (42)
		pcap_dispatch(handle, 100, capture_packet, NULL);

//	packet = pcap_next(handle, &header);
//	printf("Packet: %s\n", packet);
//	printf("Packet len: %d\n", header.len);

/*
	ethernet = (struct sniff_ethernet*)(packet);
	ip = (struct sniff_ip*)(packet + SIZE_ETHERNET);
	size_ip = IP_HL(ip)*4;
	if (size_ip < 20) {
		printf("   * Invalid IP header length: %u bytes\n", size_ip);
		return 1;
	}
	tcp = (struct sniff_tcp*)(packet + SIZE_ETHERNET + size_ip);
	size_tcp = TH_OFF(tcp)*4;
	if (size_tcp < 20) {
		printf("   * Invalid TCP header length: %u bytes\n", size_tcp);
		return 1;
	}
	payload = (u_char *)(packet + SIZE_ETHERNET + size_ip + size_tcp);
*/
	
	/*
	   ethernet = (struct sniff_ethernet *)packet;
	   printf("Ethernet: %s\n", ethernet->ether_dhost);
	   ip = (struct sniff_ip *)(packet + SIZE_ETHERNET);
	   size_ip = IP_HL(ip) * 4;

	   tcp = (struct sniff_tcp *)(packet + SIZE_ETHERNET + size_ip);
	   size_tcp = TH_OFF(tcp) * 4;

	   payload = (char *)(packet + SIZE_ETHERNET + size_ip + size_tcp);

	   printf("IP sniffed: %u\n", ip->ip_src.s_addr);
	   */
	pcap_close(handle);
	return(0);
}
