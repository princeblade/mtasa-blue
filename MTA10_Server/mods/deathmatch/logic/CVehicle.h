/*****************************************************************************
*
*  PROJECT:     Multi Theft Auto v1.0
*  LICENSE:     See LICENSE in the top level directory
*  FILE:        mods/deathmatch/logic/CVehicle.h
*  PURPOSE:     Vehicle entity class
*  DEVELOPERS:  Christian Myhre Lundheim <>
*               Jax <>
*
*  Multi Theft Auto is available from http://www.multitheftauto.com/
*
*****************************************************************************/

class CVehicle;

#ifndef __CVEHICLE_H
#define __CVEHICLE_H

#include "CCommon.h"
#include "packets/CPacket.h"
#include "CElement.h"
#include "CEvents.h"
#include "CVehicleColor.h"
#include "CVehicleUpgrades.h"

#define MAX_VEHICLE_SEATS 9
#define DEFAULT_VEHICLE_HEALTH 1000
#define MAX_VEHICLE_HEALTH 10000

typedef DWORD RGBA;
typedef DWORD ARGB;
#define COLOR_ARGB(a,r,g,b) \
    (((((a)&0xff)<<24)|(((r)&0xff)<<16)|(((g)&0xff)<<8)|((b)&0xff)))
#define COLOR_RGBA(r,g,b,a) COLOR_ARGB(a,r,g,b)
#define COLOR_ABGR(a,b,g,r) COLOR_ARGB(a,r,g,b)
#define COLOR_BGRA(b,g,r,a) COLOR_ARGB(a,r,g,b)

#define COLOR_RGBA_R(color) unsigned char ( color >> 24 )
#define COLOR_RGBA_G(color) unsigned char ( color >> 16 );
#define COLOR_RGBA_B(color) unsigned char ( color >> 8 );
#define COLOR_RGBA_A(color) unsigned char ( color );
#define COLOR_ARGB_A(color) RGBA_R(color)

enum eWheelStatus {
	DT_WHEEL_INTACT=0,
	DT_WHEEL_BURST,
	DT_WHEEL_MISSING
};

enum eDoorStatus
{
	DT_DOOR_INTACT = 0,
	DT_DOOR_SWINGING_FREE,
	DT_DOOR_BASHED,
	DT_DOOR_BASHED_AND_SWINGING_FREE,
	DT_DOOR_MISSING
};

enum eComponentStatus 
{
	DT_PANEL_INTACT = 0,
	DT_PANEL_BASHED,
	DT_PANEL_BASHED2,
	DT_PANEL_MISSING
};

enum eLightStatus 
{
	DT_LIGHT_OK=0,
	DT_LIGHT_SMASHED
};

enum eDoors
{
	BONNET = 0,
	BOOT,
	FRONT_LEFT_DOOR,
	FRONT_RIGHT_DOOR,
	REAR_LEFT_DOOR,
	REAR_RIGHT_DOOR,
	MAX_DOORS
};

enum eWheels
{
	FRONT_LEFT_WHEEL = 0,
	REAR_LEFT_WHEEL,
	FRONT_RIGHT_WHEEL,
	REAR_RIGHT_WHEEL,
	MAX_WHEELS
};

enum ePanels
{
	FRONT_LEFT_PANEL = 0,
	FRONT_RIGHT_PANEL,
	REAR_LEFT_PANEL,
	REAR_RIGHT_PANEL,
	WINDSCREEN_PANEL,
	FRONT_BUMPER,
	REAR_BUMPER,
	MAX_PANELS
};

enum eLights
{
	LEFT_HEADLIGHT = 0,
	RIGHT_HEADLIGHT,
	LEFT_TAIL_LIGHT,
	RIGHT_TAIL_LIGHT,
	MAX_LIGHTS
};

class CVehicle : public CElement
{
    friend class CPlayer;

public:
                                    CVehicle                ( class CVehicleManager* pVehicleManager, CElement* pParent, CXMLNode* pNode, unsigned short usModel );
                                    ~CVehicle               ( void );

    bool                            IsEntity                ( void )                        { return true; }

    void                            Unlink                  ( void );
    bool                            ReadSpecialData         ( void );

    void                            DoPulse                 ( void );

    inline unsigned short           GetModel            ( void )                        { return m_usModel; };
    void                            SetModel            ( unsigned short usModel );
    bool                            HasValidModel       ( void );

