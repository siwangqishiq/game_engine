
#include "ui/text.h"
#include "purple.h"

namespace purple{
    
    void Text::measure(int parentRequestWidth , int parentRequestHeight){
        int preCalaulateHeight;
        if(requestWidth_ == LAYOUT_MATCH_PARENT){
            width_ = parentRequestWidth;
        }else if(requestWidth_ == LAYOUT_WRAP_CONTENT){
            Rect outRect;
            preCalculateTextRectSize(outRect, parentRequestWidth);
            width_ = static_cast<int>(outRect.width);
            preCalaulateHeight = static_cast<int>(outRect.height);
        }

        if(requestHeight_ == LAYOUT_MATCH_PARENT){
            height_ = parentRequestHeight;
        }else if(requestHeight_ == LAYOUT_WRAP_CONTENT){
            height_ = preCalaulateHeight;
        }
    }
        
    void Text::render(){
        Widget::render();//render background
        
        //render text
        auto render = purple::Engine::getRenderEngine();
        Rect textRect(this->left , this->top , this->width_ , this->height_);
        render->renderTextWithRect(this->content_,textRect,this->textPaint_ , nullptr);
    }

    void Text::preCalculateTextRectSize(Rect &rect,int maxWidth){
        auto render = purple::Engine::getRenderEngine();
        render->preCalculateTextSize(this->content_,this->textPaint_,maxWidth,rect);
    }

    Text::~Text(){
        
    }
}
