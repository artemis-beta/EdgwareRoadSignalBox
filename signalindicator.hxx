#ifndef SignalPanelIndicator_HXX
#define SignalPanelIndicator_HXX

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
            const Signal* _mirrored_signal = nullptr;
            QMap<EWRB::SignalState, QSvgWidget*> _panel_indicators;
            int _location[2] = {0,0};
        public:
            SignalPanelIndicator(QWidget* parent, BlockSection* valid_block) :
                _parent(parent), _mirrored_signal(valid_block->getBlockSignal()), _entry_block(valid_block)
            {

            }
            void placeAt(int& x, int& y);
            void update();
    };
};

#endif // SignalPanelIndicator_HXX
