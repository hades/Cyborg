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

#ifndef CYBORGPARSER_H
#define CYBORGPARSER_H

#include <QObject>
#include <QString>

#include "Cyborg_Global.h"

struct CYBORG_EXPORT CyborgNotice
{
public:
    enum EventType { RING, SMS, MMS, BATTERY, PING, UNDEFINED=0xff };

    int version;
    QString deviceID;
    QString notificationID;
    EventType eventType;
    QString data;
    QString contents;

    CyborgNotice( const int _version, const QString& _deviceID,
                  const QString& _notificationID, const EventType _eventType,
                  const QString& _data, const QString& _contents )
                      : version(_version), deviceID(_deviceID),
                        notificationID(_notificationID), eventType(_eventType),
                        data(_data), contents(_contents)
    {}
};

class CYBORG_EXPORT CyborgParser : public QObject
{
    Q_OBJECT

public:
    CyborgParser( QObject* parent = 0 );

public slots:
    void message(const QString&);

signals:
    void notice(CyborgNotice);
};

#endif // CYBORGPARSER_H
