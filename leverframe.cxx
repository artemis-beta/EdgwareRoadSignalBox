#include "leverframe.hxx"

EWRB::LeverFrame::LeverFrame(QWidget* parent)
{
    _parent = parent;
    _frame_svg = new QSvgWidget(QString(":/svgs/svgs/EWRBFrame.svg"), _parent);
    const Scaler* scaler_ = new Scaler;
    _frame_svg->setFixedSize(scaler_->screen_width(), scaler_->screen_height());
    track_circuits_ = TrackCircuits(parent);

    for(int i{1}; i < 13; ++i)
    {
        _levers[i] = new EWRB::HomeLever(i, _parent);
        _levers[i]->PlaceAt(scaler_->scale_width(22+(i-1)*24.1), 0.7*scaler_->screen_height());
        _levers[i]->showSVG();
    }
    for(int i{13}; i < 28; ++i)
    {
        if(i == 16)
        {
            _levers[i] = new EWRB::SpareLever(i, _parent);
        }
        else if(i == 24 || i == 25)
        {
            _levers[i] = new EWRB::EmergencySignalReleaseLever(i, _parent);
        }
        else
        {
            _levers[i] = new EWRB::PointsLever(i, _parent);
        }
        if(i != 16 && i != 18)
        {   _indicators[i] = new EWRB::PointsIndicator((EWRB::PointsLever*)_levers[i], _parent);
            _indicators[i]->PlaceAt(scaler_->scale_width(291+(i-12)*24.05), scaler_->scale_height(367));
        }
        _levers[i]->PlaceAt(scaler_->scale_width(22+(i-1)*24.1), 0.7*scaler_->screen_height());
        _levers[i]->showSVG();
    }

    for(int i{28}; i < 39; ++i)
    {
        _levers[i] = new EWRB::HomeLever(i, _parent);
        _levers[i]->PlaceAt(scaler_->scale_width(22+(i-1)*24.1), 0.7*scaler_->screen_height());
        _levers[i]->showSVG();
    }

    for(int i{1}; i < 8; ++i)
    {
        _lever_sounds.append(new QSoundEffect);
        _lever_sounds[i-1]->setSource(QUrl::fromLocalFile(":/audio/audio/lever_move_"+QString::number(i)+".wav"));
    }

    _lever_failed->setSource(QUrl::fromLocalFile(":/audio/audio/lever_fail.wav"));

    connect(_levers[13], SIGNAL(sendCurrentLeverDestination(EWRB::LeverState)), this, SLOT(updatePointsInd13(EWRB::LeverState)));
    connect(_levers[14], SIGNAL(sendCurrentLeverDestination(EWRB::LeverState)), this, SLOT(updatePointsInd14(EWRB::LeverState)));
    connect(_levers[15], SIGNAL(sendCurrentLeverDestination(EWRB::LeverState)), this, SLOT(updatePointsInd15(EWRB::LeverState)));
    connect(_levers[17], SIGNAL(sendCurrentLeverDestination(EWRB::LeverState)), this, SLOT(updatePointsInd17(EWRB::LeverState)));
    connect(_levers[19], SIGNAL(sendCurrentLeverDestination(EWRB::LeverState)), this, SLOT(updatePointsInd19(EWRB::LeverState)));
    connect(_levers[20], SIGNAL(sendCurrentLeverDestination(EWRB::LeverState)), this, SLOT(updatePointsInd20(EWRB::LeverState)));
    connect(_levers[21], SIGNAL(sendCurrentLeverDestination(EWRB::LeverState)), this, SLOT(updatePointsInd21(EWRB::LeverState)));
    connect(_levers[22], SIGNAL(sendCurrentLeverDestination(EWRB::LeverState)), this, SLOT(updatePointsInd22(EWRB::LeverState)));
    connect(_levers[23], SIGNAL(sendCurrentLeverDestination(EWRB::LeverState)), this, SLOT(updatePointsInd23(EWRB::LeverState)));
    connect(_levers[26], SIGNAL(sendCurrentLeverDestination(EWRB::LeverState)), this, SLOT(updatePointsInd26(EWRB::LeverState)));
    connect(_levers[27], SIGNAL(sendCurrentLeverDestination(EWRB::LeverState)), this, SLOT(updatePointsInd27(EWRB::LeverState)));


}

