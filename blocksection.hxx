#ifndef BLOCKSECTION_HXX
#define BLOCKSECTION_HXX

#include "global_params.hxx"
#include "signal.hxx"

namespace EWRB
{
    class BlockSection
    {
        private:
            const QString _description = "";
            const int _id = -1;
            Signal* _block_signal = nullptr;
            EWRB::SignalState _required_state = EWRB::SignalState::Off;
            BlockSection* _next = nullptr;
            const QList<Signal*> _counter_signals = {}; // Signals in opposing direction
            EWRB::TrackCircuit _track_circuit = EWRB::TrackCircuit::Clear;
        public:
            BlockSection(const int id, const QString& desc) : _id(id), _description(desc) {}
            bool isOccupied() const {return _track_circuit == EWRB::TrackCircuit::Occupied;}
            void setRequiredState(EWRB::SignalState state) {_required_state = state;}
            void setBlockSignal(Signal* signal) {_block_signal = signal;}
            EWRB::TrackCircuit getState() const {return _track_circuit;}
            Signal* getBlockSignal() const {return _block_signal;}
            int id() const {return _id;}

    };
};

#endif // BLOCKSECTION_HXX
