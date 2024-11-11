
#include "ui/ui_text.h"
#include "purple.h"

namespace purple{
    // Text::Text(const wchar_t *chars,int w,int h){
    //     Text(std::wstring(chars) , w, h);
    // }

    // Text::Text(std::wstring content,int w,int h){
    //     Log::e("ui_text","000 Text::measure width = %d, height = %d", w , h);
    //     this->content_ = content;
    //     Log::e("ui_text","111 Text::measure width = %d, height = %d", width , height);
    // }

    Text& Text::setFontColor(glm::vec4 fontColor){
        textPaint_.textColor = fontColor;
        return *this;
    }
    
    Text& Text::setFontSize(float fontSize){
        textPaint_.setTextSize(fontSize);
        return *this;
    }

    void Text::measure(int parentRequestWidth , int parentRequestHeight){
        Log::e("ui_text","2222 Text::measure width = %d, height = %d", width , height);

        if(width == LAYOUT_MATCH_PARENT){
            width = parentRequestWidth;
        }else if(width == LAYOUT_WRAP_CONTENT){
            Rect outRect;
            preCalculateTextRectSize(outRect, parentRequestWidth);
            width = outRect.width;
            Log::e("ui_text","Text::measure width = %d, height = %d", width , height);
        }

        if(height == LAYOUT_MATCH_PARENT){
            height = parentRequestHeight;
        }else if(height == LAYOUT_WRAP_CONTENT){
            Rect outRect;
            preCalculateTextRectSize(outRect, parentRequestWidth);
            height = outRect.height;
            Log::e("ui_text","Text::measure width = %d, height = %d", width , height);
        }
    }
        
    void Text::render(){
        Widget::render();//render background
    }

    void Text::preCalculateTextRectSize(Rect &rect,int maxWidth){
        auto render = purple::Engine::getRenderEngine();
        render->preCalculateTextSize(this->content_,this->textPaint_,maxWidth,rect);
    }

    Text::~Text(){
        
    }
}
