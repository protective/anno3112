/* 
 * File:   SDatabase.cpp
 * Author: karsten
 * 
 * Created on 7. september 2011, 10:46
 */

#include <iterator>
#include <algorithm>
#include <map>

#include "SDatabase.h"
#include "Sspacebjects/SShipType.h"
#include "Sspacebjects/SShip.h"
#include "Sspacebjects/subsystems/SSubTypeWep.h"
#include "Sspacebjects/subsystems/SSubTypeFac.h"
#include "Sspacebjects/subsystems/SSubTypeBonus.h"
#include "Sspacebjects/subsystems/SSubTypeBoost.h"
#include "Sspacebjects/subsystems/SSubTypeRef.h"
#include "Sspacebjects/Ordres/SOrdreAction.h"
#include "Sspacebjects/subsystems/SSubTypeRef.h"
#include "Sspacebjects/SAstoroid.h"
#include "Sspacebjects/SAstoroidBelt.h"
#include "Sspacebjects/SAstoroidType.h"
#include "World/SGrid.h"
#include "World/SWorld.h"
#include "sys/stat.h"
int getAllparameter(string line, string key, uint32_t* returnbegin, uint32_t* returnlen) {
	uint32_t index = line.find(key) + key.size();
	if (index < line.size()) {
		while (line.at(index) == 32) {
			index++;
		}
		*returnbegin = index;

		while (index < line.size()) {
			index++;
		}
		*returnlen = index - (*returnbegin);
	}else{
		return 0;
	}
	
	return 1;
}


int getparameter(string line, string key, uint32_t nparam, uint32_t* returnbegin, uint32_t* returnlen) {
	uint32_t index = line.find(key) + key.size();
	for (int i = 0; i < nparam + 1; i++) {
		if (index < line.size()) {
			while (line.at(index) == 32) {
				index++;
			}
			*returnbegin = index;

			while (index < line.size() && line.at(index) != 32) {
				index++;
			}
			*returnlen = index - (*returnbegin);
		}else{
			return 0;
		}
	}
	return 1;
}



int getparameter(string line, string key, uint32_t nparam, uint32_t n2param, uint32_t* returnbegin, uint32_t* returnlen) {
	uint32_t index = line.find(key) + key.size();
	
	for (int i = 0; i < nparam + 1; i++) {
		if (index < line.size()) {
			while (line.at(index) == 32 && index < line.size()) {
				index++;
			}
			for(int j = 0; j < n2param +1; j++){
				if (index < line.size()) {
					while (line.at(index) == 58 && index < line.size()) {
						index++;
					}
					
					*returnbegin = index;
					while (index < line.size() && line.at(index) != 58) {
						if (line.at(index) == 32)
							break;
						index++;
					}
					
					*returnlen = index - (*returnbegin);
					if (index < line.size() && line.at(index) == 32)
						break;	
				}else{
					return 0;
				}
			}
			while (index < line.size()&&line.at(index) != 32 ) {
				index++;
			}
		}else{
			return 0;
		}
	}
	
	return 1;
}

BonusTypes::Enum parseBonusTypes(string str){

	if (str.find("armor")!= string::npos)
		return BonusTypes::Armor;
	if (str.find("deflector")!= string::npos)
		return BonusTypes::Deflector;
	if (str.find("hull")!= string::npos)
		return BonusTypes::Hull;
	if (str.find("shield")!= string::npos)
		return BonusTypes::ShieldStr;
	return BonusTypes::Invalid;
}

SubKeyWord::Enum parseSubKeyWord(string str){

	if (str.find("laser")!= string::npos)
		return SubKeyWord::Laser;
	if (str.find("beam")!= string::npos)
		return SubKeyWord::Beam;
	if (str.find("fusion")!= string::npos)
		return SubKeyWord::Fusion;
	if (str.find("ion")!= string::npos)
		return SubKeyWord::Ion;
	if (str.find("projectile")!= string::npos)
		return SubKeyWord::Projectile;	
	if (str.find("guided")!= string::npos)
		return SubKeyWord::Guided;
	if (str.find("plasma")!= string::npos)
		return SubKeyWord::Plasma;
	if (str.find("turret")!= string::npos)
		return SubKeyWord::Turret;
	if (str.find("bay")!= string::npos)
		return SubKeyWord::Bay;
	if (str.find("mining")!= string::npos)
		return SubKeyWord::Mining;
	return SubKeyWord::Invalid;
}

DmgTypes::Enum parseDmgTypes(string str){

	if (str.find("normal")!= string::npos)
		return DmgTypes::normal;
	if (str.find("mining")!= string::npos)
		return DmgTypes::Mining;
	return DmgTypes::Invalid;
}

int parseFireDir(string str){
	if (str == "ALL")
		return 0;
	if (str == "FW")
		return 1;
	if (str == "FWS")
		return 2;
	if (str == "FW_LS_RS")
		return 3;
	if (str == "FW_FL")
		return 4;
	if (str == "FW_FR")
		return 5;
	if (str == "FW_L")
		return 6;
	if (str == "FW_R")
		return 7;
	if (str == "FW_LS")
		return 8;
	if (str == "FW_RS")
		return 9;
	if (str == "FW_AL")
		return 10;
	if (str == "FW_AR")
		return 11;
	if (str == "FW_FL_FR")
		return 12;
	if (str == "FW_L_R")
		return 13;
	if (str == "FW_AL_AR")
		return 14;
	if (str == "FWS_FL")
		return 15;
	if (str == "FWS_FR")
		return 16;
	if (str == "FWS_LS")
		return 17;
	if (str == "FWS_RS")
		return 18;
	if (str == "FWS_R_AFS")
		return 19;
	if (str == "FWS_L_AFS")
		return 20;
	if (str == "FL")
		return 21;
	if (str == "FL_R")
		return 22;
	if (str == "FL_L")
		return 23;
	if (str == "FL_LS")
		return 24;
	if (str == "FL_AL")
		return 25;
	if (str == "FL_AFS")
		return 26;
	if (str == "FL_AF")
		return 27;
	if (str == "FR")
		return 28;
	if (str == "FR_L")
		return 29;
	if (str == "FR_R")
		return 30;
	if (str == "FR_RS")
		return 31;
	if (str == "FR_AR")
		return 32;
	if (str == "FR_AFS")
		return 33;
	if (str == "FR_AF")
		return 34;
	if (str == "L")
		return 35;
	if (str == "L_FWS_AFS")
		return 36;
	if (str == "L_AL")
		return 37;
	if (str == "L_AFS")
		return 38;
	if (str == "L_AF")
		return 39;
	if (str == "R")
		return 40;
	if (str == "R_FWS_AFS")
		return 41;
	if (str == "R_AR")
		return 42;
	if (str == "R_AFS")
		return 43;
	if (str == "R_AF")
		return 44;
	if (str == "AL")
		return 45;
	if (str == "AL_AFS")
		return 46;
	if (str == "AL_AF")
		return 47;
	if (str == "AR")
		return 48;
	if (str == "AR_AFS")
		return 49;
	if (str == "AR_AF")
		return 50;
	if (str == "AF")
		return 51;
	if (str == "AF_LS_RS")
		return 52;
	if (str == "AF_AL_AR")
		return 53;
	if (str == "AF_L_R")
		return 54;
	if (str == "AF_FL_FR")
		return 55;

	cerr<<"WARNING SDatabase::parseFireDir Error dir not found got >"<<str<<"<"<<endl;

}

