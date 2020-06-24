#ifndef SVNK_SVN_REVISIONPROVIDER_HPP
#define SVNK_SVN_REVISIONPROVIDER_HPP

#include "Revision.hpp"
#include "Change.hpp"

#include <vector>

namespace svnk {
namespace svn {

class RevisionProvider
{
  public:
    virtual Revision GetRevision(const unsigned int revision) const = 0;
    
    virtual std::vector<Revision> GetLatestRevisions(
        const unsigned int count) const = 0;

    virtual std::vector<Change> GetChangedFilesInRevision(
        const unsigned int revision) const = 0;
};

}}

#endif
