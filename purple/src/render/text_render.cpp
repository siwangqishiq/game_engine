
#include "render/text_render.h"
#include "render/render.h"
#include "resource/asset_manager.h"

#include "render/cmd/cmd_text.h"
#include "render/cmd/cmd_text_sdf.h"
#include "render/texture.h"
#include "glheader.h"

#define STB_TRUETYPE_IMPLEMENTATION 
#include "render/stb_truetype.h"

namespace purple{
    void TextRender::renderText(std::wstring text , 
            float left , 
            float bottom , 
            TextPaint &paint){
        //todo render text
        // Log::i(TAG , "start render text");

        SdfTextRenderCommand cmd(renderEngine_ , this);
        cmd.putParams(text , left , bottom , paint);
        cmd.runCommands();
    }

    int TextRender::createFontTextureRes(){
        fontTextureInfo_ = 
        TextureManager::getInstance()->createEmptyTexture2dArray(fontName_,
            texWidth_ , texHeight_ , texDepth_ , GL_RED);
        return fontTextureInfo_->textureId;
    }

    std::shared_ptr<CharInfo> TextRender::findCharInfo(wchar_t &ch , int index){
        if(charInfoMap_.find(ch) != charInfoMap_.end()){
            return charInfoMap_[ch];
        }

        std::shared_ptr<CharInfo> result = std::make_shared<CharInfo>();

        int width = 0;
        int height = 0;
        int offX = 0;
        int offY = 0;

        if(ch == L' '){
            width = SPACE_WIDTH;
        }

        unsigned char* sdfBitmap = stbtt_GetCodepointSDF(
            &fontInfo_, fontScale_, 
            ch , 0 , 128, -1.0f,
            &width, &height , &offX, &offY);
        if(sdfBitmap == nullptr || width <= 0 || height <= 0){
            Log::e(TAG ,"sdf data is null index = %d!" , index);
        }
        
        std::vector<float> coords = addBitmapToTextures(sdfBitmap , width, height);
        if(sdfBitmap != nullptr){
            stbtt_FreeSDF(sdfBitmap , nullptr);
            sdfBitmap = nullptr;
        }

        Log::e(TAG , "char width = %d , height = %d , offx = %d , offy = %d" 
            , width , height , offX , offY);

        result->value = ch;
        result->width = width;
        result->height = height;
        result->bearingX = offX;
        result->bearingY = -offY;
        result->textureId = fontTextureInfo_->textureId;
        putCoords(*result , coords);

        //add cache
        charInfoMap_[ch] = result;
        return result;
    }

    void TextRender::updateNextOffset(){
        if(offsetX_ + fontWidth_ > texWidth_){
            if(offsetY_ + fontHeight_ > texHeight_){
                if(offsetZ_ + 1 > texDepth_){
                    offsetZ_ = 1;//第0页 考虑必然是常用字符 不做替换 从第二页开始
                }
                offsetY_ = 0;
            }else{
                offsetY_ += fontHeight_;
            }
            offsetX_ = 0;
        }else{
            offsetX_ += fontWidth_;
        }
    }

    //设置纹理坐标信息
    void TextRender::putCoords(CharInfo &info , std::vector<float> &coords) const{
        if(coords.empty()){
            return;
        }

        for(int i = 0 ; i < 5 ; i++){
            info.textureCoords[i] = coords[i];
            Log::i(TAG , "textureCoords[%d] = %f" , i , info.textureCoords[i]);
        }//end for i
    }

    std::vector<float> TextRender::addBitmapToTextures(unsigned char *bitmap, 
            int width , 
            int height){
        updateNextOffset();//update offset data

        Log::i(TAG ,"copy sdf data to texture 2d array cur off_x : %d , off_y : %d , off_z : %d w :%d , h : %d",
            this->offsetX_ , this->offsetY_ , offsetZ_ , width , height);
        // fontTextureInfo_
        TextureManager::getInstance()->updateTexture2dArrayData(
            fontTextureInfo_ , 
            offsetX_ , 
            offsetY_ ,
            offsetZ_ , 
            width , height , 1 , bitmap);
        
        std::vector<float> texCoords(5);
        texCoords[0] = static_cast<float>(offsetX_) / static_cast<float>(texWidth_);
        texCoords[1] = static_cast<float>(offsetY_) / static_cast<float>(texHeight_);
        texCoords[2] = static_cast<float>(offsetX_ + width) / static_cast<float>(texWidth_);
        texCoords[3] = static_cast<float>(offsetY_ + height) / static_cast<float>(texHeight_);
        texCoords[4] = static_cast<float>(offsetZ_);

        return texCoords;
    }

    void TextRender::renderText(const wchar_t *text, 
            float left, 
            float bottom, 
            TextPaint &paint){
        renderText(std::wstring(text) , left , bottom , paint);
    }

    int TextRender::loadFontRes(std::string fontName, std::string fontFileAssetPath){
        int fontFileSize = 0;
        fontData_ = AssetManager::getInstance()->readFileAsBinRaw(fontFileAssetPath , fontFileSize);
        if(fontFileSize <= 0){
            Log::e(TAG , "Not found font file %s" , fontFileAssetPath.c_str());
            return -1;
        }
        Log::i(TAG , "%s file size : %d" , fontFileAssetPath.c_str() , fontFileSize);
        fontName_ = fontName;
        
        int errCode = -1;
        errCode = initFont();
        if(errCode < 0){
            return errCode;
        }
        errCode = createFontTextureRes();
        return errCode; 
    }

    int TextRender::initFont(){
        int errCode = stbtt_InitFont(&fontInfo_ , fontData_ , 0);
        // fontScale_ = stbtt_ScaleForPixelHeight(&fontInfo_ , static_cast<int>(FONT_DEFAULT_SIZE));
        fontScale_ = stbtt_ScaleForPixelHeight(&fontInfo_ , FONT_DEFAULT_SIZE);
        Log::i(TAG , "fontScale =  %f" , fontScale_);
        return errCode;
    }
}

