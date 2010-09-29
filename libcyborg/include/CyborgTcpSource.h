/*
 * @internal
 * Copyright 2010 Edward Toroshchin <cyborg@hades.name>
 *
 * This file is part of Cyborg.
 *
 * Cyborg is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Cyborg is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * See the full text of the GNU General Public License in the COPYING
 * file in source code directory.
 *
 * If you are unable to read that file, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef CYBORGTCPSOURCE_H
#define CYBORGTCPSOURCE_H

#include "CyborgSource.h"

class CyborgTcpSourcePrivate;

class CyborgTcpSource: public CyborgSource
{
    Q_OBJECT

    CyborgTcpSourcePrivate* d;
public:
    CyborgTcpSource(QObject* parent = 0);
    virtual ~CyborgTcpSource();

private slots:
    void readMessage();
};

#endif // CYBORGTCPSOURCE_H
