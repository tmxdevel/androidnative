#ifndef NATIVEANDROID_CAPPLICATION_H
#define NATIVEANDROID_CAPPLICATION_H

#include "CRenderer.h"
#include "CHashMap.h"

class CApplication
{
public:
    CRenderer* getRenderer(int id);

private:
    CHashMap<int, CRenderer*> _renderers;
};


#endif //NATIVEANDROID_CAPPLICATION_H
