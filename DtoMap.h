/*! VUT FIT ICP
 * @file DtoMap.h
 * @brief Abstract class for classes that can have dto representation  
 * @author Pavlo Butenko - xbuten00
 * @author Ivan Burlutskyi - xburlu00
 */

#ifndef DTOMAP_H
#define DTOMAP_H

template <typename T>
class DtoMap{
public:
    /**
     * @return dto representation
     */
    virtual T* GetDtoObject() = 0;
};

#endif // DTOMAP_H
