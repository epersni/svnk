#ifndef SVNK_SVN_DIFFOUTPUTPROVIDER_HPP
#define SVNK_SVN_DIFFOUTPUTPROVIDER_HPP

#include <string>

namespace svnk {
namespace svn {

class DiffOutputProvider
{
  public:
    virtual std::string GetDiff(const unsigned int revision) const = 0;
    
    virtual std::string GetDiff(const unsigned int revision,
                                const std::string& filepath) const = 0;
};

}}

#endif

