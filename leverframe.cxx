#include "leverframe.hxx"

EWRB::LeverFrame::LeverFrame(QWidget* parent)
{
    _parent = parent;
    _frame_svg = new QSvgWidget(QString(":/svgs/svgs/EWRBFrame.svg"), _parent);
    _frame_svg->setFixedSize(1020, 760);

    const int x = _frame_svg->geometry().width(),
              y = _frame_svg->geometry().height();

    for(int i{1}; i < 13; ++i)
    {
        _levers[i] = new EWRB::HomeLever(_parent);
        _levers[i]->PlaceAt(22+(i-1)*24.1, 620);
        _levers[i]->showSVG();
    }
    for(int i{13}; i < 28; ++i)
    {
        _levers[i] = new EWRB::PointsLever(_parent);
        if(i != 16 && i != 18)
        {   _indicators[i] = new EWRB::PointsIndicator((EWRB::PointsLever*)_levers[i], _parent);
            _indicators[i]->PlaceAt(291+(i-12)*24.05, 580);
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
        _sig_indicators[i]->PlaceAt(24+(i-1)*24,577);
    }

    for(int i{28}; i < 39; ++i)
    {
        _sig_indicators[i]->PlaceAt(24+(i-1)*24,577);
    }
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
}
