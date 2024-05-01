#ifndef UPDATABLE_ENTITY_H
#define UPDATABLE_ENTITY_H

class UpdatableEntity {
    virtual void update(long deltaNano) = 0;
};

#endif // UPDATABLE_ENTITY_H
