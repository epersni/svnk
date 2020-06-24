#ifndef SVNK_SVN_REPOSITORY_INFO_HPP
#define SVNK_SVN_REPOSITORY_INFO_HPP

#include <exception>
#include <iostream>
#include <string>

namespace svnk {
namespace svn {

class InvalidRepositoryException : public std::exception
{
public:
  InvalidRepositoryException(const std::string& directory_)
    : directory(directory_)
  {
  }
  
  ~InvalidRepositoryException() throw() 
  {
  } 

  const char* what () const throw ()
  {
    return std::string(directory + " is not a valid subversion repository").c_str();
  }
private:
  std::string directory;
};

struct RepositoryInfo
{
  std::string root;
  std::string path;
  std::string url; 

  RepositoryInfo(const std::string& r,
                 const std::string& p,
                 const std::string& u)
    : root(r)
    , path(p)
    , url(u)
  {
  }
  
  static RepositoryInfo fromDirectory(const std::string& directory);
};


}}

#endif

