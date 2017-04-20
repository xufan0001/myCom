#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    // 定义串口对象，指定串口名和查询模式，这里使用事件驱动模式
//    myCom = new Win_QextSerialPort("COM2",QextSerialBase::EventDriven);
    myCom = new Posix_QextSerialPort("/dev/pts/6",QextSerialBase::Polling);

    // 以读写方式打开串口
    myCom->open(QIODevice::ReadWrite);

    // 设置波特率
    myCom->setBaudRate(BAUD9600);

    // 设置数据位
    myCom->setDataBits(DATA_8);

    // 设计奇偶校验位
    myCom->setParity(PAR_NONE);

    // 设置停止位
    myCom->setStopBits(STOP_1);

    // 设置数据流控制
    myCom->setFlowControl(FLOW_OFF);

    // 设置延时，在window的事件驱动模式下好像不起作用
//    myCom->setTimeout(500);
    myCom->setTimeout(10);

    // 信号和槽函数关联，当串口缓冲区有数据时，进行读串口操作
//    connect(myCom,SIGNAL(readyRead()),this,SLOT(readMyCom()));
    readTimer = new QTimer(this);
    // 设置延时
    readTimer->start(100);
    connect(readTimer,SIGNAL(timeout()),this,SLOT(readMyCom()));
}

Widget::~Widget()
{
    delete ui;
}
// 发送数据
void Widget::on_pushButton_clicked()
{
    myCom->write(ui->lineEdit->text().toLatin1());
}

void Widget::readMyCom()
{
    // 输出每次获得的字节数
//    qDebug()<<"read: "<<myCom->bytesAvailable()<<" bytes";

    // 读取串口缓冲区内的所有数据
    QByteArray temp = myCom->readAll();

    // 显示串口数据
    ui->textBrowser->insertPlainText(temp);
}
