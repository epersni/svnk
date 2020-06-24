#include "TestItemProvider.hpp"

namespace svnk {
namespace view {

std::vector<std::pair<unsigned int, std::string> > TestItemProvider::GetLatestItems(const unsigned count)
{
  std::vector<std::pair<unsigned int, std::string> > items;
  
  for(unsigned int n = 0; n < count; n++)
  {
    items.push_back(std::make_pair(n, "Yes this is an item"));
  }

  return items;
}

}}
