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

#include <QTcpServer>
#include <QTcpSocket>

#include "CyborgTcpSource.h"

class CyborgTcpSourcePrivate
{
public:
    QTcpServer server;
};

CyborgTcpSource::CyborgTcpSource(QObject *parent)
    : CyborgSource(parent)
{
    d = new CyborgTcpSourcePrivate();
    if(!d->server.listen( QHostAddress::Any, 10600 ))
    {
        qDebug() << "failed to open listening socket:" << d->server.errorString();
    }

    connect(&d->server, SIGNAL(newConnection()), SLOT(readMessage()));
}

CyborgTcpSource::~CyborgTcpSource()
{
    delete d;
}

void CyborgTcpSource::readMessage()
{
    QTcpSocket *clientConnection = d->server.nextPendingConnection();
    clientConnection->waitForReadyRead(100); // TODO: make more accurate
    QByteArray data = clientConnection->readAll();
    emit message(QString::fromUtf8(data.constData(), data.size()));
    connect(clientConnection, SIGNAL(disconnected()), clientConnection, SLOT(deleteLater()));
    clientConnection->disconnectFromHost();
}
