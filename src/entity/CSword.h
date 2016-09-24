/*
 * CSword.h
 *
 *  Created on: 28.05.2016
 *      Author: Kevin
 */

#ifndef _CSWORD_H_
#define _CSWORD_H_

#include "Entity.h"
#include "IEquipable.h"

class CSword: public IEquipable, public Entity {
public:
	CSword();
	virtual ~CSword();


};

#endif /* _CSWORD_H_ */
