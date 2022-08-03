#include "ui.h"
#include <QDebug>
#include <QUrl>
UI::UI()
{
    scene = new QGraphicsScene;

    setBackgroundBrush(QBrush(Qt::black));
    setScene(scene);
    setMinimumSize(860, 900);
    setFixedWidth(860);
    scene->setSceneRect(0, 0, 860, 900);
    setWindowTitle("Project");
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QFile file(("text2.txt"));
    if (!file.open(QFile::ReadOnly))
        qDebug()<<"x";
    QTextStream stream(&file);

    QString x;
    QString Username, Password;

    User *tempuser;
    int count = 0;
    QChar type;


    while (!stream.atEnd())
    {
        x = stream.read(1);
        if (x == "\n")
        {
            count =0;
            if (type == 'c')
                tempuser = new class Customer(Username, Password);
            else
                if (type == 'w')
                    tempuser = new class Worker(Username, Password);

            credentials.insert(Username,tempuser);
            Username =Password =  "";
        }
        else if (x == ",")
        {
            if (count == 0)
            {
                count++;
            }
            else if (count == 1)
                count++;
        }
        else if(x== "\r")
        {
            continue;
        }
        else
        {
            if (count == 0)
                Username += x;
            else if (count == 1)
                Password += x;
            else
                type = x[0];
        }
    }
    if (Username != "" && Password!= "")
    {
        if (type == 'c')
            tempuser = new class Customer(Username, Password);
        else
            if (type == 'w')
                tempuser = new class Worker(Username, Password);

        credentials.insert(Username,tempuser);
    }

    file.close();


    /*for (QMap<QString, User*>::const_iterator it = credentials.begin(); it != credentials.end(); ++it)
    {
        if (it.value()->gettype()==work)
            qDebug()<< it.value()->getUsername()<<"  "<<it.value()->getPassword()<< " "<<"Worker" <<endl;
        else
            qDebug()<< it.value()->getUsername()<<"  "<<it.value()->getPassword()<< " "<<"Customer" <<endl;
    }*/


    errormessages = NULL;

    listofjobs.append(QString("Carpenter"));
    listofjobs.append(QString("Electrician"));
    listofjobs.append(QString("Plumber"));

    for (int i =0; i<12; i++)
    {
        listoftimes.append(QString::number(9+i)+":00 - "+ QString::number(9+1+i)+":00");
    }
}

void UI::displaymenu()
{
    QGraphicsTextItem *Title= new QGraphicsTextItem(QString("Project"));
    QFont titlefont("comic sans", 50);
    Title->setFont(titlefont);
    Title->setPos(width()/2-Title->boundingRect().width()/2, 50);
    Title->setDefaultTextColor(Qt::yellow);
    scene->addItem(Title);

    Button *registerbutton = new Button("Register");
    registerbutton->setPos(width()/2-registerbutton->boundingRect().width()/2, 275);
    connect(registerbutton, SIGNAL(clicked()), this, SLOT(registeracc()));
    scene->addItem(registerbutton);

    Button *Loginbutton = new Button("Login");
    Loginbutton->setPos(width()/2-Loginbutton->boundingRect().width()/2, 425);
    connect(Loginbutton, SIGNAL(clicked()), this, SLOT(loginacc()));
    scene->addItem(Loginbutton);

    Button *quitbutton = new Button("Quit");
    quitbutton->setPos(width()/2-quitbutton->boundingRect().width()/2, 575);
    connect(quitbutton, SIGNAL(clicked()), this, SLOT(close()));
    scene->addItem(quitbutton);



}

