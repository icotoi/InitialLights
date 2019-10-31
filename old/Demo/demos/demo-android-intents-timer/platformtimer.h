#pragma once

#include <QObject>

class PlatformTimer : public QObject
{
    Q_OBJECT

public:
    explicit PlatformTimer(QObject *parent = nullptr);

public slots:
    void createTimer(const QString &message, double duration, bool showUI) const;

private:
    int m_time = 0;
};
