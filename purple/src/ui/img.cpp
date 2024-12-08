#include "ui/img.h"
#include "purple.h"
#include <algorithm>
#include "utils.h"

namespace purple{
    
    std::shared_ptr<TextureImage> ImageSource::fromAsset(std::string assetPath){
        return BuildImageByAsset(assetPath);
    }
        
    std::shared_ptr<TextureImage> ImageSource::fromFile(std::string path){
        return nullptr;
    }

    Img::~Img(){
    }

    void Img::onMeasure(MeasureSpecMode widthSpecMode, 
                        int widthValue, 
                        MeasureSpecMode heightSpecMode,
                        int heightValue){
        if(widthSpecMode == MeasureSpecMode::Exactly){
            setWidth(widthValue);
        }else if(widthSpecMode == MeasureSpecMode::Atmost){
            int contentWidth = 0;
            if(textureImage_ != nullptr){
                contentWidth = textureImage_->getWidth();
            }
            const int realWidth = std::min(paddingLeft_ + paddingRight_ + contentWidth , widthValue);
            setWidth(realWidth);
        }else if(widthSpecMode == MeasureSpecMode::Unset){
            setWidth(0);
        }

        if(heightSpecMode == MeasureSpecMode::Exactly){
            setHeight(heightValue);
        }else if(heightSpecMode == MeasureSpecMode::Atmost){
            int contentHeight = 0;
            if(textureImage_ != nullptr){
                contentHeight = textureImage_->getHeight();
            }
            const int realHeight = std::min(paddingTop_ + paddingBottom_ + contentHeight , heightValue);
            setHeight(realHeight);
        }else if(widthSpecMode == MeasureSpecMode::Unset){
            setHeight(0);
        }

        // Log::i("ui","Image Widget measue size %d , %d   %s" , width_ , height_ , this->id.c_str());
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
        // if(dstRect.left >= viewRect.left && dstRect.top <= viewRect.top){
        //     // std::cout << "this src is in view" << std::endl;
        //     return dstRect;
        // }

        if(isCrop){
            dstRect.width = 0.0f;
            dstRect.height = 0.0f;
        }else{
            // scale width
            const float scaleWidth = viewRect.width / dstRect.width;
            Point pw{dstRect.left , dstRect.top};
            ScaleWithPoint(pw , scaleWidth , dstCenter);
            float wLeft = pw.x;
            float wTop = pw.y;

            const float scaleHeight = viewRect.height / dstRect.height;
            Point ph{dstRect.left , dstRect.top};
            ScaleWithPoint(ph , scaleHeight , dstCenter);

            float hLeft = scaleHeight * dstRect.left + viewCenter.x - viewCenter.x * scaleHeight;
            float hTop = scaleHeight * dstRect.top + viewCenter.y - viewCenter.y * scaleHeight;
            
            float scale = 1.0f;

            dstRect.width = dstRect.width * scale;
            dstRect.height = dstRect.height * scale;

            // dstRect.left = scaleWidth * dstRect.left + viewCenter.x - viewCenter.x * scaleWidth;
            // dstRect.top = scaleWidth * dstRect.top + viewCenter.y - viewCenter.y * scaleWidth;
            // dstRect.width = scaleWidth * dstRect.width;
            // dstRect.height = scaleWidth * dstRect.height;
        }

      

        // //do scale and src crop
        // const float srcWidth = srcRect.width;
        // const float srcHeight = srcRect.height;

        // const float scaleW = viewRect.width / srcWidth;
        // const float scaleH = viewRect.height / srcHeight;
        // // const float scale = isCrop?std::max(scaleW , scaleH):std::min(scaleW , scaleH);
        // const float scale = isCrop?std::max(scaleH , scaleW):std::min(scaleW , scaleH);
        
        // //scale with center point
        // dstRect.width = scale * srcWidth;
        // dstRect.height = scale * srcHeight;

        // dstRect.left = scale * dstRect.left + viewCenter.x - viewCenter.x * scale;
        // dstRect.top = scale * dstRect.top + viewCenter.y - viewCenter.y * scale;

        // // crop src 
        // if(dstRect.top > viewRect.top){
        //     srcRect.top = srcRect.top - (dstRect.top  - viewRect.top) / (scale);
        //     srcRect.height = viewRect.height / scale;

        //     dstRect.top = viewRect.top;
        //     dstRect.height = viewRect.height;
        // }else if(dstRect.left < viewRect.left){
        //     srcRect.left = srcRect.left + (viewRect.left - dstRect.left) / (scale);
        //     srcRect.width = viewRect.width / scale;

        //     dstRect.left = viewRect.left;
        //     dstRect.width = viewRect.height;
        // }
        return dstRect;
    }

    Rect Img::findCenterCropDstRect(Rect &srcRect,Rect &viewRect){
        return findCenterModeRect(srcRect , viewRect , true);
    }

    Rect Img::findCenterInsideDstRect(Rect &srcRect,Rect &viewRect){
        return findCenterModeRect(srcRect , viewRect , false);
    }
}