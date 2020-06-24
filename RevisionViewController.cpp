#include "RevisionViewController.hpp"

namespace svnk {

std::vector<std::pair<unsigned int, std::string> > 
  RevisionViewController::GetItems()
{
  std::vector<std::pair<unsigned int, std::string> > items;
  
  std::vector<svn::Revision> revisions = 
    mRevisionProvider->GetLatestRevisions(999999);  

  for(std::vector<svn::Revision>::const_iterator it = revisions.begin();
      it != revisions.end(); ++it)
  {
    items.push_back(std::make_pair(it->revision_number, it->PrintShort()));
  }

  return items;
}

void RevisionViewController::ReCalculateItemsBySelectedId(const unsigned int selectedId)
{
  //TODO: do something...
}

}
