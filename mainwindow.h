#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QIntValidator>
#include <QGridLayout>
#include <QtMath>
class PushButton : public QPushButton
{
public:
    PushButton(QWidget *parent = nullptr)
        : QPushButton(parent)
    {
        setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    }
};
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QLineEdit* line;
    QString op="None";
    double value=0,value1=0,value2=0;
    bool flag=0;
    void press(QString s){
        if (op=="None"){
            value1=line->text().toDouble();
            op=s;
            line->setText("0");
        }
        else{
            value2=line->text().toDouble();
            if (value2==0 && op=="/") line->setText("错误"),flag=1;
            else{
                value1=cal(op);
                line->setText(numtos(value1));
            }
            value2=0;
            op=s;
        }
    }
    void Equal(){
        value2=line->text().toDouble();
        if (value2==0 && op=="/") line->setText("错误"),flag=1;
        else{
        value=cal(op);
        line->setText(numtos(value));
        value1=value;
        }
        op="None";
    }
    double cal(QString s){
        flag=1;
        if (s=="+") return value1+value2;
        else if (s=="-") return value1-value2;
        else if (s=="*") return value1*value2;
        else if (s=="/") return value1/value2;
        else return value1;
    }
    void read(QString s){
        if (flag) line->setText("0");
        QString text = line->text();
        text+=s;
        line->setText(numtos(text.toDouble()));
        if (text.size()>15) line->setText("数字过大或精度过高"),flag=1;
        flag=0;
    }
        QString numtos(double num){
            return QString::number(num,'g',15);
    }
};
#endif // MAINWINDOW_H
