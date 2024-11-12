#pragma once

#include "ui.h"
#include "color.h"
#include "render/common.h"

namespace purple{

    class Text :public Widget{
    public:
        Text(const wchar_t *chars,int w,int h):Widget(w, h),content_(chars){}

        Text(std::wstring content,int w,int h):Widget(w, h),content_(content){}

        Text& setFontColor(glm::vec4 fontColor);
        Text& setFontSize(float fontSize);
        
        virtual void measure(int parentRequestWidth , int parentRequestHeight);
        virtual void render();

        virtual ~Text();
    private:
        std::wstring content_ = L"";
        TextPaint textPaint_;

        void preCalculateTextRectSize(Rect &outInfo,int maxWidth);
    };
}