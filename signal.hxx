#ifndef SIGNAL_HXX
#define SIGNAL_HXX

#include "global_params.hxx"

namespace EWRB
{
    class BlockSection;

    class Signal
    {
        private:
            BlockSection* _block = nullptr;
            const int _id = -1;
            EWRB::SignalState _current_state = EWRB::SignalState::On;
        public:
            Signal(const int& id) : _id(id) {};
            void setBlock(BlockSection* block) {_block = block;}
            EWRB::SignalState getState() const {return _current_state;};
            int id() const {return _id;}
    };

    class ShuntSignal : public Signal
    {
        public:
            ShuntSignal(const int& id) : Signal(id) {}
    };
};

#endif // SIGNAL_HXX
