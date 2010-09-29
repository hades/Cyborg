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

#include <QUdpSocket>

#include "CyborgUdpSource.h"

class CyborgUdpSourcePrivate
{
public:
    QUdpSocket socket;
};

CyborgUdpSource::CyborgUdpSource(QObject *parent)
    : CyborgSource(parent)
{
    d = new CyborgUdpSourcePrivate();

    connect(&d->socket, SIGNAL(readyRead()), SLOT(readMessage()));
}

CyborgUdpSource::~CyborgUdpSource()
{
    delete d;
}

void CyborgUdpSource::readMessage()
{
    while(d->socket.hasPendingDatagrams())
    {
        QByteArray data;
        data.resize(d->socket.pendingDatagramSize());
        d->socket.readDatagram(data.data(), data.size());
        emit message(QString::fromUtf8(data.constData(), qstrnlen(data.constData(), data.size())));
    }
}

void CyborgUdpSource::enable(bool on)
{
    if(on)
    {
        if(!d->socket.bind( 10600, QUdpSocket::ReuseAddressHint | QUdpSocket::DontShareAddress ))
        {
            qDebug() << "failed to open udp socket:" << d->socket.errorString();
        }
    }
    else
    {
        d->socket.close();
    }
}

