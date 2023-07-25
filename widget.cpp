#include "widget.h"
#include"func.h"
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    initWidget(); // 初始化窗口
}

Widget::~Widget()
{

}

void Widget::initWidget()
{
    this->setWindowTitle(tr("简易计算器"));        //设置程序标题
    this->setGeometry(0,0,800,480);
    /* 显示行 */
    displayLineEdit = new QLineEdit();      //文本输入与显示
//    displayLineEdit->resize(800,100); // 设置大小
    displayLineEdit->setReadOnly(true); // 设置只读
    displayLineEdit->setFont(QFont("黑体",20)); // 改变字体的大小，对话框也会变化
    /* 显示表达式 */
    displayExpressionLineEdit = new QLineEdit();      //文本输入与显示
    displayExpressionLineEdit->setReadOnly(true); // 设置只读
    displayExpressionLineEdit->setFont(QFont("黑体",16)); // 改变字体的大小，对话框也会变化

    /* 按键 */
    btnCalculator[0] = new QPushButton("%");
    btnCalculator[1] = new QPushButton("CE");
    btnCalculator[2] = new QPushButton("C");
    btnCalculator[3] = new QPushButton("<-");
    btnCalculator[4] = new QPushButton("");
    btnCalculator[5] = new QPushButton("");
    btnCalculator[6] = new QPushButton("");
    btnCalculator[7] = new QPushButton("/");
    btnCalculator[8] = new QPushButton("7");
    btnCalculator[9] = new QPushButton("8");
    btnCalculator[10] = new QPushButton("9");
    btnCalculator[11] = new QPushButton("X");
    btnCalculator[12] = new QPushButton("4");
    btnCalculator[13] = new QPushButton("5");
    btnCalculator[14] = new QPushButton("6");
    btnCalculator[15] = new QPushButton("-");
    btnCalculator[16] = new QPushButton("1");
    btnCalculator[17] = new QPushButton("2");
    btnCalculator[18] = new QPushButton("3");
    btnCalculator[19] = new QPushButton("+");
    btnCalculator[20] = new QPushButton("");
    btnCalculator[21] = new QPushButton("0");
    btnCalculator[22] = new QPushButton(".");
    btnCalculator[23] = new QPushButton("=");

    vLayout = new QVBoxLayout(this);       // 创建主布局为垂直布局
    bottomLayout = new QGridLayout();       // 为按键创建格子布局
    /* 总体布局 */
    vLayout->addWidget(displayExpressionLineEdit);      // 添加文本区域到布局
    vLayout->addWidget(displayLineEdit);      // 添加文本区域到布局

    vLayout->addLayout(bottomLayout);
    /* 下面布局 格子布局 6*4 */
    for(int i = 0; i< 6;i++){
        for(int j = 0; j< 4;j++){
            bottomLayout->addWidget(btnCalculator[i * 4 + j],i,j);
        }
    }

    /* 按键点击槽函数 */
    /* 数字按键 0-9 */
    connect(btnCalculator[21],SIGNAL(clicked()),this,SLOT(SltBtnNumber0Clicked()));     //按键连接
    connect(btnCalculator[16],SIGNAL(clicked()),this,SLOT(SltBtnNumber1Clicked()));
    connect(btnCalculator[17],SIGNAL(clicked()),this,SLOT(SltBtnNumber2Clicked()));
    connect(btnCalculator[18],SIGNAL(clicked()),this,SLOT(SltBtnNumber3Clicked()));
    connect(btnCalculator[12],SIGNAL(clicked()),this,SLOT(SltBtnNumber4Clicked()));
    connect(btnCalculator[13],SIGNAL(clicked()),this,SLOT(SltBtnNumber5Clicked()));
    connect(btnCalculator[14],SIGNAL(clicked()),this,SLOT(SltBtnNumber6Clicked()));
    connect(btnCalculator[8],SIGNAL(clicked()),this,SLOT(SltBtnNumber7Clicked()));
    connect(btnCalculator[9],SIGNAL(clicked()),this,SLOT(SltBtnNumber8Clicked()));
    connect(btnCalculator[10],SIGNAL(clicked()),this,SLOT(SltBtnNumber9Clicked()));
    /* 加减乘除 */
    connect(btnCalculator[19],SIGNAL(clicked()),this,SLOT(SltBtnAddClicked())); // 加
    connect(btnCalculator[15],SIGNAL(clicked()),this,SLOT(SltBtnMinusClicked()));// 减
    connect(btnCalculator[11],SIGNAL(clicked()),this,SLOT(SltBtnMultiplyClicked())); // 乘
    connect(btnCalculator[7],SIGNAL(clicked()),this,SLOT(SltBtnDivideClicked())); // 除
    connect(btnCalculator[22],SIGNAL(clicked()),this,SLOT(SltBtnPointClicked())); // 小数点
    connect(btnCalculator[23],SIGNAL(clicked()),this,SLOT(SltBtnEqualClicked())); // 等于
    connect(btnCalculator[3],SIGNAL(clicked()),this,SLOT(SltBtnBackSpaceClicked())); // 退格
    connect(btnCalculator[1],SIGNAL(clicked()),this,SLOT(SltBtnCEClicked())); // CE键 清除最后输入的一个数字
    connect(btnCalculator[2],SIGNAL(clicked()),this,SLOT(SltBtnCClicked())); // C键 清除全部

    /* 重新开始计算槽函数 */
    connect(this,SIGNAL(SignalsrestartCalculator()),this,SLOT(SltsrestartCalculator()));

    SltsrestartCalculator(); // 重新开始计算
}

