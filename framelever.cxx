#include "framelever.hxx"

EWRB::PointsChange::PointsChange(EWRB::FrameLever* parent)
{
    connect(_timer, SIGNAL(timeout()), this, SLOT(timerEnded()));
    _parent = parent;
    _sound_effect->setSource(QUrl::fromLocalFile(":/audio/audio/air_release.wav"));

}

bool EWRB::PointsChange::getState()
{
    if(_sound_finished)
    {
       _sound_finished = false;
       return true;
    }
    return _sound_finished;
}

void EWRB::FrameLever::PlaceAt(const int &x, const int &y)
{
    _coords[0] = x; _coords[1] = y;

    for(auto svg : _svgs) svg->move(_coords[0], _coords[1]);
}

void EWRB::FrameLever::moveLever(EWRB::LeverState state, bool points_delay)
{
    _svgs[_current_state]->hide();
    if(state == EWRB::LeverState::Mid && _current_state != state)
    {
        _prev_state = _current_state;
        _current_state = state;
        _svgs[_current_state]->show();
        return;
    }

    if(_current_state == LeverState::Off)
    {
        _prev_state = _current_state;
        if(points_delay)
        {
            _current_state = LeverState::Mid;
            _svgs[_current_state]->show();
            _points_change->run();
        }
        else _current_state = LeverState::On;
    }
    else if(_current_state == LeverState::Mid)
    {
        _current_state = (_locked) ? _prev_state : reverse(_prev_state);

    }
    else
    {
        _prev_state = _current_state;
        if(points_delay)
        {
            _current_state = LeverState::Mid;
            _svgs[_current_state]->show();
            _points_change->run();
        }
        else _current_state = LeverState::Off;

    }

    _svgs[_current_state]->show();
}

void EWRB::FrameLever::pointsChangedFinished()
{
    _svgs[_current_state]->hide();
    emit sendCurrentLeverDestination(reverse(_prev_state));
    _current_state = reverse(_prev_state);
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
