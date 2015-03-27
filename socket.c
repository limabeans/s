#include <stdio.h>
#include <stdint.h>

struct sockaddr {
  unsigned short sa_family; //address family, AF_xxx -- AF_INET (IPv4) or AF_INET6 (IPv6)
  char sa_data[14]; //14 bytes of protocol address
  //destination address and port number for the socket
};


//(IPv4 only) use struct sockaddr_in6 for IPv6x

struct in_addr {
  uint32_t s_addr; //32-bit int (4 bytes) 
  //Network Byte order
};

struct sockaddr_in {
  short int sin_family; //address family , AF_INET
  unsigned short int sin_port; //port number
  struct in_addr sin_addr; //Internet address
  unsigned char sin_zero[8]; //same size as struct sockaddr
  
};


//IPv6

struct in6_addr {
  unsigned char s6_addr[16]; //ipv6 address
};

struct sockaddr_in6 {
  uint16_t sin6_family; //address family, AF_INET6
  uint16_t sin6_port; //port number, Network Byte Order
  uint32_t sin6_flowinfo; //IPv6 flow information
  struct in6_addr sin6_addr; //ipv6 address
  uint32_t sin6_scope_id; //scope id
};


struct sockaddr_storage {
  sa_family_t ss_family; //address family
  
  //all this is padding, implementation specific, ignore it:
  char __ss_pad1[_SS_PAD1SIZE];
  int64_t __ss_align;
  char __ss_pad2[_SS_PAD2SIZE];
};


//socket descriptor is just an int

struct addrinfo {
  int ai_flags; //AI_PASSIVE, AI_CANONNAME, etc.
  int ai_family; //AF_INET, AF_INET6, AF_UNSPEC. Here you are forcing IPv4 or IPv6 or unspecified
  int ai_socktype; //SOCK_STREAM, SOCK_DGRAM
  int ai_protocol; //use 0 for "any"
  size_t ai_addrlen; //size of ai_addr in bytes
  struct sockaddr *ai_addr; //struct sockaddr _in or _in6. This is where the details of IP structure is
  char *ai_canonname; //full canonical hostname
  struct addrinfo *ai_next; //This is a linked list!
};
//getaddrinfo() to fill up the struct addrinfo

int main() {
  struct sockaddr_in sa; //ipv4
  struct sockaddr_in6 sa6; //ipv6
  //inet_pton converts ip address to structs
  inet_pton(AF_INET, "192.0.2.1", &(sa.sin_addr));
  inet_pton(AF_INET6, "2001:db8:63b3:1::3490", &(sa6.sin6_addr));
  return 0;
}

