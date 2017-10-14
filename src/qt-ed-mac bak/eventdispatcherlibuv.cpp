#include "eventdispatcherlibuv.h"
#include <QCoreApplication>
#include <QSocketNotifier>


#include "uv.h"
#include <QDebug>

#include "eventdispatcherlibuv_p.h"

//#include <QtGui/5.8/QtGui/qpa/qwindowsysteminterface.h>
#include <QtGui/5.8.0/QtGui/private/qguiapplication_p.h>
#include <QtGui/5.8.0/QtGui/qpa/qplatformintegration.h>
//#include <QtGui/private/qguiapplication_p.h>
//#include <QtGui/qpa/qplatformintegration.h>

#include <errno.h>
#include <sys/select.h>
#include <sys/sysctl.h>
#include <sys/time.h>
#include <sys/types.h>

#include <QTimer>
#include <QDateTime>

extern uint qGlobalPostedEventsCount(); // from qapplication.cpp

namespace
{

void forgetCurrentUvHandles()
{
    uv_walk(uv_default_loop(), [](uv_handle_t* handle, void* arg){
        if (uv_has_ref(handle)) {
            uv_unref(handle);
        }
    }, 0);
}

}

namespace qtjs {

//void OnWatcherQueueChanged(uv_loop_t* loop) {
//  EventDispatcherLibUv* ed = static_cast<EventDispatcherLibUv*>(loop->data);
//  qDebug() << "OnWatcherQueueChanged";
//}

void PollEvents(EventDispatcherLibUv* ed) {
  uv_loop_t* uv_loop_ = ed->default_loop_;
  struct timeval tv;
  int timeout = uv_backend_timeout(uv_loop_);
  if (timeout != -1) {
    tv.tv_sec = timeout / 1000;
    tv.tv_usec = (timeout % 1000) * 1000;
  }

  fd_set readset;
  int fd = uv_backend_fd(uv_loop_);
  FD_ZERO(&readset);
  FD_SET(fd, &readset);

  // Wait for new libuv events.
  int r;
  do {
    r = select(fd + 1, &readset, nullptr, nullptr,
               timeout == -1 ? nullptr : &tv);
    qDebug() << "UV fd event" << r;
    ed->num_fd_events_ = r;
  } while (r == -1 && errno == EINTR);
}

void EmbeddedThreadFn(void* arg) {
  EventDispatcherLibUv* ed = static_cast<EventDispatcherLibUv*>(arg);
  qDebug() << "EmbeddedThreadFn";

  while(true) {
//    uv_sem_wait(&ed->sem_uv_handle_);

//    PollEvents(ed);

//    ed->wakeUp();





    uv_loop_t* uv_loop_ = ed->default_loop_;
    struct timeval tv;
    int timeout = uv_backend_timeout(uv_loop_);
    if (timeout != -1) {
      tv.tv_sec = timeout / 1000;
      tv.tv_usec = (timeout % 1000) * 1000;
    }

    fd_set readset;
    int fd = uv_backend_fd(uv_loop_);
    FD_ZERO(&readset);
    FD_SET(fd, &readset);

    // Wait for new libuv events.
    int r;
    do {
      r = select(fd + 1, &readset, nullptr, nullptr,
                 timeout == -1 ? nullptr : &tv);
      qDebug() << "UV fd event" << r;
      ed->num_fd_events_ = r;
    } while (r == -1 && errno == EINTR);
//    uv_async_send(&ed->async_uv_handle_);
    uv_sem_wait(&ed->sem_uv_handle_);
  }
}

EventDispatcherLibUv::EventDispatcherLibUv(QObject *parent) :
    QAbstractEventDispatcher(parent),
    socketNotifier(new EventDispatcherLibUvSocketNotifier()),
    timerNotifier(new EventDispatcherLibUvTimerNotifier()),
    timerTracker(new EventDispatcherLibUvTimerTracker()),
    asyncChannel(new EventDispatcherLibUvAsyncChannel()),
    finalise(false),
    osEventDispatcher(nullptr)
{
//  uv_stop(uv_default_loop());
}

EventDispatcherLibUv::~EventDispatcherLibUv(void)
{
    socketNotifier.reset();
    timerNotifier.reset();
    timerTracker.reset();
    asyncChannel.reset();
    uv_run(uv_default_loop(), UV_RUN_NOWAIT);
    delete osEventDispatcher;
}

void EventDispatcherLibUv::wakeUp(void)
{
//  qDebug() << "wakeUp";
    if (osEventDispatcher) {
        osEventDispatcher->wakeUp();
    }

//    asyncChannel->send();
}

void EventDispatcherLibUv::interrupt(void)
{
  qDebug() << "interrupt";
    if (osEventDispatcher) {
        osEventDispatcher->interrupt();
    }
//    asyncChannel->send();
}

void EventDispatcherLibUv::flush(void)
{
  qDebug() << "flush";
    if (osEventDispatcher) {
        osEventDispatcher->flush();
    }
}

// https://github.com/joyent/libuv/issues/1286

bool EventDispatcherLibUv::processEvents(QEventLoop::ProcessEventsFlags flags)
{
    osEventDispatcher->processEvents(flags & ~QEventLoop::WaitForMoreEvents & ~QEventLoop::EventLoopExec);
    QCoreApplication::sendPostedEvents();

    uv_run(default_loop_, UV_RUN_NOWAIT);
//    if (num_fd_events_ > 0) {
//      qint64 start = QDateTime::currentDateTime().toMSecsSinceEpoch();
//      uv_run(default_loop_, UV_RUN_ONCE);
//      qDebug() << "run loop for" << (QDateTime::currentDateTime().toMSecsSinceEpoch() - start);
//    }

//    uv_sem_post(&sem_uv_handle_);
//    emit aboutToBlock();

//    int leftHandles = uv_run(uv_default_loop(), UV_RUN_NOWAIT);
//    qDebug() << "leftHandles" << leftHandles;
////    if (!leftHandles) {
//        osEventDispatcher->processEvents(flags & ~QEventLoop::EventLoopExec | QEventLoop::WaitForMoreEvents);
////    }
////        if (leftHandles) {
////          uv_run(uv_default_loop(), UV_RUN_ONCE);
////        }
    return true;
}

bool EventDispatcherLibUv::hasPendingEvents(void)
{
  qDebug() << "hasPendingEvents" << osEventDispatcher->hasPendingEvents() << qGlobalPostedEventsCount();
    return osEventDispatcher->hasPendingEvents() || qGlobalPostedEventsCount();
}

void EventDispatcherLibUv::registerSocketNotifier(QSocketNotifier* notifier)
{
  qDebug() << "registerSocketNotifier";
  osEventDispatcher->registerSocketNotifier(notifier);
//    socketNotifier->registerSocketNotifier(notifier->socket(), notifier->type(), [notifier]{
//        QEvent event(QEvent::SockAct);
//        QCoreApplication::sendEvent(notifier, &event);
//    });
}
void EventDispatcherLibUv::unregisterSocketNotifier(QSocketNotifier* notifier)
{
  qDebug() << "unregisterSocketNotifier";
  osEventDispatcher->unregisterSocketNotifier(notifier);
//    socketNotifier->unregisterSocketNotifier(notifier->socket(), notifier->type());
}

void EventDispatcherLibUv::registerTimer(int timerId, int interval, Qt::TimerType timerType, QObject* object)
{
//  uv_run(uv_default_loop(), UV_RUN_ONCE);
//  uv_async_send(&async_uv_handle_);
//  uv_sem_post(&sem_uv_handle_);
  qDebug() << "registerTimer";
  osEventDispatcher->registerTimer(timerId, interval, timerType, object);
//    timerNotifier->registerTimer(timerId, interval, [timerId, object, this] {
//        timerTracker->fireTimer(timerId);
//        QTimerEvent e(timerId);
//        QCoreApplication::sendEvent(object, &e);
//    });
//    timerTracker->registerTimer(timerId, interval, timerType, object);
}

bool EventDispatcherLibUv::unregisterTimer(int timerId)
{
  qDebug() << "unregisterTimer";
  return osEventDispatcher->unregisterTimer(timerId);
//    bool ret = timerNotifier->unregisterTimer(timerId);
//    if (ret) {
//        timerTracker->unregisterTimer(timerId);
//    }
//    return ret;
}

bool EventDispatcherLibUv::unregisterTimers(QObject* object)
{
  qDebug() << "unregisterTimers";
  return osEventDispatcher->unregisterTimers(object);
//    bool ret = true;
//    for (auto info : registeredTimers(object)) {
//        ret &= unregisterTimer(info.timerId);
//    }
//    return ret;
}


//static void embed_cb(uv_async_t* async) {
//  qDebug() << "embed_cb";
//  EventDispatcherLibUv* eb = static_cast<EventDispatcherLibUv*>(async->data);
//  uv_run(uv_default_loop(), UV_RUN_ONCE);

//  uv_sem_post(&eb->sem_uv_handle_);
//}

QList<QAbstractEventDispatcher::TimerInfo> EventDispatcherLibUv::registeredTimers(QObject* object) const
{
  qDebug() << "registeredTimers";
  return osEventDispatcher->registeredTimers(object);
//    return timerTracker->getTimerInfo(object);
}

int EventDispatcherLibUv::remainingTime(int timerId)
{
  qDebug() << "remainingTime";
  return osEventDispatcher->remainingTime(timerId);
//    return timerTracker->remainingTime(timerId);
}

void EventDispatcherLibUv::startingUp() {
  qDebug() << "startingUp";
  osEventDispatcher = QGuiApplicationPrivate::platformIntegration()->createEventDispatcher();
  osEventDispatcher->startingUp();

  default_loop_ = uv_default_loop();
//  uv_async_init(default_loop_, &async_uv_handle_, embed_cb);
//  uv_async_init(default_loop_, &async_uv_handle_, nullptr);
//  async_uv_handle_.data = this;

//  uv_sem_init(&sem_uv_handle_, 0);
//  uv_thread_create(&thread_uv_handle_, EmbeddedThreadFn, this);

//  uv_run(default_loop_, UV_RUN_ONCE);
//  uv_sem_post(&sem_uv_handle_);
}

void EventDispatcherLibUv::closingDown() {
  qDebug() << "closingDown";
    osEventDispatcher->closingDown();
}

void EventDispatcherLibUv::setFinalise()
{
  qDebug() << "setFinalise";
//    forgetCurrentUvHandles();
//    finalise = true;
}


}
