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

        virtual void measure(int parentRequestWidth , int parentRequestHeight);

        virtual void layout(int l,int t);

        virtual void measureChildWidgetSize(PWidget childWidget,
                        int limitWidth, 
                        int limitHeight);
    };
}