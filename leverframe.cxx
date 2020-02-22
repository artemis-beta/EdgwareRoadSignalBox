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
        _levers[i]->PlaceAt(25+(i-1)*24.1, 620);
        _levers[i]->showSVG();
    }
    for(int i{13}; i < 28; ++i)
    {
        _levers[i] = new EWRB::PointsLever(_parent);
        _levers[i]->PlaceAt(25+(i-1)*24.1, 620);
        _levers[i]->showSVG();
    }

    for(int i{28}; i < 39; ++i)
    {
        _levers[i] = new EWRB::HomeLever(_parent);
        _levers[i]->PlaceAt(25+(i-1)*24.1, 620);
        _levers[i]->showSVG();
    }
}
