#ifndef EVENTDISPATCHERLIBUV_H
#define EVENTDISPATCHERLIBUV_H

#include <QAbstractEventDispatcher>
#include <QMap>

#include <memory>
#include <time.h>

#include "uv.h"

namespace qtjs {

class EventDispatcherLibUvSocketNotifier;
class EventDispatcherLibUvTimerNotifier;
class EventDispatcherLibUvTimerTracker;
class EventDispatcherLibUvAsyncChannel;

class EventDispatcherLibUv : public QAbstractEventDispatcher {
    Q_OBJECT
    std::unique_ptr<EventDispatcherLibUvSocketNotifier> socketNotifier;
    std::unique_ptr<EventDispatcherLibUvTimerNotifier> timerNotifier;
    std::unique_ptr<EventDispatcherLibUvTimerTracker> timerTracker;
    std::unique_ptr<EventDispatcherLibUvAsyncChannel> asyncChannel;
public:
    uv_sem_t sem_uv_handle_;
    uv_async_t async_uv_handle_;
    uv_thread_t thread_uv_handle_;
    uv_loop_t* default_loop_;
    bool runloop = false;
    int num_fd_events_ = 0;

    explicit EventDispatcherLibUv(QObject* parent = 0);
    virtual ~EventDispatcherLibUv(void);

    virtual void wakeUp(void);
    virtual void interrupt(void);
    virtual void flush(void);

    virtual bool processEvents(QEventLoop::ProcessEventsFlags flags);
    virtual bool hasPendingEvents(void);

    virtual void registerSocketNotifier(QSocketNotifier* notifier);
    virtual void unregisterSocketNotifier(QSocketNotifier* notifier);

    virtual void registerTimer(int timerId, int interval, Qt::TimerType timerType, QObject* object);
    virtual bool unregisterTimer(int timerId);
    virtual bool unregisterTimers(QObject* object);
    virtual QList<QAbstractEventDispatcher::TimerInfo> registeredTimers(QObject* object) const;
    virtual int remainingTime(int timerId);

    virtual void startingUp();
    virtual void closingDown();

    void setFinalise();
private:
    bool finalise;
    QAbstractEventDispatcher *osEventDispatcher;

    Q_DISABLE_COPY(EventDispatcherLibUv)
};

}

#endif // EVENTDISPATCHERLIBUV_H
