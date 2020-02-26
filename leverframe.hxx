#ifndef LEVERFRAME_HXX
#define LEVERFRAME_HXX

#include <QMap>
#include <QSvgWidget>
#include <QDebug>

#include "framelever.hxx"
#include "pointsindicator.hxx"
#include "signalindicator.hxx"
#include "traindescriber.hxx"

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
            QMap<int, EWRB::TrainDescriber*> _train_describers;
            Dispatcher* _dispatcher = nullptr;

        public:
            LeverFrame(QWidget* parent);
            void setDispatcher(Dispatcher* dispatcher) {_dispatcher = dispatcher;}
            EWRB::FrameLever* operator[](const int& i)
            {
                return _levers[i];
            }
            QList<int> levers() const {return _levers.keys();}
            void update(const int& i=-1);
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

            void addTrainDescriber(const int& id, const QString& type, const int& x, const int& y)
            {
                _train_describers[id] = new TrainDescriber(_train_describers.size(), _dispatcher, _parent, type);
                _train_describers[id]->PlaceAt(x, y);
            }

            void placeSigIndicators();
            void placeMapIndicators();
            void placeDescribers();
    };
};
#endif // LEVERFRAME_HXX
