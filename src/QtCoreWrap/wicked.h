#ifndef WICKED_H
#define WICKED_H

#include <QAbstractEventDispatcher>

class Wicked : public QAbstractEventDispatcher {
  Q_OBJECT
public:
  explicit Wicked(QObject* obj);
};

#endif // WICKED_H
