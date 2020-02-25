#ifndef GLOBAL_PARAMS_HXX
#define GLOBAL_PARAMS_HXX

#include <QMap>

namespace EWRB
{
    enum class SignalState
    {
        Off,
        On,
        OffJctLeft,
        OffJctRight
    };

    enum class LeverState
    {
        Off,
        On
    };

    enum class PointsState
    {
        Normal,
        Reverse
    };

    enum class TrackCircuit
    {
        Clear,
        Occupied
    };

    enum class LeverType
    {
        Signal,
        Points
    };

};

#endif // GLOBAL_PARAMS_HXX