FitTypes::Enum parseSlotType(string str){

	if (str.find("Armo")!= string::npos)
		return FitTypes::Armo;
	if (str.find("Shie")!= string::npos)
		return FitTypes::Shie;
	if (str.find("Elec")!= string::npos)
		return FitTypes::Elec;
	if (str.find("Mech")!= string::npos)
		return FitTypes::Mech;
	if (str.find("ElMe")!= string::npos)
		return FitTypes::ElMe;
	if (str.find("ShAr")!= string::npos)
		return FitTypes::ShAr;
	if (str.find("MwSh")!= string::npos)
		return FitTypes::MwSh;
	if (str.find("MwEl")!= string::npos)
		return FitTypes::MwEl;
	if (str.find("ShEl")!= string::npos)
		return FitTypes::ShEl;
	if (str.find("Engi")!= string::npos)
		return FitTypes::Engi;
	if (str.find("Figh")!= string::npos)
		return FitTypes::Figh;
	if (str.find("LWep")!= string::npos)
		return FitTypes::Lwep;
	if (str.find("MWep")!= string::npos)
		return FitTypes::Mwep;
	if (str.find("HWep")!= string::npos)
		return FitTypes::Hwep;
	if (str.find("Lfac")!= string::npos)
		return FitTypes::Lfac;
	if (str.find("Mfac")!= string::npos)
		return FitTypes::Mfac;
	if (str.find("Hfac")!= string::npos)
		return FitTypes::Hfac;
	if (str.find("Mini")!= string::npos)
		return FitTypes::Mini;
	cerr<<"WARNING SDatabase::parseSlotType Error type not found got "<<str<<endl;

	return FitTypes::Invalid;
}


TargetType::Enum parseTargetType(string str){

	if (str.find("missel")!= string::npos)
		return TargetType::Missel;
	if (str.find("miningship")!= string::npos)
		return TargetType::MiningShip;
	if (str.find("freighter")!= string::npos)
		return TargetType::Freighter;
	if (str.find("unarmed")!= string::npos)
		return TargetType::Unarmed;
	if (str.find("fighter")!= string::npos)
		return TargetType::Fighter;
	if (str.find("frigat")!= string::npos)
		return TargetType::Frigat;
	if (str.find("lightsupport")!= string::npos)
		return TargetType::LightSupport;
	if (str.find("heavysupport")!= string::npos)
		return TargetType::HeavySupport;
	if (str.find("capital")!= string::npos)
		return TargetType::Capital;
	if (str.find("supercapital")!= string::npos)
		return TargetType::SuperCapital;
	if (str.find("structure")!= string::npos)
		return TargetType::Structure;
	if (str.find("astoroid")!= string::npos)
		return TargetType::Astoroid;
	

	cerr<<"WARNING SDatabase::parseTargetType Error type not found got "<<str<<endl;

	return TargetType::Invalid;
}

int parsetextureid(string str){

	#include "database/itemtexname.txt"

	cerr<<"WARNING SDatabase::parsetextureid Not found"<<endl;
	return 0;
}

int parseShottex(string str){

	#include "database/shottexname.txt"

	cerr<<"WARNING SDatabase::parseShottex Not found"<<endl;
	return 0;
}

int parseobjtextureid(string str){

	#include "database/objtexname.txt"


	cerr<<"WARNING SDatabase::parseobjtextureid Not found"<<endl;
	return 0;
}

int strToInt(string str) {
	int intReturn;

	intReturn = atoi(str.c_str());

	return (intReturn);
}


