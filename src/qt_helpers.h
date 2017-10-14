#ifndef QT_HELPERS_H
#define QT_HELPERS_H

#include <QObject>

#define REMOVE_ALL_CONNECTIONS() \
  foreach (QMetaObject::Connection conn, connections_) { \
    QObject::disconnect(conn); \
  }

#endif // QT_HELPERS_H
