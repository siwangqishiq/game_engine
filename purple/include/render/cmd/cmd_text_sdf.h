#pragma once

#include "render/cmd/command.h"
#include "render/cmd/cmd_text.h"
#include "render/text_render.h"

namespace purple{
    // SDF文本渲染命令
    class SdfTextRenderCommand : public TextRenderCommand{
    public:
        const std::string TAG = "SdfTextRenderCommand";
        const std::string SAHDER_NAME_SDF_TEXT = "sdf_text";

        SdfTextRenderCommand(RenderEngine *engine , TextRender *tRender) 
            : TextRenderCommand(engine) , textRender_(tRender){}
        
        virtual void putParams(
            std::wstring &text ,
            float left , 
            float bottom,
            TextPaint &paint);
        
        virtual void runCommands();

        std::shared_ptr<CharInfo> findCharInfo(wchar_t &ch , int index);
    private:
        TextRender *textRender_;

        Shader fetchSdfTextShader();
    };
}

