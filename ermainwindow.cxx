#include "ermainwindow.hxx"
#include "ui_ermainwindow.h"

ERMainWindow::ERMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ERMainWindow)
{
    ui->setupUi(this);

    _lever_failed->setSource(QUrl::fromLocalFile(":/audio/audio/lever_fail.wav"));
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
    _block_sections[1] = new EWRB::BlockSection(1, "EDGWARE ROAD EAST SIG. 1 SIG. 2");
    _block_sections[2] = new EWRB::BlockSection(2, "SIG 2. TO EAST PLAT 4 APPROACH");
    _block_sections[3] = new EWRB::BlockSection(3, "SIG 2. TO EDGWARE ROAD PLATFORM 3");
    _block_sections[4] = new EWRB::BlockSection(4, "EDGWARE ROAD PLATFORM 4");
    _block_sections[5] = new EWRB::BlockSection(5, "EDGWARE ROAD PLATFORM 2 WESTBOUND DEPART");
    _block_sections[6] = new EWRB::BlockSection(6, "EDGWARE ROAD PLATFORM 3 WESTBOUND DEPART");
    _block_sections[7] = new EWRB::BlockSection(7, "EDGWARE ROAD PLATFORM 4 WESTBOUND DEPART");
    _block_sections[8] = new EWRB::BlockSection(8, "EDGWARE ROAD SHUNT EAST APPROACH");
    _block_sections[9] = new EWRB::BlockSection(); // DISUSED BLOCK/SIGNAL
    _block_sections[10] = new EWRB::BlockSection(10, "EDGWARE ROAD SIDING SHUNT");
    _block_sections[11] = new EWRB::BlockSection(11, "PREAD ST JCT TO PADDINGTON (HCL)");
    _block_sections[12] = new EWRB::BlockSection(12, "PREAD ST JCT TO PADDINGTON (DL)");
    _block_sections[28] = new EWRB::BlockSection(28, "EDGWARE ROAD PLATFORM 3 EASTBOUND DEPART");
    _block_sections[29] = new EWRB::BlockSection(29, "EDGWARE ROAD PLATFORM 2 EASTBOUND DEPART");
    _block_sections[30] = new EWRB::BlockSection(30, "EDGWARE ROAD PLATFORM 1 EASTBOUND DEPART");
    _block_sections[31] = new EWRB::BlockSection(31, "EDGWARE ROAD PLATFORM 1");
    _block_sections[32] = new EWRB::BlockSection(32, "EDGWARE ROAD SHUNT WEST APPROACH");
    _block_sections[33] = new EWRB::BlockSection(33, "SIG. 33 TO EDGWARE ROAD PLATFORM 3");
    _block_sections[34] = new EWRB::BlockSection(34, "SIG. 33 TO EDGWARE ROAD PLATFORM 2");
    _block_sections[35] = new EWRB::BlockSection(35, "SIG. 33 TO EDGWARE ROAD PLATFORM 1");
    _block_sections[36] = new EWRB::BlockSection(36, "EDGWARE ROAD WEST SIG. 36 SIG. 33");
    _block_sections[37] = new EWRB::BlockSection(37, "PRAED ST JCN APPROACH FROM PADDINGTON (HCL)");
    _block_sections[38] = new EWRB::BlockSection(38, "PRAED ST JCN APPROACH FROM PADDINGTON (DL)");
    _block_sections[39] = new EWRB::BlockSection(39, "PADDINGTON HCL DEPART (OPX)");
    _block_sections[40] = new EWRB::BlockSection(40, "PADDINGTON DL DEPART (OPX)");
}

