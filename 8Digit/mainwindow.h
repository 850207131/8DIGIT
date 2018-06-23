#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"global.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_clear_Button_clicked();

    void on_confirm_clicked();

    void on_random_input_clicked();

    void res_show(string res);

    void on_DFS_Button_clicked();

    void on_BFS_Button_clicked();

    void on_H1_Button_clicked();

    void on_H2_Button_clicked();

    void on_H3_Button_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