    inline const CVehicleColor&     GetColor                ( void )                        { return m_Color; };
    inline void                     SetColor                ( const CVehicleColor& Color )  { m_Color = Color; };

    inline bool                     IsFrozen                ( void )                        { return m_bIsFrozen; };
    inline void                     SetFrozen               ( bool bIsFrozen )              { m_bIsFrozen = bIsFrozen; };

    inline const CVector&           GetPosition             ( void );
    inline void                     SetPosition             ( const CVector& vecPosition );
    inline void                     GetRotationDegrees      ( CVector& vecRotation )        { vecRotation = m_vecRotationDegrees; };
    inline void                     SetRotationDegrees      ( const CVector& vecRotation )  { m_vecRotationDegrees = vecRotation; };

    inline const CVector&           GetVelocity             ( void )                        { return m_vecVelocity; };
    inline void                     SetVelocity             ( const CVector& vecVelocity )  { m_vecVelocity = vecVelocity; };
    inline const CVector&           GetVelocityMeters       ( void )                        { return m_vecVelocityMeters; };
    inline void                     SetVelocityMeters       ( const CVector& vecVelocityMeters ) { m_vecVelocityMeters = vecVelocityMeters; };
    inline const CVector&           GetTurnSpeed            ( void )                        { return m_vecTurnSpeed; };
    inline void                     SetTurnSpeed            ( const CVector& vecTurnSpeed ) { m_vecTurnSpeed = vecTurnSpeed; };

    inline float                    GetHealth               ( void )                        { return m_fHealth; };
    inline void                     SetHealth               ( float fHealth )               { m_fHealth = fHealth; };
    inline unsigned long            GetHealthChangeTime     ( void )                        { return m_ulHealthChangeTime; }
    inline void                     SetHealthChangeTime     ( unsigned long ulTime )        { m_ulHealthChangeTime = ulTime; }
    
    inline unsigned long            GetBlowTime             ( void )                        { return m_ulBlowTime; };
    inline void                     SetBlowTime             ( unsigned long ulBlowTime )    { m_ulBlowTime = ulBlowTime; };
    
    inline unsigned long            GetIdleTime             ( void )                        { return m_ulIdleTime; };
    inline void                     SetIdleTime             ( unsigned long ulIdleTime )    { m_ulIdleTime = ulIdleTime; };

    CVehicleColor&                  RandomizeColor          ( void );

    inline bool                     IsLocked                ( void )                        { return m_bLocked; };
    inline void                     SetLocked               ( bool bLocked )                { m_bLocked = bLocked; };

    inline bool                     AreDoorsUndamageable    ( void )                        { return m_bDoorsUndamageable; };
    inline void                     SetDoorsUndamageable    ( bool bUndamageable )          { m_bDoorsUndamageable = bUndamageable; };

    inline float                    GetTurretPositionX      ( void )                        { return m_fTurretPositionX; };
    inline float                    GetTurretPositionY      ( void )                        { return m_fTurretPositionY; };
    void                            GetTurretPosition       ( float& fPositionX, float& fPositionY );
    void                            SetTurretPosition       ( float fPositionX, float fPositionY );

    inline bool                     IsSirenActive           ( void )                        { return m_bSirenActive; };
    inline void                     SetSirenActive          ( bool bSirenActive )           { m_bSirenActive = bSirenActive; };
    inline void                     SetTaxiLightOn          ( bool bTaxiLightState )        { m_bTaxiLightState = bTaxiLightState; };
    inline bool                     IsTaxiLightOn           ( void )                        { return m_bTaxiLightState; };

    inline bool                     IsLandingGearDown       ( void )                        { return m_bLandingGearDown; };
    inline void                     SetLandingGearDown      ( bool bLandingGearDown )       { m_bLandingGearDown = bLandingGearDown; };

    inline unsigned short           GetAdjustableProperty   ( void )                        { return m_usAdjustableProperty; };
    inline void                     SetAdjustableProperty   ( unsigned short usAdjustable ) { m_usAdjustableProperty = usAdjustable; };

    CPed*                           GetOccupant             ( unsigned int uiSeat );
    CPed*                           GetFirstOccupant        ( void );
    bool                            SetOccupant             ( CPed* pPed, unsigned int uiSeat );
    CPed*                           GetController           ( void );

