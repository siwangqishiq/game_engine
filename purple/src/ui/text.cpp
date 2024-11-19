
#include "ui/text.h"
#include "purple.h"

namespace purple{
    
    void Text::onMeasure(int parentRequestWidth , int parentRequestHeight){
        int preCalaulateHeight = -1;
        if(requestWidth_ == LAYOUT_MATCH_PARENT){
            width_ = parentRequestWidth;
        }else if(requestWidth_ == LAYOUT_WRAP_CONTENT){
            Rect outRect;
            preCalculateTextRectSize(outRect, parentRequestWidth);
            width_ = std::min(static_cast<int>(outRect.width) + this->paddingLeft_ + this->paddingRight_
                        , parentRequestWidth);
            preCalaulateHeight = static_cast<int>(outRect.height);
        }

        if(requestHeight_ == LAYOUT_MATCH_PARENT){
            height_ = parentRequestHeight;
        }else if(requestHeight_ == LAYOUT_WRAP_CONTENT){
            if(preCalaulateHeight != -1){//已经在宽度的计算中预先计算出来了
                height_ = preCalaulateHeight + this->paddingTop_ + this->paddingBottom_;
            }else{
                Rect outRect;
                preCalculateTextRectSize(outRect, parentRequestWidth);
                height_ = static_cast<int>(outRect.height)+ this->paddingTop_ + this->paddingBottom_;
            }
        }
        // Log::i("ui","Text measue size %d , %d" , width_ , height_);
    }
        
    void Text::onRender(){
        Widget::onRender();//render background
        
        //render text
        auto render = purple::Engine::getRenderEngine();

        int textLeft = paddingLeft_ + this->left;
        int textTop = this->top - paddingTop_;
        int textWidth = this->width_ - this->paddingLeft_ - this->paddingRight_;
        int textHeight = this->height_ - this->paddingTop_ - this->paddingBottom_;
        Rect textRect(textLeft , textTop , textWidth , textHeight);
        render->renderTextWithRect(this->content_,textRect,this->textPaint_ , nullptr);

        // Log::i("ui","Text render size %d , %d pos: %d, %d" , width_ , height_ , left , top);
    }

    void Text::preCalculateTextRectSize(Rect &rect,int maxWidth){
        auto render = purple::Engine::getRenderEngine();
        render->preCalculateTextSize(this->content_,this->textPaint_,maxWidth,rect);
    }

    Text::~Text(){
    }
}
