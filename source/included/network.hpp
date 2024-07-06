#include <string>
using namespace std;

extern bool initialized_network;
extern bool ping_successfull;
extern bool got_device_ip;

namespace NETWORK_FUNCTIONS{
    extern void initialize_network();
    extern void exit_network();
    extern void network_ping(const char* ip_address, const char* port);
    extern std::string retrieve_ip_address_alternative();
}