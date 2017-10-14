#ifndef EVENTDISPATCHER_H
#define EVENTDISPATCHER_H

#include <QAbstractEventDispatcher>

namespace nodeqt {

class EventDispatcher : public QAbstractEventDispatcher {
  Q_OBJECT
public:
  explicit EventDispatcher(QObject* parent = 0);
  ~EventDispatcher();

  bool processEvents(QEventLoop::ProcessEventsFlags flags);
  bool hasPendingEvents(); // ### Qt6: remove, mark final or make protected

  void registerSocketNotifier(QSocketNotifier *notifier);
  void unregisterSocketNotifier(QSocketNotifier *notifier);

  void registerTimer(int timerId, int interval, Qt::TimerType timerType, QObject *object);
  void registerTimer(int timerId, int interval, QObject * object);
  bool unregisterTimer(int timerId);
  bool unregisterTimers(QObject *object);
  QList<TimerInfo> registeredTimers(QObject *object) const;

  int remainingTime(int timerId);

//#ifdef Q_OS_WIN
//    virtual bool registerEventNotifier(QWinEventNotifier *notifier);
//    virtual void unregisterEventNotifier(QWinEventNotifier *notifier);
//#endif

  void wakeUp();
  void interrupt();
  void flush();

};

}

#endif // EVENTDISPATCHER_H
