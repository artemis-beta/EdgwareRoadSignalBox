#include "leverframe.hxx"

EWRB::LeverFrame::LeverFrame(QWidget* parent)
{
    _parent = parent;
    _frame_svg = new QSvgWidget(QString(":/svgs/svgs/EWRBFrame.svg"), _parent);
    const QScreen *screen_ = QGuiApplication::primaryScreen();
    const QRect screen_size_ = screen_->geometry();
    const int height_ = screen_size_.height()*0.98;
    const int width_ = (1020./600.)*height_;
    _frame_svg->setFixedSize(width_, height_);

    for(int i{1}; i < 13; ++i)
    {
        _levers[i] = new EWRB::HomeLever(i, _parent);
        _levers[i]->PlaceAt((width_/1020.)*(22+(i-1)*24.1), 0.7*height_);
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
            _indicators[i]->PlaceAt((width_/1020.)*(291+(i-12)*24.05), (height_/600.)*367);
        }
        _levers[i]->PlaceAt((width_/1020.)*(22+(i-1)*24.1), 0.7*height_);
        _levers[i]->showSVG();
    }

    for(int i{28}; i < 39; ++i)
    {
        _levers[i] = new EWRB::HomeLever(i, _parent);
        _levers[i]->PlaceAt((width_/1020.)*(22+(i-1)*24.1), 0.7*height_);
        _levers[i]->showSVG();
    }

    for(int i{1}; i < 9; ++i)
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
    const QScreen *screen_ = QGuiApplication::primaryScreen();
    const QRect screen_size_ = screen_->geometry();
    const int height_ = screen_size_.height()*0.98;
    const int width_ = (1020./600.)*height_;
    for(int i{1}; i < 13; ++i)
    {
        if(i == 9) continue;
        _sig_indicators[i]->PlaceAt((width_/1020.)*(24+(i-1)*24),(height_/600.)*363);
    }

    for(int i{28}; i < 39; ++i)
    {
        _sig_indicators[i]->PlaceAt((width_/1020.)*(24+(i-1)*24),(height_/600.)*363);
    }
}

void EWRB::LeverFrame::placeMapIndicators()
{
    const QScreen *screen_ = QGuiApplication::primaryScreen();
    const QRect screen_size_ = screen_->geometry();
    const int height_ = screen_size_.height()*0.98;
    const int width_ = (1020./600.)*height_;
    _map_indicators[1]->PlaceAt((width_/1020.)*243, (height_/600.)*159);
    _map_indicators[2]->PlaceAt((width_/1020.)*302, (height_/600.)*159);
    _map_indicators[4]->PlaceAt((width_/1020.)*359, (height_/600.)*154);
    _map_indicators[5]->PlaceAt((width_/1020.)*548, (height_/600.)*196);
    _map_indicators[6]->PlaceAt((width_/1020.)*548, (height_/600.)*160);
    _map_indicators[7]->PlaceAt((width_/1020.)*548, (height_/600.)*137);
    _map_indicators[8]->PlaceAt((width_/1020.)*302, (height_/600.)*201);
    _map_indicators[10]->PlaceAt((width_/1020.)*542, (height_/600.)*120);
    _map_indicators[11]->PlaceAt((width_/1020.)*695, (height_/600.)*161);
    _map_indicators[28]->PlaceAt((width_/1020.)*413, (height_/600.)*160);
    _map_indicators[29]->PlaceAt((width_/1020.)*413, (height_/600.)*196);
    _map_indicators[30]->PlaceAt((width_/1020.)*413, (height_/600.)*218);
    _map_indicators[31]->PlaceAt((width_/1020.)*585, (height_/600.)*205);
    _map_indicators[32]->PlaceAt((width_/1020.)*645, (height_/600.)*164);
    _map_indicators[33]->PlaceAt((width_/1020.)*633, (height_/600.)*196);
    _map_indicators[36]->PlaceAt((width_/1020.)*685, (height_/600.)*196);
    _map_indicators[37]->PlaceAt((width_/1020.)*739, (height_/600.)*196);
    _map_indicators[38]->PlaceAt((width_/1020.)*754, (height_/600.)*169);
    _map_indicators[39]->PlaceAt((width_/1020.)*789, (height_/600.)*238);
    _map_indicators[40]->PlaceAt((width_/1020.)*791, (height_/600.)*155);
}

