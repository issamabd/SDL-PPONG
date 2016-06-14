#ifndef NET_H
#define NET_H

#define closesocket(s) close(s)

int establish_connection(char *ip, int port);
int net(void * data); 

#endif // NET_H

