#include <QFile>
#include <QProcess>
#include "Newton.hpp"
#include "Interval.h"
#include "Number.h"
#include <iostream>
#include <QLibrary>
//test funtion
/*

double function(double x){
    return x*x-2;
}

double dfunction(double x){
    return 2*x;

}
*/
typedef double (*MyPrototype)(double);



Newton::Newton()
    : _type("zmiennopozycyjna"), _types{"zmiennopozycyjna", "przedziałowa"}
{
}

Newton::~Newton()
{
}

QString Newton::type()
{
    return _type;
}

void Newton::setType(const QString &t)
{
    // Check for valid type.
    if (!_types.contains(t))
        return;

    if (t != _type) {
        _type = t;
        emit typeChanged();
    }
}

QStringList Newton::types()
{
    return _types;
}


QString Newton::x()
{
    return _x;
}

void Newton::setX(const QString &t)
{

    if (t != _x) {
        _x = t;
        emit xChanged();
    }
}

QString Newton::x2()
{
    return _x2;
}

void Newton::setX2(const QString &t)
{

    if (t != _x2) {
        _x2 = t;
        emit x2Changed();
    }
}


QString Newton::mit()
{
    return _mit;
}

void Newton::setMit(const QString &t)
{

    if (t != _mit) {
        _mit = t;
        emit mitChanged();
    }
}



QString Newton::eps()
{
    return _eps;
}

void Newton::setEps(const QString &t)
{

    if (t != _eps) {
        _eps = t;
        emit epsChanged();
    }
}

QString Newton::filename()
{
    return _filename;
}

void Newton::setFilename(const QString &f)
{
    if (f != _filename) {
        _filename = f;
        emit filenameChanged();
    }
}


QString Newton::mfunction()
{
    return _mfunction;
}

void Newton::setMfunction(const QString &p)
{
    if (p != _mfunction) {
        _mfunction = p;
        emit mfunctionChanged();
    }
}

QString Newton::mdfunction()
{
    return _mdfunction;
}

void Newton::setMdfunction(const QString &p)
{
    if (p != _mdfunction) {
        _mdfunction = p;
        emit mdfunctionChanged();
    }
}

long double Newton::calculate(double x,int mit,double eps,int & i,int &state,double &fx){
if(mit<0){
    state=1;
    return 0;
}
MyPrototype dfunction =
        (MyPrototype) QLibrary::resolve("testlib", "dfuntion");
MyPrototype function =
        (MyPrototype) QLibrary::resolve("testlib", "funtion");

state = 3;
for(i=1;i<=mit;i++){
    double df = dfunction(x);

    if(df==0){
        state = 2;
        return 0;
    }
    fx = function(x);
    double nx=x-fx/df;
    double test = fabs(nx-x)/ std::max( fabs(nx),fabs(x) );

    if(nx==0 || x==0 ||  test<eps ){
        state = 0;
        return nx;
    }
    x = nx;
}
return x;
}

std::string showLD(long double val) {
    constexpr int BUFS = 32;
    char buf[BUFS];

    snprintf(buf, BUFS, "%.20Le", val);
    return std::string(buf);
}

long double readLD(std::string val) {
    long double buf;
    scanf(val.c_str(),"%Le",&buf);
    return buf;
}

void Newton::generateResult(QString x,QString mit,QString eps)
{
    std::cout << "lol" << std::endl;
    /*
    if(mit<1){
        state = 1;
        emit resultGenerated(1,);
    }
    // Sanity check on arguments

    if (_x.isEmpty() or _filename.isEmpty() or
        (_mfunction.length() > 0 and _mfunction.length() < 5)) {
        emit resultGenerated(false,"0");
        return;
    }

    */
    ean::Interval * interval ;
    if(_type=="przedziałowa"){
        if(_x2.isEmpty()){

            ean::Interval ival(_x.toStdString());

            interval = &ival;

        }
        else{
            ean::Interval ival(IntervalArithmetic::LeftRead(_x.toStdString()),IntervalArithmetic::RightRead(_x2.toStdString()));
            interval = &ival;
        }
std::string test(interval->to_string());
std::string test2;
std::string test3;
//IntervalArithmetic::IEndsToStrings(interval->get,test2,test3);
   emit resultGenerated(true,"b",QString::fromStdString(interval->to_string()),QString::fromStdString(test2),QString::fromStdString(test3));
        return;
    }
    else{
    int i=0;
    int state = 0;
    double fx = 0;

    // long double nx = std::stod(x.toStdString());
ean::Number<long double> number(x.toStdString());

//long double nx = number.getm_value();
    long double nx = std::stod(x.toStdString());
    //long double nx = readLD(x.toStdString());
    int nmit = std::stoi(mit.toStdString());
    double neps = std::stod(eps.toStdString());

   //std::cout <<  calculate(nx,5,1e-16,i,state);<< std::endl;
   std::cout << " state: " << state << " i:" << i << std::endl;


   long double x2 = calculate(nx,nmit,neps,i,state,fx) ;
   //std::string x1 = std::to_string(x2);
   std::string x1 = showLD(x2);




   x =QString::fromStdString(x1 );
   //x =QString::fromStdString(std::to_string(calculate(nx,nmit,neps,i,state,fx) ) );
   QString rstate =QString::fromStdString(std::to_string(state) );
   QString rfx =QString::fromStdString(std::to_string(fx ) );
   QString ri =QString::fromStdString(std::to_string(i) );

   emit resultGenerated(true,rstate,x,rfx,ri);
    }

}

