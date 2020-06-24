#ifndef SVNK_SVN_REVISION_HPP
#define SVNK_SVN_REVISION_HPP

#include <iostream>
#include <string>

namespace svnk {
namespace svn {

struct Revision
{
  unsigned int revision_number;
  std::string author;
  std::string date;
  std::string commit_message;

  Revision(unsigned int r, std::string a, std::string d, std::string msg)
    : revision_number(r)
    , author(a)
    , date(d)
    , commit_message(msg)
  {
  }

  std::string PrintShort() const;
};

std::ostream& operator<<(std::ostream& out, const Revision& rev);

}}

#endif
