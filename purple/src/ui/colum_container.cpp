
#include "ui/colum_container.h"

namespace purple{
    void ColumContainer::measure(int parentRequestWidth , int parentRequestHeight){
        // Log::i("ui","ColumContainer measure...");

        for(PWidget &child: getChildrenWidgets()){
            child->measure(width_ , height_);
        }//end for each


        //计算自身大小
        if(requestWidth_ == LAYOUT_MATCH_PARENT){
            width_ = parentRequestWidth;
        }else if(this->requestWidth_ == LAYOUT_WRAP_CONTENT){
            width_ = paddingLeft_ + contentWidth() + paddingRight_;
        }else{
            width_ = requestWidth_;
        }

        if(this->requestHeight_ == LAYOUT_MATCH_PARENT){
            height_ = parentRequestHeight;
        }else if(this->requestHeight_ == LAYOUT_WRAP_CONTENT){
            height_ = paddingTop_ + contentHeight() + paddingBottom_;
        }else{
            height_ = requestHeight_;
        }
    }

    void ColumContainer::layout(int l,int t){
        Container::layout(l, t);
    }

    ColumContainer::~ColumContainer(){
        this->Container::~Container();
    }
}
