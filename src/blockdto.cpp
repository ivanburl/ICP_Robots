/*! VUT FIT ICP
 * @file blockdto.cpp
 * @brief block.h implementation  
 * @author Pavlo Butenko - xbuten00
 * @author Ivan Burlutskyi - xburlu00
 */

#include "blockdto.h"

const QString BlockDto::xName = "x";
const QString BlockDto::yName = "y";
const QString BlockDto::wName = "w";
const QString BlockDto::hName = "h";

BlockDto::BlockDto(int x, int y, int w, int h) {
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
}

int BlockDto::getX(){
    return x;
}

int BlockDto::getY(){
    return y;
}

int BlockDto::getWidth(){
    return w;
}

int BlockDto::getHeight(){
    return h;
}

QJsonObject BlockDto::toJsonObject() const{
    QJsonObject jsonObject;
    jsonObject.insert(xName, x);
    jsonObject.insert(yName, y);
    jsonObject.insert(wName, w);
    jsonObject.insert(hName, h);
    return jsonObject;
}

BlockDto* BlockDto::fromJsonObject(QJsonObject jsonObject){
    auto xValue = jsonObject.value(xName);
    auto yValue = jsonObject.value(yName);
    auto wValue = jsonObject.value(wName);
    auto hValue = jsonObject.value(hName);


    if(!xValue.isDouble() || !yValue.isDouble()
        || !wValue.isDouble()
        || !hValue.isDouble()){
        return nullptr;
    }

    return new BlockDto(xValue.toInt(), yValue.toInt(),
                        wValue.toInt(), hValue.toInt());
}
