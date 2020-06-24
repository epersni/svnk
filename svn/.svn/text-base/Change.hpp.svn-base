#ifndef SVNK_SVN_CHANGE_HPP
#define SVNK_SVN_CHANGE_HPP

#include <iostream>
#include <string>

namespace svnk {
namespace svn {

struct Change
{
  enum Type 
  {
    NONE,
    MODIFIED,
    DELETED,
    ADDED,
  };

  std::string path;
  Type type;

  Change(const std::string& p, Type t)
    : path(p)
    , type(t)
  {
  }

  friend std::ostream& operator<<(std::ostream& out, const Change& rev);
};

std::ostream& operator<<(std::ostream& out, const Change& rev);

}}

#endif

