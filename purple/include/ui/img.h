#pragma once

#include "ui.h"
#include "color.h"
#include "render/common.h"
#include "render/sprite.h"

namespace purple{
    class ImageSource{
    public:
        static std::shared_ptr<TextureImage> fromAsset(std::string assetPath);

        static std::shared_ptr<TextureImage> fromFile(std::string path);
    };

    namespace ImgScale{
        enum Mode {
            //被等比缩放到能够填充控件大小
            FitCenter,
            
            FitTop,
            FitBottom,
            FitXY,

            //图片置于view的中心 会发生裁剪
            Center, 

            //图片置于view的中心 若图片原始尺寸大于view尺寸 进行缩放 保证覆盖满view  会产生剪裁
            CenterCrop, 

            //图片置于view的中心 若图片原始尺寸大于view尺寸 进行缩放 保证位图被完整显示 不会产生剪裁
            CenterInside
        };
    }

    class Img : public Widget{
        public:
            Img(int reqWidth,int reqHeight):Widget(reqWidth,reqHeight){}

            Img(std::shared_ptr<TextureImage> tex,int reqWidth,int reqHeight):
                Widget(reqWidth , reqHeight),textureImage_(tex){
            }

            template<typename T>
            T& setImage(std::shared_ptr<TextureImage> tex){
                this->textureImage_ = tex;
                return static_cast<T&>(*this);
            }
            
            template<typename T>
            T& setScaleMode(ImgScale::Mode mode){
                this->scaleMode_ = mode;
                return static_cast<T&>(*this);
            }

            virtual void onMeasure(int parentRequestWidth , int parentRequestHeight) override;

            virtual void onRender() override;

            ~Img();
        private:
            std::shared_ptr<TextureImage> textureImage_ = nullptr;
            
            ImgScale::Mode scaleMode_ = ImgScale::Mode::FitCenter;

            Rect findFitScaleDstRect(Rect &srcRect,Rect &viewRect);

            Rect findCenterDstRect(Rect &srcRect,Rect &viewRect);

            Rect findCenterCropDstRect(Rect &srcRect,Rect &viewRect);
    };
}