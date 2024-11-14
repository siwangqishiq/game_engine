
#include "ui/colum_container.h"
#include <limits>


namespace purple{

    int ColumContainer::measureChildWidgetSize(PWidget childWidget,
                        int limitWidth, 
                        int limitHeight,
                        std::vector<PWidget> &hasWeightList){
        int costH = childWidget->getMarginTop() + childWidget->getMarginBottom();

        childWidget->measure(limitWidth , limitHeight);
        if(childWidget->getLayoutWeight() > 0){
            hasWeightList.emplace_back(childWidget);
        }else{
            costH += childWidget->getHeight();
        }//end if
        return costH;
    }

    void ColumContainer::measure(int parentRequestWidth , int parentRequestHeight){
        // Log::i("ui","ColumContainer measure...");

        int maxChildWidth = 0;
        int childTotalHeight = 0;

        std::vector<PWidget> weightWeightList;

        int totalCostHeight = 0;
        for(PWidget &child: getChildrenWidgets()){
            //测量子布局
            const int costH = measureChildWidgetSize(child,
                parentRequestWidth - paddingLeft_ - paddingRight_ 
                    - child->getMarginLeft()- child->getMarginRight()
                    , parentRequestHeight, weightWeightList);

            totalCostHeight += costH;
            if(maxChildWidth < child->getWidth()){
                maxChildWidth = child->getWidth();
            }
            childTotalHeight += (child->getHeight() + child->getMarginTop() + child->getMarginBottom());
        }//end for each

        if(!weightWeightList.empty()){
            int realHeight = parentRequestHeight;
            if(requestHeight_ == LAYOUT_MATCH_PARENT || requestHeight_ == LAYOUT_WRAP_CONTENT){
                realHeight = parentRequestHeight;
            }else{
                realHeight = requestHeight_ - paddingTop_ - paddingBottom_;
            }
            const int weightTotalHeight = realHeight - totalCostHeight;
            int totalWeight = 0;
            for(auto &p : weightWeightList){
                totalWeight += p->getLayoutWeight();
            }//end for each

            float cubeSize = static_cast<float>(weightTotalHeight) / static_cast<float>(totalWeight);
            for(auto &p : weightWeightList){
                p->setHeight(cubeSize * p->getLayoutWeight());
                // Log::i("test" , "weightWeight %d , left : %d top:%d  width:%d", p->getHeight(),p->left,
                //     p->top,p->getWidth());
            }//end for each
        }


        //计算自身大小
        //self width
        if(requestWidth_ == LAYOUT_MATCH_PARENT){
            width_ = parentRequestWidth;
        }else if(this->requestWidth_ == LAYOUT_WRAP_CONTENT){
            width_ = paddingLeft_ + maxChildWidth + paddingRight_;
        }else{
            width_ = requestWidth_;
        }

        // self height
        if(requestHeight_ == LAYOUT_MATCH_PARENT){
            height_ = parentRequestHeight;
        }else if(requestHeight_ == LAYOUT_WRAP_CONTENT){
            height_ = paddingTop_ + childTotalHeight + paddingBottom_;
        }else{
            height_ = requestHeight_;
        }
    }

    void ColumContainer::layout(int l,int t){
        this->Widget::layout(l, t);

        int x = left;
        int y = top - paddingTop_;

        const int childLen = getChildrenWidgets().size();
        for(int i = 0; i < childLen; i++){
            PWidget child = getChildrenWidgets()[i];
            if(child == nullptr){
                continue;
            }

            const int childTop = y - child->getMarginTop();
            auto gravity = child->getLayoutGravity();
            if(gravity == LayoutGravity::TopCenter
                || gravity == LayoutGravity::Center
                || gravity == LayoutGravity::CenterLeft){
                child->layout(x + (width_ >> 1) - (child->getWidth() >> 1), childTop);
            }else if(gravity == LayoutGravity::TopRight 
                || gravity == LayoutGravity::CenterRight
                || gravity == LayoutGravity::BottomRight){
                child->layout(x + width_ - child->getWidth() - child->getMarginRight() - paddingRight_
                    , childTop);
            }else{
                child->layout(x + paddingLeft_ + child->getMarginLeft(),childTop);
            }
            
            y -= child->getMarginTop() + child->getHeight() + child->getMarginBottom();
        }//end for i
    }

    ColumContainer::~ColumContainer(){
        Log::i("widget","ColumContainer desstory");
    }
}
