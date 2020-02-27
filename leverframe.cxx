#include "leverframe.hxx"

EWRB::LeverFrame::LeverFrame(QWidget* parent)
{
    _parent = parent;
    _frame_svg = new QSvgWidget(QString(":/svgs/svgs/EWRBFrame.svg"), _parent);
    _frame_svg->setFixedSize(1020, 760);

    for(int i{1}; i < 13; ++i)
    {
        _levers[i] = new EWRB::HomeLever(_parent);
        _levers[i]->PlaceAt(22+(i-1)*24.1, 620);
        _levers[i]->showSVG();
    }
    for(int i{13}; i < 28; ++i)
    {
        if(i == 16)
        {
            _levers[i] = new EWRB::SpareLever(_parent);
        }
        else if(i == 24 || i == 25)
        {
            _levers[i] = new EWRB::EmergencySignalReleaseLever(_parent);
        }
        else
        {
            _levers[i] = new EWRB::PointsLever(_parent);
        }
        if(i != 16 && i != 18)
        {   _indicators[i] = new EWRB::PointsIndicator((EWRB::PointsLever*)_levers[i], _parent);
            _indicators[i]->PlaceAt(291+(i-12)*24.05, 566);
        }
        _levers[i]->PlaceAt(22+(i-1)*24.1, 620);
        _levers[i]->showSVG();
    }

    for(int i{28}; i < 39; ++i)
    {
        _levers[i] = new EWRB::HomeLever(_parent);
        _levers[i]->PlaceAt(22+(i-1)*24.1, 620);
        _levers[i]->showSVG();
    }

    for(int i{1}; i < 9; ++i)
    {
        _lever_sounds.append(new QSoundEffect);
        _lever_sounds[i-1]->setSource(QUrl::fromLocalFile(":/audio/audio/lever_move_"+QString::number(i)+".wav"));
    }
}

void EWRB::LeverFrame::_play_random_lever_sound()
{
    QSoundEffect* sound = _lever_sounds.at(qrand() % _lever_sounds.size());
    sound->play();
}

void EWRB::LeverFrame::placeSigIndicators()
{
    for(int i{1}; i < 13; ++i)
    {
        if(i == 9) continue;
        _sig_indicators[i]->PlaceAt(24+(i-1)*24,560);
    }

    for(int i{28}; i < 39; ++i)
    {
        _sig_indicators[i]->PlaceAt(24+(i-1)*24,560);
    }
}

void EWRB::LeverFrame::placeMapIndicators()
{
    _map_indicators[1]->PlaceAt(243, 159);
    _map_indicators[2]->PlaceAt(302, 159);
    _map_indicators[4]->PlaceAt(359, 154);
    _map_indicators[5]->PlaceAt(548, 196);
    _map_indicators[6]->PlaceAt(548, 160);
    _map_indicators[7]->PlaceAt(548, 137);
    _map_indicators[8]->PlaceAt(302, 201);
    _map_indicators[10]->PlaceAt(542, 120);
    _map_indicators[11]->PlaceAt(695, 161);
    _map_indicators[28]->PlaceAt(413, 160);
    _map_indicators[29]->PlaceAt(413, 196);
    _map_indicators[30]->PlaceAt(413, 218);
    _map_indicators[31]->PlaceAt(585, 205);
    _map_indicators[32]->PlaceAt(645, 164);
    _map_indicators[33]->PlaceAt(633, 196);
    _map_indicators[36]->PlaceAt(685, 196);
    _map_indicators[37]->PlaceAt(739, 196);
    _map_indicators[38]->PlaceAt(754, 169);
    _map_indicators[39]->PlaceAt(789, 238);
    _map_indicators[40]->PlaceAt(791, 155);
}

