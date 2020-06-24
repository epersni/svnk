#include "ListFrame.hpp"

#include <boost/lexical_cast.hpp>
#include <iostream> //TODO

#define BORDER_PADDING 1

namespace svnk {
namespace view {

ListFrame::ListFrame(
      const int lines,
      const int columns,
      const int y,
      const int x)
  : Frame(lines, columns, y, x)
  , cursor_pos(0)
  , mSelectedId(0)
  , mMaxVisibleItems(lines-(BORDER_PADDING*2)) 
{
  mSubWindow = subwin(Frame::mWindow, lines-(BORDER_PADDING*2), columns-(BORDER_PADDING*2), y+BORDER_PADDING,x+BORDER_PADDING);

  RedrawList();
}

void ListFrame::ClearItems()
{
  cursor_pos = 0;
  mSelectedId = 0;
  mItemsBelow.clear();
  while(!mItemsAbove.empty())
  {
    mItemsAbove.pop();
  }
  mList.clear();
  RedrawList();
}

void ListFrame::AddItem(const std::pair<unsigned int, std::string>& item)
{
  if(mList.size() < mMaxVisibleItems)
  {
    mList.push_back(item);
  }
  else
  {
    mItemsBelow.push_back(item);
  }
  RedrawList();
}

void ListFrame::SetOnSelection(
    const boost::function<void(const unsigned int)>& onSelect)
{
  mOnSelect = onSelect;
}

void ListFrame::RedrawList()
{
  unsigned int y = 0; 
  move(y, 0);
  werase(mSubWindow);

  for(std::deque<std::pair<unsigned int, std::string> >::const_iterator it = mList.begin();
      it != mList.end();
      ++it, ++y)
  {
    wattrset(mSubWindow, A_NORMAL);
    if(it->first == mSelectedId)
    {
      wattron(mSubWindow, A_REVERSE);
    }
    if(y == cursor_pos)
    {
      wattron(mSubWindow, A_BOLD);
    }
    mvwprintw(mSubWindow, y, 0, it->second.c_str());
  }
  wrefresh(mSubWindow);
}

void ListFrame::KeyEvent(const int key)
{
  switch(key)
  {
    case 'j':
    case KEY_DOWN:
    case 66:
      //TODO: cant go lower than there is items in list...
      if(cursor_pos >= mList.size()-1)
      {
        cursor_pos = mList.size()-1;
        if(mItemsBelow.size() != 0)
        {
          mItemsAbove.push(mList.front());
          mList.pop_front();

          mList.push_back(mItemsBelow.front());
          mItemsBelow.pop_front();
        }
      }
      else
      {
        ++cursor_pos;
      }
      break;
    case 'k':
    case 65:
    case KEY_UP:
      if(cursor_pos == 0)
      {
        cursor_pos = 0;
        if(!mItemsAbove.empty())
        {
          mList.push_front(mItemsAbove.top());
          mItemsAbove.pop();

          mItemsBelow.push_back(mList.back());
          mList.pop_back();
        }
      }
      else
      {
        --cursor_pos;
      }
      break;
    case 13:
    case KEY_ENTER:
      mSelectedId = mList[cursor_pos].first;
      mOnSelect(mSelectedId);
      break;
    default:
      break;
  }
  RedrawList();
}

}}