void EWRB::LeverFrame::_play_random_lever_sound()
{
    QSoundEffect* sound = _lever_sounds.at(qrand() % _lever_sounds.size());
    sound->play();
}

void EWRB::LeverFrame::updatePointsInd13(EWRB::LeverState state)
{
    _indicators[13]->setState((state == EWRB::LeverState::Off) ? EWRB::PointsState::Normal : EWRB::PointsState::Reverse);
    _indicators[13]->update();
}

void EWRB::LeverFrame::updatePointsInd14(EWRB::LeverState state)
{
    _indicators[14]->setState((state == EWRB::LeverState::Off) ? EWRB::PointsState::Normal : EWRB::PointsState::Reverse);
    _indicators[14]->update();
}

void EWRB::LeverFrame::updatePointsInd15(EWRB::LeverState state)
{
    _indicators[15]->setState((state == EWRB::LeverState::Off) ? EWRB::PointsState::Normal : EWRB::PointsState::Reverse);
    _indicators[15]->update();
}

void EWRB::LeverFrame::updatePointsInd17(EWRB::LeverState state)
{
    _indicators[17]->setState((state == EWRB::LeverState::Off) ? EWRB::PointsState::Normal : EWRB::PointsState::Reverse);
    _indicators[17]->update();
}

void EWRB::LeverFrame::updatePointsInd19(EWRB::LeverState state)
{
    _indicators[19]->setState((state == EWRB::LeverState::Off) ? EWRB::PointsState::Normal : EWRB::PointsState::Reverse);
    _indicators[19]->update();
}

void EWRB::LeverFrame::updatePointsInd20(EWRB::LeverState state)
{
    _indicators[20]->setState((state == EWRB::LeverState::Off) ? EWRB::PointsState::Normal : EWRB::PointsState::Reverse);
    _indicators[20]->update();
}

void EWRB::LeverFrame::updatePointsInd21(EWRB::LeverState state)
{
    _indicators[21]->setState((state == EWRB::LeverState::Off) ? EWRB::PointsState::Normal : EWRB::PointsState::Reverse);
    _indicators[21]->update();
}

void EWRB::LeverFrame::updatePointsInd22(EWRB::LeverState state)
{
    _indicators[22]->setState((state == EWRB::LeverState::Off) ? EWRB::PointsState::Normal : EWRB::PointsState::Reverse);
    _indicators[22]->update();
}

void EWRB::LeverFrame::updatePointsInd23(EWRB::LeverState state)
{
    _indicators[23]->setState((state == EWRB::LeverState::Off) ? EWRB::PointsState::Normal : EWRB::PointsState::Reverse);
    _indicators[23]->update();
}

void EWRB::LeverFrame::updatePointsInd26(EWRB::LeverState state)
{
    _indicators[26]->setState((state == EWRB::LeverState::Off) ? EWRB::PointsState::Normal : EWRB::PointsState::Reverse);
    _indicators[26]->update();
}

void EWRB::LeverFrame::updatePointsInd27(EWRB::LeverState state)
{
    _indicators[27]->setState((state == EWRB::LeverState::Off) ? EWRB::PointsState::Normal : EWRB::PointsState::Reverse);
    _indicators[27]->update();
}

