#ifndef UI_H
#define UI_H

#include "worker.h"
#include "customer.h"
#include "user.h"
#include "checkbox.h"
#include "button.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QLineEdit>
#include <QFile>
#include <QTextStream>
#include "timeslot.h"
#include "timetable.h"
#include <QComboBox>
#include <QStringList>
#include <QDate>
#include <QList>

class UI: public QGraphicsView
{
    Q_OBJECT
public:
    UI();
    QGraphicsScene *scene;
    void displaymenu();
signals:
    void leave();
    void finishedsearch();
public slots:
    void searchappointments();
    void registeracc();
    void loginacc();
    void authenticatelogin();
    void managetickC();
    void managetickW();
    void checkregistration();
    void setworkinghrs();
    void savetimetable();
    void seerequests();
    void seerequestsCust();
    void seeappointments();
    void confirmappointments();
    void seeappsCust();
    void bookapp();
    void Bookingpending();
    void declineapps();
private:
    QLineEdit *reguser, *regpass, *regpass2, *loguser, *logpass;
    bool customerclicked=false, workerclicked=false;
    Checkbox *Customer,*Worker;
    QMap<QString, User*> credentials;
    void invalidusername(QString x);
    void invalidpassword(QString text);
    bool checksameusername();
    bool checkpassword();
    bool checksamepassword();
    void completeregisteration();
    bool noacctype();
    QGraphicsTextItem* errormessages;
    bool checkusernameexists();
    bool checkcorrectpass();
    void Customerlogin(class Customer *customer );
    void Workerlogin(class Worker *worker);
    class Customer *currentcust= NULL;
    class Worker *currentworker=NULL;
    QComboBox *worklist,*timelist;
    QStringList listofjobs, listoftimes;
    QLineEdit *writedate, *jobdesc, *addressedit;//date of appointment, jobdescription
    QList<class Worker*> searchlist;
    Appointment booking;
    QVector<Button*> *confirms, *declines;
};

#endif // UI_H
