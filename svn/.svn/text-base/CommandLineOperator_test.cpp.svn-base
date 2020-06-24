#include "CommandLineOperator.hpp"

#include <iostream>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/PlatformUtils.hpp>

using namespace xercesc;

int main()
{
  try
  {
    XMLPlatformUtils::Initialize();
  }
  catch (const XMLException& toCatch)
  {
    char* message = XMLString::transcode(toCatch.getMessage());
    std::cout << "Error during initialization! :\n"
      << message << "\n";
    XMLString::release(&message);
    return 1;
  }

  svnk::svn::CommandLineOperator op(std::string("svn://design200/real-diceroulette"));
  std::cout << "diff =" << std::endl << op.GetDiff(493, "SConstruct") << std::endl;
 // std::vector<svnk::svn::Revision> revisions = op.GetRevisions(1876742, 1876658);
  
//  std::vector<std::string> files = op.GetChangedFilesInRevision(114);
//  std::cout << "files changed:" << std::endl;
//  for(std::vector<std::string>::const_iterator it = files.begin();
//      it != files.end();
//      ++it)
//  {
//    std::cout << *it << "\n";
//  }
  return 0;
}

