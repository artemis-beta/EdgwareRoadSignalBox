#ifndef GLOBAL_PARAMS_HXX
#define GLOBAL_PARAMS_HXX

#include <QMap>

namespace EWRB
{
    enum class SignalState
    {
        On,
        Off,
        OffJctLeft,
        OffJctRight
    };

    enum class LeverState
    {
        Off,
        Mid,
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
