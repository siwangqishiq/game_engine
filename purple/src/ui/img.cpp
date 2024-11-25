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
            case ImgScale::Mode::FitCenter:{
                dstRect = findFitScaleDstRect(srcRect,viewRect);
                break;
            }
            case ImgScale::Mode::FitTop:{
                dstRect = findFitScaleDstRect(srcRect,viewRect);
                dstRect.top = viewRect.top;
                break;
            }
            case ImgScale::Mode::FitBottom:{
                dstRect = findFitScaleDstRect(srcRect,viewRect);
                dstRect.top = viewRect.top - viewRect.height + dstRect.height;
                break;
            }
            case ImgScale::Mode::FitXY:{
                dstRect = viewRect;
                break;
            }
            case ImgScale::Mode::Center:{
                dstRect = findCenterDstRect(srcRect,viewRect);
                break;
            }
            case ImgScale::Mode::CenterCrop:{
                dstRect = findCenterCropDstRect(srcRect,viewRect);
                break;
            }
            case ImgScale::Mode::CenterInside:{
                break;
            }
            default:
                break;
        }//end switch


        auto render = purple::Engine::getRenderEngine();
        auto speiteBatch = render->getSpriteBatch();
        speiteBatch->begin();
        speiteBatch->renderImage(*textureImage_ , srcRect , dstRect);
        speiteBatch->end();
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

    Rect Img::findCenterCropDstRect(Rect &srcRect,Rect &viewRect){
        Rect dstRect;
        const float ratio = srcRect.width / srcRect.height;
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


        if(dstRect.left < viewRect.left){
            dstRect.left = viewRect.left;
        }

        if(dstRect.top > viewRect.top){
            dstRect.top = viewRect.top;
        }

        return dstRect;
    }

}