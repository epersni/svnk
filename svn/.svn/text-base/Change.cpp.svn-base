#include "Change.hpp"

#include <algorithm>
#include <boost/lexical_cast.hpp>

namespace svnk {
namespace svn {

std::ostream& operator<<(std::ostream& out, const Change& rev)
{
  std::string type_identifier;
  switch(rev.type)
  {
    case Change::DELETED:
      type_identifier = "D";
      break;
    case Change::ADDED:
      type_identifier = "A";
      break;
    case Change::MODIFIED:
      type_identifier = "M";
      break;
    case Change::NONE:
      type_identifier = " ";
      break;
  };
  out << type_identifier << " " << rev.path;
  return out;
}

}}

