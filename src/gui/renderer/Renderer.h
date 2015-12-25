/*
 * Render.h
 *
 *  Created on: 23.05.2015
 *      Author: Kevin
 */

#ifndef SRC_GUI_RENDERER_RENDERER_H_
#define SRC_GUI_RENDERER_RENDERER_H_

#include <grrlib.h>
#include "../ColorHelper.h"

class Renderer
{
public:
	Renderer();
	virtual ~Renderer();
	virtual void draw();
};


#endif /* SRC_GUI_RENDERER_RENDERER_H_ */
