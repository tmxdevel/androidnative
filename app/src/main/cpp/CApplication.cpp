#include "CApplication.h"

CRenderer *CApplication::getRenderer(int id) {
    if(!_renderers.containsKey(id)) {
        _renderers.put(id, new CRenderer());
    }
    return _renderers.get(id, nullptr);
}

