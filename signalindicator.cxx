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

    for(auto svg : _svgs)
    {
        svg->hide();
    }

    _svgs[_entry_block->getState()]->show();
}

void EWRB::SignalMapIndicator::PlaceAt(const int &x, const int &y)
{
    _position[0] = x;
    _position[1] = y;

    for(auto svg : _svgs)
    {
        svg->move(x, y);
    }
}

void EWRB::SignalMapIndicator::update()
{
    for(auto svg : _svgs)
    {
        svg->hide();
    }

    // State is not important here we just use it to retrieve the signal
    qDebug() << "SVG Fetch: Signal set to "<< int(_entry_blocks[EWRB::SignalState::Off]->getBlockSignal()->getState());
    _svgs[_entry_blocks[EWRB::SignalState::Off]->getBlockSignal()->getState()]->show();
}
