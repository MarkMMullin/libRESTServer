#include "request.hpp"

const char *Request_type_str[] = {
    "GET",
    "HEAD",
    "POST",
    "PUT",
    "DELETE",
    "OPTIONS",
    "TRACE",
    "CONNECT",
    "PATCH",
    "WAT"
};

Request_data Request::handle_request(const std::string &req_str) 
{
    Request_data req_data;
    std::size_t pos = req_str.find_first_of(" ");
    std::string temp_str = req_str.substr(0, pos);
    //fprintf(stderr,"raw request: %s\n",req_str.c_str());
    if (temp_str == "GET") {
        req_data.req_type = Request::type::GET;
    } else if (temp_str == "POST") {
        req_data.req_type = Request::type::POST;
    } else if (temp_str == "PUT") {
        req_data.req_type = Request::type::PUT;
    } else if (temp_str == "DELETE") {
        req_data.req_type = Request::type::DELETE;
    } else if (temp_str == "OPTIONS") {
        req_data.req_type = Request::type::OPTIONS;
    } else if (temp_str == "HEAD") {
        req_data.req_type = Request::type::HEAD;
    } else if (temp_str == "TRACE") {
        req_data.req_type = Request::type::TRACE;
    } else if (temp_str == "CONNECT") {
        req_data.req_type = Request::type::CONNECT;
    } else if (temp_str == "PATCH") {
        req_data.req_type = Request::type::PATCH;
    } else {
        req_data.req_type = Request::type::WAT;
    }

    std::size_t begin_pos = pos + 1;
    pos = req_str.find_first_of(" ", begin_pos);
    temp_str = req_str.substr(begin_pos, pos - begin_pos);
    // decode the url
    char urlBuffer[8192];
    int destlen;
    urldecode(temp_str.c_str(),temp_str.size(),urlBuffer,&destlen);
    //fprintf(stderr,"decoded buffer: %s\n",urlBuffer);
    req_data.url = urlBuffer;
    //fprintf(stderr,"decoded buffer2: %s\n",req_data.url.c_str());

    // see about a payload
    begin_pos = pos + 1;
    pos = req_str.find_first_of("Content-Length:",begin_pos);
    if(pos != std::string::npos) {
      // nb:  this is my system and any payload is deemed to be json
      pos = req_str.find_first_of("{",pos);
      if(pos == std::string::npos)
	return req_data;  // bail now, nothing to see here
      std::string payload = req_str.substr(pos - 1,std::string::npos);
      req_data.data = payload;
    }
    return req_data;

}

char *Request::urlencode(const char *src, const int src_len, char *dest, int *dest_len)
{
	static unsigned char hex_chars[] = "0123456789ABCDEF";
	const unsigned char *pSrc;
	const unsigned char *pEnd;
	char *pDest;

	pDest = dest;
	pEnd = (unsigned char *)src + src_len;
	for (pSrc=(unsigned char *)src; pSrc<pEnd; pSrc++)
	{
		if ((*pSrc >= '0' && *pSrc <= '9') || 
	 	    (*pSrc >= 'a' && *pSrc <= 'z') ||
	 	    (*pSrc >= 'A' && *pSrc <= 'Z') ||
		    (*pSrc == '_' || *pSrc == '-' || *pSrc == '.'))
		{
			*pDest++ = *pSrc;
		}
		else if (*pSrc == ' ')
		{
			*pDest++ = '+';
		}
		else
		{
			*pDest++ = '%';
			*pDest++ = hex_chars[(*pSrc) >> 4];
			*pDest++ = hex_chars[(*pSrc) & 0x0F];
		}
	}

	*pDest = '\0';
	*dest_len = pDest - dest;

	return dest;
}

char *Request::urldecode(const char *src, const int src_len, char *dest, int *dest_len)
{
    (void)urldecode_ex(src, src_len, dest, dest_len);
    *(dest + *dest_len) = '\0';
    return dest;
}

char *Request::urldecode_ex(const char *src, const int src_len, char *dest, int *dest_len)
{
#define IS_HEX_CHAR(ch) \
	((ch >= '0' && ch <= '9') || \
	 (ch >= 'a' && ch <= 'f') || \
	 (ch >= 'A' && ch <= 'F'))

#define HEX_VALUE(ch, value) \
	if (ch >= '0' && ch <= '9') \
	{ \
		value = ch - '0'; \
	} \
	else if (ch >= 'a' && ch <= 'f') \
	{ \
		value = ch - 'a' + 10; \
	} \
	else \
	{ \
		value = ch - 'A' + 10; \
	}

	const unsigned char *pSrc;
	const unsigned char *pEnd;
	char *pDest;
	unsigned char cHigh;
	unsigned char cLow;
	int valHigh;
	int valLow;

	pDest = dest;
	pSrc = (unsigned char *)src;
	pEnd = (unsigned char *)src + src_len;
	while (pSrc < pEnd)
	{
		if (*pSrc == '%' && pSrc + 2 < pEnd)
		{
			cHigh = *(pSrc + 1);
			cLow = *(pSrc + 2);

			if (IS_HEX_CHAR(cHigh) && IS_HEX_CHAR(cLow))
			{
				HEX_VALUE(cHigh, valHigh)
				HEX_VALUE(cLow, valLow)
				*pDest++ = (valHigh << 4) | valLow;
				pSrc += 3;
			}
			else
			{
				*pDest++ = *pSrc;
				pSrc++;
			}
		}
		else if (*pSrc == '+')
		{
			*pDest++ = ' ';
			pSrc++;
		}
		else
		{
			*pDest++ = *pSrc;
			pSrc++;
		}
	}

	*dest_len = pDest - dest;
	return dest;
}
