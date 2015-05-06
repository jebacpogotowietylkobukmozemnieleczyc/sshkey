#ifndef NEWTON_H
#define NEWTON_H

#include <QObject>
#include <QString>
#include <QStringList>



class Newton : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString x READ x WRITE setX NOTIFY xChanged)
    Q_PROPERTY(QString mit READ mit WRITE setMit NOTIFY mitChanged)
    Q_PROPERTY(QString eps READ eps WRITE setEps NOTIFY epsChanged)
    Q_PROPERTY(QString filename READ filename WRITE setFilename NOTIFY filenameChanged)
    Q_PROPERTY(QString mfunction READ mfunction WRITE setMfunction NOTIFY mfunctionChanged)

public:
    Newton();
    ~Newton();

    QString x();
    void setX(const QString &t);

    QString mit();
    void setMit(const QString &t);

    QString eps();
    void setEps(const QString &t);

    QString filename();
    void setFilename(const QString &f);

    QString mfunction();
    void setMfunction(const QString &p);

    double calculate(double x,int mit,double eps,int & i,int &state,double & fx);

public slots:
    void generateResult(QString x,QString mit,QString eps);

signals:
    void xChanged();
    void mitChanged();
    void epsChanged();
    void filenameChanged();
    void mfunctionChanged();
    void resultGenerated(bool success,QString state,QString result,QString fx,QString i);

private:
    QString _x;
    QString _mit;
    QString _eps;
    QString _filename;
    QString _mfunction;
};
#endif

