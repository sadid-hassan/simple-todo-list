/*
* File: mainwindow.cpp
* Project: TodoListGUI
* Author: Sadid Hassan
* Description:
* Entry point for the GUI of the To-Do List application. 
* Manages slots & signals, and other important UI details.
*
* Created: July 2025
* Updated: July 2025
*/


#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QHeaderView>
#include <QResizeEvent>
#include <QStyledItemDelegate>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Task Table Settings
    ui->taskTable->setTextElideMode(Qt::ElideNone);
    ui->taskTable->setWordWrap(true);
    ui->taskTable->setItemDelegate(new QStyledItemDelegate(ui->taskTable));
    ui->taskTable->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);


    // Usage of “Interactive” mode so the manual widths stick
    QHeaderView* h = ui->taskTable->horizontalHeader();
    h->setSectionResizeMode(0, QHeaderView::Interactive);
    h->setSectionResizeMode(1, QHeaderView::Interactive);

    // Initial apply of a 75/25 ratio
    applyColumnRatio();



    // Manual connections to Add, Remove, & Done buttons
    connect(ui->addBtn, &QPushButton::clicked, this, &MainWindow::handleAddTask);
    connect(ui->removeBtn, &QPushButton::clicked, this, &MainWindow::handleRemoveTask);
    connect(ui->doneBtn, &QPushButton::clicked, this, &MainWindow::handleDoneTask);


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::handleAddTask()
{
    // Ask the user for a task description
    bool ok;
    QString task = QInputDialog::getText(
        this,
        "Add Task",
        "Enter task:",
        QLineEdit::Normal,
        "",
        &ok
        );

    if (ok && !task.isEmpty()) {
        int row = ui->taskTable->rowCount();
        ui->taskTable->insertRow(row);
        ui->taskTable->setItem(row, 0, new QTableWidgetItem(task));
        ui->taskTable->setItem(row, 1, new QTableWidgetItem("Pending"));
    } else if (ok && task.isEmpty()) {
        QMessageBox::warning(this, "Invalid Input", "Task cannot be empty!");
    }
}

void MainWindow::handleRemoveTask()
{
    // qDebug() << "Remove button clicked!";

    int row = ui->taskTable->currentRow();
    if (row >= 0) {
        QString task = ui->taskTable->item(row, 0)->text();

        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(
            this,
            "Remove Task",
            "Are you sure you want to remove: \"" + task + "\"?",
            QMessageBox::Yes | QMessageBox::No
            );

        if (reply == QMessageBox::Yes) {
            ui->taskTable->removeRow(row);
        }
    } else {
        QMessageBox::information(this, "No Selection", "Please select a task to remove.");
    }
}


void MainWindow::handleDoneTask()
{
    int row = ui->taskTable->currentRow();
    if (row >= 0) {
        ui->taskTable->item(row, 1)->setText("Done");
    } else {
        QMessageBox::information(this, "No Selection", "Please select a task to mark as done.");
    }
}

void MainWindow::applyColumnRatio()
{
    int w = ui->taskTable->viewport()->width();
    // 75% for Task, 25% for Status
    ui->taskTable->setColumnWidth(0, int(w * 0.75));
    ui->taskTable->setColumnWidth(1, int(w * 0.25));
}


void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    applyColumnRatio();
}

void MainWindow::showEvent(QShowEvent *event)
{
    QMainWindow::showEvent(event);
    applyColumnRatio();
}



