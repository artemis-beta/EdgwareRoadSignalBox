#include "ermainwindow.hxx"
#include "ui_ermainwindow.h"

ERMainWindow::ERMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ERMainWindow)
{
    ui->setupUi(this);

    _add_indicators();

    const EWRB::Scaler* scaler_ = new EWRB::Scaler;

    this->setFixedSize(scaler_->screen_width(), scaler_->screen_height());

    for(int i{1}; i < 13; ++i)
    {
        _lever_frame_buttons[i] = new QPushButton(this);
        connect(_lever_frame_buttons[i], &QPushButton::clicked, [this, i](){_lever_action(i);});
        _lever_frame_buttons[i]->move(scaler_->scale_width(25+(i-1)*24.1), 0.7*scaler_->screen_height());
        _lever_frame_buttons[i]->setFixedSize(scaler_->scale_width(20), scaler_->scale_height(80));
        _lever_frame_buttons[i]->setStyleSheet("QPushButton{background: transparent;}");
    }
    for(int i{13}; i < 28; ++i)
    {
        _lever_frame_buttons[i] = new QPushButton(this);
        connect(_lever_frame_buttons[i], &QPushButton::clicked, [this, i](){_lever_action(i);});
        _lever_frame_buttons[i]->move(scaler_->scale_width(25+(i-1)*24.1), 0.7*scaler_->screen_height());
        _lever_frame_buttons[i]->setFixedSize(scaler_->scale_width(20), scaler_->scale_height(80));
        _lever_frame_buttons[i]->setStyleSheet("QPushButton{background: transparent;}");
    }

    for(int i{28}; i < 39; ++i)
    {
        _lever_frame_buttons[i] = new QPushButton(this);
        connect(_lever_frame_buttons[i], &QPushButton::clicked, [this, i](){_lever_action(i);});
        _lever_frame_buttons[i]->move(scaler_->scale_width(25+(i-1)*24.1), 0.7*scaler_->screen_height());
        _lever_frame_buttons[i]->setFixedSize(scaler_->scale_width(20), scaler_->scale_height(80));
        _lever_frame_buttons[i]->setStyleSheet("QPushButton{background: transparent;}");
    }

    _lever_frame->setDispatcher(_dispatcher);
    _lever_frame->update();
}

void ERMainWindow::_add_indicators()
{

    _lever_frame->addSignalPanelIndicator(_interlocking->getBlockSection(1));
    _lever_frame->addSignalMapIndicator(_interlocking->getBlockSection(1), 90);
    _lever_frame->addSignalPanelIndicator(_interlocking->getBlockSection(2));
    _lever_frame->addSignalPanelIndicator(_interlocking->getBlockSection(3));
    _lever_frame->addCustomMapIndicator(new EWRB::EWREastSignalIndicator(this, {_interlocking->getBlockSection(3), _interlocking->getBlockSection(2)}));
    _lever_frame->addSignalPanelIndicator(_interlocking->getBlockSection(4));
    _lever_frame->addSignalMapIndicator(_interlocking->getBlockSection(4), 67.5);
    _lever_frame->addSignalPanelIndicator(_interlocking->getBlockSection(5));
    _lever_frame->addSignalMapIndicator(_interlocking->getBlockSection(5), 90);
    _lever_frame->addSignalPanelIndicator(_interlocking->getBlockSection(6));
    _lever_frame->addSignalMapIndicator(_interlocking->getBlockSection(6), 90);
    _lever_frame->addSignalPanelIndicator(_interlocking->getBlockSection(7));
    _lever_frame->addSignalMapIndicator(_interlocking->getBlockSection(7), 90);
    _lever_frame->addSignalPanelIndicator(_interlocking->getBlockSection(8));
    _lever_frame->addShuntMapIndicator(_interlocking->getBlockSection(8), 90);
    _lever_frame->addSignalPanelIndicator(_interlocking->getBlockSection(10));
    _lever_frame->addShuntMapIndicator(_interlocking->getBlockSection(10), 90);
    _lever_frame->addSignalPanelIndicator(_interlocking->getBlockSection(11));
    _lever_frame->addSignalPanelIndicator(_interlocking->getBlockSection(12));
    _lever_frame->addCustomMapIndicator(new EWRB::PraedStJctSignalIndicator(this, {_interlocking->getBlockSection(11), _interlocking->getBlockSection(12)}));
    _lever_frame->addSignalPanelIndicator(_interlocking->getBlockSection(28));
    _lever_frame->addSignalMapIndicator(_interlocking->getBlockSection(28), 270);
    _lever_frame->addSignalPanelIndicator(_interlocking->getBlockSection(29));
    _lever_frame->addSignalMapIndicator(_interlocking->getBlockSection(29), 270);
    _lever_frame->addSignalPanelIndicator(_interlocking->getBlockSection(30));
    _lever_frame->addSignalMapIndicator(_interlocking->getBlockSection(30), 270);
    _lever_frame->addSignalPanelIndicator(_interlocking->getBlockSection(31));
    _lever_frame->addSignalMapIndicator(_interlocking->getBlockSection(31), 247.5);
    _lever_frame->addSignalPanelIndicator(_interlocking->getBlockSection(32));
    _lever_frame->addShuntMapIndicator(_interlocking->getBlockSection(32), 90);
    _lever_frame->addSignalPanelIndicator(_interlocking->getBlockSection(33));
    _lever_frame->addSignalPanelIndicator(_interlocking->getBlockSection(34));
    _lever_frame->addSignalPanelIndicator(_interlocking->getBlockSection(35));
    _lever_frame->addCustomMapIndicator(new EWRB::EWRWestSignalIndicator(this, {_interlocking->getBlockSection(34), _interlocking->getBlockSection(35), _interlocking->getBlockSection(33)}));
    _lever_frame->addSignalPanelIndicator(_interlocking->getBlockSection(36));
    _lever_frame->addSignalMapIndicator(_interlocking->getBlockSection(36), 270);
    _lever_frame->addSignalPanelIndicator(_interlocking->getBlockSection(37));
    _lever_frame->addSignalMapIndicator(_interlocking->getBlockSection(37), 315);
    _lever_frame->addSignalPanelIndicator(_interlocking->getBlockSection(38));
    _lever_frame->addSignalMapIndicator(_interlocking->getBlockSection(38), 225);

    // OPX Controlled Signals

    _lever_frame->addSignalMapIndicator(_interlocking->getBlockSection(39), 270);
    _lever_frame->addSignalMapIndicator(_interlocking->getBlockSection(40), 270);

    _lever_frame->placeSigIndicators();
    _lever_frame->placeMapIndicators();
    _lever_frame->placeDescribers();
}

void ERMainWindow::_lever_action(const int &i)
{

    if(!_interlocking->Query(i))
    {
        qDebug() << "Invalid Move";
        return;
    }
    _lever_frame->update(i);
}

ERMainWindow::~ERMainWindow()
{
    delete ui;
}
