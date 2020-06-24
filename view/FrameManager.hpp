#ifndef SVNK_VIEW_FRAMEMANAGER_HPP
#define SVNK_VIEW_FRAMEMANAGER_HPP

#include "Frame.hpp"
#include "ListFrame.hpp"
#include "ListItemProvider.hpp"
#include "ScrollableTextFrame.hpp"
#include "TextProvider.hpp"

#include <boost/shared_ptr.hpp>

namespace svnk {
namespace view {

class FrameManager
{
  public:
    FrameManager(const int maxx,
                 const int maxy,
                 boost::shared_ptr<TextProvider>& leftTextProvider,
                 boost::shared_ptr<ListItemProvider>& topRightItemProvider,
                 boost::shared_ptr<ListItemProvider>& bottomRightItemProvider);
  
    void KeyEvent(const int key);

  private:
    int mMaxX;
    int mMaxY;
    boost::shared_ptr<TextProvider> mTopLeftTextProvider;
    boost::shared_ptr<ListItemProvider> mBottomRightItemProvider;
    boost::shared_ptr<ListItemProvider> mTopRightItemProvider;
    ScrollableTextFrame left;
    ListFrame top_right;
    ListFrame bottom_right;
    unsigned int activatedIndex;
    
    static const unsigned int NUMBER_OF_FRAMES = 3;

    Frame* all_frames[NUMBER_OF_FRAMES];
    //Frame* all_frames[NUMBER_OF_FRAMES] = {&left, &top_right, &bottom_right};
    
    void OnTopRightSelectionChanged(const unsigned int id);
    void OnBottomRightSelectionChanged(const unsigned int id);
};

}}

#endif
