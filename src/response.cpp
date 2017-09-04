#include "response.hpp"

const char *Response::type_str[] = {
    "200 OK\n",
    "400 Bad Request\n",
    "401 Unauthorized\n",
    "404 Not Found\n",
    "500 Internal Server Error\n"
};

std::vector<uint8_t> Response::generate_response(const Html_file &file, Response::type res_type)
{
    std::string response_str;
    response_str += srv_info::http_version;
    response_str += Response::type_str[res_type];
    response_str += srv_info::server_version;
    response_str += "Cache-Control: no-cache, no-store, must-revalidate\n";
    response_str += "Pragma: no-cache\n";
    response_str += "Expires: 0\n";
    char etagbody[32];
    sprintf(etagbody,"ETag: \"%s\"\n",file.etag.c_str());
    response_str += etagbody;
    response_str += "Content-Type: " + file.contentType + "\n";
    response_str += "Content-Length: " + std::to_string(file.content.size()) + "\n";
    response_str += "Connection: close\r\n\r\n";

    std::vector<uint8_t> response(response_str.begin(), response_str.end());
    response.insert(response.end(), file.content.begin(), file.content.end());

    // if(response.size() < 1024)
    //   for(int i = 0;i < response.size();i++)
    //	fprintf(stderr,"%c",response[i]);
    return response;
}