void UI::searchappointments()
{
    QString jobreq = worklist->currentText();
    QString timing = timelist->currentText();
    QString date = writedate->text();
    QString description = jobdesc->text();booking.description = description;
    QString address = addressedit->text();booking.address = address;
    QDate Date;
    QString num = "";
    int timinginint;
    bool flag = true;
    int co = 0;
    while(flag)
    {
        if (timing[co]==':')
            flag = false;
        else
            num = num+timing[co];
        co++;
    }
    timinginint = num.toInt();
    num = "";booking.time = timinginint;



    int d, m , y;
    int c=0;
    for (auto x:date)
    {
        if (x=="/")
        {
            if (c==0)
            {
                d=num.toInt();
                c++;
            }
            else
            {
                m = num.toInt();
                c++;
            }
            num = "";

        }
        else
            num = num+x;

    }
    y=num.toInt();
    Date.setDate(y,m,d);
    struct Date date1;
    date1.day = d;date1.month = m;date1.year = y; booking.date = date1;

    int day = Date.dayOfWeek();
    day = day -1;
    day = (day+1)%7;

    for (auto x:credentials)
    {
        QVector<int> times;
        bool startsearch=false;
        if (day == 0)
            startsearch = true;
        int count = 0;
        QString r, num = "", j;

        if (dynamic_cast<class Worker*>(x))
        {
            QString Job;
            QFile file(""+x->getUsername()+".txt");
            file.open(QFile::ReadOnly);
            QTextStream stream(&file);
            bool job = false;

            while(!stream.atEnd())
            {

                r = stream.read(1);
                if (job)
                {
                if (startsearch)
                {
                    if(r == '\n')
                    {
                        times.push_back(num.toInt());
                        num ="";
                        startsearch = false;
                    }
                    else if (r=='\r')
                        continue;
                    else
                        if (r == ',')
                        {
                            times.push_back(num.toInt());
                            num ="";
                        }
                    else num = num +r;
                }
                else
                {
                    if (r == '\n')
                    {
                        count++;
                        if(count == day)
                            startsearch = true;
                        num = "";
                    }
                }
}
                else
                {

                        if (r == "\n")
                        {
                            job = true;
                            Job = j;
                        }
                        else
                            if(r == "\r")
                                continue;
                        else
                                j = j+r;

                }
            }
            for (auto tim:times)
            {
                if (tim == timinginint && Job == jobreq)
                    searchlist.append(dynamic_cast<class Worker*>(x));
            }
        }

    }

    QGraphicsView *view;
    view = new QGraphicsView;

    QGraphicsScene *scene2;
    scene2 = new QGraphicsScene;

    view->setBackgroundBrush(QBrush(Qt::black));
    view->setScene(scene2);
    view->setMinimumSize(600, 500);
    view->setFixedWidth(600);
    scene2->setSceneRect(0, 0, 600, 500);
    view->setWindowTitle("Project");
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    view->show();

    if (searchlist.size()==0)
    {
        QGraphicsTextItem *noresult= new QGraphicsTextItem(QString("There are no workers available at this time"));
        QFont writefont1("comic sans", 14);
        noresult->setFont(writefont1);
        noresult->setPos(100, 300);
        noresult->setDefaultTextColor(Qt::red);
        scene2->addItem(noresult);
    }
    else
    {
        booking.customer = currentcust->getUsername();
        booking.worker = searchlist[0]->getUsername();
        QGraphicsTextItem *result= new QGraphicsTextItem(QString("Worker Found\nName: "+searchlist[0]->getUsername()+"\nDate: "+date+"   Time:"+timing+"\nJob:"
                                                         +jobreq));
        QFont writefont1("comic sans", 14);
        result->setFont(writefont1);
        result->setPos(50, 50);
        result->setDefaultTextColor(Qt::white);
        scene2->addItem(result);

        Button *confirm = new Button("Confirm Booking");
        confirm->setPos(view->width()/2-confirm->boundingRect().width()/2, 350);
        connect(confirm, SIGNAL(clicked()), this, SLOT(Bookingpending()));
        connect(confirm, SIGNAL(clicked()), view, SLOT(close()));
        scene2->addItem(confirm);
    }
    emit(finishedsearch());
}

void UI::registeracc()
{
    for (int i = 0; i<scene->items().size(); i++)
        delete scene->items()[i];
    scene->clear();

    QGraphicsTextItem *Title= new QGraphicsTextItem(QString("Register"));
    QFont titlefont("comic sans", 50);
    Title->setFont(titlefont);
    Title->setPos(width()/2-Title->boundingRect().width()/2, 50);
    Title->setDefaultTextColor(Qt::yellow);
    scene->addItem(Title);


    QGraphicsTextItem *Username= new QGraphicsTextItem(QString("Username:"));
    QFont writefont1("comic sans", 17);
    Username->setFont(writefont1);
    Username->setPos(100, 300);
    Username->setDefaultTextColor(Qt::white);
    scene->addItem(Username);

    QGraphicsTextItem *Acctype= new QGraphicsTextItem(QString("Account\nType:"));
    Acctype->setFont(writefont1);
    Acctype->setPos(100, 175);
    Acctype->setDefaultTextColor(Qt::white);
    scene->addItem(Acctype);

    QFont writefont3("comic sans", 12);
    QGraphicsTextItem *Customertext= new QGraphicsTextItem(QString("Customer"));
    Customertext->setFont(writefont3);
    Customertext->setPos(350, 185);
    Customertext->setDefaultTextColor(Qt::white);
    scene->addItem(Customertext);




    Customer = new Checkbox(Qt::green);
    Customer->setPos(300, 175);
    scene->addItem(Customer);
    connect(Customer, SIGNAL(clicked()), this, SLOT(managetickC()));

    QGraphicsTextItem *Workertext= new QGraphicsTextItem(QString("Worker"));
    Workertext->setFont(writefont3);
    Workertext->setPos(550, 185);
    Workertext->setDefaultTextColor(Qt::white);
    scene->addItem(Workertext);

    Worker = new Checkbox(Qt::red);
    Worker->setPos(500, 175);
    scene->addItem(Worker);
    connect(Worker, SIGNAL(clicked()), this, SLOT(managetickW()));

    QFont writefont2("comic sans", 15);

    reguser = new QLineEdit;
    scene->addWidget(reguser);
    reguser->resize(350,45);
    reguser->move(300,300);
    reguser->setFont(writefont2);

    QGraphicsTextItem *Password= new QGraphicsTextItem(QString("Password:"));
    Password->setFont(writefont1);
    Password->setPos(100, 450);
    Password->setDefaultTextColor(Qt::white);
    scene->addItem(Password);

    regpass = new QLineEdit;
    scene->addWidget(regpass);
    regpass->resize(350,45);
    regpass->move(300,450);
    regpass->setFont(writefont2);
    regpass->setEchoMode(QLineEdit::Password);

    QGraphicsTextItem *ConfirmPassword= new QGraphicsTextItem(QString("Confirm\nPassword:"));
    ConfirmPassword->setFont(writefont1);
    ConfirmPassword->setPos(100, 580);
    ConfirmPassword->setDefaultTextColor(Qt::white);
    scene->addItem(ConfirmPassword);

    regpass2 = new QLineEdit;
    scene->addWidget(regpass2);
    regpass2->resize(350,45);
    regpass2->move(300,600);
    regpass2->setFont(writefont2);
    regpass2->setEchoMode(QLineEdit::Password);

    Button *registerac = new Button("Register",200);
    registerac->setPos(width()/2-registerac->boundingRect().width()/2, 700);
    connect(registerac, SIGNAL(clicked()), this, SLOT(checkregistration()));
    scene->addItem(registerac);



}
#include <QDebug>

