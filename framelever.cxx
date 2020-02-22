#include "framelever.hxx"

void EWRB::FrameLever::PlaceAt(const int &x, const int &y)
{
    _coords[0] = x; _coords[1] = y;

    for(auto svg : _svgs) svg->move(_coords[0], _coords[1]);
}

void EWRB::FrameLever::moveLever()
{
    qDebug() << "Moving: " << int(_current_state);
    _svgs[_current_state]->hide();
    if(_current_state == State::Off) _current_state = State::On;
    else _current_state = State::Off;
    _svgs[_current_state]->show();
}

void EWRB::FrameLever::hideSVG()
{
    _svgs[_current_state]->hide();
}

void EWRB::FrameLever::showSVG()
{
    _svgs[_current_state]->show();
}
