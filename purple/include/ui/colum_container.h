#pragma once

#include "ui.h"
#include "color.h"
#include "render/common.h"

namespace purple{
    class ColumContainer : public Container{
    public:
        ColumContainer(int w , int h):Container(w, h){
        }
        
        ColumContainer():Container(LAYOUT_MATCH_PARENT, LAYOUT_MATCH_PARENT){
        }

        virtual ~ColumContainer();

        virtual void onMeasure(MeasureSpecMode widthSpecMode,int widthValue, 
                                MeasureSpecMode heightSpecMode,int heightValue) override;

        virtual void onLayout(int l,int t) override;

        virtual int measureChildWidgetSize(PWidget childWidget,
                        int limitWidth, 
                        int limitHeight,
                        std::vector<PWidget> &hasWeightList);
    };
}