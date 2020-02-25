#ifndef SignalIndicator_HXX
#define SignalIndicator_HXX

#include "signal.hxx"
#include "blocksection.hxx"

#include <QMap>
#include <QSvgWidget>
#include <QDebug>

namespace EWRB
{
    class SignalMapIndicator
    {
        private:
            QMap<EWRB::SignalState, QSvgWidget*> _svgs;
            int _position[2] = {0, 0};
            QMap<EWRB::SignalState, BlockSection*> _entry_blocks;
            QWidget* _parent = nullptr;
        public:
            SignalMapIndicator(QWidget* parent, BlockSection* valid_block, double angle=90) :
                _parent(parent)
            {
                _entry_blocks[EWRB::SignalState::Off] = valid_block;
                _svgs[EWRB::SignalState::Off] = new QSvgWidget(":/svgs/svgs/AT2_Clear_"+QString::number(angle).replace(".","_")+".svg", _parent);
                _svgs[EWRB::SignalState::Off]->setFixedSize(20, 20);
                _svgs[EWRB::SignalState::Off]->hide();
                _svgs[EWRB::SignalState::On] = new QSvgWidget(":/svgs/svgs/AT2_Stop_"+QString::number(angle).replace(".","_")+".svg", _parent);
                _svgs[EWRB::SignalState::On]->setFixedSize(20, 20);
            }
            void PlaceAt(const int& x, const int& y);
            void setSVG(EWRB::SignalState state, QString image, int w, int h)
            {
                if(_svgs.keys().contains(state)) delete _svgs[state];
                _svgs[state] = new QSvgWidget(image, _parent);
                _svgs[state]->setFixedSize(w, h);
                if(state != EWRB::SignalState::On) _svgs[state]->hide();
            }
            void addValidBlocks(EWRB::SignalState state, BlockSection* block)
            {
                _entry_blocks[state] = block;
            }
            void update();
            Signal* getMirroredSignal() const {return _entry_blocks[EWRB::SignalState::Off]->getBlockSignal();}
    };

    class ShuntMapIndicator : public SignalMapIndicator
    {
        public:
            ShuntMapIndicator(QWidget* parent, BlockSection* valid_block, double angle=90) :
                SignalMapIndicator(parent, valid_block, angle)
            {
                setSVG(EWRB::SignalState::Off, ":/svgs/svgs/Disc_Clear_"+QString::number(angle).replace(".","_")+".svg", 10, 10);
                setSVG(EWRB::SignalState::On, ":/svgs/svgs/Disc_Stop_"+QString::number(angle).replace(".","_")+".svg", 10, 10);
            }
    };

    class EWREastSignalIndicator : public SignalMapIndicator
    {
    public:
        EWREastSignalIndicator(QWidget* parent, QList<BlockSection*> valid_blocks) :
            SignalMapIndicator(parent, valid_blocks[0])
        {
            setSVG(EWRB::SignalState::Off, ":/svgs/svgs/AT2EWEast_Clear_90.svg", 30, 20);
            setSVG(EWRB::SignalState::On, ":/svgs/svgs/AT2EWEast_Stop_90.svg", 30, 20);
            setSVG(EWRB::SignalState::OffJctLeft, ":/svgs/svgs/AT2EWEast_JctLeft_90.svg", 30, 20);

            addValidBlocks(EWRB::SignalState::OffJctLeft, valid_blocks[1]);
        }
    };

    class EWRWestSignalIndicator : public SignalMapIndicator
    {
    public:
        EWRWestSignalIndicator(QWidget* parent, QList<BlockSection*> valid_blocks) :
            SignalMapIndicator(parent, valid_blocks[0])
        {
            setSVG(EWRB::SignalState::Off, ":/svgs/svgs/AT2EWWest_Clear_270.svg", 30, 20);
            setSVG(EWRB::SignalState::On, ":/svgs/svgs/AT2EWWest_Stop_270.svg", 30, 20);
            setSVG(EWRB::SignalState::OffJctLeft, ":/svgs/svgs/AT2EWWest_JctLeft_270.svg", 30, 20);
            setSVG(EWRB::SignalState::OffJctRight, ":/svgs/svgs/AT2EWWest_JctRight_270.svg", 30, 20);

            addValidBlocks(EWRB::SignalState::OffJctLeft, valid_blocks[1]);
            addValidBlocks(EWRB::SignalState::OffJctRight, valid_blocks[2]);
        }
    };

    class PraedStJctSignalIndicator : public SignalMapIndicator
    {
    public:
        PraedStJctSignalIndicator(QWidget* parent, QList<BlockSection*> valid_blocks) :
            SignalMapIndicator(parent, valid_blocks[0])
        {
            setSVG(EWRB::SignalState::Off, ":/svgs/svgs/AT2EWPraedJct_Clear_90.svg", 30, 20);
            setSVG(EWRB::SignalState::On, ":/svgs/svgs/AT2EWPraedJct_Stop_90.svg", 30, 20);
            setSVG(EWRB::SignalState::OffJctRight, ":/svgs/svgs/AT2EWPraedJct_JctRight_90.svg", 30, 20);

            addValidBlocks(EWRB::SignalState::OffJctRight, valid_blocks[1]);
        }
    };

    class SignalPanelIndicator
    {
        private:
            QWidget* _parent = nullptr;
            QMap<bool, QSvgWidget*> _svgs;
            BlockSection* _entry_block = nullptr;
            int _location[2] = {0, 0};
        public:
            SignalPanelIndicator(QWidget* parent, BlockSection* valid_block) :
                _parent(parent), _entry_block(valid_block)
            {
                _svgs[false] = new QSvgWidget(QString(":/svgs/svgs/PanelSigIndOff.svg"), _parent);
                _svgs[false]->setFixedSize(20,20);
                _svgs[true] = new QSvgWidget(QString(":/svgs/svgs/PanelSigIndOn.svg"), _parent);
                _svgs[true]->setFixedSize(20,20);
                _svgs[true]->hide();
            }
            void PlaceAt(const int& x, const int& y);
            void update();
    };

};

#endif // SignalIndicator_HXX
