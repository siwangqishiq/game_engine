#include "ui/img.h"
#include "purple.h"

namespace purple{
    
    std::shared_ptr<TextureImage> ImageSource::fromAsset(std::string assetPath){
        return BuildImageByAsset(assetPath);
    }
        
    std::shared_ptr<TextureImage> ImageSource::fromFile(std::string path){
        return nullptr;
    }

    Img::~Img(){
    }

    void Img::onMeasure(int parentRequestWidth , int parentRequestHeight){
        if(requestWidth_ == LAYOUT_MATCH_PARENT){
            width_ = parentRequestWidth;
        }else if(requestWidth_ == LAYOUT_WRAP_CONTENT){
            width_ = paddingLeft_ + paddingRight_;
            if(textureImage_ != nullptr ){
                width_ += textureImage_->getWidth();
            }
        }else{
            width_ = requestWidth_;
        }

        if(requestHeight_ == LAYOUT_MATCH_PARENT){
            height_ = parentRequestHeight;
        }else if(requestHeight_ == LAYOUT_WRAP_CONTENT){
            height_ = paddingTop_ + paddingBottom_;
            if(textureImage_ != nullptr ){
                height_ += textureImage_->getHeight();
            }
        }else{
            height_ = requestHeight_;
        }
    }
            
    void Img::onRender(){
        this->Widget::onRender();

        //render image
        if(textureImage_ == nullptr 
            || textureImage_->getWidth() == 0 
            || textureImage_->getHeight() == 0){
            return;
        }

        Rect srcRect = textureImage_->getRect();

        const int viewWidth = getWidth() - paddingRight_ - paddingLeft_;
        const int viewHeight = getHeight() - paddingBottom_ - paddingTop_;
        Rect viewRect(left + paddingLeft_, 
                            top - paddingTop_, 
                            viewWidth, viewHeight);
        // Log::i("debug" , "render text id in img %d", textureImage_->getTextureId());
        Rect dstRect;
        switch(scaleMode_){
            case ImgScale::Mode::FitCenter:
                dstRect = findFitScaleDstRect(srcRect,viewRect);
                break;
            case ImgScale::Mode::FitTop:
                dstRect = findFitTopDstRect(srcRect,viewRect);
                break;
            case ImgScale::Mode::FitBottom:
                dstRect = findFitBottomDstRect(srcRect,viewRect);
                break;
            case ImgScale::Mode::FitXY:
                dstRect = viewRect;
                break;
            case ImgScale::Mode::Center:
                dstRect = findCenterDstRect(srcRect,viewRect);
                break;
            case ImgScale::Mode::CenterCrop:
                dstRect = findCenterCropDstRect(srcRect,viewRect);
                break;
            case ImgScale::Mode::CenterInside:
                dstRect = findCenterInsideDstRect(srcRect,viewRect);
                break;
            default:
                break;
        }//end switch


        auto render = purple::Engine::getRenderEngine();
        auto speiteBatch = render->getSpriteBatch();
        speiteBatch->begin();
        speiteBatch->renderImage(*textureImage_ , srcRect , dstRect);
        speiteBatch->end();
    }

    Rect Img::findFitTopDstRect(Rect &srcRect,Rect &viewRect){
        Rect dstRect = findFitScaleDstRect(srcRect,viewRect);
        dstRect.top = viewRect.top;
        return dstRect;
    }

    Rect Img::findFitBottomDstRect(Rect &srcRect,Rect &viewRect){
        Rect dstRect = findFitScaleDstRect(srcRect,viewRect);
        dstRect.top = viewRect.top - viewRect.height + dstRect.height;
        return dstRect;
    }

