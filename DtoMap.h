#ifndef DTOMAP_H
#define DTOMAP_H

template <typename T>
class DtoMap{
public:
    virtual T* GetDtoObject() const = 0;
};

#endif // DTOMAP_H
