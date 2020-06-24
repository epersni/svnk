#include "Frame.hpp"

namespace svnk {
namespace view {

Frame::Frame(const int lines, const int columns, const int y, const int x)
  : mLines(lines)
  , mColumns(columns)
{
  mWindow = newwin(lines, columns, y, x); //TODO check for error
  Refresh();
}

Frame::Frame(const std::string& title, 
             const int lines,
             const int columns,
             const int y,
             const int x)
  : mLines(lines)
  , mColumns(columns)
  , mTitle(title)
{
  mWindow = newwin(lines, columns, y, x); //TODO check for error
  //Refresh();
}

void Frame::Activate()
{
  wattron(mWindow, A_REVERSE);
  box(mWindow, 0,0);
  wrefresh(mWindow);
}

void Frame::DeActivate()
{
  wattroff(mWindow, A_REVERSE);
  box(mWindow, 0,0);
  wrefresh(mWindow);
}

void Frame::Refresh()
{
  box(mWindow, 0,0);
  if(mTitle.size() > 0)
  {
    CreateTitle();
  }
  wrefresh(mWindow);
}

void Frame::SetTitle(const std::string& title)
{
  mTitle = title; 
  Refresh();
}

void Frame::CreateTitle()
{
  const int x = (mColumns - mTitle.size())/2;
  mvwaddch(mWindow, 0, x, '<');
  waddch(mWindow, ' ');
  waddstr(mWindow, mTitle.c_str());
  waddch(mWindow, ' ');
  waddch(mWindow, '>');
}

}}
