#ifndef UPDATEDBUSPROXY_H
#define UPDATEDBUSPROXY_H

#include <QDBusObjectPath>
#include <QDBusPendingReply>
#include <QObject>

typedef QMap<QString, QStringList> LastoreUpdatePackagesInfo;
typedef QMap<QString, double> BatteryPercentageInfo;

class QDBusMessage;
class QDBusInterface;
class UpdateDBusProxy : public QObject
{
    Q_OBJECT
public:
    explicit UpdateDBusProxy(QObject *parent = nullptr);
    ~UpdateDBusProxy();

public:
    // updater
    Q_PROPERTY(bool UpdateNotify READ updateNotify NOTIFY UpdateNotifyChanged)
    bool updateNotify();
    void SetUpdateNotify(bool in0);
    LastoreUpdatePackagesInfo classifiedUpdatablePackages();
    double GetCheckIntervalAndTime(QString &out1);

    Q_PROPERTY(bool AutoDownloadUpdates READ autoDownloadUpdates NOTIFY AutoDownloadUpdatesChanged)
    bool autoDownloadUpdates();
    void SetAutoDownloadUpdates(bool in0);

    Q_PROPERTY(bool AutoInstallUpdates READ autoInstallUpdates WRITE setAutoInstallUpdates NOTIFY AutoInstallUpdatesChanged)
    bool autoInstallUpdates();
    void setAutoInstallUpdates(bool value);

    qulonglong autoInstallUpdateType();

    Q_PROPERTY(bool AutoCheckUpdates READ autoCheckUpdates NOTIFY AutoCheckUpdatesChanged)
    bool autoCheckUpdates();
    void SetAutoCheckUpdates(bool in0);
    void SetMirrorSource(const QString &in0);

    // ManagerInter
    bool autoClean();

    Q_PROPERTY(qulonglong UpdateMode READ updateMode WRITE setUpdateMode NOTIFY UpdateModeChanged)
    qulonglong updateMode();
    void setUpdateMode(qulonglong value);

    QList<QDBusObjectPath> jobList();
    QDBusPendingReply<QDBusObjectPath> UpdateSource();
    void CleanJob(const QString &in0);
    void SetAutoClean(bool in0);
    void StartJob(const QString &in0);
    void PauseJob(const QString &in0);
    QDBusPendingReply<QList<QDBusObjectPath> > ClassifiedUpgrade(qulonglong in0);
    QDBusPendingReply<qlonglong> PackagesDownloadSize(const QStringList &in0);

    // Power
    bool onBattery();
    BatteryPercentageInfo batteryPercentage();

signals:
    // updater
    void UpdateNotifyChanged(bool  value) const;
    void AutoDownloadUpdatesChanged(bool  value) const;
    void AutoInstallUpdatesChanged(bool  value) const;
    void AutoInstallUpdateTypeChanged(qulonglong  value) const;
    void MirrorSourceChanged(const QString & value) const;
    void AutoCheckUpdatesChanged(bool  value) const;
    void ClassifiedUpdatablePackagesChanged(LastoreUpdatePackagesInfo  value) const;

    // ManagerInter
    void JobListChanged(const QList<QDBusObjectPath> & value) const;
    void AutoCleanChanged(bool  value) const;
    void UpdateModeChanged(qulonglong  value) const;

    // Power
    void OnBatteryChanged(bool  value) const;
    void BatteryPercentageChanged(BatteryPercentageInfo  value) const;

public slots:
    void onPropertiesChanged(const QDBusMessage &message);

private:
    QDBusInterface *m_updateInter;
    QDBusInterface *m_managerInter;
    QDBusInterface *m_powerInter;

};

#endif // UPDATEDBUSPROXY_H