#ifndef SignalIndicator_HXX
#define SignalIndicator_HXX

#include "signal.hxx"
#include "blocksection.hxx"

#include <QMap>
#include <QSvgWidget>

namespace EWRB
{
    class SignalPanelIndicator
    {
        private:
            QWidget* _parent;
            QMap<EWRB::TrackCircuit, QSvgWidget*> _svgs;
            BlockSection* _entry_block = nullptr;
            int _location[2] = {0,0};
        public:
            SignalPanelIndicator(QWidget* parent, BlockSection* valid_block) :
                _parent(parent), _entry_block(valid_block)
            {
                _svgs[EWRB::TrackCircuit::Clear] = new QSvgWidget(QString(":/svgs/svgs/PanelSigIndOff.svg"), _parent);
                _svgs[EWRB::TrackCircuit::Clear]->setFixedSize(20,20);
                _svgs[EWRB::TrackCircuit::Occupied] = new QSvgWidget(QString(":/svgs/svgs/PanelSigIndOn.svg"), _parent);
                _svgs[EWRB::TrackCircuit::Occupied]->setFixedSize(20,20);
                _svgs[EWRB::TrackCircuit::Occupied]->hide();
            }
            void PlaceAt(const int& x, const int& y);
            void update();
    };
};

#endif // SignalIndicator_HXX
