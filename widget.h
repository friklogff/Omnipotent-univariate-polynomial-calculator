#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>
#include <QVBoxLayout>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

/* 属性 */
private:
      QPushButton *btnCalculator[24]; // 定义24个按键
      QLineEdit *displayLineEdit; // 显示文本行
      QLineEdit *displayExpressionLineEdit; // 显示表达式
      QVBoxLayout *vLayout; // 垂直布局
      QGridLayout *bottomLayout; // 格子布局

      bool equalFlag; //
      bool firstPressFlag; // 第一次按下标志位
/* 函数 */
private:
      void initWidget(); // 初始化窗口
      void BtnNumberOperator(QString num);// 数字按键操作
/* 信号 */
signals:
      void SignalsrestartCalculator(); // 重新开始计算信号
/* 槽函数 */
private slots:
      /* 按键点击槽函数 */
      void SltBtnNumber0Clicked(); // 按键点击槽函数
      void SltBtnNumber1Clicked(); // 按键点击槽函数
      void SltBtnNumber2Clicked(); // 按键点击槽函数
      void SltBtnNumber3Clicked(); // 按键点击槽函数
      void SltBtnNumber4Clicked(); // 按键点击槽函数
      void SltBtnNumber5Clicked(); // 按键点击槽函数
      void SltBtnNumber6Clicked(); // 按键点击槽函数
      void SltBtnNumber7Clicked(); // 按键点击槽函数
      void SltBtnNumber8Clicked(); // 按键点击槽函数
      void SltBtnNumber9Clicked(); // 按键点击槽函数
      void SltBtnAddClicked(); // 加
      void SltBtnMinusClicked(); // 减
      void SltBtnMultiplyClicked(); //乘
      void SltBtnDivideClicked(); // 除
      void SltBtnPointClicked(); // 小数点
      void SltBtnEqualClicked(); // 等于
      void SltBtnBackSpaceClicked(); // 退格
      void SltBtnCEClicked(); // CE
      void SltBtnCClicked(); // C
      void SltsrestartCalculator(); // 重新开始计算槽函数
};

#endif // WIDGET_H

