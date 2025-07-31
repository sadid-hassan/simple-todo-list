#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    // QWidget/QMainWindow overrides
    void resizeEvent(QResizeEvent *event) override;
    void showEvent(QShowEvent *event) override;

private slots:
    // Button handler slots
    void handleAddTask();
    void handleRemoveTask();
    void handleDoneTask();

private:
    Ui::MainWindow *ui;

    void applyColumnRatio();
};

#endif // MAINWINDOW_H

