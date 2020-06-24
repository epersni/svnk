#include "RepositoryInfo.hpp"
#include "XmlElement.hpp"

#include <cstdio>
#include <stdexcept>
#include <stdexcept>
#include <string>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/framework/MemBufInputSource.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/util/XMLString.hpp>

using namespace xercesc;

namespace svnk {
namespace svn {
namespace
{
  std::string executeCommand(const std::string& cmd)
  {
    char buffer[128];
    std::string result = "";
    FILE* pipe = popen(std::string(cmd + " 2>&1").c_str(), "r");
    if (!pipe) throw std::runtime_error("popen() failed!");
    try
    {
      while (fgets(buffer, sizeof buffer, pipe) != NULL)
      {
        result += buffer;
      }
    }
    catch (...)
    {
      pclose(pipe);
      throw;
    }
    pclose(pipe);
    return result;
  }
}

RepositoryInfo RepositoryInfo::fromDirectory(const std::string& directory)
{
  XercesDOMParser parser;
  parser.setValidationScheme(XercesDOMParser::Val_Always);
  parser.setDoNamespaces(true);

  char str[1024];
  sprintf(str, "svn info %s --xml", directory.c_str());
  try
  {
    const std::string commandResponse = executeCommand(std::string(str));

    MemBufInputSource input((const unsigned char*)commandResponse.c_str(),
        commandResponse.size(),
        "cmdReponseBuffer");
    parser.parse(input);

    XmlElement xmlRoot = parser.getDocument()->getDocumentElement();
    XmlElement entry = xmlRoot.GetChild("entry");

    const std::string root = entry.GetDestinationValue("root");
    const std::string url = entry.GetDestinationValue("url");
    const std::string path = entry.GetAttributeAs<std::string>("path");

    return RepositoryInfo(root, path, url);
  }
  catch(...)
  {
    throw InvalidRepositoryException(directory);
  }
}


}}
