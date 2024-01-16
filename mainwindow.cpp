#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    // This is the model that willn translate to the UI.
    proxyModel = new QSortFilterProxyModel;
    sourceView = new QTreeView;
    proxyTableView = new QTableView;
    proxyColumnView = new QColumnView;

    sourceView->setRootIsDecorated(false);

    // Add a visual representation of the proxy model
    proxyView = new QTreeView;
    proxyView->setRootIsDecorated(false);
    proxyView->setModel(proxyModel);
    proxyColumnView->setModel(proxyModel);
    proxyTableView->setModel(proxyModel);

    proxyView->setSortingEnabled(true);

    filterPatternLineEdit = new QLineEdit;
    filterPatternLineEdit->setClearButtonEnabled(true);
    filterPatternLabel = new QLabel(tr("&Filter pattern:"));
    filterPatternLabel->setBuddy(filterPatternLineEdit);

    // Add a filter column combobox
    filterColumnComboBox = new QComboBox;
    filterColumnComboBox->addItem(tr("Well"));
    filterColumnComboBox->addItem(tr("LogType"));
    filterColumnLabel = new QLabel(tr("Filter &column:"));

    // Create a Boxed environment for source and proxy views.
    sourceGroupBox = new QGroupBox(tr("Original Model"));
    proxyGroupBox = new QGroupBox(tr("Sorted/Filtered Model"));

    // Create a layout for the source model
    QHBoxLayout *sourceLayout = new QHBoxLayout;
    sourceLayout->addWidget(sourceView);
    sourceGroupBox->setLayout(sourceLayout);

    // Create a layout for the proxy
    QGridLayout *proxyLayout = new QGridLayout;
    proxyLayout->addWidget(proxyView, 0, 0, 1, 2);
    proxyLayout->addWidget(proxyTableView, 0, 2, 1, 2);  // Add the QTableView
    proxyLayout->addWidget(proxyColumnView, 0, 4, 1, 2);  // Add the QColumnView
    proxyLayout->addWidget(filterPatternLabel, 1, 0);
    proxyLayout->addWidget(filterPatternLineEdit, 1, 1, 1, 2);
    proxyLayout->addWidget(filterColumnLabel, 3, 0);
    proxyLayout->addWidget(filterColumnComboBox, 3, 1, 1, 2);
    proxyGroupBox->setLayout(proxyLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(sourceGroupBox);
    mainLayout->addWidget(proxyGroupBox);

    QWidget* centralWidget= new QWidget;
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);
    setWindowTitle(tr("Basic Sort/Filter Model"));
    proxyView->sortByColumn(1, Qt::AscendingOrder);
    // ui->setupUi(this);
    connect(filterPatternLineEdit, &QLineEdit::textChanged, this, &MainWindow::filterRegularExpressionChanged);
    connect(filterColumnComboBox, &QComboBox::currentIndexChanged, this, &MainWindow::filterColumnChanged);


    resize(1600, 1200);

}

MainWindow::~MainWindow()
{
}

void MainWindow::setSourceModel(QAbstractItemModel *model)
{
    proxyModel->setSourceModel(model);
    proxyModel->setSortRole(Qt::DisplayRole);  // Set the sort role to Qt::DisplayRole

    sourceView->setModel(model);
}

void MainWindow::filterRegularExpressionChanged()
{

    QString pattern = filterPatternLineEdit->text();
    QRegularExpression::PatternOptions options = QRegularExpression::NoPatternOption;
    QRegularExpression regularExpression(pattern, options);

    if (regularExpression.isValid()) {
        filterPatternLineEdit->setToolTip(QString());
        proxyModel->setFilterRegularExpression(regularExpression);
    } else {
        filterPatternLineEdit->setToolTip(regularExpression.errorString());
        proxyModel->setFilterRegularExpression(QRegularExpression());
    }
}

void MainWindow::filterColumnChanged()
{
    proxyModel->setFilterKeyColumn(filterColumnComboBox->currentIndex());

}
