/****************************************************************************
**
** Copyright (C) 2012 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the plugins of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QWAYLANDNATIVEINTERFACE_H
#define QWAYLANDNATIVEINTERFACE_H

#include <QtWaylandClient/qwaylandscreen.h>
#include <QVariantMap>
#include <qpa/qplatformnativeinterface.h>

QT_BEGIN_NAMESPACE

class QWaylandIntegration;

class Q_WAYLAND_CLIENT_EXPORT QWaylandNativeInterface : public QPlatformNativeInterface
{
public:
    QWaylandNativeInterface(QWaylandIntegration *integration);
    void *nativeResourceForIntegration(const QByteArray &resource);
    void *nativeResourceForWindow(const QByteArray &resourceString,
				  QWindow *window);
    void *nativeResourceForScreen(const QByteArray &resourceString,
                                  QScreen *screen);

    QVariantMap windowProperties(QPlatformWindow *window) const;
    QVariant windowProperty(QPlatformWindow *window, const QString &name) const;
    QVariant windowProperty(QPlatformWindow *window, const QString &name, const QVariant &defaultValue) const;
    void setWindowProperty(QPlatformWindow *window, const QString &name, const QVariant &value);

    void emitWindowPropertyChanged(QPlatformWindow *window, const QString &name);
private:
    static QWaylandScreen *qPlatformScreenForWindow(QWindow *window);

private:
    QWaylandIntegration *m_integration;
    QHash<QPlatformWindow*, QVariantMap> m_windowProperties;
};

QT_END_NAMESPACE

#endif // QWAYLANDNATIVEINTERFACE_H
