#include "server.hpp"

int Server::socketfd = 0;
char Server::buffer[RECV_BUFF_SIZE] = {0};

void Server::create(const char *address, uint16_t port) 
{
    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) {
        perror("Socket error: ");
        std::cout << "Socket creation failed.\n";
        exit(EXIT_FAILURE);
    }
    int enable = 1;
    if (setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0) {
        perror("Socket error: ");
        std::cout << "setsockopt(SO_REUSEADDR) failed.\n";
        exit(EXIT_FAILURE);
    }
    //uint32_t ipaddr;
    //inet_pton(AF_INET, address, &ipaddr);
    sockaddr_in host_addr = {0};
    host_addr.sin_family = AF_INET;
    host_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    host_addr.sin_port = htons(7777);

    if (bind(socketfd, reinterpret_cast<sockaddr*>(&host_addr), sizeof(sockaddr_in)) == -1) {
        perror("bind");
        std::cout << "IP and port binding failed.\n";
        exit(EXIT_FAILURE);
    }

}

void Server::remove()
{
    sleep(1);
    close(socketfd);
}

void Server::listen()
{
    if ( (::listen(socketfd, 1)) == -1 ) {
        perror("listen");
        std::cout << "Listening failed.\n";
        exit(EXIT_FAILURE);
    }
}

int Server::accept()
{
    return ::accept(socketfd, NULL, NULL);
}

std::string Server::receive(int clientid)
{
    ssize_t len = recv(clientid, buffer, sizeof(buffer), 0);
    return std::string(buffer, len);
}

void Server::send(int clientid, std::string response)
{
    ::send(clientid, response.c_str(), response.size(), 0);
}
void Server::send(int clientid,const std::vector<uint8_t>& response)
{
  long len = response.size();
  uint8_t* buffer = new uint8_t[len];
  for(int i = 0;i < len;i++)
    buffer[i] = response.at(i);
  ::send(clientid,buffer,len,0);
  delete buffer;
}
void Server::send(int clientid, uint8_t* response,long responseLength)
{
    ::send(clientid, response, responseLength, 0);
}

