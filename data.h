#ifndef DATA_H
#define DATA_H

#include <QByteArray>
#include <QString>
#include <QObject>

class Data : public QObject
{
    Q_OBJECT

    Q_PROPERTY(float agx READ getanX WRITE setanX NOTIFY sendagXChange)
    Q_PROPERTY(float agy READ getanY WRITE setanY NOTIFY sendagYChange)
    Q_PROPERTY(float agz READ getanZ WRITE setanZ NOTIFY sendagZChange)

public:
    static Data *getInstance();
    void init();
    void analyze(QByteArray &data);

    void setacX(float acX);
    float getacX();
    void setacY(float acY);
    float getacY();
    void setacZ(float acZ);
    float getacZ();

    void setavX(float avX);
    float getavX();
    void setavY(float avY);
    float getavY();
    void setavZ(float avZ);
    float getavZ();

    void setanX(float anX);
    float getanX();
    void setanY(float anY);
    float getanY();
    void setanZ(float anZ);
    float getanZ();

    void setgunValue(float gunValue);
    float getgunValue();

    void settemperatureValue(float temperatureValue);
    float gettemperatureValue();

    void setltf(float staute);
    float getltf();

    void setlts(float statue);
    float getlts();

    // 测试
    void test();
private:
    Data();
    static Data *myData;
    float acX;
    float acY;
    float acZ;
    float avX;
    float avY;
    float avZ;
    float anX;
    float anY;
    float anZ;
    float ltf;
    float lts;
    float gunValue;
    float temperatureValue;
    QString getData;

signals:
    void sendagXChange(void);
    void sendagYChange(void);
    void sendagZChange(void);
};

#endif // DATA_H
