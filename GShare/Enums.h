/* 
 * File:   Enums.h
 * Author: karsten
 *
 * Created on 23. maj 2011, 21:51
 */

#ifndef ENUMS_H
#define	ENUMS_H
#include <string.h>

namespace PlayerCommands{
	enum Enum{
		Invalid = 0,
        

	};

}

#define BitF_offline 0
#define BitF_online 1
#define BitF_rechargin 2
#define BitF_HaveTarget 4

#define BitF_MiningUnit 1
#define BitF_MiningPos 1
#define BitF_DropOfUnit 2

namespace MoveBitF
{
  const uint32_t TargetPosLock = 0x01;
  const uint32_t SOME_VALUE1 = 0x02;
  const uint32_t SOME_VALUE2 = 0x04;
  const uint32_t SOME_VALUE3 = 0x08;
}
namespace SubKeyWord{
	enum Enum{
		Invalid = 0,
		Laser = 1,
		Beam = 2,
		Fusion = 3,
		Ion = 4,
		Projectile = 5,
		Guided = 6,
		Plasma = 7,
		Turret = 8,
		Bay = 9,
		Mining = 10,
	};
}

namespace BonusTypes{
	enum Enum{
		Invalid = 0,
		Armor = 1,
		Deflector = 2,
		ShieldStr = 3,
		Hull = 9,
		ERecharge = 10,
		Energy = 11,
		ScanRange = 12,
		ScanPRange = 13,
		SpeedThruster = 14,
		ManuvereThruster = 15,
		TurretRes = 16,
		BeamDmgBonus = 17,
		MissileDmgBonus = 18,
		ProjectileDmgBonus = 19,
		
	};

}

namespace OrdreConditionsStat{
	enum Enum{
		Invalid = 0,
		CargoLessThen = 1,
		CargoGreaterThen = 2,
		CargoEqualTo = 3,
		CargoPLessThen = 4,
		CargoPGreaterThen = 5,
		CargoPEqualTo = 6,
	};
}

namespace Visibility{
	enum Enum{
		Invisible = 0,
		PreVisible = 1,
		Visible = 2,
		PreInvisible = 3,
	};
}

namespace OrdresConditionUnits{
	enum Enum{
		invalid = 0,
		OindexUnit = 1,
		TriggerUnit = 2,
	};
}
namespace DestroyMode{
	enum  Enum{
		Destroy = 0,
		Vanish = 1,
		Warp = 2,
		Depleted = 3,
	};
}

namespace Icontex{
		enum Enum{
			Invalid = 0,
			ok = 1,
			cancel = 2,
			Cargo = 3,
			CreateLoadOut = 4
		};
}

namespace FitTypes{
	enum Enum{
		Invalid = 0,
		Armo = 1,
		Shie = 2,
		Elec = 3,
		Mech = 4,
		ElMe = 5,
		ShAr = 6,
		MwSh = 7,
		MwEl = 8,
		ShEl = 9,
		Engi = 10,
		Figh = 11,
		Lwep = 12,
		Mwep = 13,
		Hwep = 14,
		Lfac = 15,
		Mfac = 16,
		Hfac = 17,
		Mini = 18,
	};
}

namespace Textures{
	enum Enum{
		Invalid = 0,
        test = 1,
		BC1 = 2,
		Shot_Laser_I = 3,
		EffectSheet = 4,
		SlotSheet = 5,
		ShotSheet = 6,
		ItemSheet = 7,
		SubItemSheet = 8,
		ObjSheet = 9,
		OwObjSheet = 10,
		EffectSheet2 = 11,
		IconSheet = 12,
	};
}

namespace ParticalTex{
	enum Enum{
		Invalid = 0,
        test = 1,
		eks1 = 2,
		eks2 = 3,
		eks3 = 4,
		eks4 = 5,
		eks5 = 6,
		eks6 = 7,
		eks4l = 8,
		eks5l = 9,
		eks6l = 10,
		eks7l = 11,
		eksshc1 = 12,
		eksshc2 = 13,
		eksshc3 = 14,
		eksshc4 = 15,
		eksshc5 = 16,
		eksshc6 = 17,
		eksshc7 = 18,
		eksshc4l = 19,
		eksshc5l = 20,
		eksshc6l = 21,
		eksshc7l = 22,
		LaserTail1 = 23,
		MissileTail1 = 24,
		eksship1 = 25,
		plasma1 = 26,
	};
}

namespace SpaceTypes{
	enum Enum{
		Invalid = 0,
                Ship = 1,
	};
}

namespace OrdreEvent{
	enum Enum{
		Invalid = 0,
		Tick5 = 1,
		Tick10 = 2,
		Tick25 = 3,
		UnitCreated = 4,
		Init = 5,
		UnitDestroyed = 6,
		CargoChange = 7,
		UnitEnterGrid = 8,
		UnitLeaveGrid = 9,
		UnitEnterRangeUnit = 10,
		UnitLeaveRangeUnit = 11,
	};
}
namespace TargetGroup{
	enum Enum{
		Primary = 0,
		Light = 1,
		Medium = 2,
		Heavy = 3,
		Special = 4,
	};
}


namespace TargetType{
	enum Enum{
		Invalid = 0,
		Missel,
		MiningShip,
		Freighter,
		Unarmed,
		Fighter,
		Frigat,
		LightSupport,
		HeavySupport,
		Capital,
		SuperCapital,
		Structure,
		Astoroid,
		All,
	};
}

namespace OrdresTactice{
	enum Enum{
		Invalid = 0,
		No_move,
		Front,
		FrontMinRange,
		FrontMaxRange,
		Evasive,
		OrbitClock,
		OrbitCountclock,

	};
}

namespace SubSystemClass{
	enum Enum{
		Invalid = 0,
		Wep = 1,
		Fac = 2,
		bonus = 3,
		boost = 4,
		Ref = 5,
	};
}

namespace UIviews{
	enum Enum{
		Standard = 0,
		Fit = 1,
	};

}

namespace Shields{
	enum Enum{
		FW = 0,
		FWL = 1,
		FWR = 2,
		AF = 3,
		AFL = 4,
		AFR = 5,
	};
}

namespace FireDir{
	enum Enum{
		ALL = 0,
		FW,
		FWS,
		FW_LS_RS,
		FW_FL,
		FW_FR,
		FW_L,
		FW_R,
		FW_LS,
		FW_RS,
		FW_AL,
		FW_AR,
		FW_FL_FR,
		FW_L_R,
		FW_AL_AR,

		FWS_FL,
		FWS_FR,
		FWS_LS,
		FWS_RS,
		FWS_R_AFS,
		FWS_L_AFS,

		FL,
		FL_R,
		FL_L,
		FL_LS,
		FL_AL,
		FL_AFS,
		FL_AF,

		FR,
		FR_L,
		FR_R,
		FR_RS,
		FR_AR,
		FR_AFS,
		FR_AF,

		L,
		L_FWS_AFS,
		L_AL,
		L_AFS,
		L_AF,

		R,
		R_FWS_AFS,
		R_AR,
		R_AFS,
		R_AF,

		AL,
		AL_AFS,
		AL_AF,

		AR,
		AR_AFS,
		AR_AF,

		AF,
		AF_LS_RS,
		AF_AL_AR,
		AF_L_R,
		AF_FL_FR,


	};
}



namespace DmgTypes{
	enum Enum{
		Invalid = 0,
		normal = 1,
		Mining = 2,
	};
}
#endif	/* ENUMS_H */

