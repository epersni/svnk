#include "Revision.hpp"

#include <algorithm>
#include <boost/lexical_cast.hpp>

namespace svnk {
namespace svn {

std::string Revision::PrintShort() const
{
  std::string msg_no_newline = commit_message;
  msg_no_newline.erase(
      std::remove(msg_no_newline.begin(), msg_no_newline.end(),'\n'),
      msg_no_newline.end());

  return boost::lexical_cast<std::string>(revision_number) + 
         " (" + author  + ") - " + msg_no_newline;
}

std::ostream& operator<<(std::ostream& out, const Revision& rev)
{
  out << rev.PrintShort();
  return out;
}

}}
