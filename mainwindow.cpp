#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qmessagebox.h>
#include <qfile.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    int j;
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(5);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() <<"Наименование" <<"Год издания" <<"Переодичность" <<"Тираж" <<"Типография");
    ui->tableWidget->setRowCount(1);
    for (j=0; j<ui->tableWidget->columnCount();j++)
        ui->tableWidget->setColumnWidth(j,136);
    for (j=0; j<ui->tableWidget->columnCount();j++)
    {
        QTableWidgetItem *item = new QTableWidgetItem;
        item->setText("");
        ui->tableWidget->setItem(0,j,item);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    bool Ok;
    QString str=ui->lineEdit->text();
    int k=str.toInt(&Ok),i,j;
    if ((k>0) && (k<=ui->tableWidget->rowCount()))
    {
    for (i=k-1; i<ui->tableWidget->rowCount()-1;i++)
        for (j=0; j<ui->tableWidget->columnCount();j++)
            ui->tableWidget->item(i,j)->setText(ui->tableWidget->item(i+1,j)->text());
    i=ui->tableWidget->rowCount()-1;
    for (j=0; j<ui->tableWidget->columnCount();j++)
        delete ui->tableWidget->item(i,j);
    ui->tableWidget->setRowCount(i);
    }
    else
        QMessageBox::information(this,"Error","Введено некорректное значение");
}

void MainWindow::on_pushButton_3_clicked()
{
    int i,j;
    i=ui->tableWidget->rowCount();
    ui->tableWidget->setRowCount(i+1);
    for (j=0; j<ui->tableWidget->columnCount();j++)
    {
        QTableWidgetItem *item = new QTableWidgetItem;
        item->setText("");
        ui->tableWidget->setItem(i,j,item);
    }
}