void UI::loginacc()
{
    for (int i = 0; i<scene->items().size(); i++)
        delete scene->items()[i];
    scene->clear();

    QGraphicsTextItem *Title= new QGraphicsTextItem(QString("Login"));
    QFont titlefont("comic sans", 50);
    Title->setFont(titlefont);
    Title->setPos(width()/2-Title->boundingRect().width()/2, 50);
    Title->setDefaultTextColor(Qt::yellow);
    scene->addItem(Title);


    QGraphicsTextItem *Username= new QGraphicsTextItem(QString("Username:"));
    QFont writefont1("comic sans", 17);
    Username->setFont(writefont1);
    Username->setPos(100, 300);
    Username->setDefaultTextColor(Qt::white);
    scene->addItem(Username);

    QFont writefont2("comic sans", 15);

    loguser = new QLineEdit;
    scene->addWidget(loguser);
    loguser->resize(350,45);
    loguser->move(300,300);
    loguser->setFont(writefont2);

    QGraphicsTextItem *Password= new QGraphicsTextItem(QString("Password:"));
    Password->setFont(writefont1);
    Password->setPos(100, 450);
    Password->setDefaultTextColor(Qt::white);
    scene->addItem(Password);

    logpass = new QLineEdit;
    scene->addWidget(logpass);
    logpass->resize(350,45);
    logpass->move(300,450);
    logpass->setFont(writefont2);
    logpass->setEchoMode(QLineEdit::Password);

    Button *loginac = new Button("Login",200);
    loginac->setPos(width()/2-loginac->boundingRect().width()/2, 550);
    connect(loginac, SIGNAL(clicked()), this, SLOT(authenticatelogin()));
    scene->addItem(loginac);



    /*QFont writefont3("comic sans", 12);
    QGraphicsTextItem *Customertext= new QGraphicsTextItem(QString("Customer"));
    Customertext->setFont(writefont3);
    Customertext->setPos(350, 185);
    Customertext->setDefaultTextColor(Qt::white);
    scene->addItem(Customertext);




    Customer = new Checkbox(Qt::green);
    Customer->setPos(300, 175);
    scene->addItem(Customer);
    connect(Customer, SIGNAL(clicked()), this, SLOT(managetickC()));

    QGraphicsTextItem *Workertext= new QGraphicsTextItem(QString("Worker"));
    Workertext->setFont(writefont3);
    Workertext->setPos(550, 185);
    Workertext->setDefaultTextColor(Qt::white);
    scene->addItem(Workertext);

    Worker = new Checkbox(Qt::red);
    Worker->setPos(500, 175);
    scene->addItem(Worker);
    connect(Worker, SIGNAL(clicked()), this, SLOT(managetickW()));*/
}

bool UI::checksameusername() //check username format + if used before
{
    QString x = reguser->text();
    bool temp = true;
    for (auto i:x)
    {
        if (i == ',')
        {
            invalidusername("Username should not include commas");
            temp = false;
        }

    }

    if (credentials.find(x) != credentials.end())
    {
        temp = false;
        invalidusername("Username already in use");
    }
    if (x == "")
    {
        temp = false;
        invalidusername("Username cannot be empty");
    }
    return temp;
}

