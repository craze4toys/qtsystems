/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the QtSystemKit module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** No Commercial Usage
** This file contains pre-release code and may not be distributed.
** You may use this file in accordance with the terms and conditions
** contained in the Technology Preview License Agreement accompanying
** this package.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights.  These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
**
**
**
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "qdisplayinfo.h"

#include <QtGui/qapplication.h>
#include <QtGui/qdesktopwidget.h>

#if defined(Q_OS_LINUX)
#  include "qdisplayinfo_linux_p.h"
#else
QT_BEGIN_NAMESPACE
class QDisplayInfoPrivate
{
public:
    QDisplayInfoPrivate(QDisplayInfo *) {}

    int colorDepth(int) { return -1; }
    int contrast(int) const { return -1; }
    int displayBrightness(int) { return -1; }
    int dpiX(int) { return -1; }
    int dpiY(int) { return -1; }
    int physicalHeight(int) { return -1; }
    int physicalWidth(int) { return -1; }
    QDisplayInfo::BacklightState backlightState(int) { return QDisplayInfo::BacklightUnknown; }
};
QT_END_NAMESPACE
#endif

QT_BEGIN_NAMESPACE

/*!
    \class QDisplayInfo
    \inmodule QtSystemKit
    \brief The QDisplayInfo class provides various information of the display.
*/

/*!
    \enum QDisplayInfo::BacklightState
    This enum describes the state of the backlight.

    \value BacklightUnknown     The state of the backlight is unkown.
    \value BacklightOff         Backlight is turned off.
    \value BacklightDimmed      Backlight has been dimmed.
    \value BacklightOn          Backlight is on.
*/

/*!
    \enum QDisplayInfo::DisplayOrientation
    This enum describes the orientation of the display.

    \value OrientationUnknown   The orientation is unknown.
    \value Landscape            The orientation is landscape, i.e. the width is bigger than the height.
    \value Portrait             The orientation is portrait, i.e. the height is bigger than the width.
    \value InvertedLandscape    Landscape, but inverted.
    \value InvertedPortrait     Portrait, but inverted.
*/


/*!
    \fn void QDisplayInfo::orientationChanged(int screen, QDisplayInfo::DisplayOrientation orientation)

    This signal is emitted when the orientation of the \a screen has changed to \a orientation.
*/

/*!
    Constructs a QDisplayInfo object with the given \a parent.
*/
QDisplayInfo::QDisplayInfo(QObject *parent)
    : QObject(parent)
    , d_ptr(new QDisplayInfoPrivate(this))
{
}

/*!
    Destroys the object
*/
QDisplayInfo::~QDisplayInfo()
{
    delete d_ptr;
}

/*!
    Returns the color depth of the given \a screen, in bits per pixel. -1 is returned if not
    available or on error.
*/
int QDisplayInfo::colorDepth(int screen) const
{
    if (screen < 0 || screen >= QApplication::desktop()->screenCount())
        return -1;
    return d_ptr->colorDepth(screen);
}

/*!
    Returns the contrast of the given \a screen, in 0 - 100 scale. -1 is returned if not available
    or on error.
*/
int QDisplayInfo::contrast(int screen) const
{
    if (screen < 0 || screen >= QApplication::desktop()->screenCount())
        return -1;
    return d_ptr->contrast(screen);
}

/*!
    Returns the display brightness of the given \a screen, in 0 - 100 scale. In case of error or
    the information is not available, -1 is returned.
*/
int QDisplayInfo::displayBrightness(int screen) const
{
    if (screen < 0 || screen >= QApplication::desktop()->screenCount())
        return -1;
    return d_ptr->displayBrightness(screen);
}

/*!
    Returns the horizontal resolution of the given \a screen in terms of the number of dots per inch.
    -1 is returned if not available or on error.
*/
int QDisplayInfo::dpiX(int screen) const
{
    if (screen < 0 || screen >= QApplication::desktop()->screenCount())
        return -1;
    return d_ptr->dpiX(screen);
}

/*!
    Returns the vertical resolution of the given \a screen in terms of the number of dots per inch.
    -1 is returned if not available or on error.
*/
int QDisplayInfo::dpiY(int screen) const
{
    if (screen < 0 || screen >= QApplication::desktop()->screenCount())
        return -1;
    return d_ptr->dpiY(screen);
}

/*!
    Returns the physical height of the \a screen in millimeters. -1 is returned if not available
    or on error.
*/
int QDisplayInfo::physicalHeight(int screen) const
{
    if (screen < 0 || screen >= QApplication::desktop()->screenCount())
        return -1;
    return d_ptr->physicalHeight(screen);
}

/*!
    Returns the physical width of \a screen in millimeters. -1 is returned if not available or
    on error.
*/
int QDisplayInfo::physicalWidth(int screen) const
{
    if (screen < 0 || screen >= QApplication::desktop()->screenCount())
        return -1;
    return d_ptr->physicalWidth(screen);
}

/*!
    Returns the backlight state of the given \a screen.
*/
QDisplayInfo::BacklightState QDisplayInfo::backlightState(int screen) const
{
    if (screen < 0 || screen >= QApplication::desktop()->screenCount())
        return QDisplayInfo::BacklightUnknown;
    return d_ptr->backlightState(screen);
}

/*!
    Returns the orientation of the given \a screen.
*/
QDisplayInfo::DisplayOrientation QDisplayInfo::orientation(int screen) const
{
    Q_UNUSED(screen)
    return QDisplayInfo::OrientationUnknown;
}

QT_END_NAMESPACE