    inline class CPlayer*           GetSyncer               ( void )                        { return m_pSyncer; };
    void                            SetSyncer               ( class CPlayer* pPlayer );

    unsigned char                   GetMaxPassengers        ( void );
    unsigned char                   GetFreePassengerSeat    ( void );

	inline void						SetMaxPassengers		( unsigned char ucPassengers )	{ m_ucMaxPassengersOverride = ucPassengers; };

	inline CVehicleUpgrades*		GetUpgrades				( void )						{ return m_pUpgrades; }
    void                            SetUpgrades             ( CVehicleUpgrades* pUpgrades );

    inline unsigned char            GetOverrideLights       ( void )                        { return m_ucOverrideLights; }
    inline void                     SetOverrideLights       ( unsigned char ucLights )      { m_ucOverrideLights = ucLights; }

    inline CVehicle*                GetTowedVehicle         ( void )                        { return m_pTowedVehicle; }
    bool                            SetTowedVehicle         ( CVehicle* pVehicle );
    inline CVehicle*                GetTowedByVehicle       ( void )                        { return m_pTowedByVehicle; }
    bool                            SetTowedByVehicle       ( CVehicle* pVehicle );

    inline const char*              GetRegPlate             ( void )                        { return m_szRegPlate; }
    void                            SetRegPlate             ( const char* szRegPlate );
    void                            GenerateRegPlate        ( void );

    inline unsigned char            GetPaintjob             ( void )                        { return m_ucPaintjob; }
    void                            SetPaintjob             ( unsigned char ucPaintjob );

    inline bool                     GetGunsEnabled          ( void )                        { return m_bGunsEnabled; }
    inline void                     SetGunsEnabled          ( bool bGunsEnabled )           { m_bGunsEnabled = bGunsEnabled; }
    inline bool                     IsFuelTankExplodable    ( void )                        { return m_bFuelTankExplodable; }
    inline void                     SetFuelTankExplodable   ( bool bFuelTankExplodable )    { m_bFuelTankExplodable = bFuelTankExplodable; }

    inline bool                     IsEngineOn              ( void )                        { return m_bEngineOn; }
    inline void                     SetEngineOn             ( bool bEngineOn )              { m_bEngineOn = bEngineOn; }

    inline bool                     IsOnGround              ( void )                        { return m_bOnGround; };
    inline void                     SetOnGround             ( bool bOnGround )              { m_bOnGround = bOnGround; };

    inline bool                     IsSmokeTrailEnabled     ( void )                        { return m_bSmokeTrail; }
    inline void                     SetSmokeTrailEnabled    ( bool bEnabled )               { m_bSmokeTrail = bEnabled; }

    inline unsigned char            GetAlpha                ( void )                        { return m_ucAlpha; }
    inline void                     SetAlpha                ( unsigned char ucAlpha )       { m_ucAlpha = ucAlpha; }

    void                            GetInitialDoorStates    ( unsigned char * pucDoorStates );

    inline CPlayer *                GetJackingPlayer        ( void )                        { return m_pJackingPlayer; }
    inline void                     SetJackingPlayer        ( CPlayer * pPlayer )           { m_pJackingPlayer = pPlayer; }

    inline bool                     IsInWater               ( void )                        { return m_bInWater; }
    inline void                     SetInWater              ( bool bInWater )               { m_bInWater = bInWater; }

    inline bool                     IsDamageProof           ( void )                        { return m_bDamageProof; }
    inline void                     SetDamageProof          ( bool bDamageProof )           { m_bDamageProof = bDamageProof; }

    inline bool                     IsDerailed              ( void )                        { return m_bDerailed; }
    inline void                     SetDerailed             ( bool bDerailed )              { m_bDerailed = bDerailed; }
    inline bool                     IsDerailable            ( void )                        { return m_bIsDerailable; }
    inline void                     SetDerailable           ( bool bDerailable )            { m_bIsDerailable = bDerailable; }
    inline bool                     GetTrainDirection       ( void )                        { return m_bTrainDirection; }
    inline void                     SetTrainDirection       ( bool bDirection )             { m_bTrainDirection = bDirection; }

    inline RGBA                     GetHeadLightColor       ( void )                        { return m_HeadLightColor; }
    inline void                     SetHeadLightColor       ( RGBA color )                  { m_HeadLightColor = color; }

