// SPDX-FileCopyrightText: 2024 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef SYNCDBUSPROXY_H
#define SYNCDBUSPROXY_H

#include <DDBusInterface>

#include <QDBusMetaType>
#include <QObject>
#include <QtCore/QString>
#include <QtDBus/QtDBus>

struct IntString
{
    qint32 state;
    QString description;

    bool operator!=(const IntString &intString);
};

Q_DECLARE_METATYPE(IntString)

QDBusArgument &operator<<(QDBusArgument &argument, const IntString &intString);
const QDBusArgument &operator>>(const QDBusArgument &argument, IntString &intString);

void registerIntStringMetaType();

using Dtk::Core::DDBusInterface;

class SyncDBusProxy : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qlonglong LastSyncTime READ lastSyncTime NOTIFY LastSyncTimeChanged)
    Q_PROPERTY(IntString State READ state NOTIFY StateChanged)

public:
    explicit SyncDBusProxy(QObject *parent = nullptr);

    void SwitcherSet(const QString &arg_0, bool state);
    bool SwitcherGet(const QString &arg_0);
    QDBusPendingCall SwitcherDump();

    qlonglong lastSyncTime();
    IntString state();

signals:
    void SwitcherChange(QString, bool);
    void LastSyncTimeChanged(qlonglong);
    void StateChanged(IntString);

private:
    DDBusInterface *m_syncInter;

};

#endif // SYNCDBUSPROXY_H
