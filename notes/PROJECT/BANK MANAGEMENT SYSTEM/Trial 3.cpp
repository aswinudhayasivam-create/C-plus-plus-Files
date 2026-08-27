#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QLabel>
#include <QFile>
#include <QDataStream>
#include <QMessageBox>

class Account
{
public:
    int accNo;
    QString name;
    int balance;
};

class BankApp : public QWidget
{
    Q_OBJECT

    QLineEdit *user, *pass, *acc, *name, *amt;
    QLabel *status;

public:
    BankApp()
    {
        QVBoxLayout *layout = new QVBoxLayout;

        user = new QLineEdit;
        pass = new QLineEdit;
        pass->setEchoMode(QLineEdit::Password);

        acc = new QLineEdit;
        name = new QLineEdit;
        amt = new QLineEdit;

        QPushButton *loginBtn = new QPushButton("Login");
        QPushButton *createBtn = new QPushButton("Create");
        QPushButton *depositBtn = new QPushButton("Deposit");
        QPushButton *viewBtn = new QPushButton("View");

        status = new QLabel;

        layout->addWidget(new QLabel("Username"));
        layout->addWidget(user);
        layout->addWidget(new QLabel("Password"));
        layout->addWidget(pass);
        layout->addWidget(loginBtn);

        layout->addWidget(new QLabel("Account No"));
        layout->addWidget(acc);
        layout->addWidget(new QLabel("Name"));
        layout->addWidget(name);
        layout->addWidget(new QLabel("Amount"));
        layout->addWidget(amt);

        layout->addWidget(createBtn);
        layout->addWidget(depositBtn);
        layout->addWidget(viewBtn);
        layout->addWidget(status);

        setLayout(layout);

        connect(loginBtn, &QPushButton::clicked, this, &BankApp::login);
        connect(createBtn, &QPushButton::clicked, this, &BankApp::createAcc);
        connect(depositBtn, &QPushButton::clicked, this, &BankApp::deposit);
        connect(viewBtn, &QPushButton::clicked, this, &BankApp::viewAcc);
    }

    void login()
    {
        if(user->text()=="admin" && pass->text()=="1234")
            status->setText("Login Success");
        else
            status->setText("Login Failed");
    }

    void createAcc()
    {
        QFile file("data.dat");
        file.open(QIODevice::Append);
        QDataStream out(&file);

        Account a;
        a.accNo = acc->text().toInt();
        a.name = name->text();
        a.balance = amt->text().toInt();

        out<<a.accNo<<a.name<<a.balance;
        file.close();

        status->setText("Account Created");
    }

    void deposit()
    {
        QFile file("data.dat");
        file.open(QIODevice::ReadWrite);
        QDataStream in(&file);

        QList<Account> list;

        while(!in.atEnd())
        {
            Account a;
            in>>a.accNo>>a.name>>a.balance;
            if(a.accNo == acc->text().toInt())
                a.balance += amt->text().toInt();
            list.append(a);
        }

        file.close();

        file.open(QIODevice::WriteOnly);
        QDataStream out(&file);

        for(auto a:list)
            out<<a.accNo<<a.name<<a.balance;

        file.close();

        status->setText("Deposited");
    }

    void viewAcc()
    {
        QFile file("data.dat");
        file.open(QIODevice::ReadOnly);
        QDataStream in(&file);

        while(!in.atEnd())
        {
            Account a;
            in>>a.accNo>>a.name>>a.balance;

            if(a.accNo == acc->text().toInt())
            {
                status->setText("Name: "+a.name+" Balance: "+QString::number(a.balance));
                file.close();
                return;
            }
        }

        file.close();
        status->setText("Not Found");
    }
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    BankApp w;
    w.show();

    return app.exec();
}