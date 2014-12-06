#ifndef BAZINGA_CACHE_H
#define BAZINGA_CACHE_H

#include "video.h"
#include <map>
using namespace std;

namespace bazinga {
  namespace cache {
    video::Image getTexture (Path);
  }
}

#endif /* BAZINGA_CACHE_H */