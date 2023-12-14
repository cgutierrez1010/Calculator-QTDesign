#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    displayLabel = ui->label;
    displayLabel->setAlignment(Qt::AlignRight);
    displayLabel->setStyleSheet("font-size: 18px;");
    displayLabel->setGeometry(10, 10, 280, 40);

    connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(digitClicked()));
    connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(digitClicked()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(digitClicked()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(digitClicked()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(digitClicked()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(digitClicked()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(digitClicked()));
    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(digitClicked()));
    connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(digitClicked()));
    connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(digitClicked()));

    connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(operatorClicked()));
    connect(ui->pushButton_minus, SIGNAL(clicked()), this, SLOT(operatorClicked()));
    connect(ui->pushButton_multiply, SIGNAL(clicked()), this, SLOT(operatorClicked()));
    connect(ui->pushButton_divide, SIGNAL(clicked()), this, SLOT(operatorClicked()));

    connect(ui->pushButton_equal, SIGNAL(clicked()), this, SLOT(equalClicked()));
    connect(ui->pushButton_clear, SIGNAL(clicked()), this, SLOT(clearClicked()));

    result = 0.0;
    currentOperator.clear();
    currentInput.clear();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::digitClicked() {
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    currentInput.append(button->text());
    updateDisplay();
    qDebug() << "Digit Clicked:" << currentInput;
}

void MainWindow::operatorClicked() {
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    currentOperator = button->text();
    result = currentInput.toDouble();
    currentInput.clear();
    updateDisplay();
    qDebug() << "Operator Clicked:" << currentOperator;
}

void MainWindow::equalClicked() {
    if (!currentOperator.isEmpty()) {
        double operand = currentInput.toDouble();
        if (currentOperator == "+") {
            result += operand;
        } else if (currentOperator == "-") {
            result -= operand;
        } else if (currentOperator == "*") {
            result *= operand;
        } else if (currentOperator == "/") {
            if (operand != 0.0) {
                result /= operand;
            } else {
                displayLabel->setText("Error");
                return;
            }
        }

        currentInput = QString::number(result);
        currentOperator.clear();
        updateDisplay();
        qDebug() << "Equal Clicked:" << result;
    }
}


void MainWindow::clearClicked() {
    currentInput.clear();
    currentOperator.clear();
    result = 0.0;
    updateDisplay();
    qDebug() << "Clear Clicked";
}

void MainWindow::updateDisplay() {
    QString displayText;

    if (!currentOperator.isEmpty()) {
        displayText = QString::number(result) + " " + currentOperator + " " + currentInput;
    } else {
        displayText = currentInput.isEmpty() ? QString::number(result) : currentInput;
    }

    displayLabel->setText(displayText);
    qDebug() << "Display Updated:" << displayText;
}
