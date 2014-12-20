#ifndef BAZINGA_H
#define BAZINGA_H

#include "filesystem.h"
#include "json.h"
#include "object.h"
#include "map.h"
#include "video.h"
#include "input.h"

namespace bazinga {
	extern double delta;
	void startModules ();
	void gameLoop();
	void endModules ();
}

#endif /* BAZINGA_H */