void EWRB::LeverFrame::placeSigIndicators()
{
    const Scaler* scaler_ = new Scaler;
    for(int i{1}; i < 13; ++i)
    {
        if(i == 9) continue;
        _sig_indicators[i]->PlaceAt(scaler_->scale_width(24+(i-1)*24), scaler_->scale_height(363));
    }

    for(int i{28}; i < 39; ++i)
    {
        _sig_indicators[i]->PlaceAt(scaler_->scale_width(24+(i-1)*24), scaler_->scale_height(363));
    }
}

void EWRB::LeverFrame::placeTrackCircuitIndicators()
{
    track_circuits_["UF"]->SetSize(scaler_->scale_width(39), scaler_->scale_height(39));
    track_circuits_["UF"]->PlaceAt(scaler_->scale_width(157), scaler_->scale_height(159));
    track_circuits_["UH"]->SetSize(scaler_->scale_width(39), scaler_->scale_height(39));
    track_circuits_["UH"]->PlaceAt(scaler_->scale_width(177), scaler_->scale_height(160));
    track_circuits_["UJ"]->SetSize(scaler_->scale_width(34), scaler_->scale_height(37));
    track_circuits_["UJ"]->PlaceAt(scaler_->scale_width(204), scaler_->scale_height(157));
    track_circuits_["UK"]->SetSize(scaler_->scale_width(39), scaler_->scale_height(39));
    track_circuits_["UK"]->PlaceAt(scaler_->scale_width(227), scaler_->scale_height(159));
    track_circuits_["UL"]->SetSize(scaler_->scale_width(75), scaler_->scale_height(37));
    track_circuits_["UL"]->PlaceAt(scaler_->scale_width(256), scaler_->scale_height(160));
    track_circuits_["AA"]->SetSize(scaler_->scale_width(76), scaler_->scale_height(38));
    track_circuits_["AA"]->PlaceAt(scaler_->scale_width(318), scaler_->scale_height(152));
    track_circuits_["AB"]->SetSize(scaler_->scale_width(76), scaler_->scale_height(39));
    track_circuits_["AB"]->PlaceAt(scaler_->scale_width(390), scaler_->scale_height(136));
    track_circuits_["AC"]->SetSize(scaler_->scale_width(112), scaler_->scale_height(40));
    track_circuits_["AC"]->PlaceAt(scaler_->scale_width(441), scaler_->scale_height(136));
    track_circuits_["AD"]->SetSize(scaler_->scale_width(39), scaler_->scale_height(39));
    track_circuits_["AD"]->PlaceAt(scaler_->scale_width(531), scaler_->scale_height(135));
    track_circuits_["AL"]->SetSize(scaler_->scale_width(74), scaler_->scale_height(57));
    track_circuits_["AL"]->PlaceAt(scaler_->scale_width(543), scaler_->scale_height(122.5));
    track_circuits_["AM"]->SetSize(scaler_->scale_width(39), scaler_->scale_height(40));
    track_circuits_["AM"]->PlaceAt(scaler_->scale_width(604), scaler_->scale_height(157));
    track_circuits_["AK"]->SetSize(scaler_->scale_width(55), scaler_->scale_height(42));
    track_circuits_["AK"]->PlaceAt(scaler_->scale_width(552), scaler_->scale_height(160));
    track_circuits_["AJ"]->SetSize(scaler_->scale_width(57), scaler_->scale_height(43));
    track_circuits_["AJ"]->PlaceAt(scaler_->scale_width(505), scaler_->scale_height(157));
    track_circuits_["CA"]->SetSize(scaler_->scale_width(152), scaler_->scale_height(39));
    track_circuits_["CA"]->PlaceAt(scaler_->scale_width(421), scaler_->scale_height(114));
    track_circuits_["UL"]->SetState(TrackCircuitStatus::Occupied);
    track_circuits_["AO"]->SetSize(scaler_->scale_width(75), scaler_->scale_height(39));
    track_circuits_["AO"]->PlaceAt(scaler_->scale_width(637), scaler_->scale_height(160));
    track_circuits_["AP"]->SetSize(scaler_->scale_width(38), scaler_->scale_height(39));
    track_circuits_["AP"]->PlaceAt(scaler_->scale_width(704), scaler_->scale_height(160));
    track_circuits_["AQ_AS"]->SetSize(scaler_->scale_width(77), scaler_->scale_height(76));
    track_circuits_["AQ_AS"]->PlaceAt(scaler_->scale_width(720), scaler_->scale_height(116));
    track_circuits_["AE"]->SetSize(scaler_->scale_width(79), scaler_->scale_height(41));
    track_circuits_["AE"]->PlaceAt(scaler_->scale_width(368), scaler_->scale_height(160));
    track_circuits_["AF"]->SetSize(scaler_->scale_width(39), scaler_->scale_height(40));
    track_circuits_["AF"]->PlaceAt(scaler_->scale_width(434), scaler_->scale_height(157));
    track_circuits_["AG"]->SetSize(scaler_->scale_width(75), scaler_->scale_height(41));
    track_circuits_["AG"]->PlaceAt(scaler_->scale_width(454), scaler_->scale_height(158));
    track_circuits_["AV"]->SetSize(scaler_->scale_width(38), scaler_->scale_height(39));
    track_circuits_["AV"]->PlaceAt(scaler_->scale_width(723), scaler_->scale_height(168));
    track_circuits_["177_B"]->SetSize(scaler_->scale_width(37), scaler_->scale_height(38));
    track_circuits_["177_B"]->PlaceAt(scaler_->scale_width(739), scaler_->scale_height(157));
    track_circuits_["177_A_175_B"]->SetSize(scaler_->scale_width(38), scaler_->scale_height(39));
    track_circuits_["177_A_175_B"]->PlaceAt(scaler_->scale_width(756), scaler_->scale_height(141));
    track_circuits_["175_A_173"]->SetSize(scaler_->scale_width(72), scaler_->scale_height(39));
    track_circuits_["175_A_173"]->PlaceAt(scaler_->scale_width(775), scaler_->scale_height(135));
    track_circuits_["AX_AY_AZ"]->SetSize(scaler_->scale_width(75), scaler_->scale_height(37));
    track_circuits_["AX_AY_AZ"]->PlaceAt(scaler_->scale_width(735 ), scaler_->scale_height(188));
    track_circuits_["133"]->SetSize(scaler_->scale_width(35), scaler_->scale_height(37));
    track_circuits_["133"]->PlaceAt(scaler_->scale_width(725), scaler_->scale_height(190));
    track_circuits_["129_A"]->SetSize(scaler_->scale_width(39), scaler_->scale_height(38));
    track_circuits_["129_A"]->PlaceAt(scaler_->scale_width(795), scaler_->scale_height(218));
    track_circuits_["131_A_129_B"]->SetSize(scaler_->scale_width(37), scaler_->scale_height(39));
    track_circuits_["131_A_129_B"]->PlaceAt(scaler_->scale_width(765), scaler_->scale_height(216));
    track_circuits_["131_BC"]->SetSize(scaler_->scale_width(39), scaler_->scale_height(39));
    track_circuits_["131_BC"]->PlaceAt(scaler_->scale_width(738), scaler_->scale_height(203));
    track_circuits_["BA"]->SetSize(scaler_->scale_width(38), scaler_->scale_height(38));
    track_circuits_["BA"]->PlaceAt(scaler_->scale_width(702), scaler_->scale_height(177));
    track_circuits_["BB"]->SetSize(scaler_->scale_width(36), scaler_->scale_height(37));
    track_circuits_["BB"]->PlaceAt(scaler_->scale_width(678), scaler_->scale_height(177));
    track_circuits_["BC"]->SetSize(scaler_->scale_width(39), scaler_->scale_height(36));
    track_circuits_["BC"]->PlaceAt(scaler_->scale_width(653), scaler_->scale_height(180));
    track_circuits_["BD"]->SetSize(scaler_->scale_width(112), scaler_->scale_height(38));
    track_circuits_["BD"]->PlaceAt(scaler_->scale_width(559), scaler_->scale_height(184));
    track_circuits_["BL"]->SetSize(scaler_->scale_width(77), scaler_->scale_height(38));
    track_circuits_["BL"]->PlaceAt(scaler_->scale_width(544), scaler_->scale_height(171));
    track_circuits_["BM"]->SetSize(scaler_->scale_width(75), scaler_->scale_height(40));
    track_circuits_["BM"]->PlaceAt(scaler_->scale_width(485), scaler_->scale_height(176));
    track_circuits_["BN"]->SetSize(scaler_->scale_width(75), scaler_->scale_height(40));
    track_circuits_["BN"]->PlaceAt(scaler_->scale_width(429), scaler_->scale_height(176));
    track_circuits_["BP"]->SetSize(scaler_->scale_width(76), scaler_->scale_height(41));
    track_circuits_["BP"]->PlaceAt(scaler_->scale_width(372), scaler_->scale_height(176));
    track_circuits_["BQ"]->SetSize(scaler_->scale_width(75), scaler_->scale_height(38));
    track_circuits_["BQ"]->PlaceAt(scaler_->scale_width(320), scaler_->scale_height(178));
    track_circuits_["BV_BT_BR"]->SetSize(scaler_->scale_width(152), scaler_->scale_height(38));
    track_circuits_["BV_BT_BR"]->PlaceAt(scaler_->scale_width(196), scaler_->scale_height(175));
    track_circuits_["BJ"]->SetSize(scaler_->scale_width(77), scaler_->scale_height(37));
    track_circuits_["BJ"]->PlaceAt(scaler_->scale_width(370), scaler_->scale_height(195));
    track_circuits_["BH"]->SetSize(scaler_->scale_width(75), scaler_->scale_height(37));
    track_circuits_["BH"]->PlaceAt(scaler_->scale_width(427), scaler_->scale_height(200));
    track_circuits_["BE"]->SetSize(scaler_->scale_width(94), scaler_->scale_height(38));
    track_circuits_["BE"]->PlaceAt(scaler_->scale_width(479), scaler_->scale_height(199));
}