void UI::authenticatelogin()
{
    if (errormessages != NULL)
        delete errormessages;
    if(!checkusernameexists())
        return;
    else
        if(!checkcorrectpass())
            return;

    QMap<QString, User*>::iterator it = credentials.find(loguser->text());
    if (dynamic_cast<class Worker*>(it.value()))
        Workerlogin(dynamic_cast<class Worker*>(it.value()));
    else
        Customerlogin(dynamic_cast<class Customer*>(it.value()));

}

void UI::managetickC()
{
    if (customerclicked)
    {
        Customer->maketick();
        customerclicked = false;
    }
    else
    {
        if (!workerclicked)
        {
            Customer->maketick();
            customerclicked = true;
        }
    }
}

void UI::managetickW()
{
    if (workerclicked)
    {
        Worker->maketick();
        workerclicked = false;
    }
    else
    {
        if (!customerclicked)
        {
            Worker->maketick();
            workerclicked = true;
        }
    }
}

void UI::checkregistration()
{
    if (errormessages != NULL)
        delete errormessages;
    if (noacctype())
        return;
    else
        if (!checksameusername())
            return;
        else
            if(!checkpassword())
                return;
        else
                if(!checksamepassword())
                    return;
    completeregisteration();
}

void UI::setworkinghrs()
{
    QGraphicsView *view;
    view = new QGraphicsView;

    QGraphicsScene *scene2;
    scene2 = new QGraphicsScene;

    view->setBackgroundBrush(QBrush(Qt::black));
    view->setScene(scene2);
    view->setMinimumSize(1200, 900);
    view->setFixedWidth(1200);
    scene2->setSceneRect(0, 0, 1200, 900);
    view->setWindowTitle("Project");
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    view->show();

    QGraphicsRectItem *days;
    for (int i = 0; i< 7; i++)
    {
        days = new QGraphicsRectItem(130+150*i, 100, 150,75);
        days->setBrush(QBrush(Qt::blue));
        scene2->addItem(days);


        QString txt;
        if (i==0)
            txt = "Sunday";
        else if (i==1)
            txt = "Monday";
        else if (i==2)
        txt = "Tuesday";
        else if (i==3)
        txt = "Wednesday";
        else if (i==4)
        txt = "Thursday";
        else if (i==5)
        txt = "Friday";
        else if (i==6)
        txt = "Saturday";



        QGraphicsTextItem *dayname = new QGraphicsTextItem(days);
        dayname->setPlainText(txt);
        QFont writefont1("comic sans", 17);
        dayname->setFont(writefont1);
        dayname->setPos(130+150*i+75-dayname->boundingRect().width()/2, 100+75/2.0-dayname->boundingRect().height()/2);
        //dayname->setPos(days->boundingRect().width()/2-dayname->boundingRect().width()/2, days->boundingRect().height()/2-dayname->boundingRect().height()/2);
        dayname->setDefaultTextColor(Qt::white);
        //scene2->addItem(dayname);

    }


    Timetable *tbl = new Timetable;
    scene2->addItem(tbl);
    tbl->setPos(75,175);
    tbl->makeslots();

    currentworker->settimetable(tbl);

    worklist = new QComboBox;
    worklist->addItems(listofjobs);
    scene2->addWidget(worklist);
    worklist->move(300,800);




    QFont writefont3("comic sans", 12);
    QGraphicsTextItem *jobs= new QGraphicsTextItem(QString("Type of work:"));
    jobs->setFont(writefont3);
    jobs->setPos(150, 800);
    jobs->setDefaultTextColor(Qt::white);
    scene2->addItem(jobs);

    connect(this, SIGNAL(leave()), view, SLOT(close()));

    Button *save = new Button("Save", 200,75 );
    save->setPos(500, 800);
    connect(save, SIGNAL(clicked()), this, SLOT(savetimetable()));
    scene2->addItem(save);
}

void UI::savetimetable()
{

    QString txt = worklist->currentText();
    currentworker->setJob(txt);
    currentworker->savenewtimes();



    emit(leave());

}

