#include "ui/color.h"

namespace purple{
    glm::vec4 ConverColorValue(Color color){
        glm::vec4 result(0.0f , 0.0f , 0.0f , 0.0f);
        switch(color){
            case Transparent:
            break;
            case White:
            result = glm::vec4(1.0f , 1.0f , 1.0f , 1.0f);
            break;
            case Black:
            result = glm::vec4(0.0f , 0.0f , 0.0f , 1.0f);
            break;
            case Red:
            result = glm::vec4(1.0f , 0.0f , 0.0f , 1.0f);
            break;
            case Green:
            result = glm::vec4(0.0f , 1.0f , 0.0f , 1.0f);
            break;
            case Blue:
            result = glm::vec4(0.0f , 0.0f , 1.0f , 1.0f);
            break;
        }//end switch
        return result;
    }
}
