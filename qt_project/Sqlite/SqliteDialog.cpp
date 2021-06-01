#include "SqliteDialog.h"
#include "ui_SqliteDialog.h"

SqliteDialog::SqliteDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SqliteDialog)
{
    ui->setupUi(this);
    createDB();
    createTable();
    queryTable();
}

SqliteDialog::~SqliteDialog()
{
    delete ui;
}
//创建数据库文件并建立和QT程序连接
void SqliteDialog::createDB(void)
{
    //添加sqlite数据库驱动
    db = QSqlDatabase::addDatabase("QSQLITE");
    //设置数据库文件名,如果文件不存在会自动创建
    db.setDatabaseName("menu.db");
    //打开数据库
    if(db.open() == false){
        qDebug() << db.lastError().text();
    }
}
//创建学生成绩的数据表
void SqliteDialog::createTable(void)
{
    QString str = QString("CREATE TABLE student("
                          "id INT PRIMARY KEY,"
                          "name TEXT NOT NULL,"
                          "score REAL NOT NULL)");
    //qDebug() << str;
    QSqlQuery query;
    query.exec(str);
}
//查询和遍历结果
/*sqlite> INSERT INTO student
   ...> VALUES(10011,"Jerry",90.5);
sqlite> INSERT INTO student
   ...> VALUES(10010,"TOM",89.5);*/
void SqliteDialog::queryTable(void)
{
    QString str=QString("SELECT * FROM student");
    //执行查询语句，保存结果集到model
    model.setQuery(str);
    //将结果集显示到界面
    ui->tableView->setModel(&model);
}

//插入按钮的槽函数
void SqliteDialog::on_insertButton_clicked()
{
    //获取用户输入id\name\score
    int id = ui->idEdit->text().toInt();
    QString name = ui->nameEdit->text();
    double score = ui->scoreEdit->text().toDouble();
    //创建插入操作的sql语句
    QString str = QString(
        "INSERT INTO student VALUES(%1,'%2',%3)"
                ).arg(id).arg(name).arg(score);
    //执行插入操作
    QSqlQuery query;
    query.exec(str);
    //再次查询和显示
    queryTable();
}
//删除按钮的槽函数,根据ID删除一条数据
void SqliteDialog::on_deleteButton_clicked()
{

}
//修改按钮的槽函数，根据ID修改成绩
void SqliteDialog::on_updateButton_clicked()
{

}
//排序查询按钮的槽函数
void SqliteDialog::on_sortButton_clicked()
{
    //获取排序的列名id/score
    QString value = ui->valueComBox->currentText();
    //获取排序方式：升序/降序
    QString condition;
    if(ui->condComBox->currentIndex()){
        condition = "DESC";
    }else{
        condition = "ASC";
    }
    QString str = QString(
        "SELECT * FROM student ORDER BY %1 %2"
                ).arg(value).arg(condition);
    model.setQuery(str);
    ui->tableView->setModel(&model);
}