void UI::seerequests()
{
    currentworker->readfile();
    QVector<Appointment> apps = currentworker->getnotconfirmed();
    QVector<Appointment>::iterator it;
    for (it = apps.begin();it!=apps.end();it++)
    {
        it->worker = currentworker->getUsername();
    }
    QGraphicsView *view;
    view = new QGraphicsView;

    QGraphicsScene *scene2;
    scene2 = new QGraphicsScene;

    view->setBackgroundBrush(QBrush(Qt::black));
    view->setScene(scene2);
    view->setMinimumSize(900, 850);
    view->setFixedWidth(900);
    //scene2->setSceneRect(0, 0, 800, 850);
    view->setWindowTitle("Project");
    view->show();

    int no=0;
    confirms = new QVector<Button*>;
    declines = new QVector<Button*>;
    for (int i=0; i<apps.size();i++)
    {
         QFont writefont3("comic sans", 12);
         QGraphicsTextItem *appno= new QGraphicsTextItem(QString("Appointment "+ QString::number(no+1)+":"));
         appno->setFont(writefont3);
         appno->setPos(50, 50+300*no);
         appno->setDefaultTextColor(Qt::white);
         scene2->addItem(appno);

         //customer, date
         //address
         //description
         QGraphicsTextItem *worke= new QGraphicsTextItem(QString("Worker: "+ apps[no].worker +"   Date: "+ QString::number(apps[no].date.day)
                                                                +"/"+QString::number(apps[no].date.month)+"/"+QString::number(apps[no].date.year)));
         worke->setFont(writefont3);
         worke->setPos(50, 100+300*no);
         worke->setDefaultTextColor(Qt::white);
         scene2->addItem(worke);

         QGraphicsTextItem *address= new QGraphicsTextItem(QString("Address: "+ apps[i].address));
         address->setFont(writefont3);
         address->setPos(50, 150+300*i);
         address->setDefaultTextColor(Qt::white);
         scene2->addItem(address);

         QGraphicsTextItem *desc= new QGraphicsTextItem(QString("Job Description: "+ apps[i].description));
         desc->setFont(writefont3);
         desc->setPos(50, 200+300*i);
         desc->setDefaultTextColor(Qt::white);
         scene2->addItem(desc);



         Button *confirm = new Button("Confirm",200,100);
         confirm->setPos(400, 50+300*no);
         connect(confirm, SIGNAL(clicked()), this, SLOT(confirmappointments()));
         connect(confirm, SIGNAL(clicked()), view, SLOT(close()));
         scene2->addItem(confirm);

         confirms->append(confirm);

         Button *decline = new Button("Decline",200,100);
         decline->setPos(600, 50+300*no);
         connect(decline, SIGNAL(clicked()), this, SLOT(declineapps()));
         connect(decline, SIGNAL(clicked()), view, SLOT(close()));
         scene2->addItem(decline);

         declines->append(decline);

         no++;


    }
}

void UI::seerequestsCust()
{
    currentcust->readfile();
    QVector<Appointment> apps = currentcust->getnotconfirmed();

    QGraphicsView *view;
    view = new QGraphicsView;

    QGraphicsScene *scene2;
    scene2 = new QGraphicsScene;

    view->setBackgroundBrush(QBrush(Qt::black));
    view->setScene(scene2);
    view->setMinimumSize(800, 850);
    view->setFixedWidth(800);
    scene2->setSceneRect(0, 0, 800, 850);
    view->setWindowTitle("Project");
    view->show();

    int no=0;
    for (int i=0; i<apps.size();i++)
    {
         QFont writefont3("comic sans", 12);
         QGraphicsTextItem *appno= new QGraphicsTextItem(QString("Appointment "+ QString::number(no+1)+":"));
         appno->setFont(writefont3);
         appno->setPos(50, 50+300*no);
         appno->setDefaultTextColor(Qt::white);
         scene2->addItem(appno);

         //customer, date
         //address
         //description
         QGraphicsTextItem *worke= new QGraphicsTextItem(QString("Worker: "+ apps[no].worker +"   Date: "+ QString::number(apps[no].date.day)
                                                                +"/"+QString::number(apps[no].date.month)+"/"+QString::number(apps[no].date.year)));
         worke->setFont(writefont3);
         worke->setPos(50, 100+300*no);
         worke->setDefaultTextColor(Qt::white);
         scene2->addItem(worke);

         QGraphicsTextItem *address= new QGraphicsTextItem(QString("Address: "+ apps[i].address));
         address->setFont(writefont3);
         address->setPos(50, 150+300*i);
         address->setDefaultTextColor(Qt::white);
         scene2->addItem(address);

         QGraphicsTextItem *desc= new QGraphicsTextItem(QString("Job Description: "+ apps[i].description));
         desc->setFont(writefont3);
         desc->setPos(50, 200+300*i);
         desc->setDefaultTextColor(Qt::white);
         scene2->addItem(desc);

         no++;

    }
}

