#include "pointsindicator.hxx"

void EWRB::PointsIndicator::update(bool silent)
{
    if(_linked_lever->getState() == EWRB::LeverState::On)
    {
        _current_state = EWRB::PointsState::Reverse;
        _svgs[EWRB::PointsState::Reverse]->show();
        _svgs[EWRB::PointsState::Normal]->hide();
    }

    else
    {
        _current_state = EWRB::PointsState::Normal;
        _svgs[EWRB::PointsState::Reverse]->hide();
        _svgs[EWRB::PointsState::Normal]->show();
    }
    if(!silent)_indicator_sound->play();
}

void EWRB::PointsIndicator::PlaceAt(const int &x, const int &y)
{
    _coords[0] = x; _coords[1] = y;

    _svgs[EWRB::PointsState::Normal]->move(x, y);
    _svgs[EWRB::PointsState::Reverse]->move(x, y+28);
}
