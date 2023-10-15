#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void handleTimeout();
    void setGameTime();
    void startGame();
    void stopGame();
    void togglePlayer();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    int pl_1_time;
    int pl_2_time;
    int player;
    int game_time;
    int winner;
    void updateProgressBar();
    void setGameInfoText(QString);
    void setInitialState();
    void setStartState();
    void setWinState();
};
#endif // MAINWINDOW_H