void UI::seeappointments()
{
    QGraphicsView *view;
    view = new QGraphicsView;

    QGraphicsScene *scene2;
    scene2 = new QGraphicsScene;

    view->setBackgroundBrush(QBrush(Qt::black));
    view->setScene(scene2);
    view->setMinimumSize(1200, 900);
    view->setFixedWidth(1200);
    scene2->setSceneRect(0, 0, 1200, 900);
    view->setWindowTitle("Project");
    view->show();

    QVector<Appointment> apps = currentworker->getappointmentsconfirmed();
    for (int i = 0; i<apps.size();i++)
    {
        QFont writefont3("comic sans", 12);
        QGraphicsTextItem *appno= new QGraphicsTextItem(QString("Appointment "+ QString::number(i+1)+":"));
        appno->setFont(writefont3);
        appno->setPos(50, 50+300*i);
        appno->setDefaultTextColor(Qt::white);
        scene2->addItem(appno);

        //customer, date
        //address
        //description
        QGraphicsTextItem *cust= new QGraphicsTextItem(QString("Customer: "+ apps[i].customer +"   Date: "+ QString::number(apps[i].date.day)
                                                               +"/"+QString::number(apps[i].date.month)+"/"+QString::number(apps[i].date.year)));
        cust->setFont(writefont3);
        cust->setPos(50, 100+300*i);
        cust->setDefaultTextColor(Qt::white);
        scene2->addItem(cust);

        QGraphicsTextItem *address= new QGraphicsTextItem(QString("Address: "+ apps[i].address));
        address->setFont(writefont3);
        address->setPos(50, 150+300*i);
        address->setDefaultTextColor(Qt::white);
        scene2->addItem(address);

        QGraphicsTextItem *desc= new QGraphicsTextItem(QString("Job Description: "+ apps[i].description));
        desc->setFont(writefont3);
        desc->setPos(50, 200+300*i);
        desc->setDefaultTextColor(Qt::white);
        scene2->addItem(desc);
    }

}

void UI::confirmappointments()
{
    QVector<Appointment> x = currentworker->getnotconfirmed();
    QVector<Appointment>::iterator it;
    for (it = x.begin();it!=x.end();it++)
    {
        it->worker = currentworker->getUsername();
    }
    int i;
    for (i = 0; i<confirms->size();i++)
    {
        if (confirms->at(i) == dynamic_cast<Button*>(QObject::sender()))
            break;
    }
    Appointment confirmed = x[i];
    currentworker->addconfirmed(confirmed);

    currentcust = new class Customer(confirmed.customer, credentials.find(confirmed.customer).value()->getPassword());
    currentcust->addconfirmed(confirmed);


    seerequests();
}

void UI::seeappsCust()
{
    currentcust->readfile();
    QVector<Appointment> apps = currentcust->getconfirmed();

    QGraphicsView *view;
    view = new QGraphicsView;

    QGraphicsScene *scene2;
    scene2 = new QGraphicsScene;

    view->setBackgroundBrush(QBrush(Qt::black));
    view->setScene(scene2);
    view->setMinimumSize(800, 850);
    view->setFixedWidth(800);
    scene2->setSceneRect(0, 0, 800, 850);
    view->setWindowTitle("Project");
    view->show();

    int no=0;
    for (int i=0; i<apps.size();i++)
    {
         QFont writefont3("comic sans", 12);
         QGraphicsTextItem *appno= new QGraphicsTextItem(QString("Appointment "+ QString::number(no+1)+":"));
         appno->setFont(writefont3);
         appno->setPos(50, 50+300*no);
         appno->setDefaultTextColor(Qt::white);
         scene2->addItem(appno);

         //customer, date
         //address
         //description
         QGraphicsTextItem *worke= new QGraphicsTextItem(QString("Worker: "+ apps[no].worker +"   Date: "+ QString::number(apps[no].date.day)
                                                                +"/"+QString::number(apps[no].date.month)+"/"+QString::number(apps[no].date.year)));
         worke->setFont(writefont3);
         worke->setPos(50, 100+300*no);
         worke->setDefaultTextColor(Qt::white);
         scene2->addItem(worke);

         QGraphicsTextItem *address= new QGraphicsTextItem(QString("Address: "+ apps[i].address));
         address->setFont(writefont3);
         address->setPos(50, 150+300*i);
         address->setDefaultTextColor(Qt::white);
         scene2->addItem(address);

         QGraphicsTextItem *desc= new QGraphicsTextItem(QString("Job Description: "+ apps[i].description));
         desc->setFont(writefont3);
         desc->setPos(50, 200+300*i);
         desc->setDefaultTextColor(Qt::white);
         scene2->addItem(desc);

         no++;

    }
}

