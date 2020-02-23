#include "ermainwindow.hxx"
#include "ui_ermainwindow.h"

ERMainWindow::ERMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ERMainWindow)
{
    ui->setupUi(this);

    _setup_block_sections();
    _add_signals();

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

}

void ERMainWindow::_play_random_lever_sound()
{
    QSoundEffect* sound = _lever_sounds.at(qrand() % _lever_sounds.size());
    sound->play();
}

void ERMainWindow::_setup_block_sections()
{
    _block_sections[1] = new EWRB::BlockSection(1, "EDGWARE ROAD EAST APPROACH");
    _block_sections[2] = new EWRB::BlockSection(2, "EDGWARE ROAD EAST SIG 1. SIG 2.");
    _block_sections[3] = new EWRB::BlockSection(3, "EDGWARE ROAD EAST PLAT 4 APPROACH");
    _block_sections[4] = new EWRB::BlockSection(4, "EDGWARE ROAD PLATFORM 4");
    _block_sections[5] = new EWRB::BlockSection(5, "SIG 2. TO EDGWARE ROAD PLATFORM 3");
    _block_sections[6] = new EWRB::BlockSection(6, "EDGWARE ROAD PLATFORM 3 WESTBOUND");
    _block_sections[7] = new EWRB::BlockSection(7, "EDGWARE ROAD PLATFORM 3 EASTBOUND");
    _block_sections[8] = new EWRB::BlockSection(8, "EDGWARE ROAD PLATFORM 2 EASTBOUND");
    _block_sections[9] = new EWRB::BlockSection(9, "EDGWARE ROAD PLATFORM 2 WESTBOUND");
    _block_sections[10] = new EWRB::BlockSection(10, "EDGWARE ROAD PLATFORM 1 EASTBOUND");
    _block_sections[11] = new EWRB::BlockSection(11, "EDGWARE ROAD PLATFORM 1 APPROACH");
    _block_sections[12] = new EWRB::BlockSection(12, "EDGWARE ROAD WEST PLAT 4 DEPART");
    _block_sections[13] = new EWRB::BlockSection(13, "EDGWARE ROAD WEST PLAT 3 DEPART");
    _block_sections[14] = new EWRB::BlockSection(14, "EDGWARE ROAD WEST PLAT 2 DEPART");
    _block_sections[15] = new EWRB::BlockSection(15, "EDGWARE ROAD WEST PLAT 3 ARRIVE");
    _block_sections[16] = new EWRB::BlockSection(16, "EDGWARE ROAD WEST PLAT 2 ARRIVE");
    _block_sections[17] = new EWRB::BlockSection(17, "EDGWARE ROAD WEST PLAT 1 ARRIVE");
    _block_sections[18] = new EWRB::BlockSection(18, "EDGWARE ROAD WEST APPROACH");
    _block_sections[19] = new EWRB::BlockSection(19, "TO DL PADDINGTON");
    _block_sections[20] = new EWRB::BlockSection(20, "FROM DL PADDINGTON");
    _block_sections[21] = new EWRB::BlockSection(21, "TO HCL PADDINGTON");
    _block_sections[22] = new EWRB::BlockSection(22, "FROM HCL PADDINGTON");
    _block_sections[23] = new EWRB::BlockSection(23, "DL PADDINGTON DEPART");
    _block_sections[24] = new EWRB::BlockSection(24, "HCL PADDINGTON DEPART");
}

