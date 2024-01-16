#include "mainwindow.h"

#include <QApplication>

#include <QStandardItemModel>

enum LogType{
    VP = 0,
    VS = 1,
    RHO = 2
};

void addData(QAbstractItemModel *model, const QString& wellname,  LogType type)
{
    model->insertRow(0);
    model->setData(model->index(0,0), wellname);
    model->setData(model->index(0,1), type);
}

QAbstractItemModel* createWellModel(QMainWindow *parent)
{
    QStandardItemModel *model = new QStandardItemModel(0, 2, parent);

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Well"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Type"));

    addData(model, "Alpha-1", LogType::RHO);
    addData(model, "Alpha-1", LogType::VP);
    addData(model, "Alpha-1", LogType::VS);
    addData(model, "Alpha-2", LogType::RHO);
    addData(model, "Alpha-3", LogType::RHO);

    qDebug()<<"created data" ;
    return model;

}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setSourceModel(createWellModel(&w));
    w.show();
    return a.exec();
}
