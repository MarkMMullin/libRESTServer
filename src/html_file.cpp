#include "html_file.hpp"
#include <stdint.h>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string.h>

std::string createJSON(const std::map<std::string,std::string>& kvl)
{
  char sb[2048];
  char wb[256];
  strcpy(sb,"{\n");
  for(std::map<std::string,std::string>::const_iterator iter = kvl.begin();iter != kvl.end();iter++)
  {
    if(strlen(sb) > 3)
      strcat(sb,",\n");
    sprintf(wb,"\t\"%s\" : \"%s\"",iter->first.c_str(),iter->second.c_str());
    strcat(sb,wb);
  }
  strcat(sb,"\n}\n");
  return sb;
}
void initializeTextFile(Html_file* self,const std::string& fname,const std::string& fpath,const std::string& textContent,const std::string& contentType)
{
  self->filename = fname;
  self->filepath = fpath;
  self->last_modified = "Wed, 31 August 2016 15:09:45 GMT";
  self->etag = "";
  const char* contentBuffer = textContent.c_str();
  //std:string getStringContent(Html_file* self)
  char cc;
  while((cc = *contentBuffer) != '\0')
    {
      self->content.push_back(cc);
      ++contentBuffer;
    }
  self->contentType = contentType;
  self->filesize = self->content.size();
}
void initializeRawFile(Html_file* self,std::string fname,std::string fpath,std::string actualName)
{
  const char* fn = actualName.c_str();
  std::ifstream inputFile( fn, std::ios_base::binary );
    // Stop eating new lines in binary mode!!!
    inputFile.unsetf(std::ios::skipws);

    // get its size:
    std::streampos fileSize;

    inputFile.seekg(0, std::ios::end);
    fileSize = inputFile.tellg();
    inputFile.seekg(0, std::ios::beg);
    if(fileSize <= 0)
      return;
  self->filename = fname;
  self->filepath = fpath;
  self->last_modified = "Wed, 31 August 2016 15:09:45 GMT";
    // reserve capacity
    std::vector<uint8_t> buffer;
    buffer.reserve(fileSize);

    // read the data:
    buffer.insert(buffer.begin(),
               std::istream_iterator<uint8_t>(inputFile),
               std::istream_iterator<uint8_t>());
    
    //std::istreambuf_iterator< char> start(input);
    //std::istreambuf_iterator< char> finish;
  
    // std::vector< char> buffer;
    //buffer.insert(std::back_inserter(buffer),start,finish);
      self->content = buffer;
 
  self->contentType = "image/jpeg";
  self->etag = "";
  self->filesize = self->content.size();
}
void initializeRawMemory(Html_file* self,std::string fname,std::string fpath,uint8_t* ptr,uint32_t fileSize,uint32_t etagValue)
{
    if(fileSize <= 0)
      return;
    self->filename = fname;
    self->filepath = fpath;
    self->last_modified = "Wed, 31 August 2016 15:09:45 GMT";
    // reserve capacity
    std::vector<uint8_t> buffer;
    buffer.reserve(fileSize);

    // read the data:
    for(uint32_t i = 0;i < fileSize;i++)
      buffer.push_back(*ptr++);
    self->content = buffer;
 
  self->contentType = "image/jpeg";
  char buf[16];
  sprintf(buf,"%d",etagValue);
  self->etag = buf;
  self->filesize = self->content.size();
}

std::string getStringContent(const Html_file* self)
{
  std::string s;

  for (auto x : self->content)
  {
    s += static_cast<char>(x);
  }
  return s;
}
