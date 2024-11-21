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

        const int dstWidth = getWidth() - paddingRight_ - paddingLeft_;
        const int dstHeight = getHeight() - paddingBottom_ - paddingTop_;
        Rect dstRect(left + paddingLeft_, top - paddingTop_, 
                            dstWidth, dstHeight);
        // Log::i("debug" , "render text id in img %d", textureImage_->getTextureId());
        auto render = purple::Engine::getRenderEngine();
        auto speiteBatch = render->getSpriteBatch();
        speiteBatch->begin();
        switch(scaleMode_){
            case FitCenter:
            case FitTop:
            case FitBottom:
            case FitXY:
            case ScaleCenter:
            case ScaleCrop:
            case ScaleInside:
                speiteBatch->renderImage(*textureImage_ , srcRect , dstRect);
                break;
            default:
                break;
        }//end switch
        speiteBatch->end();
    }
}