#ifndef HTML_FILE_HPP
#define HTML_FILE_HPP

#include <string>
#include <vector>
#include <map>
#include <stdint.h>
struct Html_file {
    std::string filename;
    std::string filepath;
  std::string contentType;
            int filesize;
    std::string last_modified;
  std::vector<uint8_t> content;
};

void initializeTextFile(Html_file* self,const std::string& fname,const std::string& fpath,const std::string& textContent,const std::string& contentType);
void initializeRawFile(Html_file* self,std::string fname,std::string fpath,std::string actualName);
std::string createJSON(const std::map<std::string,std::string>& kvl);
std::string getStringContent(const Html_file* self);
#endif /* end of include guard: HTML_FILE_HPP */

