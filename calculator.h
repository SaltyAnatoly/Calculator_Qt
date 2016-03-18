#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QButtonGroup>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QSpacerItem>
#include <QMessageBox>
#include <QDebug>
#include <QtMath>

enum Operation {Plus = 0, Minus, Divide, Multiply, Equal};
enum Manipulation {PlusMinus = 0, SetPoint};
enum MemoryOperation {MPlus = 0, MMinus, MStore, MRecall, MClear};
enum DeletingType {Global = 0, Entry, LastSymbol};
enum SpecialOperation {Sqrt = 0, Percent, Inverse};

namespace Ui {
class Calculator;
}

class Calculator : public QWidget
{
    Q_OBJECT

public:
    explicit Calculator(QWidget *parent = 0);
    ~Calculator();

private:
    Ui::Calculator *ui;

    double currentOperand;
    double secondOperand;
    double memoryOperand;
    bool isFirstOperation;
    Operation currentOperation;


    QButtonGroup *operationsGroup;
    QButtonGroup *numbersGroup;
    QButtonGroup *memoryGroup;
    QButtonGroup *specialOperationsGroup;
    QButtonGroup *deletingGroup;
    QButtonGroup *manipulatorsGroup;

    QGroupBox *buttonsGroupBox;
    QGroupBox *inputGroupBox;

    QPushButton *zero;
    QPushButton *one;
    QPushButton *two;
    QPushButton *three;
    QPushButton *four;
    QPushButton *five;
    QPushButton *six;
    QPushButton *seven;
    QPushButton *eight;
    QPushButton *nine;

    QPushButton *plus;
    QPushButton *minus;
    QPushButton *divide;
    QPushButton *multiply;
    QPushButton *equal;

    QPushButton *plusMinus;
    QPushButton *point;

    QPushButton *memPlus;
    QPushButton *memMinus;
    QPushButton *memStore;
    QPushButton *memRecall;
    QPushButton *memClear;

    QPushButton *sqrrt;
    QPushButton *percent;
    QPushButton *inverse;

    QPushButton *clear;
    QPushButton *clearEntry;
    QPushButton *backspace;

    QLabel *lastAction;
    QLabel *memoryLine;
    QLabel *errorLine;
    QLineEdit *calculationLine;

    double getValueFromCalculationLine();
    bool isCalculationLineEmpty();
    void calculate();

private slots:
    void numberClicked(const int id);
    void operationClicked(const int id);
    void memoryButtonClicked(const int id);
    void deletingButtonClicked(const int id);
    void manipulationButtonClicked(const int id);
    void specialOperationButtonClicked(const int id);
};

#endif // CALCULATOR_H
