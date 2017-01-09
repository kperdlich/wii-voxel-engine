/***
 *
 * Copyright (C) 2016 DaeFennek
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
***/

#ifndef SRC_UTILS_CRENDERHELPER_H_
#define SRC_UTILS_CRENDERHELPER_H_

#include <stdint.h>
#include <stddef.h>

class CRenderHelper {
private:
	CRenderHelper();
public:

    static size_t GetDisplayListSizeForFaces(uint32_t faces);

	virtual ~CRenderHelper();
};

#endif /* SRC_UTILS_CRENDERHELPER_H_ */
