#include "signalindicator.hxx"

void EWRB::SignalPanelIndicator::PlaceAt(const int& x, const int& y)
{
    _location[0] = x;
    _location[1] = y;

    for(auto svg : _svgs)
    {
        svg->move(x, y);
    }
}

void EWRB::SignalPanelIndicator::update()
{
    if(_entry_block->getState() == EWRB::TrackCircuit::Occupied)
    {
        _svgs[EWRB::TrackCircuit::Occupied]->show();
        _svgs[EWRB::TrackCircuit::Clear]->hide();
    }

    else
    {
        _svgs[EWRB::TrackCircuit::Occupied]->hide();
        _svgs[EWRB::TrackCircuit::Clear]->show();
    }
}
