#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <errno.h>
#include <stdarg.h>
#include <unistd.h>

#include <fcntl.h>

#include <sys/types.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <3ds.h>

#include <chrono>
#include <thread>


#include <string>
using namespace std;

#include "included/debug.hpp"
#include "included/tello_api.hpp"
#include "included/network.hpp"
#include "included/app.hpp"

namespace NETWORK{
    #define SOC_ALIGN       0x1000
    #define SOC_BUFFERSIZE  0x100000

    static u32* socBuffer = NULL;

    bool network_init(){
        DEBUG::print_to_Screen(colored_text("green", "", "Initializing network\n"), false, GFX_BOTTOM);
        socBuffer = (u32*)memalign(SOC_BUFFERSIZE, SOC_ALIGN);
        Result res = socInit(socBuffer, SOC_BUFFERSIZE);
        if (socBuffer == NULL){
            DEBUG::print_to_Screen(colored_text("red", "", ("Result: " + std::to_string(res) + "\n").c_str()), false, GFX_BOTTOM);
            DEBUG::print_to_Screen(colored_text("red", "", "Failed\n"), false, GFX_BOTTOM);
            DEBUG::print_to_Screen(colored_text("yellow", "", "--------------------------------\n"), false, GFX_BOTTOM);

            return false;
        }
        if (R_FAILED(res)){
            DEBUG::print_to_Screen(colored_text("red", "", ("Result: " + std::to_string(res) + "\n").c_str()), false, GFX_BOTTOM);
            DEBUG::print_to_Screen(colored_text("red", "", "Failed\n"), false, GFX_BOTTOM);
            DEBUG::print_to_Screen(colored_text("yellow", "", "--------------------------------\n"), false, GFX_BOTTOM);

            return false;
        }
        else{
            DEBUG::print_to_Screen(colored_text("green", "", ("Result: " + std::to_string(res) + "\n").c_str()), false, GFX_BOTTOM);
            DEBUG::print_to_Screen(colored_text("green", "", "Successfull\n"), false, GFX_BOTTOM);
            DEBUG::print_to_Screen(colored_text("yellow", "", "--------------------------------\n"), false, GFX_BOTTOM);

            NETWORK_FUNCTIONS::network_ping(tello_ip, tello_port);

            return true;
        }
        
        return R_SUCCEEDED(res);
    }

    void network_exit(){
        DEBUG::print_to_Screen("Exiting network\n", false, GFX_BOTTOM);
        socExit();
        if (socBuffer != NULL){
            DEBUG::print_to_Screen(colored_text("green", "", "Successfull\n"), false, GFX_BOTTOM);
            DEBUG::print_to_Screen(colored_text("yellow", "", "--------------------------------\n"), false, GFX_BOTTOM);
            free(socBuffer);
            socBuffer = NULL;
        }
    }

    bool ping(const char* ip_address, const char* port){
        struct sockaddr_in serverAddr, fromAddr;
        socklen_t fromAddrLen = sizeof(fromAddr);
        int udpSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
        if (udpSocket < 0){
            return false;
        }

        // Set the socket to non-blocking mode
        u32 flags = fcntl(udpSocket, F_GETFL, 0);
        fcntl(udpSocket, F_SETFL, flags | O_NONBLOCK);

        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(static_cast<uint16_t>(atoi(port)));
        serverAddr.sin_addr.s_addr = inet_addr(ip_address);

        const char* ping_message = "ping";
        if (sendto(udpSocket, ping_message, strlen(ping_message), 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0){
            close(udpSocket);
            return false;
        }

        char buffer[1024];
        s64 startTime = osGetTime();
        int received = -1;
        while (osGetTime() - startTime < 2000) { // 2 seconds timeout
            received = recvfrom(udpSocket, buffer, sizeof(buffer), 0, (struct sockaddr*)&fromAddr, &fromAddrLen);
            if (received >= 0) {
                break; // Data received
            }
            svcSleepThread(1000000); // Sleep for 1ms to prevent a busy loop
        }

        if (received < 0) {
            // Timeout or error
            close(udpSocket);
            return false;
        }

        // Optionally, check the content of the response here

        close(udpSocket);
        return true; // Response received
    }
}
//DEBUG::print_to_Screen("--------------------------------\n", false, GFX_BOTTOM);
namespace NETWORK_FUNCTIONS{

    bool network_initialized = false; // Track the initialization status

    void initialize_network(){
        network_initialized = NETWORK::network_init();
    }

    void exit_network(){
        DEBUG::print_to_Screen(colored_text("red", "", "Closing network\n"), false, GFX_BOTTOM);
        DEBUG::print_to_Screen(colored_text("yellow", "", "--------------------------------\n"), false, GFX_BOTTOM);
        NETWORK::network_exit();
        network_initialized = false; // Update status upon exiting
    }

    void network_ping(const char* ip_address, const char* port){
        DEBUG::print_to_Screen(colored_text("green", "", "Attempting ping\n"), false, GFX_BOTTOM);

        auto start = std::chrono::steady_clock::now();
        bool success = false;

        while (true) {
            success = NETWORK::ping(ip_address, port);

            if (success){
                DEBUG::print_to_Screen(colored_text("green", "", "Successfull - pong\n"), false, GFX_BOTTOM);
                DEBUG::print_to_Screen(colored_text("green", "", "Almost ready to fly\n"), false, GFX_BOTTOM);
                DEBUG::print_to_Screen(colored_text("yellow", "", "--------------------------------\n"), false, GFX_BOTTOM);
                break; // Exit loop if ping is successful
            } else {
                auto end = std::chrono::steady_clock::now();
                auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(end - start);
                if (elapsed.count() >= 5) {
                    // If 20 seconds have passed and ping was not successful, print failed message
                    DEBUG::print_to_Screen(colored_text("red", "", "Failed - timeout\n"), false, GFX_BOTTOM);
                    DEBUG::print_to_Screen(colored_text("red", "", "Connect to Tello's WIFI first\n"), false, GFX_BOTTOM);
                    DEBUG::print_to_Screen(colored_text("yellow", "", "--------------------------------\n"), false, GFX_BOTTOM);
                    break;
                }
                // Wait for a short period before trying again to avoid flooding
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
            }
        }
    }

    char *get_local_ip(){
        u32 ip = gethostid();
        char *ip_str = new char[16];
        snprintf(ip_str, 16, "%d.%d.%d.%d", (ip >> 24) & 0xFF, (ip >> 16) & 0xFF, (ip >> 8) & 0xFF, ip & 0xFF);
        return ip_str;
    }
}