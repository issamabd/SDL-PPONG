#ifndef NET_H
#define NET_H

#define closesocket(s) close(s)

int establish_connection();
int net(void * data);

void initialise_FIFO ();
void free_FIFO();

#endif // NET_H
