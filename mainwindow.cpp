#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->button_refresh->setEnabled(false);
    ui->button_sendNewData->setEnabled(false);
    ui->button_clear->setEnabled(false);
    ui->deleteSensor_button->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_button_getData_clicked()
{
    db = QSqlDatabase::addDatabase("QPSQL");
    db.setDatabaseName("Sensors");
    db.setHostName("localhost");
    db.setUserName("postgres");
    db.setPassword("0000");
    if(db.open())
    {
        qDebug() << "Connected to db!";
    }
    else
    {
        qDebug() << "Cant connected to db!";
    }

    ui->button_refresh->setEnabled(true);
    ui->button_sendNewData->setEnabled(true);
    ui->button_clear->setEnabled(true);
  //  ui->deleteSensor_button->setEnabled(true);

    model = new QSqlTableModel(this);
    model->setTable("sensors");
    model->select();

    ui->tableView->setModel(model);
    ui->comboBox->setModel(model);
    ui->comboBox->setModelColumn(1);

    ui->name_label->setText(ui->comboBox->currentText());

    QSqlQuery query(db);

    query.exec("SELECT sensor_value FROM sensors WHERE sensor_name = '"+ui->comboBox->currentText()+"';");

    if(query.first())
    {
        ui->label_sensor_value->setText(query.value(0).toString());
    }

    connect(ui->comboBox, &QComboBox::currentTextChanged, this, &MainWindow::slotCurrentName);
    connect(ui->tableView, &QTableView::clicked, this, &MainWindow::slotDeleteItem);
}

void MainWindow::slotCurrentName()
{
    ui->name_label->setText(ui->comboBox->currentText());

    QSqlQuery query(db);

    query.exec("SELECT sensor_value FROM sensors WHERE sensor_name = '"+ui->comboBox->currentText()+"';");

    if(query.first())
    {
        ui->label_sensor_value->setText(query.value(0).toString());
    }
}

void MainWindow::on_button_clear_clicked()
{
    model->clear();
    ui->name_label->setText("Название датчика");
    ui->label_sensor_value->clear();
    ui->newSensorName_edit->clear();
    ui->newData_edit->clear();

    ui->button_sendNewData->setEnabled(false);
    ui->button_refresh->setEnabled(false);
}


void MainWindow::on_button_sendNewData_clicked()
{
    int newCurrentID = model->rowCount() + 1;
    QString newSensorName = ui->newSensorName_edit->text();
    QString newSendorData = ui->newData_edit->text();
    QSqlQuery query(db);

    if(!newSensorName.isEmpty() && !newSendorData.isEmpty())
    {
        QString queryString = "INSERT INTO sensors VALUES ("+QString::number(newCurrentID)+",'"+newSensorName+"','"+newSendorData+"');";
        query.exec(queryString);
    }

    ui->newData_edit->clear();
    ui->newSensorName_edit->clear();
}


void MainWindow::on_button_refresh_clicked()
{
    model->select();
}

void MainWindow::slotDeleteItem()
{
    ui->deleteSensor_button->setEnabled(true);
}
