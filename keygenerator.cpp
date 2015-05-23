#include <QFile>
#include <QProcess>
#include "keygenerator.hpp"

KeyGenerator::KeyGenerator()

{
}

KeyGenerator::~KeyGenerator()
{
}

QString KeyGenerator::x()
{
    return _x;
}

void KeyGenerator::setX(const QString &t)
{

    if (t != _x) {
        _x = t;
        emit xChanged();
    }
}



QString KeyGenerator::filename()
{
    return _filename;
}

void KeyGenerator::setFilename(const QString &f)
{
    if (f != _filename) {
        _filename = f;
        emit filenameChanged();
    }
}

QString KeyGenerator::mfunction()
{
    return _mfunction;
}

void KeyGenerator::setMfunction(const QString &p)
{
    if (p != _mfunction) {
        _mfunction = p;
        emit mfunctionChanged();
    }
}

void KeyGenerator::generateResult(QString x)
{

    std::string

    // Sanity check on arguments
    /*
    if (_x.isEmpty() or _filename.isEmpty() or
        (_mfunction.length() > 0 and _mfunction.length() < 5)) {
        emit resultGenerated(false,"0");
        return;
    }

    */
    emit resultGenerated(true,);

}

