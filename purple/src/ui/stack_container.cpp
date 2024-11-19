#include "ui/stack_container.h"

namespace purple{
    StackContainer::~StackContainer(){
        Log::i("ui","StackContainer descontructor");
    }

    void StackContainer::onMeasure(int parentRequestWidth , int parentRequestHeight){
        int maxChildWidgetWidth = 0;
        int maxChildWidgetHeight = 0;
        for(PWidget widget: getChildrenWidgets()){
            if(widget == nullptr || widget->getVisible() == Gone){
                continue;
            }
            widget->measure(parentRequestWidth , parentRequestHeight);
            
            int widgetWidth = widget->getMarginLeft() + widget->getWidth() + widget->getMarginRight();
            if(maxChildWidgetWidth < widgetWidth){
                maxChildWidgetWidth = widgetWidth;
            }

            int widgetHeight = widget->getMarginTop() + widget->getHeight() + widget->getMarginBottom();
            if(maxChildWidgetHeight < widgetHeight){
                maxChildWidgetHeight = widgetHeight;
            }
        }//end for each

        measureSelf(parentRequestWidth ,parentRequestHeight, 
            maxChildWidgetWidth, maxChildWidgetHeight);//
    }

    void StackContainer::measureSelf(int parentRequestWidth , 
            int parentRequestHeight,
            int childMaxWidth , 
            int childMaxHeight){
        if(requestWidth_ == LAYOUT_MATCH_PARENT){
            setWidth(parentRequestWidth);
        }else if(requestWidth_ == LAYOUT_WRAP_CONTENT){
            setWidth(paddingLeft_ + paddingRight_ + childMaxWidth);
        }else{
            setWidth(requestWidth_);
        }

        if(requestHeight_ == LAYOUT_MATCH_PARENT){
            setHeight(parentRequestHeight);
        }else if(requestHeight_ == LAYOUT_WRAP_CONTENT){
            setHeight(paddingTop_ + paddingBottom_ + childMaxHeight);
        }else{
            setHeight(requestHeight_);
        }
    }
        
    void StackContainer::onLayout(int l,int t){
        this->Container::onLayout(l , t);

        for(PWidget widget: getChildrenWidgets()){
            if(widget == nullptr || widget->getVisible() == Gone){
                continue;
            }

            switch(widget->getLayoutGravity()){
                case TopLeft:
                    widget->layout(
                        paddingLeft_ + left + widget->getMarginLeft(), 
                        top - paddingTop_ - widget->getMarginTop()
                    );
                    break;
                case TopCenter:
                    widget->layout(
                        left + (getWidth() >> 1) - (widget->getWidth() >> 1), 
                        top - paddingTop_ - widget->getMarginTop()
                    );
                    break;
                case TopRight:
                    widget->layout(
                        left + getWidth() - paddingRight_ - widget->getWidth() - widget->getMarginRight(), 
                        top - paddingTop_ - widget->getMarginTop()
                    );
                    break;
                case CenterLeft:
                    widget->layout(
                        paddingLeft_ + left + widget->getMarginLeft(), 
                        top - (getHeight() >> 1) + (widget->getHeight() >> 1)
                    );
                    break;
                case Center:
                    widget->layout(
                        left + (getWidth() >> 1) - (widget->getWidth() >> 1), 
                        top - (getHeight() >> 1) + (widget->getHeight() >> 1)
                    );
                    break;
                case CenterRight:
                    widget->layout(
                        left + getWidth() - paddingRight_ - widget->getMarginRight() - widget->getWidth(), 
                        top - (getHeight() >> 1) + (widget->getHeight() >> 1)
                    );
                    break;
                case BottomLeft:
                    widget->layout(
                        left + paddingLeft_ + widget->getMarginLeft(),
                        top - getHeight() + paddingBottom_ + widget->getMarginBottom() + widget->getHeight()
                    );
                    break;
                case BottomCenter:
                    widget->layout(
                        left + (getWidth() >> 1) - (widget->getWidth() >> 1),
                        top - getHeight() + paddingBottom_ + widget->getMarginBottom() + widget->getHeight()
                    );
                    break;
                case BottomRight:
                    widget->layout(
                        left + getWidth() - paddingRight_ - widget->getMarginRight() - widget->getWidth(),
                        top - getHeight() + paddingBottom_ + widget->getMarginBottom() + widget->getHeight()
                    );
                    break;
                default:
                    break;
            }//end switch
        }//end for each
    }
}