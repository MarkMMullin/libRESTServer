#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include <string>
#include <unordered_map>
#include <stdint.h>

#include "constants.hpp"
#include "html_file.hpp"
#include "request.hpp"



class Response {
public:
    enum type {
        OK,
        BAD_REQUEST,
        UNAUTHORIZED,
        NOT_FOUND,
        INTERNAL_SERVER_ERROR
    };

    static const char *type_str[];

  static std::vector<uint8_t> generate_response(const Html_file &file, Response::type res_type);
};

#endif /* end of include guard: RESPONSE_HPP */
