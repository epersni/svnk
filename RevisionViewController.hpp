#ifndef SVNK_REVISIONVIEWCONTROLLER_HPP
#define SVNK_REVISIONVIEWCONTROLLER_HPP

#include "svn/RevisionProvider.hpp"
#include "view/ListItemProvider.hpp"

#include <boost/shared_ptr.hpp>
#include <vector>

namespace svnk {

/* Provides Revisions for the view when it requests items */
class RevisionViewController : public view::ListItemProvider
{
  public:
    RevisionViewController(
        const boost::shared_ptr<svn::RevisionProvider>& revisionProvider)
      : mRevisionProvider(revisionProvider)
    {}
    
    std::vector<std::pair<unsigned int, std::string> > GetItems();
    void ReCalculateItemsBySelectedId(const unsigned int selectedId);
  
  private:
    boost::shared_ptr<svn::RevisionProvider> mRevisionProvider;
};

}

#endif

