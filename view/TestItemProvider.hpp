#ifndef SVNK_VIEW_TESTITEMPROVIDER_HPP
#define SVNK_VIEW_TESTITEMPROVIDER_HPP

#include "ListItemProvider.hpp"

#include <string>

namespace svnk {
namespace view {

class TestItemProvider : public ListItemProvider 
{
  public:
    std::vector<std::pair<unsigned int, std::string> > GetLatestItems(const unsigned count);
};

}}

#endif


