#ifndef NET_H
#define NET_H

#define closesocket(s) close(s)

int establish_connection();
int net(void * data); 

#endif
