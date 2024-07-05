

namespace NETWORK_FUNCTIONS{
    extern void initialize_network();
    extern void exit_network();
    extern void network_ping(const char* ip_address, const char* port);
    extern char *get_local_ip();
}