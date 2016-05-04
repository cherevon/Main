#include "RealEstateQuery.h"


RealEstateQuery::RealEstateQuery()
{
    fCreateDate = QDateTime::currentDateTime();
    fQueryType = RealEstate::BUY;
    fRealEstateType = RealEstate::FLAT;
    fCity = "";
    fAddress = "";
    fPrice = 0;
    fFirstFloor = 1;
    fFloorCount = 1;
    fSquareTotal = 0.0;
    fSquareKitchens.resize(1);
    fSquareKitchens[0] = 0.0;
    fSquareRooms.resize(1);
    fSquareRooms[0] = 0.0;
    fContactInfo = "";
    fAddInfo = "";
}


RealEstateQuery::~RealEstateQuery()
{

}


QDateTime RealEstateQuery::createDate() const
{
    return fCreateDate;
}


QueryType RealEstateQuery::queryType() const
{
    return fQueryType;
}


RealEstateType RealEstateQuery::realEstateType() const
{
    return fRealEstateType;
}


QString RealEstateQuery::city() const
{
    return fCity;
}


QString RealEstateQuery::address() const
{
    return fAddress;
}


uint RealEstateQuery::price() const
{
    return fPrice;
}


uint RealEstateQuery::floorCount() const
{
    return fFloorCount;
}


uint RealEstateQuery::firstFloor() const
{
    return fFirstFloor;
}


uint RealEstateQuery::roomCount() const
{
    return fSquareRooms.size();
}


uint RealEstateQuery::kitchenCount() const
{
    return fSquareKitchens.size();
}


float RealEstateQuery::squareTotal() const
{
    return fSquareTotal;
}


float RealEstateQuery::squareKitchen(const uint kitchenNum) const
{
    return fSquareKitchens[kitchenNum];
}


float RealEstateQuery::squareRoom(const uint roomNum) const
{
    return fSquareRooms[roomNum];
}


QString RealEstateQuery::contactInfo() const
{
    return fContactInfo;
}


QString RealEstateQuery::additionalInfo() const
{
    return fAddInfo;
}


void RealEstateQuery::setCreateDate(const QDateTime value)
{
    fCreateDate = value;
}


void RealEstateQuery::setQueryType(const QueryType value)
{
    fQueryType = value;
}


void RealEstateQuery::setRealEstateType(const RealEstateType value)
{
    fRealEstateType = value;
}


void RealEstateQuery::setCity(const QString value)
{
    fCity = value;
}


void RealEstateQuery::setAddress(const QString value)
{
    fAddress = value;
}


void RealEstateQuery::setPrice(const uint value)
{
    fPrice = value;
}


void RealEstateQuery::setFloorCount(const uint value)
{
    fFloorCount = value;
}


void RealEstateQuery::setFirstFloor(const uint value)
{
    fFirstFloor = value;
}


void RealEstateQuery::setKitchenCount(const uint value)
{
    fSquareKitchens.resize(value);
}


void RealEstateQuery::setRoomCount(const uint value)
{
    fSquareRooms.resize(value);
}


void RealEstateQuery::setSquareTotal(const float value)
{
    fSquareTotal = value;
}


void RealEstateQuery::setSquareKitchen(const uint kitchenNum, const float value)
{
    fSquareKitchens[kitchenNum] = value;
}


void RealEstateQuery::setSquareRoom(const uint roomNum, const float value)
{
    fSquareRooms[roomNum] = value;
}


void RealEstateQuery::setContactInfo(const QString value)
{
    fContactInfo = value;
}


void RealEstateQuery::setAdditionalInfo(const QString value)
{
    fAddInfo = value;
}


