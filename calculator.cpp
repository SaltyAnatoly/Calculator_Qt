#include "calculator.h"
#include "ui_calculator.h"

Calculator::Calculator(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Calculator)
{
    ui->setupUi(this);

    lastAction = new QLabel(this);
    memoryLine = new QLabel(this);
    errorLine = new QLabel(this);
    calculationLine = new QLineEdit(this);

    calculationLine->setAlignment(Qt::AlignRight);
    errorLine->setAlignment(Qt::AlignCenter);
    errorLine->setStyleSheet("QLabel{color : red;}");
    errorLine->hide();
    lastAction->setAlignment(Qt::AlignRight);
    memoryLine->setAlignment(Qt::AlignRight);
    memoryLine->setText("Value in memory: " + QString::number(0));

    operationsGroup = new QButtonGroup(this);
    numbersGroup = new QButtonGroup(this);
    memoryGroup = new QButtonGroup(this);
    specialOperationsGroup = new QButtonGroup(this);
    deletingGroup = new QButtonGroup(this);
    manipulatorsGroup = new QButtonGroup(this);

    buttonsGroupBox = new QGroupBox(this);
    inputGroupBox = new QGroupBox(this);

    zero = new QPushButton("0", this);
    one = new QPushButton("1", this);
    two = new QPushButton("2", this);
    three = new QPushButton("3", this);
    four = new QPushButton("4", this);
    five = new QPushButton("5", this);
    six = new QPushButton("6", this);
    seven = new QPushButton("7", this);
    eight = new QPushButton("8", this);
    nine = new QPushButton("9", this);

    plus = new QPushButton("+", this);
    minus = new QPushButton("-", this);
    divide = new QPushButton("/", this);
    multiply = new QPushButton("*", this);
    equal = new QPushButton("=", this);

    plusMinus = new QPushButton("+-", this);
    point = new QPushButton(".", this);

    memPlus = new QPushButton("M+", this);
    memMinus = new QPushButton("M-", this);
    memStore = new QPushButton("MS", this);
    memRecall = new QPushButton("MR", this);
    memClear = new QPushButton("MC", this);

    sqrrt = new QPushButton("√x", this);
    //sqr = new QPushButton("x^2", this);
    percent = new QPushButton("%", this);
    inverse = new QPushButton("1/x", this);

    clear = new QPushButton("C", this);
    clearEntry = new QPushButton("CE", this);
    backspace = new QPushButton("<-", this);

    one->setFixedSize(48, 48);
    two->setFixedSize(48, 48);
    three->setFixedSize(48, 48);
    four->setFixedSize(48, 48);
    five->setFixedSize(48, 48);
    six->setFixedSize(48, 48);
    seven->setFixedSize(48, 48);
    eight->setFixedSize(48, 48);
    nine->setFixedSize(48, 48);
    zero->setFixedSize(101, 48);

    plus->setFixedSize(48, 48);
    minus->setFixedSize(48, 48);
    divide->setFixedSize(48, 48);
    multiply->setFixedSize(48, 48);
    equal->setFixedSize(48, 98);

    plusMinus->setFixedSize(48, 48);
    point->setFixedSize(48, 48);

    memPlus->setFixedSize(48, 48);
    memMinus->setFixedSize(48, 48);
    memStore->setFixedSize(48, 48);
    memRecall->setFixedSize(48, 48);
    memClear->setFixedSize(48, 48);

    sqrrt->setFixedSize(48, 48);
    percent->setFixedSize(48, 48);
    inverse->setFixedSize(48, 48);

    clear->setFixedSize(48, 48);
    clearEntry->setFixedSize(48, 48);
    backspace->setFixedSize(48, 48);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QVBoxLayout *inputLayout = new QVBoxLayout(this);
    QGridLayout *buttonsLayout = new QGridLayout(this);

    inputGroupBox->setLayout(inputLayout);
    buttonsGroupBox->setLayout(buttonsLayout);

    inputLayout->addWidget(memoryLine);
    inputLayout->addWidget(lastAction);
    inputLayout->addWidget(calculationLine);
    inputLayout->addWidget(errorLine);

    buttonsLayout->addWidget(plus, 5, 3);
    buttonsLayout->addWidget(minus, 4, 3);
    buttonsLayout->addWidget(divide, 2, 3);
    buttonsLayout->addWidget(multiply, 3, 3);
    buttonsLayout->addWidget(equal, 4, 4, 2, 1);

    buttonsLayout->addWidget(one, 4, 0);
    buttonsLayout->addWidget(two, 4, 1);
    buttonsLayout->addWidget(three, 4, 2);
    buttonsLayout->addWidget(four, 3, 0);
    buttonsLayout->addWidget(five, 3, 1);
    buttonsLayout->addWidget(six, 3, 2);
    buttonsLayout->addWidget(seven, 2, 0);
    buttonsLayout->addWidget(eight, 2, 1);
    buttonsLayout->addWidget(nine, 2, 2);
    buttonsLayout->addWidget(zero, 5, 0, 1, 2);

    buttonsLayout->addWidget(memClear, 0, 0);
    buttonsLayout->addWidget(memRecall, 0, 1);
    buttonsLayout->addWidget(memStore, 0, 2);
    buttonsLayout->addWidget(memPlus, 0, 3);
    buttonsLayout->addWidget(memMinus, 0, 4);

    buttonsLayout->addWidget(backspace, 1, 0);
    buttonsLayout->addWidget(clearEntry, 1, 1);
    buttonsLayout->addWidget(clear, 1, 2);

    buttonsLayout->addWidget(sqrrt, 1, 4);
    buttonsLayout->addWidget(percent, 2, 4);
    buttonsLayout->addWidget(inverse, 3, 4);

    buttonsLayout->addWidget(plusMinus, 1, 3);
    buttonsLayout->addWidget(point, 5, 2);

    mainLayout->addWidget(inputGroupBox);
    mainLayout->addWidget(buttonsGroupBox);

    this->setLayout(mainLayout);
    this->setFixedSize(300, 420);

    QRegExp regexp("-?[0-9]{1,6}[.]?[0-9]{0,6}");
    calculationLine->setValidator(new QRegExpValidator(regexp, this));

    currentOperand = 0;
    secondOperand = 0;
    memoryOperand = 0;
    currentOperation = Plus;
    isFirstOperation = true;

    operationsGroup->addButton(plus, Plus);
    operationsGroup->addButton(minus, Minus);
    operationsGroup->addButton(multiply, Multiply);
    operationsGroup->addButton(divide, Divide);
    operationsGroup->addButton(equal, Equal);

    numbersGroup->addButton(zero, 0);
    numbersGroup->addButton(one, 1);
    numbersGroup->addButton(two, 2);
    numbersGroup->addButton(three, 3);
    numbersGroup->addButton(four, 4);
    numbersGroup->addButton(five, 5);
    numbersGroup->addButton(six, 6);
    numbersGroup->addButton(seven, 7);
    numbersGroup->addButton(eight, 8);
    numbersGroup->addButton(nine, 9);

    memoryGroup->addButton(memPlus, MPlus);
    memoryGroup->addButton(memMinus, MMinus);
    memoryGroup->addButton(memStore, MStore);
    memoryGroup->addButton(memRecall, MRecall);
    memoryGroup->addButton(memClear, MClear);

    specialOperationsGroup->addButton(sqrrt, Sqrt);
    specialOperationsGroup->addButton(percent, Percent);
    specialOperationsGroup->addButton(inverse, Inverse);

    deletingGroup->addButton(clear, Global);
    deletingGroup->addButton(clearEntry, Entry);
    deletingGroup->addButton(backspace, LastSymbol);

    manipulatorsGroup->addButton(plusMinus, PlusMinus);
    manipulatorsGroup->addButton(point, SetPoint);

    //connect(equal, SIGNAL(clicked(bool)), this, SLOT(debugMessageBox()));
    connect(numbersGroup, SIGNAL(buttonClicked(int)), this, SLOT(numberClicked(int)));
    connect(operationsGroup, SIGNAL(buttonClicked(int)), this, SLOT(operationClicked(int)));
    connect(memoryGroup, SIGNAL(buttonClicked(int)), this, SLOT(memoryButtonClicked(int)));
    connect(specialOperationsGroup, SIGNAL(buttonClicked(int)), this, SLOT(specialOperationButtonClicked(int)));
    connect(deletingGroup, SIGNAL(buttonClicked(int)), this, SLOT(deletingButtonClicked(int)));
    connect(manipulatorsGroup, SIGNAL(buttonClicked(int)), this, SLOT(manipulationButtonClicked(int)));
}

