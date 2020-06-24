#ifndef SVNK_CHANGEDFILEDSVIEWCONTROLLER_HPP
#define SVNK_CHANGEDFILEDSVIEWCONTROLLER_HPP

#include "svn/RevisionProvider.hpp"
#include "svn/Change.hpp"
#include "svn/DiffOutputProvider.hpp"
#include "view/ListItemProvider.hpp"
#include "view/TextProvider.hpp"

#include <boost/shared_ptr.hpp>
#include <vector>

namespace svnk {

/* Provides changed files for a given revision  for the changed files view */
class ChangedFilesViewController 
  : public view::ListItemProvider
  , public view::TextProvider
{
  public:
    ChangedFilesViewController(
        const boost::shared_ptr<svn::RevisionProvider>& revisionProvider,
        const boost::shared_ptr<svn::DiffOutputProvider>& diffProvider)
      : mRevisionProvider(revisionProvider)
      , mDiffOutputProvider(diffProvider)
      , mCurrentRevision(0)
    {}
    
    std::vector<std::pair<unsigned int, std::string> > GetItems()
    {
      return mItems;
    }

    void ReCalculateItemsBySelectedId(const unsigned int revision);
  
    std::string GetText(const unsigned int id);

  private:
    boost::shared_ptr<svn::RevisionProvider> mRevisionProvider;
    boost::shared_ptr<svn::DiffOutputProvider> mDiffOutputProvider;
    std::vector<std::pair<unsigned int, std::string> > mItems;
    std::vector<svn::Change> mModifiedFiles;
    unsigned int mCurrentRevision;
};

}

#endif


