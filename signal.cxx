#include "signal.hxx"

bool EWRB::Signal::tryClear(EWRB::SignalState state)
{
    if(!protectedBlockOccupied())
    {
        _current_state = state;
    }
}