Calculator::~Calculator()
{
    delete ui;
}

double Calculator::getValueFromCalculationLine()
{
    QString tempStr = calculationLine->text();
    return tempStr.toDouble();
}

bool Calculator::isCalculationLineEmpty()
{
    QString tempStr = calculationLine->text();
    if (tempStr.isEmpty() || tempStr == "-")
        return true;
    else
        return false;
}

void Calculator::calculate()
{
    switch (currentOperation) {
    case Plus:
        if (!isCalculationLineEmpty())
            currentOperand = getValueFromCalculationLine();
        secondOperand += currentOperand;
        lastAction->setText(QString::number(secondOperand, 'g', 12) + " +");
        break;
    case Minus:
        if (!isCalculationLineEmpty())
            currentOperand = getValueFromCalculationLine();
        secondOperand -= currentOperand;
        lastAction->setText(QString::number(secondOperand, 'g', 12) + " -");
        break;
    case Divide:
        if (!isCalculationLineEmpty())
            currentOperand = getValueFromCalculationLine();
        if (currentOperand == 0)
        {
            errorLine->show();
            errorLine->setText("Error! Illegal operation!");
        }
        else
        {
            secondOperand /= currentOperand;
            lastAction->setText(QString::number(secondOperand, 'g', 12) + " /");
        }
        break;
    case Multiply:
        if (!isCalculationLineEmpty())
            currentOperand = getValueFromCalculationLine();
        secondOperand *= currentOperand;
        lastAction->setText(QString::number(secondOperand, 'g', 12) + " *");
        break;
    }
    calculationLine->setText(QString::number(currentOperand, 'g', 12));
}

