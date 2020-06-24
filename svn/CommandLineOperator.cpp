#include "CommandLineOperator.hpp"

#include <cstdio>
#include <boost/make_shared.hpp>
#include <xercesc/framework/MemBufInputSource.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/util/XMLString.hpp>
#include <stdexcept>
#include <string>

using namespace xercesc;

namespace svnk {
namespace svn {
namespace
{
  svnk::svn::Change::Type getChangeTypeFromString(const std::string& typeString)
  {
    if(typeString == "deleted")
    {
      return svnk::svn::Change::DELETED;
    }
    else if(typeString == "modified")
    {
      return svnk::svn::Change::MODIFIED;
    }
    else if(typeString == "added")
    {
      return svnk::svn::Change::ADDED;
    }
    return svnk::svn::Change::NONE;
  }
}

CommandLineOperator::CommandLineOperator(const std::string workingDirectory)
  : mWorkingDirectory(workingDirectory)
  , mParser(boost::make_shared<XercesDOMParser>())
  , mXmlErrorHandler(new HandlerBase())
{
  mParser->setValidationScheme(XercesDOMParser::Val_Always);
  mParser->setDoNamespaces(true);
  mParser->setErrorHandler(mXmlErrorHandler.get());
}

std::vector<Change> CommandLineOperator::GetChangedFilesInRevision(
    const unsigned int rev) const
{
  char str[255];
  sprintf(str, "svn diff %s --summarize -c %d --xml", mWorkingDirectory.c_str(), rev);
  const XmlElement diffElement = 
    ConvertCommandResponseToXml(ExecuteCommand(std::string(str)));

  const XmlElement::XmlElementList elements = 
    diffElement.GetChild("paths").GetChildren("path");
  
  std::vector<Change> changedFiles;

  for(std::vector<XmlElement>::const_iterator it = elements.begin();
      it != elements.end();
      ++it) 
  {
    if(it->GetAttributeAs<std::string>("kind") == "file")
    {
      const std::string typeStr = it->GetAttributeAs<std::string>("item");
      changedFiles.push_back(Change(it->GetDestinationValue(),
                                    getChangeTypeFromString(typeStr)));
    }
  }

  return changedFiles;
}


std::vector<Revision> CommandLineOperator::GetRevisions(
    const unsigned int from_rev,
    const unsigned int to_rev) const
{
  char str[255];
  sprintf(str, "svn log %s -r %d:%d --xml", mWorkingDirectory.c_str(), from_rev, to_rev);
  
  const XmlElement::XmlElementList elements = 
    ConvertCommandResponseToXml(ExecuteCommand(std::string(str)), "logentry");
  
  std::vector<Revision> result;

  for(std::vector<XmlElement>::const_iterator it = elements.begin();
      it != elements.end();
      ++it) 
  {
    XmlElement elem = *it;
    result.push_back(Revision(elem.GetAttributeAs<unsigned int>("revision"),
                              elem.GetDestinationValue("author"),
                              elem.GetDestinationValue("date"),
                              elem.GetDestinationValue("msg")));
  }

  return result;
}

Revision CommandLineOperator::GetRevision(const unsigned int revision) const
{
  char str[255];
  sprintf(str, "svn log %s -r %d --xml", mWorkingDirectory.c_str(), revision);
  
  const XmlElement::XmlElementList elements = 
    ConvertCommandResponseToXml(ExecuteCommand(std::string(str)), "logentry");
  
  const XmlElement elem = elements.at(0);
  
  return Revision(elem.GetAttributeAs<unsigned int>("revision"),
                  elem.GetDestinationValue("author"),
                  elem.GetDestinationValue("date"),
                  elem.GetDestinationValue("msg"));
}

std::vector<Revision> CommandLineOperator::GetLatestRevisions(
    const unsigned int count) const
{
  char str[255];
  sprintf(str, "svn log %s --xml  --limit %d", mWorkingDirectory.c_str(), count);
  
  const XmlElement::XmlElementList elements = 
    ConvertCommandResponseToXml(ExecuteCommand(std::string(str)), "logentry");
  
  std::vector<Revision> result;

  for(std::vector<XmlElement>::const_iterator it = elements.begin();
      it != elements.end();
      ++it) 
  {
    XmlElement elem = *it;
    result.push_back(Revision(elem.GetAttributeAs<unsigned int>("revision"),
                              elem.GetDestinationValue("author"),
                              elem.GetDestinationValue("date"),
                              elem.GetDestinationValue("msg")));
  }

  return result;
}

std::string CommandLineOperator::GetDiff(const unsigned int revision,
                                         const std::string& filepath) const
{
  char str[255];
  sprintf(str,
          "svn diff -c %d %s",
          revision,
          filepath.c_str());
  
  try
  {
    return ExecuteCommand(std::string(str)); 
  }
  catch(...)
  {
    return "Could not get requested diff"; 
  }
}

std::string CommandLineOperator::GetDiff(const unsigned int revision) const
{
  char str[255];
  sprintf(str, "svn diff %s -c %d", mWorkingDirectory.c_str(), revision);
  return ExecuteCommand(std::string(str)); 
}

std::string CommandLineOperator::ExecuteCommand(const std::string& cmd) const
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

XmlElement CommandLineOperator::ConvertCommandResponseToXml(
    const std::string& cmdResponse) const
{
  MemBufInputSource input((const unsigned char*)cmdResponse.c_str(),
                          cmdResponse.size(),
                          "cmdReponseBuffer");
  mParser->parse(input);
  return mParser->getDocument()->getDocumentElement();
}

XmlElement::XmlElementList CommandLineOperator::ConvertCommandResponseToXml(
    const std::string& cmdResponse,
    const std::string& children) const
{
  MemBufInputSource input((const unsigned char*)cmdResponse.c_str(),
                          cmdResponse.size(),
                          "cmdReponseBuffer");
  mParser->parse(input);
  XmlElement root(mParser->getDocument()->getDocumentElement());
  return root.GetChildren(children);
}

}}