void EWRB::LeverFrame::placeDescribers()
{
    const int start_x = 36;
    const int start_y = 97;

    addTrainDescriber(3, "W", start_x+2*13, start_y+0*6);
    addTrainDescriber(6, "W", start_x+5*13, start_y+0*6);
    addTrainDescriber(7, "W", start_x+0*13, start_y+1*6);
    addTrainDescriber(8, "W", start_x+1*13, start_y+1*6);
    addTrainDescriber(9, "W", start_x+2*13, start_y+1*6);
    addTrainDescriber(10, "W", start_x+3*13, start_y+1*6);

    addTrainDescriber(13, "W", start_x+0*13, start_y+5*6);
    addTrainDescriber(14, "W", start_x+1*13, start_y+5*6);
    addTrainDescriber(15, "W", start_x+2*13, start_y+5*6);
    addTrainDescriber(16, "W", start_x+3*13, start_y+5*6);
    addTrainDescriber(17, "W", start_x+4*13, start_y+5*6);
    addTrainDescriber(18, "W", start_x+5*13, start_y+5*6);
    addTrainDescriber(19, "W", start_x+0*13, start_y+6*6);
    addTrainDescriber(20, "W", start_x+1*13, start_y+6*6);
    addTrainDescriber(21, "W", start_x+2*13, start_y+6*6);
    addTrainDescriber(22, "W", start_x+3*13, start_y+6*6);
    addTrainDescriber(23, "W", start_x+4*13, start_y+6*6);
    addTrainDescriber(24, "W", start_x+5*13, start_y+6*6);
    addTrainDescriber(25, "W", start_x+0*13, start_y+7*6);
    addTrainDescriber(26, "W", start_x+1*13, start_y+7*6);
    addTrainDescriber(27, "W", start_x+2*13, start_y+7*6);
    addTrainDescriber(28, "W", start_x+3*13, start_y+7*6);
    addTrainDescriber(29, "W", start_x+4*13, start_y+7*6);
    addTrainDescriber(30, "W", start_x+5*13, start_y+7*6);

    addTrainDescriber(31, "W", start_x+0*13, start_y+11*6);
    addTrainDescriber(32, "W", start_x+1*13, start_y+11*6);
    addTrainDescriber(33, "W", start_x+2*13, start_y+11*6);
    addTrainDescriber(34, "W", start_x+3*13, start_y+11*6);
    addTrainDescriber(35, "W", start_x+4*13, start_y+11*6);
    addTrainDescriber(36, "W", start_x+5*13, start_y+11*6);
    addTrainDescriber(37, "W", start_x+0*13, start_y+12*6);
    addTrainDescriber(38, "W", start_x+1*13, start_y+12*6);
    addTrainDescriber(39, "W", start_x+2*13, start_y+12*6);
    addTrainDescriber(40, "W", start_x+3*13, start_y+12*6);
    addTrainDescriber(41, "W", start_x+4*13, start_y+12*6);
    addTrainDescriber(42, "W", start_x+5*13, start_y+12*6);
    addTrainDescriber(43, "W", start_x+0*13, start_y+13*6);
    addTrainDescriber(44, "C", start_x+1*13, start_y+13*6);
    addTrainDescriber(45, "W", start_x+2*13, start_y+13*6);
    addTrainDescriber(46, "W", start_x+3*13, start_y+13*6);
    addTrainDescriber(47, "W", start_x+4*13, start_y+13*6);
    addTrainDescriber(48, "W", start_x+5*13, start_y+13*6);

    addTrainDescriber(49, "W", start_x+0*13, start_y+17*6);
    addTrainDescriber(50, "W", start_x+1*13, start_y+17*6);
    addTrainDescriber(51, "W", start_x+2*13, start_y+17*6);
    addTrainDescriber(52, "W", start_x+3*13, start_y+17*6);
    addTrainDescriber(53, "W", start_x+4*13, start_y+17*6);
    addTrainDescriber(54, "W", start_x+5*13, start_y+17*6);
    addTrainDescriber(55, "W", start_x+0*13, start_y+18*6);
    addTrainDescriber(56, "W", start_x+1*13, start_y+18*6);
    addTrainDescriber(57, "W", start_x+2*13, start_y+18*6);
    addTrainDescriber(58, "W", start_x+3*13, start_y+18*6);
    addTrainDescriber(59, "W", start_x+4*13, start_y+18*6);
    addTrainDescriber(60, "W", start_x+5*13, start_y+18*6);
    addTrainDescriber(61, "W", start_x+0*13, start_y+19*6);
    addTrainDescriber(62, "W", start_x+1*13, start_y+19*6);
    addTrainDescriber(64, "W", start_x+3*13, start_y+19*6);
    addTrainDescriber(65, "W", start_x+4*13, start_y+19*6);
    addTrainDescriber(66, "W", start_x+5*13, start_y+19*6);

    addTrainDescriber(67, "W", start_x+0*13, start_y+23*6);
    addTrainDescriber(68, "W", start_x+1*13, start_y+23*6);
    addTrainDescriber(69, "W", start_x+2*13, start_y+23*6);
    addTrainDescriber(70, "W", start_x+3*13, start_y+23*6);
    addTrainDescriber(71, "W", start_x+4*13, start_y+23*6);
    addTrainDescriber(72, "W", start_x+5*13, start_y+23*6);
    addTrainDescriber(73, "W", start_x+0*13, start_y+24*6);
    addTrainDescriber(74, "W", start_x+1*13, start_y+24*6);
    addTrainDescriber(75, "W", start_x+2*13, start_y+24*6);
    addTrainDescriber(76, "W", start_x+3*13, start_y+24*6);
    addTrainDescriber(77, "W", start_x+4*13, start_y+24*6);
    addTrainDescriber(78, "W", start_x+5*13, start_y+24*6);
    addTrainDescriber(79, "HM", start_x+0*13, start_y+25*6);
    addTrainDescriber(80, "W", start_x+1*13, start_y+25*6);
    addTrainDescriber(82, "W", start_x+3*13, start_y+25*6);
    addTrainDescriber(83, "W", start_x+4*13, start_y+25*6);
    addTrainDescriber(84, "W", start_x+5*13, start_y+25*6);
}

void EWRB::LeverFrame::update(const int& i)
{
    qDebug() << "Running Frame Update...";

    if(i == -1)
    {
        for(auto pi : _indicators)
        {
            pi->update(true);
        }

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
        if(_indicators.contains(i))_indicators[i]->update(false);
        if(_map_indicators.contains(i))_map_indicators[i]->update();
        if(_sig_indicators.contains(i))_sig_indicators[i]->update();
    }
}
