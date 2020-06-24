#ifndef SVNK_LISTFRAME_HPP
#define SVNK_LISTFRAME_HPP

#include "Frame.hpp"

#include <boost/function.hpp>
#include <string>
#include <vector>
#include <queue>
#include <deque>
#include <stack>

namespace svnk {
namespace view {

class ListFrame : public Frame
{
  public:
    ListFrame(const int lines,
              const int columns,
              const int y = 0,
              const int x = 0);
    
    void AddItem(const std::pair<unsigned int, std::string>& item);
    void ClearItems();
  
    void SetOnSelection(
        const boost::function<void(const unsigned int)>& onSelect);

  private:
    WINDOW* mSubWindow;
    unsigned int cursor_pos;
    unsigned int mSelectedId;
    const unsigned int mMaxVisibleItems;
    boost::function<void(const unsigned int)> mOnSelect;

    std::deque<std::pair<unsigned int, std::string> > mList;
    std::stack<std::pair<unsigned int, std::string> > mItemsAbove;
    std::deque<std::pair<unsigned int, std::string> > mItemsBelow;
    
    void RedrawList();
    void KeyEvent(const int key);
};

}}

#endif
