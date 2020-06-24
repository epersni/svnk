#ifndef SVNK_SCROLLABLETEXTFRAME_HPP
#define SVNK_SCROLLABLETEXTFRAME_HPP

#include "Frame.hpp"

#include <vector>

namespace svnk {
namespace view {

class ScrollableTextFrame : public Frame
{
  public:
    ScrollableTextFrame(const int lines,
                        const int columns,
                        const int y = 0,
                        const int x = 0);
    
    void AddLineOfText(const std::string& text);  
    void ClearText();
    void RedrawText();
    
  private:
    int mY;
    int mX;
    WINDOW* mSubWindow;
    std::vector<std::string> mTextLines;
    void KeyEvent(const int key);

};

}}

#endif