void parseDataItemrefs(){
	for (map<string,uint32_t>::iterator it = itemlistFileNames.begin(); it != itemlistFileNames.end();it++){
		SItemType* itemt = new SItemType(it->second);
		itemlist[it->second] = itemt;
	}
}
void ParseGame(ifstream* file,string filename){
	
		uint32_t beginint = 0;
	uint32_t lenint = 0;
	string parseState = "";
	string parseSubState = "";
	string line;
	SGrid* gridtemp = NULL;
	SObj* objtemp = NULL;
	SAstoroidBelt* astobelttemp = NULL;
	cerr<<"fname "<<filename<<endl;
	while (std::getline((*file), line)) {

		if (line.find("//") != string::npos)
			continue;
		if (line.find("[Game]", 0) != string::npos) {
			cerr<<"NewGame"<<endl;
			parseState = "Game";
			parseSubState = "base";
		}

		if (parseState == "Game") {
			if (line.find("{map}") != string::npos) {
				parseSubState = "map";
				gridtemp = new SGrid(1);
				world->addGrid(gridtemp);
			}else if (line.find("{playerUnits}") != string::npos) {
				parseSubState = "playerUnits";
			}


			if (parseSubState == "base") {
			}else if (parseSubState == "map") {
				if (line.find("grid") != string::npos) {
					getparameter(line, "grid", 1, &beginint, &lenint);			
					gridtemp->setWight(1000*strToInt(line.substr(beginint, lenint)));
					getparameter(line, "grid", 2, &beginint, &lenint);
					gridtemp->setHight(1000*strToInt(line.substr(beginint, lenint)));
				}else if (line.find("belt") != string::npos) {

					getparameter(line, "belt", 0, &beginint, &lenint);
					int32_t x = (1000*strToInt(line.substr(beginint, lenint)));
					getparameter(line, "belt", 1, &beginint, &lenint);
					int32_t y = (1000*strToInt(line.substr(beginint, lenint)));
					SPos temppos(x,y,0);
					temppos.grid = world->getGrids()[1];
					astobelttemp = new SAstoroidBelt(getFreeID(),temppos);
					getparameter(line, "belt", 2, &beginint, &lenint);
					astobelttemp->setSize((100*strToInt(line.substr(beginint, lenint))));
					world->getGrids()[1]->addObj(astobelttemp);

					for (int i = 3; i < 30; i++){
						if (getparameter(line, "belt", i,0, &beginint, &lenint)){
						SAstoroidType* at = NULL;
							if(astoroidTypes.find(itemlistFileNames.find(line.substr(beginint, lenint))->second) != astoroidTypes.end()){
								at = astoroidTypes.find(itemlistFileNames.find(line.substr(beginint, lenint))->second)->second;

								getparameter(line, "belt", i,1, &beginint, &lenint);
								uint32_t acounter = strToInt(line.substr(beginint, lenint));

								getparameter(line, "belt", i,2, &beginint, &lenint);
								uint32_t timer = strToInt(line.substr(beginint, lenint));
								for(int j = 0; j < acounter; j++){
									astobelttemp->AddRoid(at,timer);
								}
							}else
								break;
						}
					}
					
				}
			}else if (parseSubState == "playerUnits") {
				if (line.find("Unit") != string::npos) {
					getparameter(line, "Unit", 0, &beginint, &lenint);
					uint32_t team =  strToInt(line.substr(beginint, lenint));
					getparameter(line, "Unit", 1, &beginint, &lenint);
					if (itemlistFileNames.find(line.substr(beginint, lenint)) != itemlistFileNames.end()){
						SShipType* st = NULL;
						if(shipTypes.find(itemlistFileNames.find(line.substr(beginint, lenint))->second) != shipTypes.end()){
							st = shipTypes.find(itemlistFileNames.find(line.substr(beginint, lenint))->second)->second;
						
							getparameter(line, "Unit", 2, &beginint, &lenint);
							int32_t x = 1000 * strToInt(line.substr(beginint, lenint));
							getparameter(line, "Unit", 3, &beginint, &lenint);
							int32_t y = 1000 * strToInt(line.substr(beginint, lenint));
							SPos temppos(x,y,0);
							temppos.grid = world->getGrids()[1];
							SShip* ship = new SShip(getFreeID(), temppos, *st,team);
							world->getGrids()[1]->addShip(ship);

		
							for (int i = 4; i < 30; i++){
								if (getparameter(line, "Unit", i,0, &beginint, &lenint)){
									for (int j = 1; j < 25; j++){
										getparameter(line, "Unit", i,0, &beginint, &lenint);
										if(strToInt(line.substr(beginint, lenint)) == j){
											getparameter(line, "Unit", i,1, &beginint, &lenint);
											map<string,uint32_t>::iterator susi = itemlistFileNames.find(line.substr(beginint, lenint));
											if(susi != itemlistFileNames.end()){
												if (getparameter(line, "Unit", i,2, &beginint, &lenint)){
													itemlist[susi->second];
													ship->AddSub(itemlist[susi->second],j,strToInt(line.substr(beginint, lenint)));
												}
											}else{
												cerr<<"WARNING Sdatabase::parsegame initialFit item not found"<<endl;
											}
											break;
										}else if(line.substr(beginint, lenint) == "cargo"){
											getparameter(line, "Unit", i,1, &beginint, &lenint);
											map<string,uint32_t>::iterator susi = itemlistFileNames.find(line.substr(beginint, lenint));
											if(susi != itemlistFileNames.end()){
												if (getparameter(line, "Unit", i,2, &beginint, &lenint)){
													itemlist[susi->second];
													ship->getCargoBay()->AddReturn(itemlist[susi->second],strToInt(line.substr(beginint, lenint)));
												}
											}else{
												cerr<<"WARNING Sdatabase::parsegame initialFit item not found"<<endl;
											}
											break;
										}
									}
								}else
									break;
							}
						}
					}
				}
			}
		}
	}
}

