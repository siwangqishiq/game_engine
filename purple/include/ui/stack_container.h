#pragma once

#include "ui.h"
#include "color.h"
#include "render/common.h"

namespace purple{
    class StackContainer : public Container{
    public:
        StackContainer(int reqWidth , int reqHeight):Container(reqWidth, reqHeight){
        }

        StackContainer():Container(LAYOUT_MATCH_PARENT,LAYOUT_MATCH_PARENT){
        }

        virtual void onMeasure(MeasureSpecMode widthSpecMode, 
                                int widthValue, 
                                MeasureSpecMode heightSpecMode,
                                int heightValue) override;

        virtual void onLayout(int l,int t) override;
        
        virtual ~StackContainer();
        
    private:
        void measureSelf(int parentRequestWidth , 
                        int parentRequestHeight,
                        int childMaxWidth , 
                        int childMaxHeight);
    };//end class
}