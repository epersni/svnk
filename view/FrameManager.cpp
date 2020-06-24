#include "FrameManager.hpp"
#include <boost/lambda/bind.hpp>
#include <boost/lambda/lambda.hpp>
#include <ncurses.h>

namespace svnk {
namespace view {

FrameManager::FrameManager(
      const int maxx,
      const int maxy,
      boost::shared_ptr<TextProvider>& leftTextProvider,
      boost::shared_ptr<ListItemProvider>& topRightItemProvider,
      boost::shared_ptr<ListItemProvider>& bottomRightItemProvider)
  : mMaxX(maxx)
  , mMaxY(maxy)
  , mTopLeftTextProvider(leftTextProvider)
  , mBottomRightItemProvider(bottomRightItemProvider)
  , mTopRightItemProvider(topRightItemProvider)
  , left(maxy, maxx / 2)
  , top_right(maxy/2, maxx/2+1, 0, maxx/2)
  , bottom_right(maxy/2+1, maxx/2+1, maxy/2, maxx/2)
  , activatedIndex(1)
{
  all_frames[0] = &left;
  all_frames[1] = &top_right;
  all_frames[2] = &bottom_right;
  
  std::vector<std::pair<unsigned int, std::string> > items = 
    mTopRightItemProvider->GetItems();
  
  for(std::vector<std::pair<unsigned int, std::string> >::const_iterator it =
      items.begin(); it != items.end(); ++it)
  {
    top_right.AddItem(*it);
  }

  bottom_right.SetOnSelection(
      boost::lambda::bind(&FrameManager::OnBottomRightSelectionChanged,
                          this,
                          boost::lambda::_1));
  top_right.SetOnSelection(
      boost::lambda::bind(&FrameManager::OnTopRightSelectionChanged,
                          this,
                          boost::lambda::_1));
  
  top_right.Activate();
}

void FrameManager::OnBottomRightSelectionChanged(const unsigned int id)
{
  std::vector<std::pair<unsigned int, std::string> > items = 
    mBottomRightItemProvider->GetItems();
  left.AddLineOfText(mTopLeftTextProvider->GetText(id));
}

void FrameManager::OnTopRightSelectionChanged(const unsigned int id)
{
  mBottomRightItemProvider->ReCalculateItemsBySelectedId(id);
  
  bottom_right.ClearItems();
    
  std::vector<std::pair<unsigned int, std::string> > items = 
    mBottomRightItemProvider->GetItems();
  
  for(std::vector<std::pair<unsigned int, std::string> >::const_iterator it =
      items.begin(); it != items.end(); ++it)
  {
    bottom_right.AddItem(*it);
  }
}

void FrameManager::KeyEvent(const int key)
{
  switch(key)
  {
    case '\t':
      {
        Frame* prev_activated = all_frames[activatedIndex];
        prev_activated->DeActivate();
        ++activatedIndex;
        if(activatedIndex >= NUMBER_OF_FRAMES)
        {
          activatedIndex = 0;
        }
        Frame* next_activated = all_frames[activatedIndex];
        next_activated->Activate();
        
        /* FIX: We need to redraw the text on the scrollableTextFrame because
         * when it redraws its box it (for some reason) also clears the Pad
         */
        left.RedrawText();
      }
      break;
    case 27:
      {
        Frame* prev_activated = all_frames[activatedIndex];
        prev_activated->DeActivate();
        if(activatedIndex-- == 0)
        {
          activatedIndex = NUMBER_OF_FRAMES-1;
        }
        Frame* next_activated = all_frames[activatedIndex];
        next_activated->Activate();
      }
  }

  all_frames[activatedIndex]->KeyEvent(key);
}

}}
