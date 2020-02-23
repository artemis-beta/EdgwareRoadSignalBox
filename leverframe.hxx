#ifndef LEVERFRAME_HXX
#define LEVERFRAME_HXX

#include <QMap>
#include <QSvgWidget>
#include <QDebug>

#include "framelever.hxx"
#include "pointsindicator.hxx"
#include "signalindicator.hxx"

namespace EWRB
{
    class LeverFrame
    {
        private:
            QWidget* _parent = nullptr;
            QSvgWidget* _frame_svg = nullptr;
            QMap<int, EWRB::FrameLever*> _levers;
            QMap<int, EWRB::PointsIndicator*> _indicators;
            QMap<int, EWRB::SignalPanelIndicator*> _sig_indicators;
            QMap<int, EWRB::SignalMapIndicator*> _map_indicators;

        public:
            LeverFrame(QWidget* parent);
            EWRB::FrameLever* operator[](const int& i)
            {
                return _levers[i];
            }
            QList<int> levers() const {return _levers.keys();}
            void update();
            void addSignalPanelIndicator(BlockSection* section)
            {
                _sig_indicators[section->id()] = new SignalPanelIndicator(_parent, section);
            }
            void addSignalMapIndicator(BlockSection* section, double angle=90)
            {
                _map_indicators[section->getBlockSignal()->id()] = new SignalMapIndicator(_parent, section, angle);
            }
            void addShuntMapIndicator(BlockSection* section, double angle=90)
            {
                _map_indicators[section->getBlockSignal()->id()] = new ShuntMapIndicator(_parent, section, angle);
            }
            void addCustomMapIndicator(SignalMapIndicator* indicator)
            {
                _map_indicators[indicator->getMirroredSignal()->id()] = indicator;
            }

            void placeSigIndicators();
            void placeMapIndicators();
    };
};
#endif // LEVERFRAME_HXX
