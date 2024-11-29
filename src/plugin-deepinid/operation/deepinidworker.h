// SPDX-FileCopyrightText: 2024 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef DEEPINIDWORKER_H
#define DEEPINIDWORKER_H

#include "deepinidmodel.h"
#include "deepiniddbusproxy.h"
#include "syncdbusproxy.h"
#include "utclouddbusproxy.h"

class DeepinWorker : public QObject
{
    Q_OBJECT
public:
    explicit DeepinWorker(DeepinidModel *model, QObject *parent = nullptr);

    void initData();


    Q_INVOKABLE void loginUser();
    Q_INVOKABLE void logoutUser();
    Q_INVOKABLE void openWeb();
    Q_INVOKABLE void setAutoSync(bool autoSync);
    Q_INVOKABLE void setSyncSwitcher(const QStringList &keyList, bool enable);
    Q_INVOKABLE void setUtcloudSwitcher(const QString &key, bool enable);

public Q_SLOTS:
    void onSyncSwitcherChange(const QString &key, bool enable);
    void licenseStateChangeSlot();

    void onUtcloudSwitcherChange(const QVariantList &args);
    void onUtcloudLoginStatusChange(const QVariantList &args);

private:
    void requestSyncDump();
    void requestUtCloudDump();
    QString loadCodeURL();
    void getLicenseState();

private:
    DeepinidModel *m_model;
    DeepinidDBusProxy *m_deepinIDProxy;
    SyncDBusProxy *m_syncProxy;
    UtcloudDBusProxy *m_utcloudProxy;
};

#endif // DEEPINIDWORKER_H
