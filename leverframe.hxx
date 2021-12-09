#ifndef LEVERFRAME_HXX
#define LEVERFRAME_HXX

#include <QMap>
#include <QSvgWidget>
#include <QDebug>
#include <QGuiApplication>
#include <QScreen>

#include "framelever.hxx"
#include "pointsindicator.hxx"
#include "signalindicator.hxx"
#include "traindescriber.hxx"

namespace EWRB
{
    class LeverFrame : public QObject
    {
        Q_OBJECT
        private:
            QList<QSoundEffect*> _lever_sounds;
            QSoundEffect* _lever_failed = new QSoundEffect;
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
                _sig_indicators[section->id()] = new SignalPanelIndicator(_parent, section, section->id());
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
            void moveLever(const int& i, EWRB::LeverState lever_state, bool points_move)
            {
                if(_levers[i]->getState() == EWRB::LeverState::Mid) _play_failed();
                else if(lever_state != EWRB::LeverState::Mid)_play_random_lever_sound();
                else _play_failed();
                _levers[i]->moveLever(lever_state, points_move);
            }
            void placeSigIndicators();
            void placeMapIndicators();
            void placeDescribers();
            void _play_random_lever_sound();
            void _play_failed() {_lever_failed->play();}
       public slots:
            void updatePointsInd13(EWRB::LeverState);
            void updatePointsInd14(EWRB::LeverState);
            void updatePointsInd15(EWRB::LeverState);
            void updatePointsInd17(EWRB::LeverState);
            void updatePointsInd19(EWRB::LeverState);
            void updatePointsInd20(EWRB::LeverState);
            void updatePointsInd21(EWRB::LeverState);
            void updatePointsInd22(EWRB::LeverState);
            void updatePointsInd23(EWRB::LeverState);
            void updatePointsInd26(EWRB::LeverState);
            void updatePointsInd27(EWRB::LeverState);
    };
};
#endif // LEVERFRAME_HXX
