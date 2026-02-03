#include "CanClient.h"
#include "CanServer.h"

int main() {
    CanServer server;
    CanClient client(server);

    client.requestandPrint(0x100);
    client.requestandPrint(0x200);
    client.requestandPrint(0x300);  // Unsupported CAN ID example

    return 0;
}