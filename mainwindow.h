#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE


class QAbstractItemModel;
class QSortFilterProxyModel;
class QTreeView;
class QLineEdit;
class QComboBox;
class QLabel;
class QGroupBox;
class QTableView;
class QColumnView;


QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setSourceModel(QAbstractItemModel* model);

private slots:
    void filterRegularExpressionChanged();
    void filterColumnChanged();

private:

    QSortFilterProxyModel* proxyModel;
    QTreeView* sourceView;
    QTreeView* proxyView;
    QTableView* proxyTableView;
    QColumnView* proxyColumnView;

    QLineEdit* filterPatternLineEdit;
    QComboBox* filterColumnComboBox;
    QLabel* filterPatternLabel;
    QLabel* filterColumnLabel;

    QGroupBox* sourceGroupBox;
    QGroupBox* proxyGroupBox;

};
#endif // MAINWINDOW_H
