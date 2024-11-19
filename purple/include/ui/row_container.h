#pragma once

#include "ui.h"
#include "color.h"
#include "render/common.h"

namespace purple{

    class RowContainer : public Container{
    public:
        RowContainer():Container(LAYOUT_MATCH_PARENT, LAYOUT_WRAP_CONTENT){

        }

        RowContainer(int reqWidth,int reqHeight):Container(reqWidth, reqHeight){

        }

        virtual void onMeasure(int parentRequestWidth , int parentRequestHeight) override;

        virtual void onLayout(int l,int t) override;

        virtual ~RowContainer();

    private:
        
    };
}