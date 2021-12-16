#ifndef SERVICE_HXX
#define SERVICE_HXX

#include <QString>
#include <QRunnable>
#include <QList>
#include <QWidget>

namespace EWRB {
    class Service : public QRunnable {
    private:
        const QWidget* parent_;
        const QString descriptor_ = "";
        const QList<QList<QString>> permitted_paths_;
        QString current_block_ = "";
    public:
        Service(const QWidget* parent, const QString& descriptor, const QList<QList<QString>> paths) : parent_(parent), descriptor_(descriptor), permitted_paths_(paths) {
            current_block_ = paths[0][0];
        }
        void moveService(const QString& block) {
            current_block_ = block;
        }
        QString getLocation() const {return current_block_;}
    };
};

#endif // SERVICE_HXX
