#ifndef COMMANDDATA_H
#define COMMANDDATA_H

#include <QMetaType>

struct CommandData
{
    float pan = 0.0f;
    float tilt = 0.0f;
    float panVel = 0.0f;
    float tiltVel = 0.0f;
    bool laserOn = false;
    bool fanOn = false;
};

Q_DECLARE_METATYPE(CommandData)

#endif // COMMANDDATA_H