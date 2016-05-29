/*
 * CSword.h
 *
 *  Created on: 28.05.2016
 *      Author: Kevin
 */

#ifndef SRC_ENTITY_CSWORD_H_
#define SRC_ENTITY_CSWORD_H_

#include "Entity.h"
#include "IEquipable.h"

class CSword: public IEquipable, public Entity {
public:
	CSword();
	virtual ~CSword();


};

#endif /* SRC_ENTITY_CSWORD_H_ */
