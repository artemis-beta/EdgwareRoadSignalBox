#include "traindescriber.hxx"

void EWRB::TrainDescriber::PlaceAt(const int &x, const int &y)
{
    _location[0] = x;
    _location[1] = y;

    for(auto svg : _svgs)
    {
        svg->move(x, y);
    }

    _svgs[true]->hide();
}