    Rect Img::findFitScaleDstRect(Rect &srcRect,Rect &viewRect){
        const float ratio = srcRect.width / srcRect.height;
        Rect dstRect;
        if(viewRect.width >= viewRect.height){
            dstRect.height = viewRect.height;
            dstRect.width = dstRect.height * ratio;
            if(dstRect.width > viewRect.width){
                dstRect.width = viewRect.width;
                dstRect.height = dstRect.width / ratio;
                dstRect.left = viewRect.left;
                dstRect.top = viewRect.top - viewRect.height / 2.0f + dstRect.height / 2.0f;
            }else{
                dstRect.left = viewRect.left + viewRect.width / 2.0f - dstRect.width / 2.0f;
                dstRect.top = viewRect.top;
            }
        }else{
            dstRect.width = viewRect.width;
            dstRect.height = viewRect.width/ ratio;
            if(dstRect.height > viewRect.height){
                dstRect.height = viewRect.height;
                dstRect.width = dstRect.height * ratio;
                dstRect.left = viewRect.left + viewRect.width / 2.0f - dstRect.width / 2.0f;
                dstRect.top = viewRect.top;
            }else{
                dstRect.left = viewRect.left;
                dstRect.top = viewRect.top - viewRect.height / 2.0f + dstRect.height / 2.0f;
            }
        }
        return dstRect;
    }

    Rect Img::findCenterDstRect(Rect &srcRect,Rect &viewRect){
        Rect dstRect;
        if(srcRect.width <= viewRect.width){
            dstRect.width = srcRect.width;
            dstRect.left = viewRect.left + viewRect.width / 2.0f - dstRect.width / 2.0f;
        } else { //原图大于view 需要截断
            dstRect.width = viewRect.width;
            dstRect.left = viewRect.left;

            srcRect.left = srcRect.left + (srcRect.width - viewRect.width) / 2.0f;
            srcRect.width = dstRect.width;
        }

        if(srcRect.height <=viewRect.height){
            dstRect.height = srcRect.height;
            dstRect.top = viewRect.top - viewRect.height / 2.0f + dstRect.height / 2.0f;
        }else{
            dstRect.height = viewRect.height;
            dstRect.top = viewRect.top;

            srcRect.top = srcRect.top - (srcRect.height - viewRect.height)/2.0f;
            srcRect.height = viewRect.height;
        }
        return dstRect;
    }

    Rect Img::findCenterModeRect(Rect &srcRect,Rect &viewRect,bool isCrop){
        Rect dstRect;
        dstRect.left = viewRect.left;
        dstRect.top = viewRect.top;
        dstRect.width = srcRect.width;
        dstRect.height = srcRect.height;

        auto dstCenter = dstRect.center();
        auto viewCenter = viewRect.center();
        float tranX = dstCenter.x - viewCenter.x;
        float tranY = dstCenter.y - viewCenter.y;

        dstRect.left -= tranX;
        dstRect.top -= tranY;

        // is in view quit
        if(dstRect.left >= viewRect.left && dstRect.top <= viewRect.top){
            return dstRect;
        }
    
        //do scale and src crop
        const float srcWidth = srcRect.width;
        const float srcHeight = srcRect.height;

        const float scaleW = viewRect.width / srcWidth;
        const float scaleH = viewRect.height / srcHeight;
        const float scale = isCrop?std::max(scaleW , scaleH):std::min(scaleW , scaleH);
        
        //scale with center point
        dstRect.width = scale * srcWidth;
        dstRect.height = scale * srcHeight;

        dstRect.left = scale * dstRect.left + viewCenter.x - viewCenter.x * scale;
        dstRect.top = scale * dstRect.top + viewCenter.y - viewCenter.y * scale;

        // crop src 
        if(dstRect.top > viewRect.top){
            srcRect.top = srcRect.top - (dstRect.top  - viewRect.top) / (scale);
            srcRect.height = viewRect.height / scale;
                        
            dstRect.top = viewRect.top;
            dstRect.height = viewRect.height;
        }else if(dstRect.left < viewRect.left){
            srcRect.left = srcRect.left + (viewRect.left - dstRect.left) / (scale);
            srcRect.width = viewRect.width / scale;

            dstRect.left = viewRect.left;
            dstRect.width = viewRect.height;
        }
        return dstRect;
    }

    Rect Img::findCenterCropDstRect(Rect &srcRect,Rect &viewRect){
        return findCenterModeRect(srcRect , viewRect , true);
    }

    Rect Img::findCenterInsideDstRect(Rect &srcRect,Rect &viewRect){
        return findCenterModeRect(srcRect , viewRect , false);
    }
}