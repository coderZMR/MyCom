#include "data.h"
#include <QString>

using namespace std;

Data* Data::myData = nullptr;

Data::Data() : QObject()
{
    init();
}

Data* Data::getInstance()
{
    if (myData == nullptr) myData = new Data();
    return myData;
}

void Data::init()
{
    setacX(0);
    setacY(0);
    setacZ(0);

    setanX(0);
    setanY(0);
    setanZ(0);

    setavX(0);
    setavY(0);
    setavZ(0);

    setgunValue(0);
    setltf(0);
    setlts(0);
    settemperatureValue(0);

    // 测试
    qsrand(0);
}

void Data::analyze(QByteArray &data)
{
    this->getData = data;
    QString sigQue;
    QString figQue;
    sigQue.clear();
    figQue.clear();
    for (int i = 0; i < getData.size(); ++i) {
        if ('a' <= getData.at(i) && getData.at(i) <= 'z')
        {
            if (!figQue.isEmpty()) {
                if (sigQue == "acx") this->acX = figQue.toFloat();
                if (sigQue == "acy") this->acY = figQue.toFloat();
                if (sigQue == "acz") this->acZ = figQue.toFloat();

                if (sigQue == "avx") this->avX = figQue.toFloat();
                if (sigQue == "avy") this->avY = figQue.toFloat();
                if (sigQue == "avz") this->avZ = figQue.toFloat();

                if (sigQue == "agx") this->anX = figQue.toFloat();
                if (sigQue == "agy") this->anY = figQue.toFloat();
                if (sigQue == "agz") this->anZ = figQue.toFloat();

                if (sigQue == "tem") this->temperatureValue = figQue.toFloat();

                if (sigQue == "oi") this->gunValue = figQue.toFloat();

                if (sigQue == "ltf") this->ltf = figQue.toFloat();
                if (sigQue == "lts") this->lts = figQue.toFloat();

                figQue.clear();
                sigQue.clear();
            }
            if (getData.at(i) != 'd') sigQue.append(getData.at(i));
        }
        else {
            figQue.append(getData.at(i));
        }
    }
}

void Data::setacX(float acX) {
    this->acX = acX;
}

float Data::getacX() {
    return this->acX;
}

void Data::setacY(float acY) {
    this->acY = acY;
}

float Data::getacY() {
    return this->acY;
}

void Data::setacZ(float acZ){
    this->acZ = acZ;
}

float Data::getacZ() {
    return this->acZ;
}

void Data::setavX(float avX) {
    this->avX = avX;
}

float Data::getavX() {
    return this->avX;
}

void Data::setavY(float avY) {
    this->avY = avY;
}

float Data::getavY() {
    return this->avY;
}

void Data::setavZ(float avZ){
    this->avZ = avZ;
}

float Data::getavZ() {
    return this->avZ;
}

void Data::setanX(float anX) {
    this->anX = anX;
    emit sendagXChange();
}

float Data::getanX() {
    return this->anX;
}

void Data::setanY(float anY) {
    this->anY = anY;
    emit sendagYChange();
}

float Data::getanY() {
    return this->anY;
}

void Data::setanZ(float anZ){
    this->anZ = anZ;
    emit sendagZChange();
}

float Data::getanZ() {
    return this->anZ;
}

void Data::setgunValue(float gunValue) {
    this->gunValue = gunValue;
}

float Data::getgunValue() {
    return this->gunValue;
}


void Data::settemperatureValue(float temperatureValue) {
    this->temperatureValue = temperatureValue;
}

float Data::gettemperatureValue() {
    return this->temperatureValue;
}

void Data::setltf(float staute) {
    this->ltf = staute;
}

float Data::getltf() {
    return this->ltf;
}

void Data::setlts(float statue) {
    this->lts = statue;
}

float Data::getlts() {
    return this->lts;
}


void Data::test() {
    setacX(qrand() % 100);
    setacY(qrand() % 100);
    setacZ(qrand() % 100);
    setanX(qrand() % 100);
    setanY(qrand() % 100);
    setanZ(qrand() % 100);
    setavX(qrand() % 100);
    setavY(qrand() % 100);
    setavZ(qrand() % 100);
    setgunValue(qrand() % 100);
    settemperatureValue(qrand() % 100);
}
