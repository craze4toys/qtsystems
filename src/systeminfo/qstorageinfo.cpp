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

#include "qstorageinfo.h"

#include <QtCore/qstringlist.h>

#if defined(Q_OS_LINUX)
#  include "qstorageinfo_linux_p.h"
#else
QT_BEGIN_NAMESPACE
class QStorageInfoPrivate
{
public:
    QStorageInfoPrivate(QStorageInfo *) {}

    qlonglong availableDiskSpace(const QString &) { return -1; }
    qlonglong totalDiskSpace(const QString &) { return -1; }
    QString uriForDrive(const QString &) { return QString(); }
    QStringList allLogicalDrives() { return QStringList(); }
    QStorageInfo::DriveType driveType(const QString &) { return QStorageInfo::UnknownDrive; }
};
QT_END_NAMESPACE
#endif

QT_BEGIN_NAMESPACE

/*!
    \class QStorageInfo
    \inmodule QtSystemKit
    \brief The QStorageInfo class provides various disk storage information of the system.
*/

/*!
    \enum QStorageInfo::DriveType
    This enum describes the type of drive or volume

    \value UnknownDrive         Drive type unknown.
    \value InternalDrive        Internal mass storage drive, e.g. hard drive.
    \value RemovableDrive       Removable drive, e.g. memory card.
    \value RemoteDrive          Network drive.
    \value CdromDrive           CD-ROM.
    \value InternalFlashDrive   Internal flash disk, or phone memory.
    \value RamDrive             Virtual drive made in RAM memory.
*/

/*!
    \fn void QStorageInfo::logicalDriveChanged(const QString &drive, bool added)

    This signal gets emitted when a new \a drive storage has been \a added or removed.
*/

/*!
    Constructs a QStorageInfo object with the given \a parent.
*/
QStorageInfo::QStorageInfo(QObject *parent)
    : QObject(parent)
    , d_ptr(new QStorageInfoPrivate(this))
{
}

/*!
    Destroys the object
*/
QStorageInfo::~QStorageInfo()
{
}

/*!
    \property QStorageInfo::allLogicalDrives
    \brief The  list of all drives.

    Returns a list of all logical drives or volumes, or an empty list if no drives are found or
    on error.
*/
QStringList QStorageInfo::allLogicalDrives()
{
    QStorageInfoPrivate priv(0);
    return priv.allLogicalDrives();
}

/*!
    Returns the available free space on the \a drive, in bytes. -1 is returned if the drive doesn't
    exist, or the information is not available.
*/
qlonglong QStorageInfo::availableDiskSpace(const QString &drive) const
{
    return d_ptr->availableDiskSpace(drive);
}

/*!
    Returns the total space of the \a drive, in bytes. -1 is returned if the drive doesn't exist,
    or the information is not available.
*/
qlonglong QStorageInfo::totalDiskSpace(const QString &drive) const
{
    return d_ptr->totalDiskSpace(drive);
}

/*!
    Returns the URI, or unique identifier for the given \a drive. If the drive doesn't exist, or the
    information is not available, an empty string is returned.
*/
QString QStorageInfo::uriForDrive(const QString &drive) const
{
    return d_ptr->uriForDrive(drive);
}

/*!
    Returns the type of the given \a drive.
*/
QStorageInfo::DriveType QStorageInfo::driveType(const QString &drive) const
{
    return d_ptr->driveType(drive);
}

/*!
    \internal
*/
void QStorageInfo::connectNotify(const char *signal)
{
    connect(d_ptr, signal, this, signal, Qt::UniqueConnection);
}

/*!
    \internal
*/
void QStorageInfo::disconnectNotify(const char *signal)
{
    // We can only disconnect with the private implementation, when there is no receivers for the signal.
    if (receivers(signal) > 0)
        return;

    disconnect(d_ptr, signal, this, signal);
}

QT_END_NAMESPACE