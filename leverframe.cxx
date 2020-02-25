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

void EWRB::LeverFrame::update()
{
    for(auto pi : _indicators)
    {
        pi->update();
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
