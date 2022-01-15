#pragma once

#include "AEDoorAudioEntity.h"

enum eGarageType : uint8 {
    INVALID = 0,
    ONLY_TARGET_VEH = 1,
    BOMBSHOP_TIMED = 2,
    BOMBSHOP_ENGINE = 3,
    BOMBSHOP_REMOTE = 4,
    PAYNSPRAY = 5,

    UNKN_CLOSESONTOUCH = 11,
    OPEN_FOR_TARGET_FREEZE_PLAYER = 14,
    SCRIPT_ONLY_OPEN = 15,

    SAFEHOUSE_GANTON = 16,
    SAFEHOUSE_SANTAMARIA = 17,
    SAGEHOUSE_ROCKSHORE = 18,

    SCRIPT_CONTROLLED = 19,
    STAY_OPEN_WITH_CAR_INSIDE = 20,
    CLOSE_WITH_CAR_DONT_OPEN_AGAIN = 21,
    SCRIPT_OPEN_FREEZE_WHEN_CLOSING = 23,

    SAFEHOUSE_FORTCARSON = 24,
    SAFEHOUSE_VERDANTMEADOWS = 25,
    SAFEHOUSE_DILLIMORE = 26,
    SAFEHOUSE_PRICKLEPINE = 27,
    SAFEHOUSE_WHITEWOOD = 28,
    SAFEHOUSE_PALOMINOCREEK = 29,
    SAFEHOUSE_REDSANDSWEST = 30,
    SAFEHOUSE_ELCORONA = 31,
    SAFEHOUSE_MULHOLLAND = 32,

    IMPOUND_LS = 33,
    IMPOUND_SF = 34,
    IMPOUND_LV = 35,

    TUNING_LOCO_LOW_CO = 36,
    TUNING_WHEEL_ARCH_ANGELS = 37,
    TUNING_TRANSFENDER = 38,

    SAFEHOUSE_CALTONHEIGHTS = 39,
    SAFEHOUSE_PARADISO = 40,
    SAFEHOUSE_DOHERTY = 41,
    SAFEHOUSE_HASHBURY = 42,

    BURGLARY = 43,

    HANGAR_AT400 = 44,
    HANGAR_ABANDONED_AIRPORT = 45
};

enum eGarageDoorState : uint8 {
    GARAGE_DOOR_CLOSED = 0,
    GARAGE_DOOR_OPEN = 1,
    GARAGE_DOOR_CLOSING = 2,
    GARAGE_DOOR_OPENING = 3,
    GARAGE_DOOR_WAITING_PLAYER_TO_EXIT = 4,
    GARAGE_DOOR_CLOSED_DROPPED_CAR = 5,
};

struct CStoredCar {
    CVector  m_vPosn;
    uint32 m_dwHandlingFlags;
    uint8  m_nStoredCarFlags;
    uint8  _pad0;
    uint16 m_wModelIndex;
    int16  m_awCarMods[15];
    uint8  m_nPrimaryColor;
    uint8  m_nSecondaryColor;
    uint8  m_nTertiaryColor;
    uint8  m_nQuaternaryColor;
    uint8  m_nRadiostation;
    uint8  m_anCompsToUse[2];
    uint8  m_nBombType;
    uint8  m_nPaintjob;
    uint8  m_nNitroBoosts;
    uint8  m_nPackedForwardX;
    uint8  m_nPackedForwardY;
    uint8  m_nPackedForwardZ;
    uint8  _pad1;

public:
    static void InjectHooks();

    CVehicle* RestoreCar();
    void      StoreCar(CVehicle* pVehicle);
};
VALIDATE_SIZE(CStoredCar, 0x40);

