#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSql>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_button_getData_clicked();

    void slotCurrentName();

    void on_button_clear_clicked();

    void on_button_sendNewData_clicked();

    void on_button_refresh_clicked();

    void slotDeleteItem();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    QSqlTableModel *model;
};
#endif // MAINWINDOW_H
