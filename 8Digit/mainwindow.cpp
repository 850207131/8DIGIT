#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QTime>
#include<QTimer>
#include<math.h>
#include<QMessageBox>
#include<stdlib.h>


string init_state,dfs_res,bfs_res,AStar1_res,AStar2_res,AStar3_res;
char dir[]={'U','D','L','R'};
int dir_x[]={0,0,-1,1};
int dir_y[]={-1,1,0,0};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_clear_Button_clicked()
{
    ui->init_Table->clearContents();
}


void MainWindow::on_confirm_clicked()
{
    QString init="";
    for(int row=0;row<3;row++)
        for(int col=0;col<3;col++)
            init=init+ui->init_Table->item(row,col)->text();
    init_state=init.toStdString();
    int c_n[5],e_n[5];
    dfs_res=DFS(init_state,c_n[0],e_n[0]);
    bfs_res=BFS(init_state,c_n[1],e_n[1]);
    AStar1_res=AStar1(init_state,c_n[2],e_n[2]);
    AStar2_res=AStar2(init_state,c_n[3],e_n[3]);
    AStar3_res=AStar3(init_state,c_n[4],e_n[4]);
    //在控制台中输出解答路径
    //cout<<"dfs:"<<dfs_res<<endl;
    //cout<<"bfs:"<<bfs_res<<endl;
    //cout<<"H1:"<<AStar1_res<<endl;
    //cout<<"H2:"<<AStar2_res<<endl;
    //cout<<"H3:"<<AStar3_res<<endl;
    for(int i=0;i<5;i++)
    {
        ui->compare_Table->setItem(1,i,new QTableWidgetItem(QString::number(c_n[i])));
        ui->compare_Table->setItem(0,i,new QTableWidgetItem(QString::number(e_n[i])));
    }
}

//生成随机输入
void MainWindow::on_random_input_clicked()
{
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    bool num[9]={0};
    for(int i=0;i<9;i++)
    {
        int ran;
        do{
            ran=qrand()%9;
        }while(num[ran]==1);
        ui->init_Table->setItem(floor(i/3),i%3,new QTableWidgetItem(QString::number(ran,10)));
        num[ran]=1;
    }
}

//打印解答过程
void MainWindow::res_show(string res)
{
    string state=init_state;
    for(int i=0;i<9;i++)
        ui->res_Table->setItem(floor(i/3),i%3,new QTableWidgetItem(QString(state[i])));
    //实现延时
    QEventLoop eventloop;
    QTimer::singleShot(500, &eventloop, SLOT(quit()));
    eventloop.exec();

    for(int pos=0;pos<(int)res.length();pos++){
        int move;
        for(move=0;move<4;move++)
            if(dir[move]==res[pos])
                break;
        int blank_idx=state.find('0',0);
        int row=floor(blank_idx/3),col=blank_idx%3;
        int a_row=row+dir_y[move],a_col=col+dir_x[move];
        swap(state[blank_idx],state[a_row*3+a_col]);
        for(int i=0;i<9;i++)
            ui->res_Table->setItem(floor(i/3),i%3,new QTableWidgetItem(QString(state[i])));

        //实现延时
        QEventLoop eventloop;
        QTimer::singleShot(500, &eventloop, SLOT(quit()));
        eventloop.exec();
    }
}

void MainWindow::on_DFS_Button_clicked()
{
    if(dfs_res=="No Answer!")
        QMessageBox::critical(NULL,"res","No Answer!");
    else if(dfs_res=="Input Is Answer!")
        QMessageBox::critical(NULL,"end_state","Input Is Answer!");
    else
        res_show(dfs_res);
}

void MainWindow::on_BFS_Button_clicked()
{
    if(bfs_res=="No Answer!")
        QMessageBox::critical(NULL,"res","No Answer!");
    else if(bfs_res=="Input Is Answer!")
        QMessageBox::critical(NULL,"end_state","Input Is Answer!");
    else
        res_show(bfs_res);
}

void MainWindow::on_H1_Button_clicked()
{
    if(AStar1_res=="No Answer!")
        QMessageBox::critical(NULL,"res","No Answer!");
    else if(AStar1_res=="Input Is Answer!")
        QMessageBox::critical(NULL,"end_state","Input Is Answer!");
    else
        res_show(AStar1_res);
}


void MainWindow::on_H2_Button_clicked()
{
    if(AStar2_res=="No Answer!")
        QMessageBox::critical(NULL,"res","No Answer!");
    else if(AStar2_res=="Input Is Answer!")
        QMessageBox::critical(NULL,"end_state","Input Is Answer!");
    else
        res_show(AStar2_res);
}

void MainWindow::on_H3_Button_clicked()
{
    if(AStar3_res=="No Answer!")
        QMessageBox::critical(NULL,"res","No Answer!");
    else if(AStar3_res=="Input Is Answer!")
        QMessageBox::critical(NULL,"end_state","Input Is Answer!");
    else
        res_show(AStar3_res);
}