/**
 * @brief Widget::SltBtnNumber0Clicked
 * 按键0
 */
void Widget::SltBtnNumber0Clicked()
{
    BtnNumberOperator("0");
}

void Widget::SltBtnNumber1Clicked()
{
    BtnNumberOperator("1");
}

void Widget::SltBtnNumber2Clicked()
{
    BtnNumberOperator("2");
}

void Widget::SltBtnNumber3Clicked()
{
    BtnNumberOperator("3");
}

void Widget::SltBtnNumber4Clicked()
{
    BtnNumberOperator("4");
}

void Widget::SltBtnNumber5Clicked()
{
   BtnNumberOperator("5");
}

void Widget::SltBtnNumber6Clicked()
{
    BtnNumberOperator("6");
}

void Widget::SltBtnNumber7Clicked()
{
   BtnNumberOperator("7");
}

void Widget::SltBtnNumber8Clicked()
{
    BtnNumberOperator("8");
}

void Widget::SltBtnNumber9Clicked()
{
   BtnNumberOperator("9");
}
/**
 * @brief Widget::SltBtnAddClicked
 * + 运算符
 */
void Widget::SltBtnAddClicked()
{
    firstPressFlag = false; // 不是第一次按下
    equalFlag = false; // 等号被打断

    /* 判断符号重复 */
    // 截取最后一个字符
    QString operatorSignal = "+-*/.="; // 一些操作运算符
    QString laststr = displayLineEdit->text().right(1);
   // qDebug() << laststr << endl;
    /* 判断最后一个字符是不是不是下面这些符号 */
    bool iscontains = operatorSignal.contains(laststr,Qt::CaseSensitive); // 大小写敏感
    if(!iscontains){ // 包含 啥也不管
        displayLineEdit->setAlignment(Qt::AlignLeft); // 左对齐
        displayLineEdit->setText(displayLineEdit->text()+="+");
    }

}

void Widget::SltBtnMinusClicked()
{
    firstPressFlag = false; // 不是第一次按下
    equalFlag = false; // 等号被打断

    /* 判断符号重复 */
    // 截取最后一个字符
    QString operatorSignal = "+-*/.="; // 一些操作运算符
    QString laststr = displayLineEdit->text().right(1);
   // qDebug() << laststr << endl;
    /* 判断最后一个字符是不是不是下面这些符号 */
    bool iscontains = operatorSignal.contains(laststr,Qt::CaseSensitive); // 大小写敏感
    if(!iscontains){ // 包含 啥也不管
        displayLineEdit->setAlignment(Qt::AlignLeft); // 左对齐
        displayLineEdit->setText(displayLineEdit->text()+="-");
    }
}

void Widget::SltBtnMultiplyClicked()
{
    firstPressFlag = false; // 不是第一次按下
    equalFlag = false; // 等号被打断
    /* 判断符号重复 */
    // 截取最后一个字符
    QString operatorSignal = "+-*/.="; // 一些操作运算符
    QString laststr = displayLineEdit->text().right(1);
   // qDebug() << laststr << endl;
    /* 判断最后一个字符是不是不是下面这些符号 */
    bool iscontains = operatorSignal.contains(laststr,Qt::CaseSensitive); // 大小写敏感
    if(!iscontains){ // 包含 啥也不管
        displayLineEdit->setAlignment(Qt::AlignLeft); // 左对齐
        displayLineEdit->setText(displayLineEdit->text()+="*");
    }
}

void Widget::SltBtnDivideClicked()
{
    firstPressFlag = false; // 不是第一次按下
    equalFlag = false; // 等号被打断
    /* 判断符号重复 */
    // 截取最后一个字符
    QString operatorSignal = "+-*/.="; // 一些操作运算符
    QString laststr = displayLineEdit->text().right(1);
   // qDebug() << laststr << endl;
    /* 判断最后一个字符是不是不是下面这些符号 */
    bool iscontains = operatorSignal.contains(laststr,Qt::CaseSensitive); // 大小写敏感
    if(!iscontains){ // 包含 啥也不管
        displayLineEdit->setAlignment(Qt::AlignLeft); // 左对齐
        displayLineEdit->setText(displayLineEdit->text()+="/");
    }
}

