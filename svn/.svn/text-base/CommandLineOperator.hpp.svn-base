#ifndef SVNK_SVN_COMMANDLINEOPERATOR_HPP
#define SVNK_SVN_COMMANDLINEOPERATOR_HPP

#include "Change.hpp"
#include "DiffOutputProvider.hpp"
#include "Revision.hpp"
#include "RevisionProvider.hpp"
#include "XmlElement.hpp"

#include <boost/shared_ptr.hpp>
#include <memory>
#include <string>
#include <vector>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/sax/HandlerBase.hpp>

namespace svnk {
namespace svn {

class CommandLineOperator
  : public RevisionProvider
  , public DiffOutputProvider
{
  public:
    CommandLineOperator(const std::string workingDirectory);
    
    Revision GetRevision(const unsigned int revision) const;
    
    std::vector<Change> GetChangedFilesInRevision(const unsigned int rev) const;

    std::vector<Revision> GetRevisions(const unsigned int from_rev,
                                       const unsigned int to_rev) const;
    
    std::vector<Revision> GetLatestRevisions(const unsigned int count) const;
    
    std::string GetDiff(const unsigned int revision) const;

    std::string GetDiff(const unsigned int revision,
                        const std::string& filepath) const;

  private:
    const std::string mWorkingDirectory;
    boost::shared_ptr<xercesc::XercesDOMParser> mParser;
    boost::shared_ptr<xercesc::HandlerBase> mXmlErrorHandler;
    
    XmlElement ConvertCommandResponseToXml(
        const std::string& cmdResponse) const;

    XmlElement::XmlElementList ConvertCommandResponseToXml(
        const std::string& cmdResponse,
        const std::string& children) const;

    std::string ExecuteCommand(const std::string& cmd) const;
};

}}

#endif
