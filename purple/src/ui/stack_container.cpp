#include "ui/stack_container.h"

namespace purple{
    StackContainer::~StackContainer(){
        Log::i("ui","StackContainer descontructor");
    }

    void StackContainer::onMeasure(MeasureSpecMode widthSpecMode, 
                                int widthValue, 
                                MeasureSpecMode heightSpecMode,
                                int heightValue){

        this->Widget::onMeasure(widthSpecMode, widthValue , heightSpecMode , heightValue);
        
        for(auto &pWidget : getChildrenWidgets()){
            if(pWidget == nullptr){
                continue;
            }

            //width set
            MeasureSpecMode widthMode = MeasureSpecMode::Unset;
            int widthValue = 0;
            const int limitMaxWidth = this->getWidth() 
                    - this->paddingLeft_ - this->paddingRight_
                    - pWidget->getMarginLeft() - pWidget->getMarginRight();
            if(pWidget->getRequestWidth() == LAYOUT_MATCH_PARENT){
                widthMode = MeasureSpecMode::Exactly;
                widthValue = std::max(0, limitMaxWidth);
            }else if(pWidget->getRequestWidth() == LAYOUT_WRAP_CONTENT){
                widthMode = MeasureSpecMode::Atmost;
                widthValue = limitMaxWidth;
            }else{
                widthMode = MeasureSpecMode::Exactly;
                widthValue = std::min(pWidget->getRequestWidth() , limitMaxWidth);
            }

            //height set
            MeasureSpecMode heightMode = MeasureSpecMode::Unset;
            int heightValue = 0;
            const int limitMaxHeight = this->getHeight() 
                - this->paddingTop_ - this->paddingBottom_
                - pWidget->getMarginTop() - pWidget->getMarginBottom();
            if(pWidget->getRequestHeight() == LAYOUT_MATCH_PARENT){
                heightMode = MeasureSpecMode::Exactly;
                heightValue = std::max(0, limitMaxHeight);
            }else if(pWidget->getRequestHeight() == LAYOUT_WRAP_CONTENT){
                heightMode = MeasureSpecMode::Atmost;
                heightValue = limitMaxHeight;
            }else{
                heightMode = MeasureSpecMode::Exactly;
                heightValue = std::min(pWidget->getRequestHeight() , limitMaxHeight);
            }

            pWidget->measure(widthMode , widthValue , heightMode , heightValue);
        }//end for each                                  
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