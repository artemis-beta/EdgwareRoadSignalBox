#ifndef POINTSINDICATOR_HXX
#define POINTSINDICATOR_HXX

#include <QMap>
#include <QSvgWidget>
#include <QSoundEffect>
#include <QTimer>

#include "global_params.hxx"
#include "framelever.hxx"

namespace EWRB
{
    class PointsIndicator
    {
        private:
            QWidget* _parent;
            QSoundEffect* _indicator_sound = new QSoundEffect;
            int _coords[2] = {0, 0};
            const EWRB::PointsLever* _linked_lever = nullptr;
            EWRB::PointsState _current_state = EWRB::PointsState::Normal;
            QMap<EWRB::PointsState, QSvgWidget*> _svgs;
        public:
            PointsIndicator(EWRB::PointsLever* lever, QWidget* parent) : _linked_lever(lever), _parent(parent)
            {
                _indicator_sound->setSource(QUrl::fromLocalFile(":/audio/audio/points_indicator.wav"));

                _svgs[EWRB::PointsState::Normal] = new QSvgWidget(QString(":/svgs/svgs/PointIndicatorNorm.svg"), parent);
                _svgs[EWRB::PointsState::Normal]->setFixedSize(15,15);
                _svgs[EWRB::PointsState::Normal]->show();
                _svgs[EWRB::PointsState::Reverse] = new QSvgWidget(QString(":/svgs/svgs/PointIndicatorReverse.svg"), parent);
                _svgs[EWRB::PointsState::Reverse]->setFixedSize(15,15);
                _svgs[EWRB::PointsState::Reverse]->hide();
            }
            void update(bool silent=false);
            void PlaceAt(const int& x, const int& y);
    };
};

#endif // POINTSINDICATOR_HXX