void ParseData(ifstream* file,string filename) {
	uint32_t id = 0;
	map<string,uint32_t>::iterator tempit = itemlistFileNames.find(filename);
	if (tempit != itemlistFileNames.end() )
		id = tempit->second;

	if (filename.find("itemtexname.txt", 0) != string::npos)
		return;
	if (filename.find("objtexname.txt", 0) != string::npos)
		return;
	if (filename.find("shottexname.txt", 0) != string::npos)
		return;
	if (!id){
		cerr<<"WARNING Sdatabase::parsedata itemfilename not found"<<endl;
	}
	uint32_t beginint = 0;
	uint32_t lenint = 0;
	string parseState = "";
	string parseSubState = "";
	string line;

	SShipType* shiptype = NULL;
	SAstoroidType* astoroidtype = NULL;
	SSubType* subtype = NULL;
	cerr<<filename<<endl;
	while (std::getline((*file), line)) {
		
		if (line.find("//") != string::npos)
			continue;
		if (line.find("[ShipType]", 0) != string::npos) {
			cerr<<"ship"<<endl;
			parseState = "ShipType";
			parseSubState = "base";
			shiptype = new SShipType(id);
			shipTypes[id] = shiptype;
			SItemType* itemt = itemlist[id];
			itemt->setShipType(shiptype);
			itemlist[id] = itemt;
		}else if (line.find("[Weapon]", 0) != string::npos) {
			cerr<<"wep"<<endl;
			parseState = "WeaponType";
			parseSubState = "base";
			SItemType* itemt = itemlist[id];
			subtype = new SSubTypeWep();
			itemt->setSubType(subtype);
			itemlist[id] = itemt;
		}else if (line.find("[Bonus]", 0) != string::npos) {
			cerr<<"bonus"<<endl;
			parseState = "BonusType";
			parseSubState = "base";
			SItemType* itemt = itemlist[id];
			subtype = new SSubTypeBonus();
			itemt->setSubType(subtype);
			itemlist[id] = itemt;
		}else if (line.find("[Boost]", 0) != string::npos) {
			cerr<<"boost"<<endl;
			parseState = "BoostType";
			parseSubState = "base";
			SItemType* itemt = itemlist[id];
			subtype = new SSubTypeBoost();
			itemt->setSubType(subtype);
			itemlist[id] = itemt;
		}else if (line.find("[FactoryType]", 0) != string::npos) {
			cerr<<"fac"<<endl;
			parseState = "FactoryType";
			parseSubState = "base";
			SItemType* itemt = itemlist[id];
			subtype = new SSubTypeFac();
			itemt->setSubType(subtype);
			itemlist[id] = itemt;
		}else if (line.find("[RefineryType]", 0) != string::npos) {
			cerr<<"ref"<<endl;
			parseState = "RefineryType";
			parseSubState = "base";
			SItemType* itemt = itemlist[id];
			subtype = new SSubTypeRef();
			itemt->setSubType(subtype);
			itemlist[id] = itemt;
		}else if (line.find("[Material]", 0) != string::npos) {
			cerr<<"mat"<<endl;
			parseState = "MaterialType";
			parseSubState = "base";
			SItemType* itemt = itemlist[id];
			itemlist[id] = itemt;
		}else if (line.find("[AstoroidType]", 0) != string::npos) {
			cerr<<"asttype"<<endl;
			parseState = "AstoroidType";
			parseSubState = "base";
			astoroidtype = new SAstoroidType(id);
			astoroidTypes[id] = astoroidtype;
		}

		if (parseState == "ShipType") {
			for (int i = 0; i < 20; i++) {
				std::stringstream ss;
				ss << "{sub" << i << "}";
				if (line.find(ss.str()) != string::npos) {
					std::stringstream ss2;
					ss2 << "sub" << i;
					parseSubState = ss2.str();
					shiptype->getSlots()[i] = new SShipTypeSlotData();

				}
			}
			if (line.find("{item}") != string::npos) {
				parseSubState = "item";
			}

			if (parseSubState == "base") {
				if (line.find("name") != string::npos) {
					getAllparameter(line, "name", &beginint, &lenint);
					shiptype->setName(line.substr(beginint, lenint));
				} else if (line.find("size") != string::npos) {
					getparameter(line, "size", 0, &beginint, &lenint);
					shiptype->setSize(strToInt(line.substr(beginint, lenint)));
				} else if (line.find("mass") != string::npos) {
					getparameter(line, "mass", 0, &beginint, &lenint);
					shiptype->setMass(strToInt(line.substr(beginint, lenint)));
				} else if (line.find("recoilrecharge") != string::npos) {
					getparameter(line, "recoilrecharge", 0, &beginint, &lenint);
					shiptype->setRecoilRecharge(strToInt(line.substr(beginint, lenint)));
				} else if (line.find("speed") != string::npos) {
					getparameter(line, "speed", 0, &beginint, &lenint);
					shiptype->setTopSpeed(strToInt(line.substr(beginint, lenint)));
				} else if (line.find("agility") != string::npos) {
					getparameter(line, "agility", 0, &beginint, &lenint);
					shiptype->setAgility(strToInt(line.substr(beginint, lenint)));
				} else if (line.find("cargo") != string::npos) {
					getparameter(line, "cargo", 0, &beginint, &lenint);
					shiptype->setCargo(strToInt(line.substr(beginint, lenint)));
				} else if (line.find("targettype") != string::npos) {
					getparameter(line, "targettype", 0, &beginint, &lenint);
					shiptype->setTargetType(parseTargetType(line.substr(beginint, lenint)));
				} else if (line.find("texture") != string::npos) {
					getparameter(line, "texture", 0, &beginint, &lenint);
					shiptype->settexture(parseobjtextureid(line.substr(beginint, lenint)));
				} else if (line.find("energy") != string::npos) {
					getparameter(line, "energy", 0, &beginint, &lenint);
					shiptype->setEnergy(strToInt(line.substr(beginint, lenint)));
				} else if (line.find("scanrange") != string::npos) {
					getparameter(line, "scanrange", 0, &beginint, &lenint);
					shiptype->setScanRange(strToInt(line.substr(beginint, lenint)));
				} else if (line.find("scanprange") != string::npos) {
					getparameter(line, "scanprange", 0, &beginint, &lenint);
					shiptype->setScanPRange(strToInt(line.substr(beginint, lenint)));
				} else if (line.find("recharge") != string::npos) {
					getparameter(line, "recharge", 0, &beginint, &lenint);
					shiptype->setRecharge(strToInt(line.substr(beginint, lenint)));
				} else if (line.find("hull") != string::npos) {
					getparameter(line, "hull", 0, &beginint, &lenint);
					shiptype->setHull(strToInt(line.substr(beginint, lenint)));
				} else if (line.find("armor") != string::npos) {
					getparameter(line, "armor", 0, &beginint, &lenint);
					shiptype->setarmor(strToInt(line.substr(beginint, lenint)));
				} else if (line.find("deflector") != string::npos) {
					getparameter(line, "deflector", 0, &beginint, &lenint);
					shiptype->setdeflector(strToInt(line.substr(beginint, lenint)));
				}else if (line.find("shieldStr") != string::npos) {
					getparameter(line, "shieldStr", 0, &beginint, &lenint);
					shiptype->setShieldStr(strToInt(line.substr(beginint, lenint)));
				}else if (line.find("shieldFw") != string::npos) {
					getparameter(line, "shieldFw", 0, &beginint, &lenint);
					shiptype->setShield(strToInt(line.substr(beginint, lenint)),0);
				}else if (line.find("shieldFL") != string::npos) {
					getparameter(line, "shieldFL", 0, &beginint, &lenint);
					shiptype->setShield(strToInt(line.substr(beginint, lenint)),1);
				}else if (line.find("shieldFR") != string::npos) {
					getparameter(line, "shieldFR", 0, &beginint, &lenint);
					shiptype->setShield(strToInt(line.substr(beginint, lenint)),2);
				}else if (line.find("shieldAf") != string::npos) {
					getparameter(line, "shieldAf", 0, &beginint, &lenint);
					shiptype->setShield(strToInt(line.substr(beginint, lenint)),3);
				}else if (line.find("shieldAL") != string::npos) {
					getparameter(line, "shieldAL", 0, &beginint, &lenint);
					shiptype->setShield(strToInt(line.substr(beginint, lenint)),4);
				}else if (line.find("shieldAR") != string::npos) {
					getparameter(line, "shieldAR", 0, &beginint, &lenint);
					shiptype->setShield(strToInt(line.substr(beginint, lenint)),5);
				}

			} else {
				for (int i = 0; i < 20; i++) {
					std::stringstream ss;
					ss << "sub" << i;

					if (parseSubState == ss.str()) {
						if (line.find("uicord") != string::npos){
							getparameter(line, "uicord", 0, &beginint, &lenint);
							uint32_t uix = strToInt(line.substr(beginint, lenint));
							getparameter(line, "uicord", 1, &beginint, &lenint);
							uint32_t uiy = strToInt(line.substr(beginint, lenint));
							shiptype->getSlots()[i]->setuiX(uix);
							shiptype->getSlots()[i]->setuiY(uiy);
						}
						if (line.find("cord") != string::npos){
							getparameter(line, "cord", 0, &beginint, &lenint);
							uint32_t gx = strToInt(line.substr(beginint, lenint));
							getparameter(line, "cord", 1, &beginint, &lenint);
							uint32_t gy = strToInt(line.substr(beginint, lenint));
							shiptype->getSlots()[i]->setgX(gx);
							shiptype->getSlots()[i]->setgY(gy);
						}
						if (line.find("type") != string::npos){
							getparameter(line, "type", 0, &beginint, &lenint);
							FitTypes::Enum stype = parseSlotType(line.substr(beginint, lenint));
							shiptype->getSlots()[i]->setslotType(stype);
						}
						if (line.find("mount") != string::npos){
							getparameter(line, "mount", 0, &beginint, &lenint);
							uint32_t smount = strToInt(line.substr(beginint, lenint));
							shiptype->getSlots()[i]->setslotMount(smount);
						}
						if (line.find("firedir") != string::npos){
							getparameter(line, "firedir", 0, &beginint, &lenint);
							uint32_t fdir = parseFireDir(line.substr(beginint, lenint));
							shiptype->getSlots()[i]->setFireDir((FireDir::Enum)fdir);
						}
					}
				}
			}
		}else if(parseState == "BonusType" || parseState == "BoostType"){
			if (line.find("{bonus}") != string::npos) {
				parseSubState = "bonus";
			}
			if (line.find("{boost}") != string::npos) {
				parseSubState = "boost";
			}
			if (line.find("{item}") != string::npos) {
				parseSubState = "item";
			}

			if (parseSubState == "base") {
				if (line.find("name") != string::npos) {
					getAllparameter(line, "name", &beginint, &lenint);
					itemlist[id]->setName(line.substr(beginint, lenint));
				} else if (line.find("fit") != string::npos) {
					getparameter(line, "fit", 0, &beginint, &lenint);
					(subtype)->setMountType(parseSlotType(line.substr(beginint, lenint)));
					getparameter(line, "fit", 1, &beginint, &lenint);
					(subtype)->setMount(strToInt(line.substr(beginint, lenint)));
				}
			}else if (parseSubState == "bonus") {
				if (line.find("bonusarmor") != string::npos) {
					getparameter(line, "bonusarmor",0, &beginint, &lenint);
					((SSubTypeBonus*)subtype)->addBonus(BonusTypes::Armor,strToInt(line.substr(beginint, lenint)));
					(line.substr(beginint, lenint));
				}else if (line.find("bonushull") != string::npos) {
					getparameter(line, "bonushull",0, &beginint, &lenint);
					((SSubTypeBonus*)subtype)->addBonus(BonusTypes::Hull,strToInt(line.substr(beginint, lenint)));
					(line.substr(beginint, lenint));
				} else if (line.find("bonusdeflector") != string::npos) {
					getparameter(line, "bonusdeflector",0, &beginint, &lenint);
					((SSubTypeBonus*)subtype)->addBonus(BonusTypes::Deflector,strToInt(line.substr(beginint, lenint)));
					(line.substr(beginint, lenint));
				} else if (line.find("bonusenergy") != string::npos) {
					getparameter(line, "bonusenergy",0, &beginint, &lenint);
					((SSubTypeBonus*)subtype)->addBonus(BonusTypes::Energy,strToInt(line.substr(beginint, lenint)));
					(line.substr(beginint, lenint));
				} else if (line.find("bonusscanrange") != string::npos) {
					getparameter(line, "bonusscanrange",0, &beginint, &lenint);
					((SSubTypeBonus*)subtype)->addBonus(BonusTypes::ScanRange,strToInt(line.substr(beginint, lenint)));
					(line.substr(beginint, lenint));
				} else if (line.find("bonusscanprange") != string::npos) {
					getparameter(line, "bonusscanprange",0, &beginint, &lenint);
					((SSubTypeBonus*)subtype)->addBonus(BonusTypes::ScanPRange,strToInt(line.substr(beginint, lenint)));
					(line.substr(beginint, lenint));
				} else if (line.find("bonusturretscanres") != string::npos) {
					getparameter(line, "bonusturretscanres",0, &beginint, &lenint);
					((SSubTypeBonus*)subtype)->addBonus(BonusTypes::TurretRes,strToInt(line.substr(beginint, lenint)));
					(line.substr(beginint, lenint));
				} else if (line.find("bonusmissiledmg") != string::npos) {
					getparameter(line, "bonusmissiledmg",0, &beginint, &lenint);
					((SSubTypeBonus*)subtype)->addBonus(BonusTypes::MissileDmgBonus,strToInt(line.substr(beginint, lenint)));
					(line.substr(beginint, lenint));
				} else if (line.find("bonusbeamdmg") != string::npos) {
					getparameter(line, "bonusbeamdmg",0, &beginint, &lenint);
					((SSubTypeBonus*)subtype)->addBonus(BonusTypes::BeamDmgBonus,strToInt(line.substr(beginint, lenint)));
					(line.substr(beginint, lenint));
				} else if (line.find("bonusprojectiledmg") != string::npos) {
					getparameter(line, "bonusprojectiledmg",0, &beginint, &lenint);
					((SSubTypeBonus*)subtype)->addBonus(BonusTypes::ProjectileDmgBonus,strToInt(line.substr(beginint, lenint)));
					(line.substr(beginint, lenint));
				} else if (line.find("speedthruster") != string::npos) {
					getparameter(line, "speedthruster",0, &beginint, &lenint);
					((SSubTypeBonus*)subtype)->addBonus(BonusTypes::SpeedThruster,strToInt(line.substr(beginint, lenint)));
					(line.substr(beginint, lenint));
				} else if (line.find("manuverethruster") != string::npos) {
					getparameter(line, "manuverethruster",0, &beginint, &lenint);
					((SSubTypeBonus*)subtype)->addBonus(BonusTypes::ManuvereThruster,strToInt(line.substr(beginint, lenint)));
					(line.substr(beginint, lenint));
				} else if (line.find("bonuserecharge") != string::npos) {
					getparameter(line, "bonuserecharge",0, &beginint, &lenint);
					((SSubTypeBonus*)subtype)->addBonus(BonusTypes::ERecharge,strToInt(line.substr(beginint, lenint)));
					(line.substr(beginint, lenint));
				} else if (line.find("bonusshieldstr") != string::npos) {
					getparameter(line, "bonusshieldstr",0, &beginint, &lenint);
					((SSubTypeBonus*)subtype)->addBonus(BonusTypes::ShieldStr,strToInt(line.substr(beginint, lenint)));
					(line.substr(beginint, lenint));
				}
				
			}else if (parseSubState == "boost") {
				 if (line.find("amorechargerate") != string::npos) {
					getparameter(line, "amorechargerate", 0, &beginint, &lenint);
					((SSubTypeBoost*)subtype)->setAmoRechargeRate(strToInt(line.substr(beginint, lenint)));
				} else if (line.find("amotype") != string::npos) {
					getparameter(line, "amotype", 0, &beginint, &lenint);
					if (line.substr(beginint, lenint).find("energy") != 0){
						map<string,uint32_t>::iterator susi = itemlistFileNames.find(line.substr(beginint, lenint));
						if(susi != itemlistFileNames.end())
							((SSubTypeBoost*)subtype)->setAmoCostType(itemlist[susi->second]);
						else
							cerr<<"WARNING Sdatabase::parsedata amotype itemname not found"<<endl;
					}else
						((SSubTypeBoost*)subtype)->setAmoCostType(NULL);
				} else if (line.find("amocost") != string::npos) {
					getparameter(line, "amocost", 0, &beginint, &lenint);
					((SSubTypeBoost*)subtype)->setamoCost(strToInt(line.substr(beginint, lenint)));
				} else if (line.find("energycost") != string::npos) {
					getparameter(line, "energycost", 0, &beginint, &lenint);
					((SSubTypeBoost*)subtype)->setenegyCost(strToInt(line.substr(beginint, lenint)));
				} else if (line.find("maxamo") != string::npos) {
					getparameter(line, "maxamo", 0, &beginint, &lenint);
					((SSubTypeBoost*)subtype)->setMaxAmo(strToInt(line.substr(beginint, lenint)));
				} else if (line.find("cooldown") != string::npos) {
					getparameter(line, "cooldown", 0, &beginint, &lenint);
					((SSubTypeBoost*)subtype)->setMaxCd(100*strToInt(line.substr(beginint, lenint)));
				} else if (line.find("boosttype") != string::npos) {
					getparameter(line, "boosttype", 0, &beginint, &lenint);
					((SSubTypeBoost*)subtype)->setBoostType(parseBonusTypes(line.substr(beginint, lenint)));
				} else if (line.find("boostvalue") != string::npos) {
					getparameter(line, "boostvalue", 0, &beginint, &lenint);
					((SSubTypeBoost*)subtype)->setBoostAmount(strToInt(line.substr(beginint, lenint)));

				}
			}
		}else if (parseState == "WeaponType") {
			
			if (line.find("{projectile}") != string::npos) {
				parseSubState = "projectile";
			}

			if (line.find("{item}") != string::npos) {
				parseSubState = "item";
			}

			if (parseSubState == "base") {
				if (line.find("name") != string::npos) {
					getAllparameter(line, "name", &beginint, &lenint);
					itemlist[id]->setName(line.substr(beginint, lenint));
				} else if (line.find("sequence ") != string::npos) {
					for (int i = 0; i < 10; i++){
						if (getparameter(line, "sequence", i, &beginint, &lenint)){
							((SSubTypeWep*)subtype)->fireseq().push_back(strToInt(line.substr(beginint, lenint)));
						}
					}
				} else if (line.find("keys ") != string::npos) {
					for (int i = 0; i < 10; i++){
						if (getparameter(line, "keys", i, &beginint, &lenint)){
							(subtype)->getSubKeys()[(parseSubKeyWord(line.substr(beginint, lenint)))] = true;
						}
					}
				} else if (line.find("sequencemax") != string::npos) {
					getparameter(line, "sequencemax", 0, &beginint, &lenint);
					((SSubTypeWep*)subtype)->setmaxseq(strToInt(line.substr(beginint, lenint)));
				} else if (line.find("fit") != string::npos) {
					getparameter(line, "fit", 0, &beginint, &lenint);
					(subtype)->setMountType(parseSlotType(line.substr(beginint, lenint)));
					getparameter(line, "fit", 1, &beginint, &lenint);
					(subtype)->setMount(strToInt(line.substr(beginint, lenint)));
				} else if (line.find("recoil") != string::npos) {
					getparameter(line, "recoil", 0, &beginint, &lenint);
					((SSubTypeWep*)subtype)->setRecoil(strToInt(line.substr(beginint, lenint)));
				} else if (line.find("amorechargerate") != string::npos) {
					getparameter(line, "amorechargerate", 0, &beginint, &lenint);
					((SSubTypeWep*)subtype)->setAmoRechargeRate(strToInt(line.substr(beginint, lenint)));
				} else if (line.find("amotype") != string::npos) {
					getparameter(line, "amotype", 0, &beginint, &lenint);
					if (line.substr(beginint, lenint).find("energy") != 0){
						map<string,uint32_t>::iterator susi = itemlistFileNames.find(line.substr(beginint, lenint));
						if(susi != itemlistFileNames.end())
							((SSubTypeWep*)subtype)->setAmoCostType(itemlist[susi->second]);
						else
							cerr<<"WARNING Sdatabase::parsedata amotype itemname not found"<<endl;
					}else
						((SSubTypeWep*)subtype)->setAmoCostType(NULL);
				} else if (line.find("amocost") != string::npos) {
					getparameter(line, "amocost", 0, &beginint, &lenint);
					((SSubTypeWep*)subtype)->setamoCost(strToInt(line.substr(beginint, lenint)));
				} else if (line.find("energycost") != string::npos) {
					getparameter(line, "energycost", 0, &beginint, &lenint);
					((SSubTypeWep*)subtype)->setenegyCost(strToInt(line.substr(beginint, lenint)));
				} else if (line.find("maxamo") != string::npos) {
					getparameter(line, "maxamo", 0, &beginint, &lenint);
					((SSubTypeWep*)subtype)->setMaxAmo(strToInt(line.substr(beginint, lenint)));
				} else if (line.find("cooldown") != string::npos) {
					getparameter(line, "cooldown", 0, &beginint, &lenint);
					((SSubTypeWep*)subtype)->setMaxCd(100*strToInt(line.substr(beginint, lenint)));
				} else if (line.find("damage") != string::npos) {
					getparameter(line, "damage", 0, &beginint, &lenint);
					((SSubTypeWep*)subtype)->setDmgMin(1000*strToInt(line.substr(beginint, lenint)));
					getparameter(line, "damage", 1, &beginint, &lenint);
					((SSubTypeWep*)subtype)->setDmgMax(1000*strToInt(line.substr(beginint, lenint)));
				} else if (line.find("dmgtype") != string::npos) {
					getparameter(line, "dmgtype", 0, &beginint, &lenint);
					((SSubTypeWep*)subtype)->setDmgTypes(parseDmgTypes(line.substr(beginint, lenint)));
				} else if (line.find("range") != string::npos) {
					getparameter(line, "range", 0, &beginint, &lenint);
					((SSubTypeWep*)subtype)->setRange(1000*strToInt(line.substr(beginint, lenint)));
				} else if (line.find("flighttime") != string::npos) {
					getparameter(line, "flighttime", 0, &beginint, &lenint);
					((SSubTypeWep*)subtype)->setFlightTime(strToInt(line.substr(beginint, lenint)));
				} else if (line.find("trackingspeed") != string::npos) {
					getparameter(line, "trackingspeed", 0, &beginint, &lenint);
					((SSubTypeWep*)subtype)->setTracking(strToInt(line.substr(beginint, lenint)));
				} else if (line.find("trackingtime") != string::npos) {
					getparameter(line, "trackingtime", 0, &beginint, &lenint);
					((SSubTypeWep*)subtype)->setTrackingTime(strToInt(line.substr(beginint, lenint)));
				} else if (line.find("resolution") != string::npos) {
					getparameter(line, "resolution", 0, &beginint, &lenint);
					((SSubTypeWep*)subtype)->setResolution(strToInt(line.substr(beginint, lenint)));

				}

			}else if (parseSubState == "projectile") {
				if (line.find("speed") != string::npos) {
					getparameter(line, "speed", 0, &beginint, &lenint);
					((SSubTypeWep*)subtype)->setSpeed(strToInt(line.substr(beginint, lenint)));
				}else if (line.find("texture") != string::npos) {
					getparameter(line, "texture", 0, &beginint, &lenint);
					((SSubTypeWep*)subtype)->setTexId(parseShottex(line.substr(beginint, lenint)));
				} else if (line.find("spread") != string::npos) {
					getparameter(line, "spread", 0, &beginint, &lenint);
					((SSubTypeWep*)subtype)->setSpread(strToInt(line.substr(beginint, lenint)));
				}
			}


		}else if (parseState == "FactoryType") {

			if (line.find("{item}") != string::npos) {
				parseSubState = "item";
			}

			if (parseSubState == "base") {
				if (line.find("name") != string::npos) {
					getAllparameter(line, "name", &beginint, &lenint);
					itemlist[id]->setName(line.substr(beginint, lenint));
				} else if (line.find("fit") != string::npos) {
					getparameter(line, "fit", 0, &beginint, &lenint);
					(subtype)->setMountType(parseSlotType(line.substr(beginint, lenint)));
					getparameter(line, "fit", 1, &beginint, &lenint);
					(subtype)->setMount(strToInt(line.substr(beginint, lenint)));
				} else if (line.find("builds") != string::npos) {
					for (int i = 0; i < 50; i++){
						if (getparameter(line, "builds", i, &beginint, &lenint)){
							map<string,uint32_t>::iterator susi = itemlistFileNames.find(line.substr(beginint, lenint));
							if(susi != itemlistFileNames.end())
								((SSubTypeFac*)subtype)->getCanBuildList()[susi->second] = itemlist[susi->second];
							else
								cerr<<"WARNING Sdatabase::parsedata FactoryType itemname not found"<<endl;

						}
					}
				}

			}
		}else if (parseState == "RefineryType") {

			if (line.find("{item}") != string::npos) {
				parseSubState = "item";
			}

			if (parseSubState == "base") {
				if (line.find("name") != string::npos) {
					getAllparameter(line, "name", &beginint, &lenint);
					itemlist[id]->setName(line.substr(beginint, lenint));
				} else if (line.find("fit") != string::npos) {
					getparameter(line, "fit", 0, &beginint, &lenint);
					(subtype)->setMountType(parseSlotType(line.substr(beginint, lenint)));
					getparameter(line, "fit", 1, &beginint, &lenint);
					(subtype)->setMount(strToInt(line.substr(beginint, lenint)));
				} else if (line.find("cooldown") != string::npos) {
					getparameter(line, "cooldown", 0, &beginint, &lenint);
					((SSubTypeRef*)subtype)->setCooldown(100*strToInt(line.substr(beginint, lenint)));
				} else if (line.find("refine") != string::npos) {
					for (int i = 0; i < 25; i++){
						if (getparameter(line, "refine", i, &beginint, &lenint)){
							map<string,uint32_t>::iterator susi = itemlistFileNames.find(line.substr(beginint, lenint));
							if(susi != itemlistFileNames.end())
								((SSubTypeRef*)subtype)->getCanRefineList()[susi->second] = itemlist[susi->second];
							else
								cerr<<"WARNING Sdatabase::parsedata RefineryType itemname not found"<<endl;

						}
					}
				}
			}
		}else if (parseState == "MaterialType") {
			if (line.find("{item}") != string::npos) {
				parseSubState = "item";
			}
			if (parseSubState == "base") {
				if(line.find("name") != string::npos) {
					getAllparameter(line, "name", &beginint, &lenint);
					itemlist[id]->setName(line.substr(beginint, lenint));
				}
			}
		}else if (parseState == "AstoroidType") {
			if (parseSubState == "base") {
				if(line.find("name") != string::npos) {
					getAllparameter(line, "name", &beginint, &lenint);
					astoroidtype->setName(line.substr(beginint, lenint));
				}else if (line.find("size") != string::npos) {
					getparameter(line, "size", 0, &beginint, &lenint);
					astoroidtype->setSize(strToInt(line.substr(beginint, lenint)));
				}else if (line.find("texture") != string::npos) {
					getparameter(line, "texture", 0, &beginint, &lenint);
					astoroidtype->settexture(parseobjtextureid(line.substr(beginint, lenint)));
				}else if (line.find("minquan") != string::npos) {
					getparameter(line, "minquan", 0, &beginint, &lenint);
					astoroidtype->setMinQuan(strToInt(line.substr(beginint, lenint)));
				}else if (line.find("maxquan") != string::npos) {
					getparameter(line, "maxquan", 0, &beginint, &lenint);
					astoroidtype->setMaxQuan(strToInt(line.substr(beginint, lenint)));
				}else if (line.find("itemtype") != string::npos) {
					getparameter(line, "itemtype", 0, &beginint, &lenint);
					map<string,uint32_t>::iterator susi = itemlistFileNames.find(line.substr(beginint, lenint));
					if(susi != itemlistFileNames.end())
						astoroidtype->setItemType(itemlist[susi->second]);
					else
						cerr<<"WARNING Sdatabase::parsedata AstoroidType itemname not found"<<endl;

				}
			}
		}
		if (parseSubState == "item") {
			if (line.find("texture") != string::npos) {
				getparameter(line, "texture", 0, &beginint, &lenint);
				itemlist[id]->setTexId(parsetextureid(line.substr(beginint, lenint)));
			}else if (line.find("buildtime") != string::npos) {
				getparameter(line, "buildtime", 0, &beginint, &lenint);
				itemlist[id]->setBuildTime(1000*strToInt(line.substr(beginint, lenint)));
			}else if (line.find("buildbatch") != string::npos) {
				getparameter(line, "buildbatch", 0, &beginint, &lenint);
				itemlist[id]->setBatch(strToInt(line.substr(beginint, lenint)));
			}else if (line.find("mass") != string::npos) {
				getparameter(line, "mass", 0, &beginint, &lenint);
				itemlist[id]->setMass(strToInt(line.substr(beginint, lenint)));
			}else if (line.find("refineBatch") != string::npos) {
				getparameter(line, "refineBatch", 0, &beginint, &lenint);
				itemlist[id]->setRefineBatch(strToInt(line.substr(beginint, lenint)));
			}else if (line.find("buildCost") != string::npos) {

				for (int i = 0; i < 10; i++){
					if (getparameter(line, "buildCost", i,0, &beginint, &lenint)){
						//cerr<<"add cost item index "<<beginint<<" len "<<lenint<<" val "<<line.substr(beginint, lenint)<<endl;
						map<string,uint32_t>::iterator susi = itemlistFileNames.find(line.substr(beginint, lenint));
						if(susi != itemlistFileNames.end()){
							if (getparameter(line, "buildCost", i,1, &beginint, &lenint)){
								bmaterial tempb;
								tempb._item = itemlist[susi->second];
								tempb._quan = strToInt(line.substr(beginint, lenint));
								itemlist[id]->getCost()[susi->second] = tempb;
							}
						}else{
							cerr<<"WARNING Sdatabase::parsedata buildcost item not found"<<endl;
						}
					}
				}
			}else if (line.find("refineResult") != string::npos) {
				
				for (int i = 0; i < 10; i++){
					if (getparameter(line, "refineResult", i,0, &beginint, &lenint)){
						//cerr<<"add cost item index "<<beginint<<" len "<<lenint<<" val "<<line.substr(beginint, lenint)<<endl;
						map<string,uint32_t>::iterator susi = itemlistFileNames.find(line.substr(beginint, lenint));
						if(susi != itemlistFileNames.end()){
							if (getparameter(line, "refineResult", i,1, &beginint, &lenint)){
								bmaterial tempb;
								tempb._item = itemlist[susi->second];
								tempb._quan = strToInt(line.substr(beginint, lenint));
								itemlist[id]->getRefineTo()[susi->second] = tempb;
							}
						}else{
							cerr<<"WARNING Sdatabase::parsedata refineTo item not found"<<endl;
						}
					}
				}
			}
		}
	}
}

