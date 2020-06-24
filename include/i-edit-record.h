#ifndef IEDITRECORD_H
#define IEDITRECORD_H

#include <QObject>
#include <QString>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlTableModel>
#include <QFuture>
#include <QFutureWatcher>
#include "data.hpp"

class QTZ_DATA_SHARED_EXPORT IEditRecord : public QObject
{
    Q_OBJECT
public:
    explicit IEditRecord(QSqlTableModel* model, QObject *parent = nullptr);


signals:

public slots:

};

#endif // IEDITRECORD_H
