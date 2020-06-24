#ifndef SVNK_VIEW_LISTITEMPROVIDER_HPP
#define SVNK_VIEW_LISTITEMPROVIDER_HPP

#include <string>
#include <vector>
#include <utility>

namespace svnk {
namespace view {

class ListItemProvider
{
  public:
    virtual std::vector<std::pair<unsigned int, std::string> > GetItems() = 0;
    virtual void ReCalculateItemsBySelectedId(const unsigned int selectedId) = 0;
};

}}

#endif

