
#include "ui/text.h"
#include "purple.h"

namespace purple{
    
    void Text::onMeasure(MeasureSpecMode widthSpecMode, 
                            int widthValue, 
                            MeasureSpecMode heightSpecMode,
                            int heightValue){
        int preCalaulateHeight = -1;
        if(requestWidth_ == LAYOUT_MATCH_PARENT){
            width_ = widthValue;
        }else if(requestWidth_ == LAYOUT_WRAP_CONTENT){
            Rect outRect;
            preCalculateTextRectSize(outRect, heightValue);
            width_ = std::min(static_cast<int>(outRect.width) + this->paddingLeft_ + this->paddingRight_
                        , widthValue);
            preCalaulateHeight = static_cast<int>(outRect.height);
        }else{
            width_ = requestWidth_;
        }

        if(requestHeight_ == LAYOUT_MATCH_PARENT){
            height_ = heightValue;
        }else if(requestHeight_ == LAYOUT_WRAP_CONTENT){
            if(preCalaulateHeight != -1){//已经在宽度的计算中预先计算出来了
                height_ = preCalaulateHeight + this->paddingTop_ + this->paddingBottom_;
            }else{
                Rect outRect;
                preCalculateTextRectSize(outRect, widthValue);
                height_ = static_cast<int>(outRect.height)+ this->paddingTop_ + this->paddingBottom_;
            }
        }else{
            height_ = requestHeight_;
        }
        Log::i("ui","Text measue size %d , %d   %s" , width_ , height_ , this->id.c_str());
    }
        
    void Text::onRender(){
        Widget::onRender();//render background

        if(width_ == 0 || height_ == 0){
            return;
        }
        
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
