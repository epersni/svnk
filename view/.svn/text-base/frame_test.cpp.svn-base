#include <boost/program_options.hpp>
#include <boost/make_shared.hpp>
#include <fstream>
#include <iostream>
#include <ncurses.h>
#include "FrameManager.hpp"
#include "TestItemProvider.hpp"

#define FILENAME "gettysburg.txt"

void bomb(void);

int main(int argc, char *argv[])
{
  int maxx, maxy, halfx, halfy;
  initscr();
  keypad(stdscr, TRUE);
  //start_color();
  noecho(); 
  curs_set(0);
  getmaxyx(stdscr, maxy, maxx);

  halfx = maxx /2;
  halfy = maxy /2;
  
  boost::shared_ptr<svnk::view::TestItemProvider> testItemProvider(new svnk::view::TestItemProvider());

  boost::shared_ptr<svnk::view::ListItemProvider> itemProvider = 
    boost::dynamic_pointer_cast<svnk::view::ListItemProvider>(testItemProvider);
  
  int c;
  svnk::view::FrameManager frameManager(maxx, maxy, itemProvider, itemProvider);
  do
  {
    c = std::getchar(); 
    frameManager.KeyEvent(c);
  } while (c != '~');
  endwin();
  return 0;
}

void bomb(void)
{
  addstr("Unable to allocate memory for new windows.\n");
  refresh();
  endwin();
  exit(1);
}
