#include "ChangedFilesViewController.hpp"
#include <sstream>

namespace svnk {

void ChangedFilesViewController::ReCalculateItemsBySelectedId(
  const unsigned int revision)
{
  mCurrentRevision = revision;
  mItems.clear();

  mModifiedFiles = mRevisionProvider->GetChangedFilesInRevision(mCurrentRevision);  
 
  unsigned int incrementingId = 0;
  for(std::vector<svn::Change>::const_iterator it = mModifiedFiles.begin();
      it != mModifiedFiles.end(); ++it)
  {
    std::stringstream sstream;
    sstream << *it;
    mItems.push_back(std::make_pair(incrementingId++, sstream.str()));
  }
}

std::string ChangedFilesViewController::GetText(const unsigned int id)
{
  const svn::Change change = mModifiedFiles[id];
  
  if(change.type == svn::Change::DELETED)
  {
    return change.path + " was deleted";
  }
  else
  {
    return mDiffOutputProvider->GetDiff(mCurrentRevision, change.path); 
  }
}

}

