#ifndef STORY_H
#define STORY_H

#include <QWidget>

namespace Ui {
class story;
}

class story : public QWidget
{
    Q_OBJECT

public:
    explicit story(QWidget *parent = nullptr);
    ~story();

private:
    Ui::story *ui;
};

#endif // STORY_H
