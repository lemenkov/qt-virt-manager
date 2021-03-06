/*
   Copyright (C) 2014 Lindsay Mathieson (lindsay.mathieson@gmail.com).

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with this library; if not, see <http://www.gnu.org/licenses/>.
*/

#include "qspicehelper.h"

#include "qspiceobject.h"

QSpiceObject::QSpiceObject(QObject *parent) :
    QObject(parent)
{
}

void QSpiceHelper::GDisposeEvent(gpointer data, GObject *gobject)
{
    Q_UNUSED(gobject);

    QSpiceObject *so = static_cast<QSpiceObject *>(data);
    if (so->objectDisposed())
        delete so;

}

QSpiceObject::QSpiceObject(void *_gobject) : gobject(_gobject)
{
    g_object_weak_ref((GObject *) gobject, QSpiceHelper::GDisposeEvent, this);
}

bool QSpiceObject::objectDisposed()
{
    return false;
}

int QSpiceObject::getPropInt(QString name)
{
    gint v = 0;
    g_object_get(G_OBJECT (gobject),
                 name.toLatin1().data(), &v,
                 NULL);

    return v;
}

void QSpiceObject::setProp(QString name, const int i)
{
    g_object_set (G_OBJECT (gobject),
              name.toLatin1().data(), i,
              NULL);
}

QString QSpiceObject::getPropString(QString name)
{
    gchar *v = NULL;
    g_object_get(G_OBJECT (gobject),
                 name.toLatin1().data(), &v,
                 NULL);

    if (v)
    {

        QString s = v;
        g_free(v);
        return s;
    }
    else
        return "";
}

void QSpiceObject::setProp(QString name, const QString& s)
{
    g_object_set (G_OBJECT (gobject),
              name.toLatin1().data(), s.toLatin1().data(),
              NULL);
}