void UI::bookapp()
{
    QGraphicsView *view;
    view = new QGraphicsView;

    QGraphicsScene *scene2;
    scene2 = new QGraphicsScene;

    QGraphicsTextItem *Title= new QGraphicsTextItem(QString("Book Appointment"));
    QFont titlefont("comic sans", 35);
    Title->setFont(titlefont);
    Title->setPos(view->width()/2-Title->boundingRect().width()/2, 50);
    Title->setDefaultTextColor(Qt::yellow);
    scene2->addItem(Title);


    view->setBackgroundBrush(QBrush(Qt::black));
    view->setScene(scene2);
    view->setMinimumSize(700, 900);
    view->setFixedWidth(600);
    scene2->setSceneRect(0, 0, 700, 900);
    view->setWindowTitle("Project");
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    view->show();

    connect(this, SIGNAL(finishedsearch()), view, SLOT(close()));


    QFont writefont1("comic sans", 14);

    QGraphicsTextItem *jobtype= new QGraphicsTextItem(QString("Job Type:"));
    jobtype->setFont(writefont1);
    jobtype->setPos(50, 150);
    jobtype->setDefaultTextColor(Qt::white);
    scene2->addItem(jobtype);

    worklist = new QComboBox;
    worklist->addItems(listofjobs);
    scene2->addWidget(worklist);
    worklist->move(250,150);

    QGraphicsTextItem *time= new QGraphicsTextItem(QString("Choose Time: "));
    time->setFont(writefont1);
    time->setPos(50, 250);
    time->setDefaultTextColor(Qt::white);
    scene2->addItem(time);



    QGraphicsTextItem *date= new QGraphicsTextItem(QString("Choose Date: (dd/mm/yyyy)"));
    date->setFont(writefont1);
    date->setPos(50, 350);
    date->setDefaultTextColor(Qt::white);
    scene2->addItem(date);


    writedate= new QLineEdit;
    scene2->addWidget(writedate);
    writedate->resize(350,45);
    writedate->move(50,400);
    writedate->setFont(writefont1);

    timelist = new QComboBox;
    timelist->addItems(listoftimes);
    scene2->addWidget(timelist);
    timelist->move(250,250);

    QGraphicsTextItem *description= new QGraphicsTextItem(QString("Describe job required: "));
    description->setFont(writefont1);
    description->setPos(50, 500);
    description->setDefaultTextColor(Qt::white);
    scene2->addItem(description);

    jobdesc= new QLineEdit;
    scene2->addWidget(jobdesc);
    jobdesc->resize(350,45);
    jobdesc->move(50,550);
    jobdesc->setFont(writefont1);

    QGraphicsTextItem *address= new QGraphicsTextItem(QString("Enter Address: "));
    address->setFont(writefont1);
    address->setPos(50, 650);
    address->setDefaultTextColor(Qt::white);
    scene2->addItem(address);

    addressedit= new QLineEdit;
    scene2->addWidget(addressedit);
    addressedit->resize(350,45);
    addressedit->move(50,700);
    addressedit->setFont(writefont1);


    Button *search = new Button("Search Available Appointments",500, 100 );
    search->setPos(view->width()/2-search->boundingRect().width()/2, 775);
    connect(search, SIGNAL(clicked()), this, SLOT(searchappointments()));
    scene2->addItem(search);
}

void UI::Bookingpending()
{
    currentcust->addpending(booking);
    searchlist[0]->addpending(booking);
}

void UI::declineapps()
{
    QVector<Appointment> x = currentworker->getnotconfirmed();
    QVector<Appointment>::iterator it;
    for (it = x.begin();it!=x.end();it++)
    {
        it->worker = currentworker->getUsername();
    }
    int i;
    for (i = 0; i<declines->size();i++)
    {
        if (declines->at(i) == dynamic_cast<Button*>(QObject::sender()))
            break;
    }
    Appointment declined = x[i];
    currentworker->decline(declined);

    currentcust = new class Customer(declined.customer, credentials.find(declined.customer).value()->getPassword());
    currentcust->decline(declined);


    seerequests();
}

bool UI::checksamepassword()
{
    QString text = "Passwords do not match";
    if (regpass->text() != regpass2->text())
    {
        invalidpassword(text);
        return false;
    }
    return true;
}

void UI::completeregisteration()
{
    User *tmp;
    if (workerclicked == true)
    {
        tmp = new class Worker(reguser->text(), regpass->text());
    }
    else
        tmp = new class Customer(reguser->text(), regpass->text());

    credentials.insert(reguser->text(), tmp);


    QFile file("text2.txt");
    if (file.open(QFile::WriteOnly | QFile::Append))
{
        QTextStream stream(&file);
    if (tmp->gettype() == work)
        stream<<reguser->text()<<','<<regpass->text()<<','<<'w'<<endl;
    else
        stream<<reguser->text()<<','<<regpass->text()<<','<<'c'<<endl;
}

    file.close();
    workerclicked = customerclicked = false;

    QMap<QString, User*>::iterator it = credentials.find(reguser->text());
    if (dynamic_cast<class Worker*>(it.value()))
        Workerlogin(dynamic_cast<class Worker*>(it.value()));
    else
        Customerlogin(dynamic_cast<class Customer*>(it.value()));
}

