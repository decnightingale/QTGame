#include "mainwindow.h"
#include "get_start.h"
#include "help_window.h"
#include "game_story_window.h"
#include "game_map.h"
#include "ui_mainwindow.h"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    qDebug()<<size();
    ui->setupUi(this);
    setWindowTitle("Adventure");
    get_start* start_menu = new get_start();
    help_window* help = new help_window();
    game_story_window* game_story = new game_story_window();
    game_map* map = new game_map();
    start_menu->show();
    ui->stackedWidget->addWidget(start_menu);
    ui->stackedWidget->addWidget(help);
    ui->stackedWidget->addWidget(game_story);
    ui->stackedWidget->addWidget(map);
    ui->stackedWidget->setCurrentIndex(0);
    connect(start_menu,&get_start::quit_called,[=](){
        this->close();
    });
    connect(start_menu,&get_start::help_called,[=](){
        ui->stackedWidget->setCurrentIndex(1);
    });
    connect(help,&help_window::return_called,[=](){
        ui->stackedWidget->setCurrentIndex(0);
    });
    connect(start_menu,&get_start::play_called,[=](){
        ui->stackedWidget->setCurrentIndex(2);
    });
    connect(game_story,&game_story_window::continue_called,[=](){
        ui->stackedWidget->setCurrentIndex(3);
    });
    connect(map,&game_map::help_called,[=](){
        ui->stackedWidget->setCurrentIndex(1);
    });
    connect(map,&game_map::return_called,[=](){
        ui->stackedWidget->setCurrentIndex(0);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

