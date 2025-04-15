#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("计算器");
    setWindowIcon(QIcon(":/icons/app_icon"));
    setCentralWidget(new QWidget);
    QGridLayout *layout = new QGridLayout;
    centralWidget()->setLayout(layout);
    QFont font;
    font.setPointSize(14);
    line = new QLineEdit;
    line->setText("0");
    line->setFont(font);
    line->setAlignment(Qt::AlignRight);
    line->setValidator(new QDoubleValidator);
    line->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    layout->addWidget(line,0,0,1,6);
    {
        PushButton *button = new PushButton;
        button->setText("AC");
        layout->addWidget(button,1,0);
        connect(button,&PushButton::clicked,this,[this]{
            line->setText("0");
            value=0,value1=0,value2=0,op="None";
        });
    }
    {
        PushButton *button = new PushButton;
        button->setText("C");
        layout->addWidget(button,1,1);
        connect(button,&PushButton::clicked,this,[this]{
            line->setText("0");
        });
    }
    {
        PushButton *button = new PushButton;
        button->setText("<-");
        layout->addWidget(button,1,2);
        connect(button,&PushButton::clicked,this,[this]{
        QString text = line->text();
        if (!text.isEmpty()) {
            text.remove(text.size() - 1, 1);
        }
        if (text.isEmpty()) text="0";
        line->setText(text);
        });
    }
    QString ops[4] = {"+", "-", "*", "/"};
    for (int i=1;i<=3;i++){
        for (int j=0;j<3;j++){
            PushButton *button = new PushButton;
            button->setText(QString::number((i-1)*3+j+1));
            layout->addWidget(button,i+1,j);
            connect(button,&PushButton::clicked,this,[this,it=(i-1)*3+j+1]{
                read(QString::number(it));
            });
        }
    }
    {
        PushButton *button = new PushButton;
        button->setText(QString::number(0));
        layout->addWidget(button,5,1);
        connect(button,&PushButton::clicked,this,[this]{
            read("0");
        });
    }
    {
        PushButton *button = new PushButton;
        button->setText("00");
        layout->addWidget(button,5,0);
        connect(button,&PushButton::clicked,this,[this]{
            read("00");
        });
    }
    {
        PushButton *button = new PushButton;
        button->setText(".");
        layout->addWidget(button,5,2);
        connect(button,&PushButton::clicked,this,[this]{
            QString text = line->text();
            if (text.isEmpty()) {
                text = "0";
            }
            if (text.size()>0 && text[text.size()-1]!='.') text+=".";
            line->setText(text);
        });
    }
    for (int i=0;i<4;i++){
    PushButton *button = new PushButton;
    button->setText(ops[i]);
    layout->addWidget(button,i+1,3);
    connect(button,&PushButton::clicked,this,[this,it=ops[i]]{
        press(it);
    });
    }
    {
    PushButton *button = new PushButton;
    button->setText("=");
    layout->addWidget(button,5,3);
    connect(button,&PushButton::clicked,this,&MainWindow::Equal);
    }
}

MainWindow::~MainWindow() {}
