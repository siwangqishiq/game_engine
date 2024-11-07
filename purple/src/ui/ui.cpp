#include "ui/ui.h"
#include "log.h"
#include "purple.h"

namespace purple{

    UiRoot::UiRoot(int w, int h) {
        this->rootWidth_ = w;
        this->rootHeight_ = h;
        Log::i("ui", "UiRoot create width:%d, height:%d"
            ,this->rootWidth_
            ,this->rootHeight_);
    }

    UiRoot::~UiRoot(){
        Log::i("ui", "UiRoot destoryed");
    }


    void UiRoot::build(RenderBlock block){
        // widget --> render command

    }

     void UiRoot::renderUi(){
        // Log::i("ui", "UiRoot begin renderUI...");
        auto renderEngine = purple::Engine::getRenderEngine();
        auto myImageRenderBlock = [self = this,render = renderEngine](int w, int h){
            auto shapeBatch = render->getShapeBatch();
            shapeBatch->begin();
            purple::RectI rect;
            rect.left = 0;
            rect.top = 200;
            rect.width = 200;
            rect.height = 200;
            
            purple::Paint paint;
            paint.color = glm::vec4(1.0f, 0.0f,0.0f,1.0f);

            purple::RectI bgRect;
            bgRect.left = 0;
            bgRect.top = h;
            bgRect.width = w;
            bgRect.height = h;
            paint.color = glm::vec4(1.0f, 0.0f,0.0f,0.5f);
            shapeBatch->renderRect(bgRect , paint);

            shapeBatch->renderRect(rect , paint);
            paint.color = glm::vec4(0.0f, 1.0f,1.0f,1.0f);
            shapeBatch->renderCircle(100,100,60,paint);
            shapeBatch->end();

            purple::TextPaint textPaint;
            textPaint.textColor = glm::vec4(0.0f, 0.0f , 0.0f , 1.0f);
            textPaint.setTextSize(400.0f);
            purple::Engine::getRenderEngine()->renderText(L"你好世界",0,100,textPaint);
        };

        if(this->textureInfo_ == nullptr){
            this->textureInfo_ = 
                renderEngine->buildVirtualTexture("my_image",1024,1024,myImageRenderBlock);
        }else{
            renderEngine->updateVirtualTexture(this->textureInfo_, myImageRenderBlock);
        }


        purple::TextureImage img = purple::TextureImage(this->textureInfo_);
        purple::Rect srcRect = img.getRect();

        purple::Rect dstRect;
        dstRect.left = 0;
        dstRect.top = 400;
        dstRect.width = 100;
        dstRect.height = 100;

        renderEngine->getSpriteBatch()->begin();
        renderEngine->getSpriteBatch()->renderImage(img, srcRect, dstRect);
        renderEngine->getSpriteBatch()->end();

        renderEngine->getShapeBatch()->begin();
        purple::Paint paint;
        paint.color = glm::vec4(1.0f, 0.0f,0.0f,1.0f);
        dstRect.top = 200;
        renderEngine->getShapeBatch()->renderRect(dstRect ,paint);
        renderEngine->getShapeBatch()->end();
        
        // TextureManager::getInstance()->freeTexture(*myImage);
     }


    void ViewWidget::setWidth(int width){
        this->width = width;
    }
    void ViewWidget::setHeight(int height){
        this->height = height;
    }

    void ViewWidget::onRender(){
    }

    void ViewWidget::onMeasure(int w , int h){

    }

    void ContainerWidget::onRender(){

    }
    
    void ContainerWidget::onLayoutChild(){
        
    }

    std::shared_ptr<ContainerWidget> Container(ChildWidgetBlock block){
        auto container = std::make_shared<ContainerWidget>();
        return container;
    }
}

