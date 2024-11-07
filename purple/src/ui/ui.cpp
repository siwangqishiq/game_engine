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

    void UiRoot::measure(){
        Log::i("widget" , "UiRoot start measure");
        if(this->rootContainer_ == nullptr){
            return;
        }

        this->rootContainer_->measure(this->rootWidth_ , this->rootHeight_);
    }
    
    void UiRoot::layout(){
        Log::i("widget" , "UiRoot start layout");
        if(this->rootContainer_ == nullptr){
            return;
        }

        this->rootContainer_->layout(0 , this->rootHeight_);
    }
    
    void UiRoot::render(){
        Log::i("widget" , "UiRoot start render");
        if(this->rootContainer_ == nullptr){
            return;
        }

        this->rootContainer_->render();
    }

    void UiRoot::startRenderUI(){
        measure();
        layout();
        render();
    }

    // void UiRoot::renderUi(){
    //     // Log::i("ui", "UiRoot begin renderUI...");
    //     auto renderEngine = purple::Engine::getRenderEngine();
    //     auto myImageRenderBlock = [self = this,render = renderEngine](int w, int h){
    //         auto shapeBatch = render->getShapeBatch();
    //         shapeBatch->begin();
    //         purple::RectI rect;
    //         rect.left = 0;
    //         rect.top = 200;
    //         rect.width = 200;
    //         rect.height = 200;
            
    //         purple::Paint paint;
    //         paint.color = glm::vec4(1.0f, 0.0f,0.0f,1.0f);

    //         purple::Rect bgRect;
    //         bgRect.left = 0;
    //         bgRect.top = h;
    //         bgRect.width = w;
    //         bgRect.height = h;
    //         paint.color = glm::vec4(1.0f, 0.0f,0.0f,0.5f);
    //         shapeBatch->renderRect(bgRect , paint);

    //         shapeBatch->renderRect(rect , paint);
    //         paint.color = glm::vec4(0.0f, 1.0f,1.0f,1.0f);
    //         shapeBatch->renderCircle(100,100,60,paint);
    //         shapeBatch->end();

    //         purple::TextPaint textPaint;
    //         textPaint.textColor = glm::vec4(1.0f, 0.0f , 0.0f , 1.0f);
    //         textPaint.setTextSize(400.0f);
    //         purple::Engine::getRenderEngine()->renderText(L"你好世界",0,100,textPaint);

    //         textPaint.setTextSize(200.0f);
    //         purple::Engine::getRenderEngine()->renderTextWithRect(L"你好世界你好世界你好世界你好世界你好世界你好世界你好世界你好世界你好世界你好世界"
    //                 ,bgRect,textPaint,nullptr);
    //     };

    //     if(this->textureInfo_ == nullptr){
    //         this->textureInfo_ = 
    //             renderEngine->buildVirtualTexture("my_image",1024,1024,myImageRenderBlock);
    //     }else{
    //         renderEngine->updateVirtualTexture(this->textureInfo_, myImageRenderBlock);
    //     }


    //     purple::TextureImage img = purple::TextureImage(this->textureInfo_);
    //     purple::Rect srcRect = img.getRect();

    //     purple::Rect dstRect;
    //     dstRect.left = 0;
    //     dstRect.top = 400;
    //     dstRect.width = 100;
    //     dstRect.height = 100;

    //     renderEngine->getSpriteBatch()->begin();
    //     renderEngine->getSpriteBatch()->renderImage(img, srcRect, dstRect);
    //     renderEngine->getSpriteBatch()->end();

    //     renderEngine->getShapeBatch()->begin();
    //     purple::Paint paint;
    //     paint.color = glm::vec4(1.0f, 0.0f,0.0f,1.0f);
    //     dstRect.top = 200;
    //     renderEngine->getShapeBatch()->renderRect(dstRect ,paint);
    //     renderEngine->getShapeBatch()->end();
        
    //     // TextureManager::getInstance()->freeTexture(*myImage);
    //  }

    Widget::Widget(){
        Log::i("widget","widget construct");
    }

    void Widget::setParentWidget(Container *parent){
        this->parent_ = parent;
    }

    void Widget::setBackgroundColor(glm::vec4 color){
        this->bgColor_ = color;
    }

    void Widget::measure(int parentRequestWidth , int parentRequestHeight){
        if(this->width == LAYOUT_MATCH_PARENT){
            this->width = parentRequestWidth;
        }

        if(this->height == LAYOUT_MATCH_PARENT){
            this->height = parentRequestHeight;
        }
    }

    void Widget::layout(int l,int t){
        this->left = l;
        this->top = t;
    }

    void Widget::render(){
        Rect bgRect(this->left , this->top , this->width , this->height);
        Paint bgPaint;
        bgPaint.color = this->bgColor_;

        auto render = purple::Engine::getRenderEngine();
        auto shapeBatch = render->getShapeBatch();
        shapeBatch->begin();
        shapeBatch->renderRect(bgRect, bgPaint);
        shapeBatch->end();
    }

    Widget::~Widget(){
        Log::i("widget","widget desstory");
    }

    void Container::addChild(PWidget widget){
        this->children_.push_back(widget);
        widget->setParentWidget(this);
    }

    void Container::removeChild(PWidget widget){
        widget->setParentWidget(nullptr);
        this->children_.erase(std::find(this->children_.begin(),this->children_.end(),widget));
    }

    void Container::measure(int parentRequestWidth , int parentRequestHeight){
        //set self width and height
        this->Widget::measure(parentRequestWidth, parentRequestHeight);
        
        //set child measure
        if(this->children_.empty()){
            return;
        }

        for(auto &child: this->getChildrenWidgets()){
            child->measure(this->width , this->height);
        }//end for each
    }

    void Container::layout(int l,int t){
        this->Widget::layout(l,t);
        //Container绝对布局 不需要设置子Widget位置
    }

    void Container::render(){
        this->renderContainerSelf();

        //set child measure
        if(this->children_.empty()){
            return;
        }

        for(auto &child: this->getChildrenWidgets()){
            child->render();
        }//end for each
    }

    void Container::renderContainerSelf(){
        this->Widget::render();
    }

    std::vector<PWidget> Container::getChildrenWidgets(){
        return this->children_;
    }

    PWidget FunContainer(std::vector<PWidget> children){
        std::shared_ptr<Container> container = std::make_shared<Container>();

        //set container
        
        return container;
    }


}

