/****************************************************************************
**
** This file is part of QtCompositor**
**
** Copyright © 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
**
** Contact:  Nokia Corporation qt-info@nokia.com
**
** You may use this file under the terms of the BSD license as follows:
**
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**
** Redistributions of source code must retain the above copyright
** notice, this list of conditions and the following disclaimer.
**
** Redistributions in binary form must reproduce the above copyright
** notice, this list of conditions and the following disclaimer in the
** documentation and/or other materials provided with the distribution.
**
** Neither the name of Nokia Corporation and its Subsidiary(-ies) nor the
** names of its contributors may be used to endorse or promote products
** derived from this software without specific prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
****************************************************************************/

#include "wloutput.h"
#include <QGuiApplication>
#include <QtGui/QScreen>
#include <QRect>

namespace Wayland {

OutputGlobal::OutputGlobal()
    : m_displayId(-1)
    , m_numQueued(0)
{
    QScreen *screen = QGuiApplication::primaryScreen();
    m_geometry = QRect(QPoint(0, 0), screen->availableGeometry().size());
}

void OutputGlobal::setGeometry(const QRect &geometry)
{
    m_geometry = geometry;
}

Output *OutputGlobal::outputForClient(wl_client *client) const
{
    return static_cast<Output *>(resourceForClient(client)->data);
}

void OutputGlobal::output_bind_func(struct wl_client *client, void *data,
                          uint32_t version, uint32_t id)
{
    Q_UNUSED(version);
    OutputGlobal *output_global = static_cast<OutputGlobal *>(data);

    Output *output = new Output(output_global,client,version,id);
    output_global->registerResource(output->handle());
}



Output::Output(OutputGlobal *outputGlobal, wl_client *client, uint32_t version, uint32_t id)
    : m_output_global(outputGlobal)
    , m_extended_output(0)
{
    Q_UNUSED(version);
    m_output_resource = wl_client_add_object(client,&wl_output_interface,0,id,this);
    wl_resource_post_event(m_output_resource, WL_OUTPUT_GEOMETRY, 0, 0,
                         m_output_global->size().width(), m_output_global->size().height(),0,"","");

    wl_resource_post_event(m_output_resource,WL_OUTPUT_MODE, WL_OUTPUT_MODE_CURRENT|WL_OUTPUT_MODE_PREFERRED,
                           m_output_global->size().width(),m_output_global->size().height());

}

ExtendedOutput *Output::extendedOutput() const
{
    return m_extended_output;
}

void Output::setExtendedOutput(ExtendedOutput *extendedOutput)
{
    m_extended_output = extendedOutput;
}

wl_resource *Output::handle() const
{
    return m_output_resource;
}

} // namespace Wayland
