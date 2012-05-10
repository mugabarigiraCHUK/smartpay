#ifndef CLIENTRUNNER_H
#define CLIENTRUNNER_H

#include <QThread>

class ClientRunner : public QThread
{
   // Q_OBJECT

public:
    void run();
};

#endif // CLIENTRUNNER_H