void EWRB::LeverFrame::placeDescribers()
{
    const QScreen *screen_ = QGuiApplication::primaryScreen();
    const QRect screen_size_ = screen_->geometry();
    const int height_ = screen_size_.height()*0.98;
    const int width_ = (1020./600.)*height_;
    const int start_x = 36;
    const int start_y = 97;

    addTrainDescriber(3, "W", (width_/1020.)*(start_x+2* 13), (height_/600.)*(start_y+0*6));
    addTrainDescriber(6, "W", (width_/1020.)*(start_x+5* 13), (height_/600.)*(start_y+0*6));
    addTrainDescriber(7, "W", (width_/1020.)*(start_x+0* 13), (height_/600.)*(start_y+1*6));
    addTrainDescriber(8, "W", (width_/1020.)*(start_x+1* 13), (height_/600.)*(start_y+1*6));
    addTrainDescriber(9, "W", (width_/1020.)*(start_x+2* 13), (height_/600.)*(start_y+1*6));
    addTrainDescriber(10, "W", (width_/1020.)*(start_x+3* 13), (height_/600.)*(start_y+1*6));

    addTrainDescriber(13, "W", (width_/1020.)*(start_x+0* 13), (height_/600.)*(start_y+5*6));
    addTrainDescriber(14, "W", (width_/1020.)*(start_x+1* 13), (height_/600.)*(start_y+5*6));
    addTrainDescriber(15, "W", (width_/1020.)*(start_x+2* 13), (height_/600.)*(start_y+5*6));
    addTrainDescriber(16, "W", (width_/1020.)*(start_x+3* 13), (height_/600.)*(start_y+5*6));
    addTrainDescriber(17, "W", (width_/1020.)*(start_x+4* 13), (height_/600.)*(start_y+5*6));
    addTrainDescriber(18, "W", (width_/1020.)*(start_x+5* 13), (height_/600.)*(start_y+5*6));
    addTrainDescriber(19, "W", (width_/1020.)*(start_x+0* 13), (height_/600.)*(start_y+6*6));
    addTrainDescriber(20, "W", (width_/1020.)*(start_x+1* 13), (height_/600.)*(start_y+6*6));
    addTrainDescriber(21, "W", (width_/1020.)*(start_x+2* 13), (height_/600.)*(start_y+6*6));
    addTrainDescriber(22, "W", (width_/1020.)*(start_x+3* 13), (height_/600.)*(start_y+6*6));
    addTrainDescriber(23, "W", (width_/1020.)*(start_x+4* 13), (height_/600.)*(start_y+6*6));
    addTrainDescriber(24, "W", (width_/1020.)*(start_x+5* 13), (height_/600.)*(start_y+6*6));
    addTrainDescriber(25, "W", (width_/1020.)*(start_x+0* 13), (height_/600.)*(start_y+7*6));
    addTrainDescriber(26, "W", (width_/1020.)*(start_x+1* 13), (height_/600.)*(start_y+7*6));
    addTrainDescriber(27, "W", (width_/1020.)*(start_x+2* 13), (height_/600.)*(start_y+7*6));
    addTrainDescriber(28, "W", (width_/1020.)*(start_x+3* 13), (height_/600.)*(start_y+7*6));
    addTrainDescriber(29, "W", (width_/1020.)*(start_x+4* 13), (height_/600.)*(start_y+7*6));
    addTrainDescriber(30, "W", (width_/1020.)*(start_x+5* 13), (height_/600.)*(start_y+7*6));

    addTrainDescriber(31, "W", (width_/1020.)*(start_x+0* 13), (height_/600.)*(start_y+11*6));
    addTrainDescriber(32, "W", (width_/1020.)*(start_x+1* 13), (height_/600.)*(start_y+11*6));
    addTrainDescriber(33, "W", (width_/1020.)*(start_x+2* 13), (height_/600.)*(start_y+11*6));
    addTrainDescriber(34, "W", (width_/1020.)*(start_x+3* 13), (height_/600.)*(start_y+11*6));
    addTrainDescriber(35, "W", (width_/1020.)*(start_x+4* 13), (height_/600.)*(start_y+11*6));
    addTrainDescriber(36, "W", (width_/1020.)*(start_x+5* 13), (height_/600.)*(start_y+11*6));
    addTrainDescriber(37, "W", (width_/1020.)*(start_x+0* 13), (height_/600.)*(start_y+12*6));
    addTrainDescriber(38, "W", (width_/1020.)*(start_x+1* 13), (height_/600.)*(start_y+12*6));
    addTrainDescriber(39, "W", (width_/1020.)*(start_x+2* 13), (height_/600.)*(start_y+12*6));
    addTrainDescriber(40, "W", (width_/1020.)*(start_x+3* 13), (height_/600.)*(start_y+12*6));
    addTrainDescriber(41, "W", (width_/1020.)*(start_x+4* 13), (height_/600.)*(start_y+12*6));
    addTrainDescriber(42, "W", (width_/1020.)*(start_x+5* 13), (height_/600.)*(start_y+12*6));
    addTrainDescriber(43, "W", (width_/1020.)*(start_x+0* 13), (height_/600.)*(start_y+13*6));
    addTrainDescriber(44, "C", (width_/1020.)*(start_x+1* 13), (height_/600.)*(start_y+13*6));
    addTrainDescriber(45, "W", (width_/1020.)*(start_x+2* 13), (height_/600.)*(start_y+13*6));
    addTrainDescriber(46, "W", (width_/1020.)*(start_x+3* 13), (height_/600.)*(start_y+13*6));
    addTrainDescriber(47, "W", (width_/1020.)*(start_x+4* 13), (height_/600.)*(start_y+13*6));
    addTrainDescriber(48, "W", (width_/1020.)*(start_x+5* 13), (height_/600.)*(start_y+13*6));

    addTrainDescriber(49, "W", (width_/1020.)*(start_x+0* 13), (height_/600.)*(start_y+17*6));
    addTrainDescriber(50, "W", (width_/1020.)*(start_x+1* 13), (height_/600.)*(start_y+17*6));
    addTrainDescriber(51, "W", (width_/1020.)*(start_x+2* 13), (height_/600.)*(start_y+17*6));
    addTrainDescriber(52, "W", (width_/1020.)*(start_x+3* 13), (height_/600.)*(start_y+17*6));
    addTrainDescriber(53, "W", (width_/1020.)*(start_x+4* 13), (height_/600.)*(start_y+17*6));
    addTrainDescriber(54, "W", (width_/1020.)*(start_x+5* 13), (height_/600.)*(start_y+17*6));
    addTrainDescriber(55, "W", (width_/1020.)*(start_x+0* 13), (height_/600.)*(start_y+18*6));
    addTrainDescriber(56, "W", (width_/1020.)*(start_x+1* 13), (height_/600.)*(start_y+18*6));
    addTrainDescriber(57, "W", (width_/1020.)*(start_x+2* 13), (height_/600.)*(start_y+18*6));
    addTrainDescriber(58, "W", (width_/1020.)*(start_x+3* 13), (height_/600.)*(start_y+18*6));
    addTrainDescriber(59, "W", (width_/1020.)*(start_x+4* 13), (height_/600.)*(start_y+18*6));
    addTrainDescriber(60, "W", (width_/1020.)*(start_x+5* 13), (height_/600.)*(start_y+18*6));
    addTrainDescriber(61, "W", (width_/1020.)*(start_x+0* 13), (height_/600.)*(start_y+19*6));
    addTrainDescriber(62, "W", (width_/1020.)*(start_x+1* 13), (height_/600.)*(start_y+19*6));
    addTrainDescriber(64, "W", (width_/1020.)*(start_x+3* 13), (height_/600.)*(start_y+19*6));
    addTrainDescriber(65, "W", (width_/1020.)*(start_x+4* 13), (height_/600.)*(start_y+19*6));
    addTrainDescriber(66, "W", (width_/1020.)*(start_x+5* 13), (height_/600.)*(start_y+19*6));

    addTrainDescriber(67, "W", (width_/1020.)*(start_x+0* 13), (height_/600.)*(start_y+23*6));
    addTrainDescriber(68, "W", (width_/1020.)*(start_x+1* 13), (height_/600.)*(start_y+23*6));
    addTrainDescriber(69, "W", (width_/1020.)*(start_x+2* 13), (height_/600.)*(start_y+23*6));
    addTrainDescriber(70, "W", (width_/1020.)*(start_x+3* 13), (height_/600.)*(start_y+23*6));
    addTrainDescriber(71, "W", (width_/1020.)*(start_x+4* 13), (height_/600.)*(start_y+23*6));
    addTrainDescriber(72, "W", (width_/1020.)*(start_x+5* 13), (height_/600.)*(start_y+23*6));
    addTrainDescriber(73, "W", (width_/1020.)*(start_x+0* 13), (height_/600.)*(start_y+24*6));
    addTrainDescriber(74, "W", (width_/1020.)*(start_x+1* 13), (height_/600.)*(start_y+24*6));
    addTrainDescriber(75, "W", (width_/1020.)*(start_x+2* 13), (height_/600.)*(start_y+24*6));
    addTrainDescriber(76, "W", (width_/1020.)*(start_x+3* 13), (height_/600.)*(start_y+24*6));
    addTrainDescriber(77, "W", (width_/1020.)*(start_x+4* 13), (height_/600.)*(start_y+24*6));
    addTrainDescriber(78, "W", (width_/1020.)*(start_x+5* 13), (height_/600.)*(start_y+24*6));
    addTrainDescriber(79, "HM", (width_/1020.)*(start_x+0* 13), (height_/600.)*(start_y+25*6));
    addTrainDescriber(80, "W", (width_/1020.)*(start_x+1* 13), (height_/600.)*(start_y+25*6));
    addTrainDescriber(82, "W", (width_/1020.)*(start_x+3* 13), (height_/600.)*(start_y+25*6));
    addTrainDescriber(83, "W", (width_/1020.)*(start_x+4* 13), (height_/600.)*(start_y+25*6));
    addTrainDescriber(84, "W", (width_/1020.)*(start_x+5* 13), (height_/600.)*(start_y+25*6));
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
}
