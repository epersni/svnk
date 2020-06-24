#include "ScrollableTextFrame.hpp"

namespace svnk {
namespace view {
    
ScrollableTextFrame::ScrollableTextFrame(const int lines,
                                         const int columns,
                                         const int y,
                                         const int x)
  : Frame(lines, columns, y, x)
  , mY(0)
  , mX(0)
{
  mSubWindow = newpad(512, 512);
  //keypad(mSubWindow, TRUE);
  //RedrawText();
  //Refresh();
}

void ScrollableTextFrame::KeyEvent(const int key)
{
  switch(key)
  {
    case KEY_UP:
    case 'k':
    case 'K':
      {
        mY = mY - 1;
        if(mY <= 0)
        {
          mY = 0;
        }
      }
      break;
    case 'j':
    case 'J':
    case KEY_DOWN:
      {
        mY = mY + 1;
        if(mY >= mLines)
        {
          mY = mLines;
        }
      }
      break;
    case KEY_LEFT:
    case 'h':
    case 'H':
      {
        mX = mX - 1;
        if(mX <= 0)
        {
          mX = 0;
        }
      }
      break;
    case 'l':
    case 'L':
    case KEY_RIGHT:
      {
        mX = mX + 1;
        if(mX >= mColumns)
        {
          mX = mColumns;
        }
      }
      break;
    default:
      break;
  }
  RedrawText();
}

void ScrollableTextFrame::AddLineOfText(const std::string& text)
{
  //mTextLines.push_back(text);
  werase(mSubWindow); 
  waddstr(mSubWindow, text.c_str());
  prefresh(mSubWindow, mY, mX, 1, 1, mLines-2, mColumns-2);
  wrefresh(mWindow);
}

void ScrollableTextFrame::ClearText()
{
  //mTextLines.clear();
  werase(mSubWindow); 
}

void ScrollableTextFrame::RedrawText()
{
  Refresh();
  prefresh(mSubWindow, mY, mX, 1, 1, mLines-2, mColumns-2);
}

}}