SDatabase::SDatabase() {

}

void SDatabase::LoadGame() {
	DIR *dp;
	struct dirent *ep;
	struct stat st;
	string datapath = "";
	if(stat("Games",&st) == 0){
		datapath= "Games";
		dp = opendir(datapath.c_str());
	}else{
		datapath= "../../../Games";
		dp = opendir(datapath.c_str());
	}
	if (dp != NULL) {
		while (ep = readdir(dp)) {
			if (string(ep->d_name) != "." && string(ep->d_name) != "..") {
				string temp = datapath + (string) "/" + string(ep->d_name);
				ifstream file(temp.c_str());
				ParseGame(&file,string(ep->d_name));
				break;
			}
		}
		(void) closedir(dp);
	} else {
		cerr << "ERROR dir not found" << endl;
	}
}
















void SDatabase::ReadSubDir(DIR *dp, string datapath){
	struct dirent *ep;
	if (dp != NULL) {
		while (ep = readdir(dp)) {
			if (string(ep->d_name) != "." && string( ep->d_name) != "..") {
				string temp = datapath + (string) "/" + string(ep->d_name);			
				DIR *dp;
				dp = opendir(temp.c_str());
				if(dp){
					ReadSubDir(opendir(temp.c_str()),temp);
				}else{
					ifstream file(temp.c_str());
					ParseData(&file,string(ep->d_name));
				}
			}
		}
		(void) closedir(dp);
	}
}

