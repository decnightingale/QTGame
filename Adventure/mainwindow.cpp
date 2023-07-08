#include "mainwindow.h"
#include "get_start.h"
#include "help_window.h"
#include "game_story_window.h"
#include "game_map.h"
#include "victory_window.h"
#include "lose_window.h"
#include "ui_mainwindow.h"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //qDebug()<<size();//(640,480)
    ui->setupUi(this);
    setWindowTitle("Adventure");
    get_start* start_menu = new get_start();
    help_window* help = new help_window();
    game_story_window* game_story = new game_story_window();
    game_map* map = new game_map();
    victory_window* victory = new victory_window();
    lose_window* lose = new lose_window();
    start_menu->show();
    ui->stackedWidget->addWidget(start_menu);
    ui->stackedWidget->addWidget(help);
    ui->stackedWidget->addWidget(game_story);
    ui->stackedWidget->addWidget(map);
    ui->stackedWidget->addWidget(victory);
    ui->stackedWidget->addWidget(lose);
    ui->stackedWidget->setCurrentIndex(0);
    connect(start_menu,&get_start::quit_called,[=](){
        this->close();
    });
    connect(start_menu,&get_start::help_called,[=](){
        help->index = 1;
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
        help->index = 1;
        ui->stackedWidget->setCurrentIndex(1);
    });
    connect(map,&game_map::return_called,[=](){
        ui->stackedWidget->setCurrentIndex(0);
    });
    connect(map,&game_map::win_sign,[=](){
        victory->collection_num.setNum(map->collection_num);
        victory->life_num.setNum(map->life_value);
        victory->light_num.setNum(map->light_value);
        victory->mark.setNum(map->collection_num*5 + map->light_value +map->life_value *10);
        ui->stackedWidget->setCurrentIndex(4);
    });

    connect(map,&game_map::lose_sign,[=](){
        lose->collection_num.setNum(map->collection_num);
        lose->life_num.setNum(map->life_value);
        lose->light_num.setNum(map->light_value);
        lose->mark.setNum(map->collection_num*5 + map->light_value +map->life_value *10);
        ui->stackedWidget->setCurrentIndex(5);
    });

    connect(victory,&victory_window::close_called,[=](){
        this->close();
    });
    connect(lose,&lose_window::close_called,[=](){
        this->close();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