bool RealEstateQuery::fits(const RealEstateQuery &Q) const
{
    bool queriesFit = true; // подходят ли запросы друг другу

    // город
    queriesFit = queriesFit && (fCity == Q.fCity);
    // тип недвижимости
    if ((fQueryType == RENT_SELL) || (fQueryType == SELL))
        queriesFit = queriesFit && (fRealEstateType >= Q.fRealEstateType);
    else
        queriesFit = queriesFit && (fRealEstateType <= Q.fRealEstateType);
    // тип запроса
    queriesFit = queriesFit &&
        (
            ((fQueryType == RENT_SELL) && (Q.fQueryType == RENT_BUY)) ||
            ((fQueryType == RENT_BUY) && ((Q.fQueryType == RENT_SELL) || (Q.fQueryType == SELL))) ||
            ((fQueryType == SELL) && (Q.fQueryType == BUY)) ||
            ((fQueryType == BUY) && (Q.fQueryType == SELL))
        );
    // стоимость
    if ((fQueryType == RENT_SELL) || (fQueryType == SELL))
        queriesFit = queriesFit && (fPrice <= Q.fPrice);
    else
        queriesFit = queriesFit && (fPrice >= Q.fPrice);
    // этаж
    queriesFit = queriesFit && (fFirstFloor == Q.fFirstFloor);
    // количество этажей
    if ((fQueryType == RENT_SELL) || (fQueryType == SELL))
        queriesFit = queriesFit && (fFloorCount >= Q.fFloorCount);
    else
        queriesFit = queriesFit && (fFloorCount <= Q.fFloorCount);
    // общая площадь
    if ((fQueryType == RENT_SELL) || (fQueryType == SELL))
        queriesFit = queriesFit && (fSquareTotal >= Q.fSquareTotal);
    else
        queriesFit = queriesFit && (fSquareTotal <= Q.fSquareTotal);

    return queriesFit;
}


bool RealEstateQuery::operator ==(const RealEstateQuery& Q) const
{
    // сравниваем комнаты
    bool roomsEqual = this->roomCount() == Q.roomCount();
    if (roomsEqual)
    {
        for(int roomNum = 0; roomNum < fSquareRooms.size(); ++roomNum)
            if (fSquareRooms[roomNum] != Q.fSquareRooms[roomNum])
            {
                roomsEqual = false;
                break;
            }
    }

    // сравниваем кухни
    bool kitchensEqual = this->kitchenCount() == Q.kitchenCount();
    if (kitchensEqual)
    {
        for(int kitchenNum = 0; kitchenNum < fSquareKitchens.size(); ++kitchenNum)
            if (fSquareKitchens[kitchenNum] != Q.fSquareKitchens[kitchenNum])
            {
                kitchensEqual = false;
                break;
            }
    }

    // сравниваем все параметры запроса
    return (fQueryType == Q.fQueryType) &&
        (fCreateDate == Q.fCreateDate) &&
        (fRealEstateType == Q.fRealEstateType) &&
        (fCity == Q.fCity) &&
        (fAddress == Q.fAddress) &&
        (fPrice == Q.fPrice) &&
        (fFloorCount == Q.fFloorCount) &&
        (fFirstFloor == Q.fFirstFloor) &&
        kitchensEqual && roomsEqual &&
        (fSquareTotal == Q.fSquareTotal) &&
        (fContactInfo == Q.fContactInfo) &&
        (fAddInfo == Q.fAddInfo);
}


RealEstateQuery& RealEstateQuery::operator =(const RealEstateQuery& Q)
{
    // общая информация о запросе
    fCreateDate = Q.fCreateDate;
    fQueryType = Q.fQueryType;
    fRealEstateType = Q.fRealEstateType;
    fCity = Q.fCity;
    fAddress = Q.fAddress;
    fPrice = Q.fPrice;
    fFloorCount = Q.fFloorCount;
    fSquareTotal = Q.fSquareTotal;
    fContactInfo = Q.fContactInfo;
    fAddInfo = Q.fAddInfo;

    // кухни
    fSquareKitchens.resize(Q.fSquareKitchens.size());
    for(int kitchenNum = 0; kitchenNum < fSquareKitchens.size(); ++kitchenNum)
        fSquareKitchens[kitchenNum] = Q.fSquareKitchens[kitchenNum];

    // комнаты
    fSquareRooms.resize(Q.fSquareRooms.size());
    for(int roomNum = 0; roomNum < fSquareRooms.size(); ++roomNum)
        fSquareRooms[roomNum] = Q.fSquareRooms[roomNum];

    return *this;
}


QString queryTypeToString(const QueryType &queryT)
{
    if (queryT == SELL)
        return QString("Продать");
    else if (queryT == BUY)
        return QString("Купить");
    else if (queryT == RENT_SELL)
        return QString("Сдать в аренду");
    else
        return QString("Снять в аренду");
}


QString realEstateTypeToString(const RealEstateType& rt)
{
    if (rt == COTTAGE)
        return QString("Коттедж");
    else if (rt == ROOM)
        return QString("Комната");
    else if (rt == FLAT)
        return QString("Квартира");
    else if (rt == TOWNHOUSE)
        return QString("Таунхаус");
}