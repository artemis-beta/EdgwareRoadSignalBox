#ifndef POINTS_H
#define POINTS_H

#include "global_params.hxx"

namespace EWRB
{
    class Points
    {
        private:
            EWRB::PointsState _current_state;
            int _id = -1;
        public:
            Points() {}
            Points(const int& id) : _id(id) {}
            EWRB::PointsState getState() const {return _current_state;}
            int id() const {return _id;}
    };
};
#endif // POINTS_H
