/*
* Copyright (C) 2021 ~ 2021 Deepin Technology Co., Ltd.
*
* Author:     caixiangrong <caixiangrong@uniontech.com>
*
* Maintainer: caixiangrong <caixiangrong@uniontech.com>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "powerplugin.h"
#include "generalmodule.h"
#include "useelectricmodule.h"
#include "usebatterymodule.h"
#include "powermodel.h"
#include "powerworker.h"
#include "utils.h"

#include <QLabel>

DCORE_USE_NAMESPACE
const QString gsetting_showSuspend = "showSuspend";
const QString gsetting_showHiberante = "showHibernate";
const QString gsetting_showShutdown = "showShutdown";

PowerModule::PowerModule(QObject *parent)
    : ModuleObject("power", tr("Power"), tr("Power"), QIcon::fromTheme("dcc_nav_power"), parent)
    , m_model(nullptr)
    , m_nBatteryPercentage(100.0)
    , m_useElectric(nullptr)
    , m_useBattery(nullptr)
{
    setChildType(ModuleObject::ChildType::HList);

    m_model = new PowerModel(this);
    m_work = new PowerWorker(m_model, this);

    m_work->active(); //refresh data
#if 0                 // gsettings 待改为dconfig
    QGSettings *m_powerSetting = new QGSettings("com.deepin.dde.control-center", QByteArray(), this);

    m_model->setSuspend(!IsServerSystem && m_powerSetting->get(gsetting_showSuspend).toBool() && m_model->canSuspend());
    connect(m_model, &PowerModel::suspendChanged, this, [=](const bool &value) {
        m_model->setSuspend(!IsServerSystem && m_powerSetting->get(gsetting_showSuspend).toBool() && value);
    });

    m_model->setHibernate(!IsServerSystem && m_powerSetting->get(gsetting_showHiberante).toBool() && m_model->canHibernate());
    connect(m_model, &PowerModel::canHibernateChanged, this, [=](const bool &value) {
        m_model->setHibernate(!IsServerSystem && m_powerSetting->get(gsetting_showHiberante).toBool() && value);
    });

    m_model->setShutdown(m_powerSetting->get(gsetting_showShutdown).toBool());

    connect(m_powerSetting, &QGSettings::changed, this, [=](const QString &key) {
        if (key == gsetting_showSuspend) {
            m_model->setSuspend(!IsServerSystem && m_powerSetting->get(gsetting_showSuspend).toBool() && m_model->canSuspend());
        } else if (key == gsetting_showHiberante) {
            m_model->setHibernate(!IsServerSystem && m_powerSetting->get(gsetting_showHiberante).toBool() && m_model->canHibernate());
        } else if (key == gsetting_showShutdown) {
            m_model->setShutdown(m_powerSetting->get(gsetting_showShutdown).toBool());
        } else {
            qWarning() << " not contains the key : " << key;
        }
    });
#else
    m_model->setSuspend(!IsServerSystem && true);
    m_model->setHibernate(!IsServerSystem && true);
    m_model->setShutdown(true);
#endif
    connect(m_model, &PowerModel::haveBettaryChanged, this, &PowerModule::onBatteryChanged);
    connect(m_model, &PowerModel::batteryPercentageChanged, this, &PowerModule::onBatteryPercentageChanged);

    //-------------------------------------------
    if (!IsServerSystem) {
        appendChild(new GeneralModule(m_model, m_work, this));
    }
    //-------------------------------------------
    m_useElectric = new UseElectricModule(m_model, m_work, this);
    appendChild(m_useElectric);
    //-------------------------------------------
    onBatteryChanged(m_model->haveBettary());
}

void PowerModule::active()
{
}

void PowerModule::onBatteryChanged(const bool &state)
{
    if (state) {
        const QList<ModuleObject *> &childrens = ModuleObject::childrens();
        m_useBattery = new UseBatteryModule(m_model, m_work, this);
        insertChild(childrens.indexOf(m_useElectric) + 1, m_useBattery);
    } else if (m_useBattery) {
        removeChild(m_useBattery);
        m_useBattery->deleteLater();
        m_useBattery = nullptr;
    }
}
//done: 遗留问题，控制中心不应该发电量低通知
void PowerModule::onBatteryPercentageChanged(const double value)
{
    if (!m_model->getDoubleCompare(m_nBatteryPercentage, value)) {
        m_nBatteryPercentage = value;

        QString remindData = "";
        if (m_model->getDoubleCompare(value, 20.0)
            || m_model->getDoubleCompare(value, 15.0)
            || m_model->getDoubleCompare(value, 10.0)) {
            remindData = tr("Battery low, please plug in");
        } else if (m_model->getDoubleCompare(value, 5.0)) {
            remindData = tr("Battery critically low");
        }

        //send system info
        if ("" != remindData) {
            Dtk::Core::DUtil::DNotifySender(remindData.toLatin1().data());
        }
    }
}

PowerPlugin::PowerPlugin()
    : m_moduleRoot(nullptr)
{
}

QString PowerPlugin::name() const
{
    return QStringLiteral("power");
}

ModuleObject *PowerPlugin::module()
{
    if (m_moduleRoot)
        return m_moduleRoot;

    m_moduleRoot = new PowerModule;
    return m_moduleRoot;
}
