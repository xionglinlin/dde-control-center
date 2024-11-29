// SPDX-FileCopyrightText: 2024 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "appinfolistmodel.h"

AppInfoListModel::AppInfoListModel(QObject *parent)
    : QAbstractListModel(parent)
{

}

void AppInfoListModel::addAppItem(AppItemData *item)
{
    beginInsertRows(QModelIndex(), m_appItemList.count(), m_appItemList.count());
    m_appItemList.append(item);
    endInsertRows();
}

void AppInfoListModel::removeAppItem(AppItemData* item)
{
    beginResetModel();
    m_appItemList.removeAll(item);
    delete item;
    item = nullptr;
    endResetModel();
}

void AppInfoListModel::clearItem()
{
    for (AppItemData* item : m_appItemList) {
        delete item;
        item = nullptr;
    }
    m_appItemList.clear();
}

void AppInfoListModel::updateAppItem(const QString &key, bool enable)
{
    for (AppItemData* item : m_appItemList) {
        if (item->key == key) {
            item->enable = enable;
            QModelIndex modelIndex = createIndex(m_appItemList.indexOf(item), 0);
            emit dataChanged(modelIndex, modelIndex, { EnableRole });
            return;
        }
    }
}

int AppInfoListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return m_appItemList.count();
}

QVariant AppInfoListModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_appItemList.count())
        return QVariant();

    auto appItem = m_appItemList[index.row()];
    if (role == NameRole)
        return appItem->name;
    else if (role == IconRole)
        return appItem->icon;
    else if (role == KeyRole)
        return appItem->key;
    else if (role == EnableRole)
        return appItem->enable;

    return QVariant();
}
