#ifndef PORT_H
#define PORT_H

typedef struct {
	int LRUD, offset;
} Port;

Port *port_create(int lrud, int offset);
void port_destroy(Port *port);

#endif
