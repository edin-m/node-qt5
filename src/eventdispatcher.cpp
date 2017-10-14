#include "eventdispatcher.h"

namespace nodeqt {

EventDispatcher::EventDispatcher(QObject* parent)
  : QAbstractEventDispatcher(parent)
{

}

EventDispatcher::~EventDispatcher()
{

}

bool EventDispatcher::processEvents(QEventLoop::ProcessEventsFlags flags)
{

}

bool EventDispatcher::hasPendingEvents()
{

}

void EventDispatcher::registerSocketNotifier(QSocketNotifier* notifier)
{

}

void EventDispatcher::unregisterSocketNotifier(QSocketNotifier* notifier)
{

}

void EventDispatcher::registerTimer(int timerId, int interval, Qt::TimerType timerType, QObject* object)
{

}

void EventDispatcher::registerTimer(int timerId, int interval, QObject* object)
{

}

bool EventDispatcher::unregisterTimer(int timerId)
{

}

bool EventDispatcher::unregisterTimers(QObject* object)
{

}

QList<QAbstractEventDispatcher::TimerInfo> EventDispatcher::registeredTimers(QObject* object) const
{

}

int EventDispatcher::remainingTime(int timerId)
{

}

void EventDispatcher::wakeUp()
{

}

void EventDispatcher::interrupt()
{

}

void EventDispatcher::flush()
{

}

}