void Calculator::debugMessageBox()
{
    QString tempStr;
    tempStr = QString::number(getValueFromCalculationLine(), 'g', 12);
    QMessageBox::information(this, "Info", tempStr);
}

void Calculator::numberClicked(const int id)
{
    errorLine->hide();
    calculationLine->insert(QString::number(id));
}

void Calculator::operationClicked(const int id)
{
    errorLine->hide();
    switch (id)
    {
    case Plus:
        if (isFirstOperation)
        {
            calculate();
            secondOperand = currentOperand;
            isFirstOperation = false;
        } else
        {
            if (currentOperation == Plus)
                calculate();
        }
        currentOperation = Plus;
        lastAction->setText(QString::number(secondOperand, 'g', 12) + " +");
        break;
    case Minus:
        if (isFirstOperation)
        {
            calculate();
            secondOperand = currentOperand;
            isFirstOperation = false;
        } else
        {
            if (currentOperation == Minus)
                calculate();
        }
        currentOperation = Minus;
        lastAction->setText(QString::number(secondOperand, 'g', 12) + " -");
        break;
    case Divide:
        if (isFirstOperation)
        {
            calculate();
            secondOperand = currentOperand;
            isFirstOperation = false;
        } else
        {
            if (currentOperation == Divide)
                    calculate();
        }
        currentOperation = Divide;
        lastAction->setText(QString::number(secondOperand, 'g', 12) + " /");
        break;
    case Multiply:
        if (isFirstOperation)
        {
            calculate();
            secondOperand = currentOperand;
            isFirstOperation = false;
        } else
        {
            if (currentOperation == Multiply)
                calculate();
        }
        currentOperation = Multiply;
        lastAction->setText(QString::number(secondOperand, 'g', 12) + " *");
        break;
    case Equal:
        calculate();
        calculationLine->setText(QString::number(secondOperand, 'g', 12));
        break;
    }
    calculationLine->selectAll();
}

void Calculator::memoryButtonClicked(const int id)
{
    errorLine->hide();
    switch (id)
    {
        case MPlus:
            memoryOperand += getValueFromCalculationLine();
            memoryLine->setText("Value in memory: " + QString::number(memoryOperand));
            break;
        case MMinus:
            memoryOperand -= getValueFromCalculationLine();
            memoryLine->setText("Value in memory: " + QString::number(memoryOperand));
            break;
        case MStore:
            memoryOperand = getValueFromCalculationLine();
            memoryLine->setText("Value in memory: " + QString::number(memoryOperand));
            break;
        case MRecall:
            calculationLine->setText(QString::number(memoryOperand));
            memoryLine->setText("Value in memory: " + QString::number(memoryOperand));
            break;
        case MClear:
            memoryOperand = 0;
            memoryLine->setText("Value in memory: " + QString::number(memoryOperand));
            break;
    }
}

void Calculator::deletingButtonClicked(const int id)
{
    errorLine->hide();
    switch (id)
    {
    case Global:
        calculationLine->clear();
        lastAction->clear();
        currentOperand = 0;
        secondOperand = 0;
        memoryOperand = 0;
        currentOperation = Plus;
        isFirstOperation = true;
        break;
    case Entry:
        calculationLine->clear();
        break;
    case LastSymbol:
        QString tempStr = calculationLine->text();
        tempStr.remove(tempStr.length() - 1, 1);
        calculationLine->setText(tempStr);
        break;
    }
}

void Calculator::manipulationButtonClicked(const int id)
{
    errorLine->hide();
    switch (id)
    {
        case PlusMinus:
        {
            double tempVar = getValueFromCalculationLine();
            tempVar *= -1;
            calculationLine->setText(QString::number(tempVar, 'g', 12));
        } break;
        case SetPoint:
        {
            if (!calculationLine->text().contains('.'))
            {
                QString tempStr = QString::number(getValueFromCalculationLine(), 'g', 12);
                calculationLine->setText(tempStr + '.');
            }
        } break;
    }
}

void Calculator::specialOperationButtonClicked(const int id)
{
    errorLine->hide();
    switch (id)
    {
        case Sqrt:
            if (!isCalculationLineEmpty())
                currentOperand = getValueFromCalculationLine();
            if (currentOperand < 0)
            {
                errorLine->show();
                errorLine->setText("Error! Illegal operation!");
            } else
            {
                calculationLine->setText(QString::number(sqrt(currentOperand), 'g', 12));
            }
            break;
        case Inverse:
            if (!isCalculationLineEmpty())
                currentOperand = getValueFromCalculationLine();
            if (currentOperand == 0)
            {
                errorLine->show();
                errorLine->setText("Error! Illegal operation!");
            } else
            {
                calculationLine->setText(QString::number(1 / currentOperand, 'g', 12));
            }
            break;
        case Percent:
            if (!isCalculationLineEmpty())
                currentOperand = getValueFromCalculationLine();
            calculationLine->setText(QString::number(secondOperand * currentOperand / 100, 'g', 12));
            break;
    }
    calculationLine->selectAll();
}
