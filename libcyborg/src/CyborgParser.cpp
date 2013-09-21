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

#include <QDebug>
#include <QStringList>

#include "CyborgParser.h"

CyborgParser::CyborgParser(QObject *parent)
    : QObject(parent)
{
}

void CyborgParser::message(const QByteArray& msgdata)
{
    QString text = QString::fromUtf8(msgdata);
    QStringList parts = text.split('/');
    if(parts.size() < 4)
    {
        qDebug() << "invalid message format:" << text;
        return;
    }

    int version = 1;
    if(parts[0].startsWith('v'))
    {
        parts[0].remove(0, 1);
        version = parts[0].toInt();
        parts.removeFirst();
    }

    if(parts.size() < 4)
    {
        qDebug() << "invalid message format:" << text;
        return;
    }

    QString deviceid = parts.takeFirst();
    QString noticeid = parts.takeFirst();
    QString evttype = parts.takeFirst().toUpper();
    QString data;
    if(version >= 2)
        data = parts.takeFirst();

    CyborgNotice::EventType t = CyborgNotice::UNDEFINED;
    if( evttype == "RING" )
        t = CyborgNotice::RING;
    else if( evttype == "SMS" )
        t = CyborgNotice::SMS;
    else if( evttype == "MMS" )
        t = CyborgNotice::MMS;
    else if( evttype == "BATTERY" )
        t = CyborgNotice::BATTERY;
    else if( evttype == "PING" )
        t = CyborgNotice::PING;

    emit notice( CyborgNotice( version, deviceid, noticeid, t,
                               data, parts.join( "/" ) ) );
}
