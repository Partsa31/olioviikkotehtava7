#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

ui->setupUi(this);
timer = new QTimer(this);
timer->setSingleShot(false);
ui->game_info->setAlignment(Qt::AlignCenter);
ui->winner->setAlignment(Qt::AlignCenter);
setInitialState();
connect(ui->min_2,SIGNAL(clicked()),this,SLOT(setGameTime()));
connect(ui->min_5,SIGNAL(clicked()),this,SLOT(setGameTime()));
connect(timer,SIGNAL(timeout()),this,SLOT(handleTimeout()));
connect(ui->start,SIGNAL(clicked()),this,SLOT(startGame()));
connect(ui->stop,SIGNAL(clicked()),this,SLOT(stopGame()));
connect(ui->switch_to_2,SIGNAL(clicked()),this,SLOT(togglePlayer()));
connect(ui->switch_to_1,SIGNAL(clicked()),this,SLOT(togglePlayer()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleTimeout()
{
    if(player == 1) {
        pl_1_time--;
    }
    else {
        pl_2_time--;
    }
    if(pl_1_time == 0) {
        winner = 2;
        setWinState();
    }
    else if(pl_2_time == 0) {
        winner = 1;
        setWinState();
    }
    else {
        updateProgressBar();
    }
}

void MainWindow::setGameTime()
{
    QPushButton * btn = qobject_cast<QPushButton*>(sender());
    QString m = btn->objectName();
    int minutes = m.last(1).toInt();
    game_time = 60 * minutes;
    pl_1_time = game_time;
    pl_2_time = game_time;
    ui->pl_1_bar->setRange(0,game_time);
    ui->pl_2_bar->setRange(0,game_time);
    updateProgressBar();
    ui->start->setDisabled(false);
    setGameInfoText(QString("Ready to play"));
    ui->winner->setText(QString(""));
}

void MainWindow::startGame()
{
    timer->start(1000);
    setStartState();
}

void MainWindow::stopGame()
{
    timer->stop();
    setInitialState();
}

void MainWindow::togglePlayer()
{
    if(player == 1) {
        player = 2;
        ui->switch_to_2->setDisabled(true);
        ui->switch_to_1->setDisabled(false);
    }
    else {
        player = 1;
        ui->switch_to_1->setDisabled(true);
        ui->switch_to_2->setDisabled(false);
    }
}

void MainWindow::updateProgressBar()
{
    ui->pl_1_bar->setValue(pl_1_time);
    ui->pl_2_bar->setValue(pl_2_time);
}

void MainWindow::setGameInfoText(QString t)
{
    ui->game_info->setText(t);
}

void MainWindow::setInitialState()
{
    timer->stop();
    ui->min_2->setDisabled(false);
    ui->min_5->setDisabled(false);
    ui->switch_to_2->setDisabled(true);
    ui->switch_to_1->setDisabled(true);
    ui->stop->setDisabled(true);
    ui->start->setDisabled(true);
    pl_1_time = 0;
    pl_2_time = 0;
    winner = -1;
    updateProgressBar();
    setGameInfoText(QString("Select playtime and press start game"));
}
void MainWindow::setStartState()
{
    ui->min_2->setDisabled(true);
    ui->min_5->setDisabled(true);
    ui->switch_to_2->setDisabled(false);
    ui->switch_to_1->setDisabled(true);
    ui->stop->setDisabled(false);
    ui->start->setDisabled(true);
    player = 1;
    setGameInfoText(QString("Game ongoing"));
}

void MainWindow::setWinState()
{
    if(winner == 1) {
        ui->winner->setText(QString("Player 1 won!"));
    }
    else {
        ui->winner->setText(QString("Player 2 won!"));
    }
    setInitialState();
}
