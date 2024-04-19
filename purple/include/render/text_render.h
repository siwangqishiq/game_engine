#pragma once

#include <string>
#include "render/common.h"
#include "log.h"
#include "render/stb_truetype.h"
#include <memory>
#include <unordered_map>

namespace purple{
    class RenderEngine;
    class TextureInfo;
    
    class TextRender{
    public:
        const std::string TAG = "TextRender";

        const int CHARS_MAX_COUNT_PER_COLUM = 8;

        const int texWidth_ = CHARS_MAX_COUNT_PER_COLUM * FONT_DEFAULT_SIZE;
        const int texHeight_ = CHARS_MAX_COUNT_PER_COLUM * FONT_DEFAULT_SIZE;
        const int texDepth_ = 32;

        TextRender(RenderEngine *engine):renderEngine_(engine){
            Log::i(TAG , "TextRender construct");
        };

        ~TextRender(){
            if(fontData_ != nullptr){
                delete[] fontData_;
                fontData_ = nullptr;
            }
            Log::i(TAG , "TextRender deconstructed");
        };
        
        int loadFontRes(std::string fontName , std::string fontFileAssetPath);

        void renderText(const wchar_t *text, 
            float left , float baseLine, 
            TextPaint &textPaint);
        
        void renderText(std::wstring text , 
            float left , float baseLine, 
            TextPaint &textPaint);

        std::shared_ptr<CharInfo> findCharInfo(wchar_t &ch , int index);

        stbtt_fontinfo* getFontInfo(){
            return &fontInfo_;
        }

        float getFonScale(){
            return fontScale_;
        }
    private:

        RenderEngine *renderEngine_;

        const unsigned char *fontData_ = nullptr;
        stbtt_fontinfo fontInfo_;

        float fontScale_ = 1.0f;

        int initFont();

        void buildTextRenderVertexData(std::wstring &text , 
                float left , 
                float top , 
                TextPaint &paint);
        
        void submitRenderCommand();

        //create 3D texture
        int createFontTextureRes();

        std::unordered_map<wchar_t , std::shared_ptr<CharInfo>> charInfoMap_;

        std::shared_ptr<TextureInfo> fontTextureInfo_;

        std::string fontName_;
    };
} // namespace  