void SDatabase::LoadAllItems() {

	parseDataItemrefs();
	DIR *dp;
	struct dirent *ep;

	uint32_t susi = 1;
	struct stat st;
	string datapath = "";
	if(stat("database",&st) == 0){
		datapath= "database";
		dp = opendir(datapath.c_str());
	}else{
		datapath= "../../../database";
		dp = opendir(datapath.c_str());
	}
	if (dp != NULL) {
		ReadSubDir(dp,datapath);
	}

}



void SDatabase::CheckRefs(){
	for (map<uint32_t,SItemType*>::iterator it = itemlist.begin(); it != itemlist.end();it++){
		if (it->second->getSubType() && it->second->getSubType()->getClass() == SubSystemClass::Fac){
			SSubTypeFac* temp = it->second->getSubType()->isFac();
			for ( map<uint32_t,SItemType*>::iterator it2 = temp->getCanBuildList().begin(); it2 != temp->getCanBuildList().end();it2++){
				if (it2->second == NULL){
					temp->getCanBuildList()[it2->first] = itemlist[it2->first];
				}
			}
		}
		if( it->second){
			for (map <uint32_t,bmaterial>::iterator it2 = it->second->getCost().begin();it2 != it->second->getCost().end();it2++){
				if (!it2->second._item){
					it2->second._item = itemlist[it2->first];
				}
			}
		}
	}
	for (map<uint32_t, SAstoroidType*>::iterator it = astoroidTypes.begin(); it != astoroidTypes.end(); it++){
		if (it->second){
			if(it->second->getItemTypeId()){
				if (itemlist.find(it->second->getItemTypeId()) != itemlist.end()){
					it->second->setItemType(itemlist[it->second->getItemTypeId()]);
				}
			}
		}
	}
}

SDatabase::~SDatabase() {
}

