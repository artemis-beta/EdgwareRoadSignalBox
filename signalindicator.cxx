#include "SignalPanelIndicator.hxx"

void EWRB::SignalPanelIndicator::placeAt(int& x, int& y)
{
    _location[0] = x;
    _location[1] = y;

    for(auto svg : _panel_indicators)
    {
        svg->move(x, y);
    }
}

void EWRB::SignalPanelIndicator::update()
{
    if(_mirrored_signal->getState() == EWRB::SignalState::Off)
    {

    }

    else
    {

    }
}
