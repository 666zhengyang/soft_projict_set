#ifndef SQLITEDIALOG_H
#define SQLITEDIALOG_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QDebug>

namespace Ui {
class SqliteDialog;
}

class SqliteDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SqliteDialog(QWidget *parent = 0);
    ~SqliteDialog();
private:
    //创建数据库文件并建立和QT程序连接
    void createDB(void);
    //创建学生成绩的数据表
    void createTable(void);
    //查询和遍历结果
    void queryTable(void);
private slots:
    void on_insertButton_clicked();
    void on_deleteButton_clicked();
    void on_updateButton_clicked();
    void on_sortButton_clicked();
private:
    Ui::SqliteDialog *ui;
    QSqlDatabase db;
    QSqlQueryModel model;

};

#endif // SQLITEDIALOG_H