void ERMainWindow::_add_signals()
{
    //TODO Change actual panel/block IDs to match those on track diagram

    _signals[1] = new EWRB::Signal(1);                                      // Edgware Road East Signal 1
    _block_sections[2]->setBlockSignal(_signals[1]);
    _block_sections[2]->setRequiredState(EWRB::SignalState::Off);           // Normal 2AT Signal
    _lever_frame->addSignalPanelIndicator(_block_sections[2]);

    _signals[2] = new EWRB::Signal(2);                                         // Edgware Road Jct Feather Pos 1
    _block_sections[3]->setBlockSignal(_signals[2]);                        // Edgware Road East Jct
    _block_sections[3]->setRequiredState(EWRB::SignalState::OffJctLeft);    // Diverge Left
    _lever_frame->addSignalPanelIndicator(_block_sections[3]);
    _block_sections[5]->setBlockSignal(_signals[2]);
    _block_sections[5]->setRequiredState(EWRB::SignalState::Off);           // Straight ahead
    _lever_frame->addSignalPanelIndicator(_block_sections[5]);

    _signals[3] = new EWRB::Signal(3);                                         // Platform 4 Approach Signal
    _block_sections[4]->setBlockSignal(_signals[3]);
    _block_sections[4]->setRequiredState(EWRB::SignalState::Off);           // Normal 2AT Signal
    _lever_frame->addSignalPanelIndicator(_block_sections[4]);

    _signals[5] = new EWRB::Signal(4);
    _block_sections[6]->setBlockSignal(_signals[4]);                        // Westbound Starter Platform 3
    _block_sections[6]->setRequiredState(EWRB::SignalState::Off);           // Normal 2AT Signal
    _lever_frame->addSignalPanelIndicator(_block_sections[6]);

    _signals[4] = new EWRB::Signal(5);
    _block_sections[7]->setBlockSignal(_signals[4]);                        // Eastbound Starter Platform 3
    _block_sections[7]->setRequiredState(EWRB::SignalState::Off);           // Normal 2AT Signal
    _lever_frame->addSignalPanelIndicator(_block_sections[7]);

    _signals[7] = new EWRB::Signal(6);
    _block_sections[9]->setBlockSignal(_signals[7]);                        // Westbound Starter Platform 2
    _block_sections[9]->setRequiredState(EWRB::SignalState::Off);           // Normal 2AT Signal
    _lever_frame->addSignalPanelIndicator(_block_sections[9]);

    _signals[6] = new EWRB::Signal(7);
    _block_sections[8]->setBlockSignal(_signals[6]);                        // Eastbound Starter Platform 2
    _block_sections[8]->setRequiredState(EWRB::SignalState::Off);           // Normal 2AT Signal
    _lever_frame->addSignalPanelIndicator(_block_sections[8]);

    _signals[8] = new EWRB::Signal(8);
    _block_sections[10]->setBlockSignal(_signals[8]);                        // Eastbound Starter Platform 1
    _block_sections[10]->setRequiredState(EWRB::SignalState::Off);           // Normal 2AT Signal
    _lever_frame->addSignalPanelIndicator(_block_sections[10]);

    _signals[9] = new EWRB::Signal(9);
    _block_sections[11]->setBlockSignal(_signals[9]);                        // Platform 1 Approach signal
    _block_sections[11]->setRequiredState(EWRB::SignalState::Off);           // Normal 2AT Signal
    _lever_frame->addSignalPanelIndicator(_block_sections[11]);

    _signals[10] = new EWRB::Signal(10);
    _block_sections[12]->setBlockSignal(_signals[10]);                       // Platform 4 Start Signal
    _block_sections[12]->setRequiredState(EWRB::SignalState::Off);           // Normal 2AT Signal
    _lever_frame->addSignalPanelIndicator(_block_sections[12]);

    _signals[11] = new EWRB::Signal(11);
    _block_sections[13]->setBlockSignal(_signals[11]);                       // Platform 3 West Start Signal
    _block_sections[13]->setRequiredState(EWRB::SignalState::Off);           // Normal 2AT Signal
    _lever_frame->addSignalPanelIndicator(_block_sections[8]);

    _signals[12] = new EWRB::Signal(12);
    _block_sections[14]->setBlockSignal(_signals[12]);                       // Platform 2 West Start Signal
    _block_sections[14]->setRequiredState(EWRB::SignalState::Off);           // Normal 2AT Signal
    _lever_frame->addSignalPanelIndicator(_block_sections[14]);

    _signals[13] = new EWRB::Signal(13);
    _block_sections[15]->setBlockSignal(_signals[13]);                       // Edgware Road West Approach Jct Feather Pos 1,2
    _block_sections[15]->setRequiredState(EWRB::SignalState::OffJctRight);   // Platform 3 approach
    _lever_frame->addSignalPanelIndicator(_block_sections[15]);
    _block_sections[16]->setBlockSignal(_signals[13]);
    _block_sections[16]->setRequiredState(EWRB::SignalState::Off);           // Platform 2 approach
    _lever_frame->addSignalPanelIndicator(_block_sections[16]);
    _block_sections[17]->setBlockSignal(_signals[13]);
    _block_sections[17]->setRequiredState(EWRB::SignalState::OffJctLeft);    // Platform 1 approach
    _lever_frame->addSignalPanelIndicator(_block_sections[17]);

    _signals[14] = new EWRB::Signal(14);
    _block_sections[18]->setBlockSignal(_signals[14]);                       // Edgware Road West Approach
    _block_sections[18]->setRequiredState(EWRB::SignalState::Off);           // Normal 2AT Signal
    _lever_frame->addSignalPanelIndicator(_block_sections[18]);

    _signals[15] = new EWRB::Signal(15);
    _block_sections[19]->setBlockSignal(_signals[15]);                       // Praed St Junction Feather Pos 2
    _block_sections[19]->setRequiredState(EWRB::SignalState::Off);           // Towards Paddington DL
    _lever_frame->addSignalPanelIndicator(_block_sections[19]);
    _block_sections[21]->setBlockSignal(_signals[15]);
    _block_sections[21]->setRequiredState(EWRB::SignalState::OffJctRight);   // Towards Paddington HCL
    _lever_frame->addSignalPanelIndicator(_block_sections[21]);

    _signals[16] = new EWRB::Signal(16);                                         // Praed Jct Approach from DL Paddington
    _block_sections[20]->setBlockSignal(_signals[16]);
    _block_sections[20]->setRequiredState(EWRB::SignalState::Off);           // Normal 2AT Signal
    _lever_frame->addSignalPanelIndicator(_block_sections[20]);

    _signals[17] = new EWRB::Signal(17);                                         // Praed Jct Approach from HCL Paddington
    _block_sections[22]->setBlockSignal(_signals[17]);
    _block_sections[22]->setRequiredState(EWRB::SignalState::Off);           // Normal 2AT Signal
    _lever_frame->addSignalPanelIndicator(_block_sections[22]);

    _signals[18] = new EWRB::Signal(18);                                         // DL Paddington Starter
    _block_sections[23]->setBlockSignal(_signals[18]);
    _block_sections[23]->setRequiredState(EWRB::SignalState::Off);           // Normal 2AT Signal
    _lever_frame->addSignalPanelIndicator(_block_sections[23]);

    _signals[19] = new EWRB::Signal(19);                                         // HCL Paddington Starter
    _block_sections[24]->setBlockSignal(_signals[19]);
    _block_sections[24]->setRequiredState(EWRB::SignalState::Off);           // Normal 2AT Signal
    _lever_frame->addSignalPanelIndicator(_block_sections[24]);
}

void ERMainWindow::_lever_action(const int &i)
{
    _lever_frame->operator[](i)->moveLever();
    _lever_frame->update();
    _play_random_lever_sound();
}

ERMainWindow::~ERMainWindow()
{
    delete ui;
}