void EWRB::LeverFrame::placeMapIndicators()
{
    _map_indicators[1]->PlaceAt(scaler_->scale_width(243), scaler_->scale_height(159));
    _map_indicators[2]->PlaceAt(scaler_->scale_width(302), scaler_->scale_height(159));
    _map_indicators[4]->PlaceAt(scaler_->scale_width(359), scaler_->scale_height(154));
    _map_indicators[5]->PlaceAt(scaler_->scale_width(548), scaler_->scale_height(196));
    _map_indicators[6]->PlaceAt(scaler_->scale_width(548), scaler_->scale_height(160));
    _map_indicators[7]->PlaceAt(scaler_->scale_width(548), scaler_->scale_height(137));
    _map_indicators[8]->PlaceAt(scaler_->scale_width(302), scaler_->scale_height(201));
    _map_indicators[10]->PlaceAt(scaler_->scale_width(542), scaler_->scale_height(120));
    _map_indicators[11]->PlaceAt(scaler_->scale_width(695), scaler_->scale_height(161));
    _map_indicators[28]->PlaceAt(scaler_->scale_width(413), scaler_->scale_height(160));
    _map_indicators[29]->PlaceAt(scaler_->scale_width(413), scaler_->scale_height(196));
    _map_indicators[30]->PlaceAt(scaler_->scale_width(413), scaler_->scale_height(218));
    _map_indicators[31]->PlaceAt(scaler_->scale_width(585), scaler_->scale_height(205));
    _map_indicators[32]->PlaceAt(scaler_->scale_width(645), scaler_->scale_height(164));
    _map_indicators[33]->PlaceAt(scaler_->scale_width(633), scaler_->scale_height(196));
    _map_indicators[36]->PlaceAt(scaler_->scale_width(685), scaler_->scale_height(196));
    _map_indicators[37]->PlaceAt(scaler_->scale_width(739), scaler_->scale_height(196));
    _map_indicators[38]->PlaceAt(scaler_->scale_width(754), scaler_->scale_height(169));
    _map_indicators[39]->PlaceAt(scaler_->scale_width(789), scaler_->scale_height(238));
    _map_indicators[40]->PlaceAt(scaler_->scale_width(791), scaler_->scale_height(155));
}

