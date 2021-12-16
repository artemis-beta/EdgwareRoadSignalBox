#ifndef BLOCKSECTION_HXX
#define BLOCKSECTION_HXX

#include "global_params.hxx"
#include "signal.hxx"
#include "points.hxx"
#include "trackcircuit.hxx"

namespace EWRB
{
    class BlockSection
    {
        private:
            const QString _description = "";
            const int _id = -1;
            Signal* _block_signal = nullptr;
            QList<TrackCircuit*> track_circuits_ = {};
            QList<Points*> _points_set = {};
            EWRB::SignalState _required_state = EWRB::SignalState::Off;
            QList<EWRB::PointsState> _required_points_state = {};
            BlockSection* _next = nullptr;
            const QList<Signal*> _counter_signals = {}; // Signals in opposing direction
        public:
            BlockSection(){}
            BlockSection(const int id, const QString& desc) : _id(id), _description(desc) {}
            void addTrackCircuits(const QList<TrackCircuit*>& circuits) {
                track_circuits_.append(circuits);
            }
            void setRequiredState(EWRB::SignalState state) {_required_state = state;}
            void setRequiredPointsState(EWRB::PointsState state) {_required_points_state = {state};}
            void setRequiredPointsState(QList<EWRB::PointsState> states) {_required_points_state = states;}
            void setBlockSignal(Signal* signal) {_block_signal = signal;}
            void setBlockPoints(Points* points) {_points_set = {points};}
            void setBlockPoints(QList<Points*> points) {_points_set = points;}
            EWRB::TrackCircuitStatus getState();
            EWRB::SignalState getRequiredState() const {return _required_state;}
            Signal* getBlockSignal() const {return _block_signal;}
            QList<Points*> getPoints() const {return _points_set;}
            int id() const {return _id;}
            void update();

    };
};

#endif // BLOCKSECTION_HXX
