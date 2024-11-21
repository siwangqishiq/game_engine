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
            FitCenter,//被等比缩放到能够填充控件大小
            FitTop,//
            FitBottom,
            FitXY,
            Center,
            CenterCrop,
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
    };
}