void EWRB::LeverFrame::placeDescribers()
{
    const int start_x = 36;
    const int start_y = 97;

    addTrainDescriber(3, "W", scaler_->scale_width(start_x+2* 13), scaler_->scale_height(start_y+0*6));
    addTrainDescriber(6, "W", scaler_->scale_width(start_x+5* 13), scaler_->scale_height(start_y+0*6));
    addTrainDescriber(7, "W", scaler_->scale_width(start_x+0* 13), scaler_->scale_height(start_y+1*6));
    addTrainDescriber(8, "W", scaler_->scale_width(start_x+1* 13), scaler_->scale_height(start_y+1*6));
    addTrainDescriber(9, "W", scaler_->scale_width(start_x+2* 13), scaler_->scale_height(start_y+1*6));
    addTrainDescriber(10, "W", scaler_->scale_width(start_x+3* 13), scaler_->scale_height(start_y+1*6));

    addTrainDescriber(13, "W", scaler_->scale_width(start_x+0* 13), scaler_->scale_height(start_y+5*6));
    addTrainDescriber(14, "W", scaler_->scale_width(start_x+1* 13), scaler_->scale_height(start_y+5*6));
    addTrainDescriber(15, "W", scaler_->scale_width(start_x+2* 13), scaler_->scale_height(start_y+5*6));
    addTrainDescriber(16, "W", scaler_->scale_width(start_x+3* 13), scaler_->scale_height(start_y+5*6));
    addTrainDescriber(17, "W", scaler_->scale_width(start_x+4* 13), scaler_->scale_height(start_y+5*6));
    addTrainDescriber(18, "W", scaler_->scale_width(start_x+5* 13), scaler_->scale_height(start_y+5*6));
    addTrainDescriber(19, "W", scaler_->scale_width(start_x+0* 13), scaler_->scale_height(start_y+6*6));
    addTrainDescriber(20, "W", scaler_->scale_width(start_x+1* 13), scaler_->scale_height(start_y+6*6));
    addTrainDescriber(21, "W", scaler_->scale_width(start_x+2* 13), scaler_->scale_height(start_y+6*6));
    addTrainDescriber(22, "W", scaler_->scale_width(start_x+3* 13), scaler_->scale_height(start_y+6*6));
    addTrainDescriber(23, "W", scaler_->scale_width(start_x+4* 13), scaler_->scale_height(start_y+6*6));
    addTrainDescriber(24, "W", scaler_->scale_width(start_x+5* 13), scaler_->scale_height(start_y+6*6));
    addTrainDescriber(25, "W", scaler_->scale_width(start_x+0* 13), scaler_->scale_height(start_y+7*6));
    addTrainDescriber(26, "W", scaler_->scale_width(start_x+1* 13), scaler_->scale_height(start_y+7*6));
    addTrainDescriber(27, "W", scaler_->scale_width(start_x+2* 13), scaler_->scale_height(start_y+7*6));
    addTrainDescriber(28, "W", scaler_->scale_width(start_x+3* 13), scaler_->scale_height(start_y+7*6));
    addTrainDescriber(29, "W", scaler_->scale_width(start_x+4* 13), scaler_->scale_height(start_y+7*6));
    addTrainDescriber(30, "W", scaler_->scale_width(start_x+5* 13), scaler_->scale_height(start_y+7*6));

    addTrainDescriber(31, "W", scaler_->scale_width(start_x+0* 13), scaler_->scale_height(start_y+11*6));
    addTrainDescriber(32, "W", scaler_->scale_width(start_x+1* 13), scaler_->scale_height(start_y+11*6));
    addTrainDescriber(33, "W", scaler_->scale_width(start_x+2* 13), scaler_->scale_height(start_y+11*6));
    addTrainDescriber(34, "W", scaler_->scale_width(start_x+3* 13), scaler_->scale_height(start_y+11*6));
    addTrainDescriber(35, "W", scaler_->scale_width(start_x+4* 13), scaler_->scale_height(start_y+11*6));
    addTrainDescriber(36, "W", scaler_->scale_width(start_x+5* 13), scaler_->scale_height(start_y+11*6));
    addTrainDescriber(37, "W", scaler_->scale_width(start_x+0* 13), scaler_->scale_height(start_y+12*6));
    addTrainDescriber(38, "W", scaler_->scale_width(start_x+1* 13), scaler_->scale_height(start_y+12*6));
    addTrainDescriber(39, "W", scaler_->scale_width(start_x+2* 13), scaler_->scale_height(start_y+12*6));
    addTrainDescriber(40, "W", scaler_->scale_width(start_x+3* 13), scaler_->scale_height(start_y+12*6));
    addTrainDescriber(41, "W", scaler_->scale_width(start_x+4* 13), scaler_->scale_height(start_y+12*6));
    addTrainDescriber(42, "W", scaler_->scale_width(start_x+5* 13), scaler_->scale_height(start_y+12*6));
    addTrainDescriber(43, "W", scaler_->scale_width(start_x+0* 13), scaler_->scale_height(start_y+13*6));
    addTrainDescriber(44, "C", scaler_->scale_width(start_x+1* 13), scaler_->scale_height(start_y+13*6));
    addTrainDescriber(45, "W", scaler_->scale_width(start_x+2* 13), scaler_->scale_height(start_y+13*6));
    addTrainDescriber(46, "W", scaler_->scale_width(start_x+3* 13), scaler_->scale_height(start_y+13*6));
    addTrainDescriber(47, "W", scaler_->scale_width(start_x+4* 13), scaler_->scale_height(start_y+13*6));
    addTrainDescriber(48, "W", scaler_->scale_width(start_x+5* 13), scaler_->scale_height(start_y+13*6));

    addTrainDescriber(49, "W", scaler_->scale_width(start_x+0* 13), scaler_->scale_height(start_y+17*6));
    addTrainDescriber(50, "W", scaler_->scale_width(start_x+1* 13), scaler_->scale_height(start_y+17*6));
    addTrainDescriber(51, "W", scaler_->scale_width(start_x+2* 13), scaler_->scale_height(start_y+17*6));
    addTrainDescriber(52, "W", scaler_->scale_width(start_x+3* 13), scaler_->scale_height(start_y+17*6));
    addTrainDescriber(53, "W", scaler_->scale_width(start_x+4* 13), scaler_->scale_height(start_y+17*6));
    addTrainDescriber(54, "W", scaler_->scale_width(start_x+5* 13), scaler_->scale_height(start_y+17*6));
    addTrainDescriber(55, "W", scaler_->scale_width(start_x+0* 13), scaler_->scale_height(start_y+18*6));
    addTrainDescriber(56, "W", scaler_->scale_width(start_x+1* 13), scaler_->scale_height(start_y+18*6));
    addTrainDescriber(57, "W", scaler_->scale_width(start_x+2* 13), scaler_->scale_height(start_y+18*6));
    addTrainDescriber(58, "W", scaler_->scale_width(start_x+3* 13), scaler_->scale_height(start_y+18*6));
    addTrainDescriber(59, "W", scaler_->scale_width(start_x+4* 13), scaler_->scale_height(start_y+18*6));
    addTrainDescriber(60, "W", scaler_->scale_width(start_x+5* 13), scaler_->scale_height(start_y+18*6));
    addTrainDescriber(61, "W", scaler_->scale_width(start_x+0* 13), scaler_->scale_height(start_y+19*6));
    addTrainDescriber(62, "W", scaler_->scale_width(start_x+1* 13), scaler_->scale_height(start_y+19*6));
    addTrainDescriber(64, "W", scaler_->scale_width(start_x+3* 13), scaler_->scale_height(start_y+19*6));
    addTrainDescriber(65, "W", scaler_->scale_width(start_x+4* 13), scaler_->scale_height(start_y+19*6));
    addTrainDescriber(66, "W", scaler_->scale_width(start_x+5* 13), scaler_->scale_height(start_y+19*6));
    addTrainDescriber(67, "W", scaler_->scale_width(start_x+0* 13), scaler_->scale_height(start_y+23*6));
    addTrainDescriber(68, "W", scaler_->scale_width(start_x+1* 13), scaler_->scale_height(start_y+23*6));
    addTrainDescriber(69, "W", scaler_->scale_width(start_x+2* 13), scaler_->scale_height(start_y+23*6));
    addTrainDescriber(70, "W", scaler_->scale_width(start_x+3* 13), scaler_->scale_height(start_y+23*6));
    addTrainDescriber(71, "W", scaler_->scale_width(start_x+4* 13), scaler_->scale_height(start_y+23*6));
    addTrainDescriber(72, "W", scaler_->scale_width(start_x+5* 13), scaler_->scale_height(start_y+23*6));
    addTrainDescriber(73, "W", scaler_->scale_width(start_x+0* 13), scaler_->scale_height(start_y+24*6));
    addTrainDescriber(74, "W", scaler_->scale_width(start_x+1* 13), scaler_->scale_height(start_y+24*6));
    addTrainDescriber(75, "W", scaler_->scale_width(start_x+2* 13), scaler_->scale_height(start_y+24*6));
    addTrainDescriber(76, "W", scaler_->scale_width(start_x+3* 13), scaler_->scale_height(start_y+24*6));
    addTrainDescriber(77, "W", scaler_->scale_width(start_x+4* 13), scaler_->scale_height(start_y+24*6));
    addTrainDescriber(78, "W", scaler_->scale_width(start_x+5* 13), scaler_->scale_height(start_y+24*6));
    addTrainDescriber(79, "HM", scaler_->scale_width(start_x+0* 13), scaler_->scale_height(start_y+25*6));
    addTrainDescriber(80, "W", scaler_->scale_width(start_x+1* 13), scaler_->scale_height(start_y+25*6));
    addTrainDescriber(82, "W", scaler_->scale_width(start_x+3* 13), scaler_->scale_height(start_y+25*6));
    addTrainDescriber(83, "W", scaler_->scale_width(start_x+4* 13), scaler_->scale_height(start_y+25*6));
    addTrainDescriber(84, "W", scaler_->scale_width(start_x+5* 13), scaler_->scale_height(start_y+25*6));
}

void EWRB::LeverFrame::update(const int& i)
{
    qDebug() << "Running Frame Update...";

    int signal_id = i;

    if(i == 3) signal_id = 2;
    else if (i == 34 || i == 35) signal_id = 33;
    else if (i == 12) signal_id = 11;

    if(i == -1)
    {

        for(auto si : _sig_indicators)
        {
            si->update();
        }

        for(auto mi : _map_indicators)
        {
            mi->update();
        }
    }

    else
    {
        if(_map_indicators.contains(signal_id))
        {
            _map_indicators[signal_id]->update();
        }
        if(_sig_indicators.contains(i))_sig_indicators[i]->update();
    }

    for(const auto& tc : track_circuits_) {
        tc->update();
    }
}
