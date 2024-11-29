// SPDX-FileCopyrightText: 2024 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "syncinfolistmodel.h"

SyncInfoListModel::SyncInfoListModel(QObject *parent)
    : QAbstractListModel(parent)
{
    m_syncItemList = {
        { Sound, "dcc_cloud_voice", tr("Sound"), QStringList() << "audio", false },
        { Theme, "dcc_cloud_them", tr("Theme"), QStringList() << "appearance", false },
        { Power, "dcc_cloud_power", tr("Power"), QStringList() << "power", false },
        { Network, "dcc_cloud_net", tr("Network"), QStringList() << "network", false },
        { Mouse, "dcc_cloud_mouse", tr("Mouse"), QStringList() << "peripherals", false },
        { Update, "dcc_cloud_update", tr("Update"), QStringList() << "updater", false },
        { Dock, "dcc_cloud_taskbar", tr("Dock"), QStringList() << "dock", false },
        { Launcher, "dcc_cloud_luncher", tr("Launcher"), QStringList() << "launcher", false },
        { Wallpaper, "dcc_cloud_wallpaper", tr("Wallpaper"), QStringList() << "background" << "screensaver", false },
    };    
}

void SyncInfoListModel::updateSyncItem(const QString &key, bool enable)
{
    for (int i = 0; i < m_syncItemList.count(); i++) {
        auto &syncItem = m_syncItemList[i];
        if (syncItem.keyList.contains(key)) {
            syncItem.isChecked = enable;
            QModelIndex modelIndex = createIndex(i, 0);
            emit dataChanged(modelIndex, modelIndex, { IsCheckedRole });
            break;
        }
    }
}

int SyncInfoListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return m_syncItemList.count();
}

QVariant SyncInfoListModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_syncItemList.count())
        return QVariant();

    auto syncItem = m_syncItemList[index.row()];
    if (role == TypeRole)
        return syncItem.type;
    else if (role == DisplayIconRole)
        return syncItem.displayIcon;
    else if (role == DisplayNameRole)
        return syncItem.displayName;
    else if (role == KeyListRole)
        return syncItem.keyList;
    else if (role == IsCheckedRole)
        return syncItem.isChecked;

    return QVariant();
}
