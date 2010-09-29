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

#include <QAction>
#include <QMenu>
#include <QSystemTrayIcon>

#include <QDebug>

#include "Cyborg.h"

#include "CyborgParser.h"
#include "CyborgTcpSource.h"
#include "CyborgUdpSource.h"

Cyborg::Cyborg(int argc, char**argv)
    : QApplication(argc, argv)
{
    tray = new QSystemTrayIcon(this);
    if(!tray->isSystemTrayAvailable())
    {
        qFatal("system tray unavailable");
    }

    exit = new QAction(tr("&Exit"), this);
    exit->setShortcuts(QKeySequence::Quit);
    connect(exit, SIGNAL(triggered()), SLOT(quit()));

    QAction* tcp = new QAction(tr("&TCP Enabled"), this);
    tcp->setCheckable(true);
    tcp->setChecked(true);

    QAction* udp = new QAction(tr("&UDP Enabled"), this);
    udp->setCheckable(true);
    udp->setChecked(true);

    menu.reset(new QMenu());
    menu->addAction(tcp);
    menu->addAction(udp);
    menu->addAction(exit);

    tray->setContextMenu(menu.data());
    tray->setIcon(QIcon(":/images/android.png"));
    tray->show();

    p = new CyborgParser(this);
    ts = new CyborgTcpSource(this);
    ts->enable();

    us = new CyborgUdpSource(this);
    us->enable();

    connect(ts, SIGNAL(message(QString)), p, SLOT(message(QString)));
    connect(us, SIGNAL(message(QString)), p, SLOT(message(QString)));
    connect(tcp, SIGNAL(triggered(bool)), ts, SLOT(enable(bool)));
    connect(udp, SIGNAL(triggered(bool)), us, SLOT(enable(bool)));
    connect(p, SIGNAL(notice(CyborgNotice)), SLOT(notice(CyborgNotice)));
}

void Cyborg::notice(const CyborgNotice &n)
{
    tray->showMessage(tr("Notice from device %1").arg(n.deviceID), n.contents,
                      QSystemTrayIcon::Information, 10000);
}
