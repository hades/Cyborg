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

#ifndef CYBORG_H
#define CYBORG_H

#include <QApplication>
#include <QScopedPointer>
#include <QMenu>

class QAction;
class QSystemTrayIcon;

class CyborgNotice;
class CyborgParser;
class CyborgTcpSource;

class Cyborg : public QApplication
{
    Q_OBJECT

    QSystemTrayIcon* tray;
    QAction* exit;
    QScopedPointer<QMenu> menu;

    CyborgTcpSource* ts;
    CyborgParser* p;

public:
    Cyborg(int argc, char** argv);

private slots:
    void notice(const CyborgNotice&);
};

#endif // CYBORG_H
