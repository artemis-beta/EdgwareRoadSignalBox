#ifndef LEVERFRAME_HXX
#define LEVERFRAME_HXX

#include <QMap>
#include <QSvgWidget>
#include <QDebug>

#include "framelever.hxx"

namespace EWRB
{
    class LeverFrame
    {
        private:
            QWidget* _parent = nullptr;
            QSvgWidget* _frame_svg = nullptr;
            QMap<int, EWRB::FrameLever*> _levers;
        public:
            LeverFrame(QWidget* parent);
            EWRB::FrameLever* operator[](const int& i)
            {
                return _levers[i];
            }
            QList<int> levers() const {return _levers.keys();}
    };
};
#endif // LEVERFRAME_HXX
