/*
 * Render.h
 *
 *  Created on: 23.05.2015
 *      Author: Kevin
 */

#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "../utils/ColorHelper.h"

class Renderer
{
public:
	Renderer();
	virtual ~Renderer();
	virtual void draw() const;
};


#endif /* _RENDERER_H_ */
