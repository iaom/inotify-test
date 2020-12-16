#ifndef INDEXGENERATOR_H
#define INDEXGENERATOR_H

#include <QObject>
#include "xapian.h"

class IndexGenerator : public QObject
{
    Q_OBJECT
public:
    explicit IndexGenerator(QObject *parent = nullptr);

};

#endif // INDEXGENERATOR_H
