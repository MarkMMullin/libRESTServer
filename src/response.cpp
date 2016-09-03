#include "response.hpp"

const char *Response::type_str[] = {
    "200 OK\n",
    "400 Bad Request\n",
    "401 Unauthorized\n",
    "404 Not Found\n",
    "500 Internal Server Error\n"
};
/* example response

const char *indexhtml = 
    "HTTP/1.1 200 OK\n"
    "Date: Mon, 23 May 2005 22:38:34 GMT\n"
    "Server: httpserver/0.1.0 (Unix) (Arch linux)\n"
    "Last-Modified: Wed, 08 Jan 2003 23:11:55 GMT\n"
    "ETag: \"3f80f-1b6-3e1cb03b\"\n"
    "Content-Type: text/html; charset=UTF-8\n"
    "Content-Length: 131\n"
    "Accept-Ranges: bytes\n"
    "Connection: close\n"
    "\n"
    "<html>\n"
    "<head>\n"
    "  <title>An Example Page</title>\n"
    "</head>\n"
    "<body>\n"
    "  Hello World, this is a very simple HTML document.\n"
    "</body>\n"
    "</html>\n";
*/

std::vector<uint8_t> Response::generate_response(const Html_file &file, Response::type res_type)
{
    std::string response_str;
    response_str += srv_info::http_version;
    response_str += Response::type_str[res_type];
    response_str += srv_info::server_version;
    response_str += "Cache-Control: no-cache, no-store, must-revalidate";
    response_str += "Pragma: no-cache";
    response_str += "Expires: 0";
    // TODO: response_str += ETag;
    response_str += "Content-Type: " + file.contentType + "\n";
    response_str += "Content-Length: " + std::to_string(file.filesize) + "\n";
    response_str += "Accept-Ranges: bytes\n";
    response_str += "Connection: close\n\n";

    std::vector<uint8_t> response(response_str.begin(), response_str.end());
    response.insert(response.end(), file.content.begin(), file.content.end());
    return response;
}