    // Functions used to remember where this vehicle spawns
    void                            PutAtRespawnLocation    ( void );
    inline const CVector&           GetRespawnPosition      ( void )                        { return m_vecRespawnPosition; };
    inline void                     SetRespawnPosition      ( const CVector& vecPosition )  { m_vecRespawnPosition = vecPosition; };
    inline void                     GetRespawnRotationDegrees ( CVector& vecRotation )      { vecRotation = m_vecRespawnRotationDegrees; };
    inline void                     SetRespawnRotationDegrees ( const CVector& vecRotation ){ m_vecRespawnRotationDegrees = vecRotation; };
    inline float                    GetRespawnHealth        ( void )                        { return m_fRespawnHealth; };
    inline void                     SetRespawnHealth        ( float fHealth )               { m_fRespawnHealth = fHealth; };
    inline bool                     GetRespawnInfoChanged   ( void )                        { return m_bRespawnInfoChanged; }
    inline bool                     GetRespawnEnabled       ( void )                        { return m_bRespawnEnabled; }
    inline void                     SetRespawnEnabled       ( bool bEnabled )               { m_bRespawnEnabled = bEnabled; m_bRespawnInfoChanged = true; };
    inline unsigned long            GetRespawnTime          ( void )                        { return m_ulRespawnTime; };
    inline void                     SetRespawnTime          ( unsigned long ulTime )        { m_ulRespawnTime = ulTime; m_bRespawnInfoChanged = true; };
    inline unsigned long            GetIdleRespawnTime      ( void )                        { return m_ulIdleRespawnTime; };
    inline void                     SetIdleRespawnTime      ( unsigned long ulTime )        { m_ulIdleRespawnTime = ulTime; m_bRespawnInfoChanged = true; };

private:
    class CVehicleManager*          m_pVehicleManager;

    CPlayer*                        m_pSyncer;
    CPed*                           m_pOccupants [MAX_VEHICLE_SEATS];

    unsigned short                  m_usModel;
    CVector                         m_vecPosition;
    CVector                         m_vecRotationDegrees;
    CVector                         m_vecVelocity;
    CVector                         m_vecVelocityMeters;
    CVector                         m_vecTurnSpeed;
    float                           m_fHealth;
    unsigned long                   m_ulHealthChangeTime;
    unsigned long                   m_ulBlowTime;
    unsigned long                   m_ulIdleTime;

	unsigned char					m_ucMaxPassengersOverride;

    CVehicleColor                   m_Color;

    bool                            m_bIsFrozen;    

	CVehicleUpgrades*				m_pUpgrades;

    unsigned char                   m_ucOverrideLights;

    CVehicle*                       m_pTowedVehicle;
    CVehicle*                       m_pTowedByVehicle;

    char                            m_szRegPlate [9];
    unsigned char                   m_ucPaintjob;

    bool                            m_bLocked;
    bool                            m_bDoorsUndamageable;
    bool                            m_bEngineOn;
    bool                            m_bGunsEnabled;
    bool                            m_bFuelTankExplodable;
    bool                            m_bOnGround;
    bool                            m_bSmokeTrail;
    unsigned char                   m_ucAlpha;
    bool                            m_bInWater;
    bool                            m_bDerailed;
    bool                            m_bIsDerailable;
    bool                            m_bTrainDirection;
    CPlayer *                       m_pJackingPlayer;
    RGBA                            m_HeadLightColor;

    // Used to remember where this vehicle spawns
    CVector                         m_vecRespawnPosition;
    CVector                         m_vecRespawnRotationDegrees;
    float                           m_fRespawnHealth;
    bool                            m_bRespawnInfoChanged;
    bool                            m_bRespawnEnabled;
    unsigned long                   m_ulRespawnTime;
    unsigned long                   m_ulIdleRespawnTime;

    // Vehicle specific data
    float                           m_fTurretPositionX;
    float                           m_fTurretPositionY;
    bool                            m_bSirenActive;
    bool                            m_bTaxiLightState;
    bool                            m_bLandingGearDown;
    unsigned short                  m_usAdjustableProperty;

public: // 'Safe' variables (that have no need for accessors)
    bool                            m_bDamageProof;
    unsigned char                   m_ucDoorStates [MAX_DOORS];
    unsigned char                   m_ucWheelStates [MAX_WHEELS];
    unsigned char                   m_ucPanelStates [MAX_PANELS];
    unsigned char                   m_ucLightStates [MAX_LIGHTS];
};

#endif
