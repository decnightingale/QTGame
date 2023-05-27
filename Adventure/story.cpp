#include "story.h"
#include "ui_story.h"

story::story(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::story)
{
    ui->setupUi(this);
}

story::~story()
{
    delete ui;
}
