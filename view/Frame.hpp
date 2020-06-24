#ifndef SVNK_FRAME_HPP
#define SVNK_FRAME_HPP

#include <ncurses.h>
#include <string>

namespace svnk {
namespace view {

class Frame
{
  public:
    Frame(const int lines,
          const int columns,
          const int y = 0,
          const int x = 0);

    Frame(const std::string& title, 
          const int lines,
          const int columns,
          const int y = 0,
          const int x = 0);

    void Activate();
    void DeActivate();
    void Refresh();
    void SetTitle(const std::string& title);
    virtual void KeyEvent(const int key) = 0;
  
  protected:
    const int mLines;
    const int mColumns;
    std::string mTitle;
    WINDOW* mWindow;
    

  private: 
    void CreateTitle();
};

}}

#endif