void ERMainWindow::_add_signals()
{
    //TODO Change actual panel/block IDs to match those on track diagram

    _signals[1] = new EWRB::Signal(1);                                      // Edgware Road East SIG. 1
    _block_sections[1]->setBlockSignal(_signals[1]);
    _block_sections[1]->setRequiredState(EWRB::SignalState::Off);           // Normal 2AT Signal
    _lever_frame->addSignalPanelIndicator(_block_sections[1]);
    _lever_frame->addSignalMapIndicator(_block_sections[1], 90);

    _signals[2] = new EWRB::Signal(2);                                      // Edgware Road East Jct Feather Pos 1 SIG. 2, 3
    _block_sections[2]->setBlockSignal(_signals[2]);                        // Edgware Road East Jct
    _block_sections[2]->setRequiredState(EWRB::SignalState::OffJctLeft);    // Diverge Left
    _lever_frame->addSignalPanelIndicator(_block_sections[3]);
    _block_sections[3]->setBlockSignal(_signals[2]);
    _block_sections[3]->setRequiredState(EWRB::SignalState::Off);           // Straight ahead
    _lever_frame->addSignalPanelIndicator(_block_sections[2]);
    _lever_frame->addCustomMapIndicator(new EWRB::EWREastSignalIndicator(this, {_block_sections[3], _block_sections[2]}));

    _signals[4] = new EWRB::Signal(4);                                      // Platform 4 Approach SIG. 4
    _block_sections[4]->setBlockSignal(_signals[4]);
    _block_sections[4]->setRequiredState(EWRB::SignalState::Off);           // Normal 2AT Signal
    _lever_frame->addSignalPanelIndicator(_block_sections[4]);
    _lever_frame->addSignalMapIndicator(_block_sections[4], 67.5);

    _signals[5] = new EWRB::Signal(5);
    _block_sections[5]->setBlockSignal(_signals[5]);                        // Westbound Starter Platform 2 SIG. 5
    _block_sections[5]->setRequiredState(EWRB::SignalState::Off);           // Normal 2AT Signal
    _lever_frame->addSignalPanelIndicator(_block_sections[5]);
    _lever_frame->addSignalMapIndicator(_block_sections[5], 90);

    _signals[6] = new EWRB::Signal(6);
    _block_sections[6]->setBlockSignal(_signals[6]);                        // Westbound Starter Platform 3 SIG. 6
    _block_sections[6]->setRequiredState(EWRB::SignalState::Off);           // Normal 2AT Signal
    _lever_frame->addSignalPanelIndicator(_block_sections[6]);
    _lever_frame->addSignalMapIndicator(_block_sections[6], 90);

    _signals[7] = new EWRB::Signal(7);
    _block_sections[7]->setBlockSignal(_signals[7]);                        // Westbound Starter Platform 4 SIG. 7
    _block_sections[7]->setRequiredState(EWRB::SignalState::Off);           // Normal 2AT Signal
    _lever_frame->addSignalPanelIndicator(_block_sections[7]);
    _lever_frame->addSignalMapIndicator(_block_sections[7], 90);

    _signals[8] = new EWRB::ShuntSignal(8);
    _block_sections[8]->setBlockSignal(_signals[8]);                        // Edgware Road Eastbound Wrong Dir. SIG. 8
    _block_sections[8]->setRequiredState(EWRB::SignalState::Off);           // Disc 2AT Signal
    _lever_frame->addSignalPanelIndicator(_block_sections[8]);
    _lever_frame->addShuntMapIndicator(_block_sections[8], 90);

    // Signal 9 absent

    _signals[10] = new EWRB::ShuntSignal(10);
    _block_sections[10]->setBlockSignal(_signals[10]);                      // Edgware Road Siding SIG. 10
    _block_sections[10]->setRequiredState(EWRB::SignalState::Off);          // Disc 2AT Signal
    _lever_frame->addSignalPanelIndicator(_block_sections[10]);
    _lever_frame->addShuntMapIndicator(_block_sections[10], 90);

    _signals[11] = new EWRB::Signal(11);
    _block_sections[11]->setBlockSignal(_signals[11]);                       // Praed St Junction Feather Pos 2
    _block_sections[11]->setRequiredState(EWRB::SignalState::Off);           // Towards Paddington DL
    _lever_frame->addSignalPanelIndicator(_block_sections[11]);
    _block_sections[12]->setBlockSignal(_signals[11]);
    _block_sections[12]->setRequiredState(EWRB::SignalState::OffJctRight);   // Towards Paddington HCL
    _lever_frame->addSignalPanelIndicator(_block_sections[12]);
    _lever_frame->addCustomMapIndicator(new EWRB::PraedStJctSignalIndicator(this, {_block_sections[11], _block_sections[12  ]}));

    _signals[28] = new EWRB::Signal(28);
    _block_sections[28]->setBlockSignal(_signals[28]);                       // Eastbound Starter Platform 3 SIG. 28
    _block_sections[28]->setRequiredState(EWRB::SignalState::Off);           // Normal 2AT Signal
    _lever_frame->addSignalPanelIndicator(_block_sections[28]);
    _lever_frame->addSignalMapIndicator(_block_sections[28], 270);

    _signals[29] = new EWRB::Signal(29);
    _block_sections[29]->setBlockSignal(_signals[29]);                       // Eastbound Starter Platform 2 SIG. 29
    _block_sections[29]->setRequiredState(EWRB::SignalState::Off);           // Normal 2AT Signal
    _lever_frame->addSignalPanelIndicator(_block_sections[29]);
    _lever_frame->addSignalMapIndicator(_block_sections[29], 270);

    _signals[30] = new EWRB::Signal(30);
    _block_sections[30]->setBlockSignal(_signals[30]);                       // Eastbound Starter Platform 1 SIG. 30
    _block_sections[30]->setRequiredState(EWRB::SignalState::Off);           // Normal 2AT Signal
    _lever_frame->addSignalPanelIndicator(_block_sections[30]);
    _lever_frame->addSignalMapIndicator(_block_sections[30], 270);

    _signals[31] = new EWRB::Signal(31);
    _block_sections[31]->setBlockSignal(_signals[31]);                       // Platform 1 Approach SIG. 31
    _block_sections[31]->setRequiredState(EWRB::SignalState::Off);           // Normal 2AT Signal
    _lever_frame->addSignalPanelIndicator(_block_sections[31]);
    _lever_frame->addSignalMapIndicator(_block_sections[31], 247.5);

    _signals[32] = new EWRB::ShuntSignal(32);
    _block_sections[32]->setBlockSignal(_signals[32]);                       // Edgware Road Westbound Wrong Dir. SIG. 32
    _block_sections[32]->setRequiredState(EWRB::SignalState::Off);           // Disc 2AT Signal
    _lever_frame->addSignalPanelIndicator(_block_sections[32]);
    _lever_frame->addShuntMapIndicator(_block_sections[32], 90);

    _signals[33] = new EWRB::Signal(33);
    _block_sections[33]->setBlockSignal(_signals[33]);                       // Edgware Road East Jct Feather Pos 1, 2 SIG. 33, 34, 35
    _block_sections[33]->setRequiredState(EWRB::SignalState::OffJctRight);   // Routed to Platform 3
    _lever_frame->addSignalPanelIndicator(_block_sections[33]);
    _block_sections[34]->setBlockSignal(_signals[33]);
    _block_sections[34]->setRequiredState(EWRB::SignalState::Off);           // Routed to Platform 2
    _lever_frame->addSignalPanelIndicator(_block_sections[34]);
    _block_sections[35]->setBlockSignal(_signals[33]);
    _block_sections[35]->setRequiredState(EWRB::SignalState::OffJctLeft);    // Routed to Platform 1
    _lever_frame->addSignalPanelIndicator(_block_sections[35]);
    _lever_frame->addCustomMapIndicator(new EWRB::EWRWestSignalIndicator(this, {_block_sections[34], _block_sections[35], _block_sections[33]}));

    _signals[36] = new EWRB::Signal(36);
    _block_sections[36]->setBlockSignal(_signals[36]);                       // Edgware Road Westbound Approach
    _block_sections[36]->setRequiredState(EWRB::SignalState::Off);           // Normal 2AT Signal
    _lever_frame->addSignalPanelIndicator(_block_sections[36]);
    _lever_frame->addSignalMapIndicator(_block_sections[36], 270);

    _signals[37] = new EWRB::Signal(37);
    _block_sections[37]->setBlockSignal(_signals[37]);                       // Praed St Jct Approach from HCL Paddington
    _block_sections[37]->setRequiredState(EWRB::SignalState::Off);           // Normal 2AT Signal
    _lever_frame->addSignalPanelIndicator(_block_sections[37]);
    _lever_frame->addSignalMapIndicator(_block_sections[37], 315);

    _signals[38] = new EWRB::Signal(38);
    _block_sections[38]->setBlockSignal(_signals[38]);                       // Praed St Jct Approach from HCL Paddington
    _block_sections[38]->setRequiredState(EWRB::SignalState::Off);           // Normal 2AT Signal
    _lever_frame->addSignalPanelIndicator(_block_sections[38]);
    _lever_frame->addSignalMapIndicator(_block_sections[38], 225);

    // OPX Controlled Signals

    _signals[39] = new EWRB::Signal(39);
    _block_sections[39]->setBlockSignal(_signals[39]);                       // Paddington HCL Depart
    _block_sections[39]->setRequiredState(EWRB::SignalState::Off);           // Disc 2AT Signal
    _lever_frame->addSignalMapIndicator(_block_sections[39], 270);

    _signals[40] = new EWRB::Signal(40);
    _block_sections[40]->setBlockSignal(_signals[40]);                       // Paddington DL Depart
    _block_sections[40]->setRequiredState(EWRB::SignalState::Off);           // Disc 2AT Signal
    _lever_frame->addSignalMapIndicator(_block_sections[40], 270);

    _lever_frame->placeSigIndicators();
    _lever_frame->placeMapIndicators();
}

void ERMainWindow::_lever_action(const int &i)
{
    if(_lever_frame->operator[](i)->isLocked())
    {
        _lever_failed->play();
        return;
    }
    _lever_frame->operator[](i)->moveLever();
    _lever_frame->update();
    _play_random_lever_sound();
}

ERMainWindow::~ERMainWindow()
{
    delete ui;
}