class CGarage {
public:
    CGarage() = default;
    ~CGarage() = default;

public:
    CVector   m_vPosn;
    CVector2D m_vDirectionA;
    CVector2D m_vDirectionB;
    float     m_fTopZ;
    float     m_fWidth;
    float     m_fHeight;
    float     m_fLeftCoord;
    float     m_fRightCoord;
    float     m_fFrontCoord;
    float     m_fBackCoord;
    float     m_fDoorPosition;
    uint32  m_dwTimeToOpen;
    CVehicle* m_pTargetCar;
    char      m_anName[8];
    eGarageType   m_nType;      // see eGarageType
    eGarageDoorState   m_nDoorState; // see eGarageDoorState
    union {
        uint8 m_nFlags;
        struct {
            uint8 m_b0x1 : 1;
            uint8 m_bInactive : 1;
            uint8 m_bUsedRespray : 1;
            uint8 m_bDoorOpensUp : 1;
            uint8 m_bDoorGoesIn : 1;
            uint8 m_bCameraFollowsPlayer : 1;
            uint8 m_bDoorClosed : 1;
            uint8 m_bRespraysAlwaysFree : 1;
        };
    };
    eGarageType            m_nOriginalType;
    CAEDoorAudioEntity m_GarageAudio;

public:
    static void InjectHooks();

    void TidyUpGarageClose();
    void TidyUpGarage();
    void StoreAndRemoveCarsForThisHideOut(CStoredCar* car, int32 maxSlot);
    void RemoveCarsBlockingDoorNotInside();
    bool IsEntityTouching3D(CEntity* entity);
    bool IsEntityEntirelyOutside(CEntity* entity, float radius);
    bool IsStaticPlayerCarEntirelyInside();
    bool IsEntityEntirelyInside3D(CEntity* entity, float radius);
    bool IsPointInsideGarage(CVector point);
    uint8 PlayerArrestedOrDied();
    void Close();
    int8_t Open();
    void InitDoorsAtStart();
    bool IsPointInsideGarage(CVector point, float radius);
    void Update(int32 thisGarageId);

    bool RightModTypeForThisGarage(CVehicle* pVehicle);
    void OpenThisGarage();
    void CloseThisGarage();
    float CalcDistToGarageRectangleSquared(float, float);
    void NeatlyLineUpStoredCars(CStoredCar* pCar);
    bool RestoreCarsForThisHideOut(CStoredCar* pCar);
    bool RestoreCarsForThisImpoundingGarage(CStoredCar* pCar);
    int32 FindMaxNumStoredCarsForGarage();
    bool IsPlayerOutsideGarage(float fRadius);
    bool IsPlayerEntirelyInsideGarage();
    bool EntityHasASpehereWayOutsideGarage(CEntity* pEntity, float fRadius);
    bool IsAnyOtherCarTouchingGarage(CVehicle* pIgnoredVehicle);
    void ThrowCarsNearDoorOutOfGarage(CVehicle* pIgnoredVehicle);
    bool IsAnyOtherPedTouchingGarage(CPed* pIgnoredPed);
    bool IsAnyCarBlockingDoor();
    int32 CountCarsWithCenterPointWithinGarage(CVehicle* pIgnoredVeh);
    void StoreAndRemoveCarsForThisImpoundingGarage(CStoredCar* pStoredCar, int32 iMaxSlot);
    void CenterCarInGarage(CVehicle* pVehicle);
    void FindDoorsWithGarage(CObject** ppFirstDoor, CObject** ppSecondDoor);
    bool SlideDoorOpen();
    bool SlideDoorClosed();
    bool IsGarageEmpty();

public:
    static void BuildRotatedDoorMatrix(CEntity* pEntity, float fDoorPosition);

private:
    CGarage* Constructor();
    CGarage* Destructor();
};
VALIDATE_SIZE(CGarage, 0xD8);

struct CSaveGarage {
    eGarageType      type{};
    eGarageDoorState doorState{};
    uint16           flags{};
    CVector          pos{};
    CVector2D        dirA, dirB{};
    float            topZ{};
    float            width, height{};
    float            leftCoord{};
    float            rightCoord{};
    float            frontCoord{};
    float            backCoord{};
    float            doorPos{};
    uint32           timeToOpen{};
    char             name[8]{};
    eGarageType      originalType{};

    void CopyGarageIntoSaveGarage(const CGarage&);
};
VALIDATE_SIZE(CSaveGarage, 0x50);
