#include "framelever.hxx"

void EWRB::FrameLever::PlaceAt(const int &x, const int &y)
{
    _coords[0] = x; _coords[1] = y;

    for(auto svg : _svgs) svg->move(_coords[0], _coords[1]);
}

void EWRB::FrameLever::moveLever(EWRB::LeverState state)
{
    _svgs[_current_state]->hide();
    if(state == EWRB::LeverState::Mid && _current_state != state)
    {
        _prev_state = _current_state;
        _current_state = state;
        _svgs[_current_state]->show();
        return;
    }

    if(_current_state == LeverState::Off) _current_state = LeverState::On;
    else if(_current_state == LeverState::Mid)
    {
        _current_state = (_locked) ? _prev_state : reverse(_prev_state);
    }
    else _current_state = LeverState::Off;

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
