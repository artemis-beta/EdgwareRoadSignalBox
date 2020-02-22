#include "ermainwindow.hxx"
#include "ui_ermainwindow.h"

ERMainWindow::ERMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ERMainWindow)
{
    ui->setupUi(this);

    for(int i{1}; i < 13; ++i)
    {
        _lever_frame_buttons[i] = new QPushButton(this);
        connect(_lever_frame_buttons[i], &QPushButton::clicked, [this, i](){_lever_action(i);});
        _lever_frame_buttons[i]->move(25+(i-1)*24.1, 620);
        _lever_frame_buttons[i]->setFixedSize(20, 80);
        _lever_frame_buttons[i]->setStyleSheet("QPushButton{background: transparent;}");
    }
    for(int i{13}; i < 28; ++i)
    {
        _lever_frame_buttons[i] = new QPushButton(this);
        connect(_lever_frame_buttons[i], &QPushButton::clicked, [this, i](){_lever_action(i);});
        _lever_frame_buttons[i]->move(25+(i-1)*24.1, 620);
        _lever_frame_buttons[i]->setFixedSize(20, 80);
        _lever_frame_buttons[i]->setStyleSheet("QPushButton{background: transparent;}");
    }

    for(int i{28}; i < 39; ++i)
    {
        _lever_frame_buttons[i] = new QPushButton(this);
        connect(_lever_frame_buttons[i], &QPushButton::clicked, [this, i](){_lever_action(i);});
        _lever_frame_buttons[i]->move(25+(i-1)*24.1, 620);
        _lever_frame_buttons[i]->setFixedSize(20, 80);
        _lever_frame_buttons[i]->setStyleSheet("QPushButton{background: transparent;}");
    }

    for(int i{1}; i < 9; ++i)
    {
        _lever_sounds.append(new QSoundEffect);
        _lever_sounds[i-1]->setSource(QUrl::fromLocalFile(":/audio/audio/lever_move_"+QString::number(i)+".wav"));
    }

    QMetaObject::connectSlotsByName(this);
}

void ERMainWindow::_play_random_lever_sound()
{
    QSoundEffect* sound = _lever_sounds.at(qrand() % _lever_sounds.size());
    sound->play();
}

void ERMainWindow::_lever_action(const int &i)
{
    _lever_frame->operator[](i)->moveLever();
    _play_random_lever_sound();
}

ERMainWindow::~ERMainWindow()
{
    delete ui;
}
