#include "game/port.h"
#include <stdlib.h>

Port *port_create(int lrud, int offset) {
	Port *port = malloc(sizeof(Port));

	port->LRUD = lrud;
	port->offset = offset;
	
	return port;
}

void port_destroy(Port *port) {
	if (port == NULL)
		return;

	free(port);
}