void Widget::SltBtnPointClicked()
{
    firstPressFlag = false; // 不是第一次按下
    equalFlag = false; // 等号被打断

    /* 判断符号重复 */
    // 截取最后一个字符
    QString operatorSignal = "+-*/.="; // 一些操作运算符
    QString laststr = displayLineEdit->text().right(1);
   // qDebug() << laststr << endl;
    /* 判断最后一个字符是不是不是下面这些符号 */
    bool iscontains = operatorSignal.contains(laststr,Qt::CaseSensitive); // 大小写敏感
    if(!iscontains){ // 包含 啥也不管
        displayLineEdit->setAlignment(Qt::AlignLeft); // 左对齐
        displayLineEdit->setText(displayLineEdit->text()+=".");
    }
}

/**
 * @brief Widget::SltBtnEqualClicked
 * = 运算符 获取表达式 计算结果
 */
void Widget::SltBtnEqualClicked()
{
    firstPressFlag = false; // 不是第一次按下
    equalFlag = true; // 等号按下

    /* 剔除最后一个字符不是数字的情况 */
    // 截取最后一个字符
    QString operatorSignal = "+-*/.="; // 一些操作运算符
    QString laststr = displayLineEdit->text().right(1);
    QString str = displayLineEdit->text(); // 获取表达式
   // qDebug() << laststr << endl;
    /* 判断最后一个字符是不是不是下面这些符号 */
    bool iscontains = operatorSignal.contains(laststr,Qt::CaseSensitive); // 大小写敏感
    if(iscontains){ // 包含  剔除最后一个字符
         str = str.left(str.length() -1); // 删除最后一个字符
    }
    // 如果不包含直接计算下面的
    // 计算结果
    displayLineEdit->setAlignment(Qt::AlignRight); // 靠右对齐
    displayExpressionLineEdit->setAlignment(Qt::AlignRight); // 靠右对齐
    displayLineEdit->setText(str += "="); // 表达式加上等号
    QString res = displayLineEdit->text(); // 获取表达式
    string s = res.toStdString(); // Qt 转化为 c++ 使用的字符串
    double ans = postfix2ans(InfixToPostfix(s)); // 计算结果
    displayExpressionLineEdit->setText(displayLineEdit->text()); // 显示表达式
    displayLineEdit->setText(QString::number(ans)); // 显示结果
}

/**
 * @brief Widget::SltBtnBackSpaceClicked
 * 退格键 去掉最后一个字符
 */
void Widget::SltBtnBackSpaceClicked()
{
    QString res = displayLineEdit->text(); // 获取表达式
    /* 删除最后一个字符 */
    res = res.left(res.length() - 1); // 去掉最后一个字符
    displayLineEdit->setText(res); // 显示在文本行中
}
/**
 * @brief Widget::SltBtnCEClicked
 * CE键 删除掉最后输入的数字
 */
void Widget::SltBtnCEClicked()
{
    QString operatorSignal = "+-*/.="; // 一些操作运算符
    QString numberSignal = "0123456789"; // 数字
    QString str = displayLineEdit->text(); // 获取表达式
    int index = 0; // 记录删除数字的个数
    /* 333  333+ 333+333 */

    while(1){
        /* 判断 字符串是否为空 或者是 333这种纯数字 后面也会为空的情况  */
        if(str == ""){
            displayLineEdit->setText("0");
            firstPressFlag = true; // 第一次按下
            break;
        }
         QString laststr = str.right(1); // 截取最后一个字符
         qDebug() << laststr <<endl;
         /* 判断最后一个字符是不是数字 */
         if(numberSignal.contains(laststr,Qt::CaseSensitive)){ // 是数字 操作
            str = str.left(str.length() -1); // 删除最后一个字符
            index ++;
         }else{ // 不是数字 那就是表达式 退出
             displayLineEdit->setText(displayLineEdit->text().left(displayLineEdit->text().length() - index));
             break;
         }
    }

}
/**
 * @brief Widget::SltBtnCClicked
 * C键 清除全部
 */
void Widget::SltBtnCClicked()
{
    SltsrestartCalculator(); // 重新开始计算
}

/**
 * @brief BtnNumberOperator
 * 数字按键操作 相同的操作 封装一个函数
 */
void Widget::BtnNumberOperator(QString num)
{
    if(equalFlag)// 如果上一个是等号 按下数字就是重新开始
        emit SignalsrestartCalculator(); // 发出信号
    if(firstPressFlag){ // 如果是第一次按下 需要先清除数字0 也就是直接显示这个数字 否则加上这个数字
        firstPressFlag = false;
        displayLineEdit->setText(num); // 显示num
    }
    else
        displayLineEdit->setText(displayLineEdit->text()+= num); // 显示的文字加上num
}

/**
 * @brief Widget::SltsrestartCalculator
 * 重新开始计算槽函数
 */
void Widget::SltsrestartCalculator()
{
    firstPressFlag = true; // 第一次按下
    equalFlag = false; // 等号被打断
    displayLineEdit->clear(); // 清空
    displayExpressionLineEdit->clear(); // 清空
    displayLineEdit->setText("0"); // 默认状态显示一个0
    displayLineEdit->setAlignment(Qt::AlignLeft); // 左对齐
}

