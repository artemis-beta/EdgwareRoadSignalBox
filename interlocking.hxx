#ifndef INTERLOCKING_HXX
#define INTERLOCKING_HXX

#include <QPair>
#include <QSoundEffect>

#include "signal.hxx"
#include "points.hxx"
#include "framelever.hxx"
#include "leverframe.hxx"
#include "blocksection.hxx"

namespace EWRB
{
    typedef QMap<int, EWRB::LeverState> interlock_coordinate;
    typedef QMap<EWRB::LeverState, interlock_coordinate> lever_logic;
    typedef QMap<int, lever_logic> interlock_logic;
    typedef QMap<int, QPair<EWRB::FrameLever*, EWRB::Points*>> points_connection;
    typedef QPair<EWRB::Signal*, EWRB::SignalState> lever_active_signal_state;
    typedef QMap<int, QPair<EWRB::FrameLever*, lever_active_signal_state>> signal_connection;

    class InterLocking
    {
        private:
            LeverFrame* _lever_frame;
            interlock_logic _logic;
            QMap<int, EWRB::BlockSection*> _block_sections;
            QMap<int, EWRB::Signal*> _signals;
            QMap<int, EWRB::Points*> _points;
            points_connection _point_lever_connections;
            signal_connection _signal_lever_connections;

            EWRB::LeverState reverse(EWRB::LeverState state) const
            {
                return EWRB::FrameLever().reverse(state);
            }

            void _setup_block_sections();
            void _create_logic_table();
            void _add_points();
            void _add_signals();
            void _connect_levers();
            void _perform_action(const int& i);
            void _connect(const int& id, HomeLever* lever, Signal* signal, EWRB::SignalState aspect = EWRB::SignalState::Off);
            void _connect(const int& id, PointsLever* lever, Points* points);

        public:
            InterLocking(LeverFrame* lever_frame);
            BlockSection* getBlockSection(const int& id) const {return _block_sections[id];}
            bool Query(const int& id);
            void update(const int& id);

    };
};
#endif // INTERLOCKING_HXX