bool UI::noacctype()
{
    if (customerclicked == false && workerclicked == false)
    {
            QGraphicsTextItem *errormessage= new QGraphicsTextItem(QString("You must choose an account type!"));
            QFont titlefont("comic sans", 10);
            errormessage->setFont(titlefont);
            errormessage->setPos(300,230);
            errormessage->setDefaultTextColor(Qt::red);
            scene->addItem(errormessage);
            errormessages = errormessage;
            return true;
    }
    return false;

}

bool UI::checkusernameexists()
{
    QMap<QString, User*>::const_iterator it = credentials.find(loguser->text());
    if ( it == credentials.end() )
    {
        invalidusername(QString("Username does not exist"));
        return false;
    }
    return true;
}

bool UI::checkcorrectpass()
{
    QMap<QString, User*>::const_iterator it = credentials.find(loguser->text());
    if (logpass->text() != it.value()->getPassword())
    {
        invalidpassword("Password incorrect");
        return false;
    }
    return true;
}

void UI::Customerlogin(class Customer *customer )
{
    for (int i = 0; i<scene->items().size(); i++)
        delete scene->items()[i];
    scene->clear();

    currentcust = customer;
    currentworker = NULL;

    for (int i = 0; i<scene->items().size(); i++)
        delete scene->items()[i];
    scene->clear();



    QGraphicsTextItem *Title= new QGraphicsTextItem(QString("Appointments"));
    QFont titlefont("comic sans", 50);
    Title->setFont(titlefont);
    Title->setPos(width()/2-Title->boundingRect().width()/2, 50);
    Title->setDefaultTextColor(Qt::yellow);
    scene->addItem(Title);

    Button *bookapps = new Button("Book an appointment",500, 100 );
    bookapps->setPos(width()/2-bookapps->boundingRect().width()/2, 200);
    connect(bookapps, SIGNAL(clicked()), this, SLOT(bookapp()));
    scene->addItem(bookapps);

    Button *mycurrapps = new Button("My Appointments",500, 100 );
    mycurrapps->setPos(width()/2-mycurrapps->boundingRect().width()/2, 350);
    connect(mycurrapps, SIGNAL(clicked()), this, SLOT(seeappsCust()));
    scene->addItem(mycurrapps);

    Button *mypendingapps = new Button("My Pending Appointments",500, 100 );
    mypendingapps->setPos(width()/2-mypendingapps->boundingRect().width()/2, 500);
    connect(mypendingapps, SIGNAL(clicked()), this, SLOT(seerequestsCust()));
    scene->addItem(mypendingapps);


}

void UI::Workerlogin(class Worker *worker)
{
    for (int i = 0; i<scene->items().size(); i++)
        delete scene->items()[i];
    scene->clear();

    currentcust = NULL;
    currentworker = worker;

    worker->readfile();

    QGraphicsTextItem *Title= new QGraphicsTextItem(QString("Appointments"));
    QFont titlefont("comic sans", 50);
    Title->setFont(titlefont);
    Title->setPos(width()/2-Title->boundingRect().width()/2, 50);
    Title->setDefaultTextColor(Qt::yellow);
    scene->addItem(Title);

    Button *workinghrs = new Button("Working Hours",500, 100 );
    workinghrs->setPos(width()/2-workinghrs->boundingRect().width()/2, 200);
    connect(workinghrs, SIGNAL(clicked()), this, SLOT(setworkinghrs()));
    scene->addItem(workinghrs);

    Button *appointmentrequets = new Button("Appointment Requests",500, 100 );
    appointmentrequets->setPos(width()/2-appointmentrequets->boundingRect().width()/2, 350);
    connect(appointmentrequets, SIGNAL(clicked()), this, SLOT(seerequests()));
    scene->addItem(appointmentrequets);

    Button *myappointments = new Button("My Appointment",500, 100 );
    myappointments->setPos(width()/2-myappointments->boundingRect().width()/2, 500);
    connect(myappointments, SIGNAL(clicked()), this, SLOT(seeappointments()));
    scene->addItem(myappointments);
}

bool UI::checkpassword()
{
    QString x= regpass->text();
    QString text = "Password must be between 8 and 20 characters";
    if (x.length() < 8 || x.length() >20)
    {
        invalidpassword(text);
        return false;
    }
    return true;
}

void UI::invalidusername(QString x)
{
    QGraphicsTextItem *errormessage= new QGraphicsTextItem(x);
    QFont titlefont("comic sans", 10);
    errormessage->setFont(titlefont);
    errormessage->setPos(300,350);
    errormessage->setDefaultTextColor(Qt::red);
    scene->addItem(errormessage);
    errormessages = errormessage;
}

void UI::invalidpassword(QString x)
{
    QGraphicsTextItem *errormessage= new QGraphicsTextItem(x);
    QFont titlefont("comic sans", 10);
    errormessage->setFont(titlefont);
    errormessage->setPos(300,500);
    errormessage->setDefaultTextColor(Qt::red);
    scene->addItem(errormessage);
    errormessages = errormessage;
}


