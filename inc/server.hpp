#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <cstdio>
#include <stdint.h>

#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <vector>

#include "constants.hpp"

class Server {
public:
    static void create(const char *address, uint16_t port);
    static void listen();
    static int  accept();
    static std::string receive(int clientid);
    static void send(int clientid, std::string response);
  static void send(int clientid,const std::vector<uint8_t>& response);
  static void send(int clientid, uint8_t* response,long responseLength);
    static void remove();

   static inline std::string GetVersion() {
    char vb[32];
    sprintf(vb,"%s-%s:%s:%s.%s",BUILDTYPE,MAJORVER,MINORVER,PATCHVER,BUILDVER);
    return std::string(vb);
  }
private:
    static int socketfd;
    static char buffer[RECV_BUFF_SIZE];
};


#endif /* end of include guard: SERVER_HPP */
