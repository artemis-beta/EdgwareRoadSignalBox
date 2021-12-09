#ifndef SIGNAL_HXX
#define SIGNAL_HXX

#include "global_params.hxx"

namespace EWRB
{

    class Signal
    {
        private:
            bool _block_occupied = false;
            const int _id = -1;
            EWRB::SignalState _current_state = EWRB::SignalState::On;
        public:
            Signal() {}
            Signal(const int& id) : _id(id) {};
            EWRB::SignalState getState() const {return _current_state;};
            int id() const {return _id;}
            bool tryClear(EWRB::SignalState state = EWRB::SignalState::Off);
            void setBlockOccupied(bool is_occupied) {_block_occupied = is_occupied;}
            bool protectedBlockOccupied() const {return _block_occupied;}
            void setOn(bool set_on)
            {
                if(set_on) _current_state = EWRB::SignalState::On;
            }
    };

    class ShuntSignal : public Signal
    {
        public:
            ShuntSignal(const int& id) : Signal(id) {}
    };
};

#endif // SIGNAL_HXX