void MainWindow::on_pushButton_clicked()
{
    QFile file("pechat.txt");
    if (file.open(QIODevice::WriteOnly))
    {
        QDataStream stream(&file);
        int row=ui->tableWidget->rowCount(),column=ui->tableWidget->columnCount(),i,j;
        stream << row << column;
        for (i=0; i<row; i++)
            for (j=0; j<column; j++)
                ui->tableWidget->item(i,j)->write(stream);
        file.close();
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    int i,j,row,column;
    ui->tableWidget->clear();
    for (i=0; i<ui->tableWidget->rowCount();i++)
        for (j=0; j<ui->tableWidget->columnCount();j++)
            delete ui->tableWidget->item(i,j);
    ui->tableWidget->setRowCount(0);
    QFile file("pechat.txt");
    if (file.open(QIODevice::ReadOnly))
    {
        QDataStream stream(&file);
        stream >> row >> column;
        ui->tableWidget->setRowCount(row);
        ui->tableWidget->setColumnCount(column);
        ui->tableWidget->setHorizontalHeaderLabels(QStringList() <<"Наименование" <<"Год издания" <<"Переодичность" <<"Тираж" <<"Типография");
        for (i=0; i<row; i++)
            for (j=0; j<column; j++)
            {
                ui->tableWidget->setItem(i,j,new QTableWidgetItem);
                ui->tableWidget->item(i,j)->read(stream);
            }
        file.close();
    }

}

void MainWindow::on_pushButton_5_clicked()
{
    QString s1,s2,s3=ui->lineEdit_2->text();
    int i,k=0;
    for (i=0;i<ui->tableWidget->rowCount();i++)
    {
        s1=ui->tableWidget->item(i,2)->text();  // переодичность
        s2=ui->tableWidget->item(i,4)->text();  // типография
        if ((s1 == "ежедневно") && (s2 == s3))
        {
            ui->tableWidget->item(i,0)->setBackgroundColor(Qt::blue);
            ui->tableWidget->item(i,0)->setTextColor(Qt::white);
            k++;
        }
    }
    if (k == 0)
        QMessageBox::information(this,"Info","Таких изданий нет");
}

void MainWindow::on_pushButton_6_clicked()
{
    int i,j;
    for (i=0; i<ui->tableWidget->rowCount();i++)
        for (j=0; j<ui->tableWidget->columnCount();j++)
        {
            ui->tableWidget->item(i,0)->setBackgroundColor(Qt::white);
            ui->tableWidget->item(i,0)->setTextColor(Qt::black);
        }
}

void MainWindow::on_pushButton_7_clicked()
{
    bool Ok;
    QString s1,s2,s3=ui->lineEdit_3->text();
    int i,max=0,imax=-1,k;
    for (i=0;i<ui->tableWidget->rowCount();i++)
    {
        s1=ui->tableWidget->item(i,2)->text(); // переодичность
        s2=ui->tableWidget->item(i,3)->text(); // тираж
        k=s2.toInt(&Ok);
        if ((s1 == s3) && (k>max))
        {
            max=k;
            imax=i;
        }
    }
    if (imax>=0)
    {
        ui->tableWidget->item(imax,0)->setBackgroundColor((Qt::blue));
        ui->tableWidget->item(imax,0)->setTextColor(Qt::white);
    }
    else
        QMessageBox::information(this,"Info","Такого издания нет");
}

void MainWindow::on_pushButton_8_clicked()
{
    bool Ok;
    QString s2,s3,s4;
    int i,j,max=0,k;
    for (i=0;i<ui->tableWidget->rowCount();i++)
    {
        s2=ui->tableWidget->item(i,4)->text(); // типография
        k=0;
        for (j=0; j<ui->tableWidget->rowCount(); j++)
        {
            s3=ui->tableWidget->item(j,4)->text(); // типография
            if (s3 == s2)
                k=k+(ui->tableWidget->item(j,3)->text()).toInt(&Ok) ; // тираж
        }
        if (k>max)
        {
            max=k;
            s4=s2;
        }
    }
    for (i=0;i<ui->tableWidget->rowCount();i++)
    {
        s2=ui->tableWidget->item(i,4)->text();
        if (s2 == s4)
        {
            ui->tableWidget->item(i,0)->setBackgroundColor((Qt::blue));
            ui->tableWidget->item(i,0)->setTextColor(Qt::white);
        }
    }
}

void MainWindow::on_pushButton_9_clicked()
{
    bool Ok;
    int i,N=0,k;
    double temp1,temp2;
    QString s1,s2,s3;
    s1=ui->lineEdit_4->text();
    for (i=0; i<ui->tableWidget->rowCount();i++)
        if (ui->tableWidget->item(i,0)->text() == s1)
            N++;
    if ((N != 0) && (N != 1))
    {
    QVector<double> x(N), y(N); //Массивы координат точек
    k=0;
    for (i=0; i<ui->tableWidget->rowCount();i++)
        if (ui->tableWidget->item(i,0)->text() == s1)
        {
            x[k]=(ui->tableWidget->item(i,1)->text()).toDouble(&Ok);
            y[k]=(ui->tableWidget->item(i,3)->text()).toDouble(&Ok);
            k++;
        }
    // сортировка массива х
    Ok=false;
    while (!Ok)
    {
        Ok = true;
        for ( i = 0; i < N-1 ; i++)
        if (x[i] > x[i + 1])
        {
            temp1 = x[i];
            temp2 = y[i];
            x[i] = x[i + 1];
            x[i + 1] = temp1;
            y[i] = y[i + 1];
            y[i + 1] = temp2;
            Ok = false;
        }
    }

    ui->widget->clearGraphs();//Если нужно, то очищаем все графики
    //Добавляем один график в widget
    ui->widget->addGraph();
    //Говорим, что отрисовать нужно график по нашим двум массивам x и y
    ui->widget->graph(0)->setData(x, y);

    //Подписываем оси Ox и Oy
    ui->widget->xAxis->setLabel("Год");
    ui->widget->yAxis->setLabel("Тираж");

    //Установим область, которая будет показываться на графике
    ui->widget->xAxis->setRange(x[0], x[N-1]+0.1);//Для оси Ox

    double minY = y[0], maxY = y[0];
    for (int i=1; i<N; i++)
    {
        if (y[i]<minY) minY = y[i];
        if (y[i]>maxY) maxY = y[i];
    }
    ui->widget->yAxis->setRange(minY, maxY+100);//Для оси Oy

    QVector<double> Ticks;  // вектор с шагом в 30 градусов
    i = x[0];
    while(i<=x[N-1])
    {
        Ticks << i;
        i++;
    }
    ui->widget->xAxis->setAutoTicks(false); // выключаем автоматические отсчеты
    ui->widget->xAxis->setTickVector(Ticks);  // задаем созданный нами вектор

    //И перерисуем график на нашем widget
    ui->widget->replot();
    }
    if (N == 0)
        QMessageBox::information(this,"Info","Такого издания нет");
    if (N == 1)
        QMessageBox::information(this,"Info","Нельзя построить график зависимости");
}
