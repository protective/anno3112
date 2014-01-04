/* 
 * File:   GFunctions.cpp
 * Author: karsten
 * 
 * Created on 23. april 2011, 10:43
 */

#include <math.h>

#include "GFunctions.h"
#include "../Network/Serialize.h"
void printBuffer(char* buffer, uint32_t len){
	int offset = 0;
	int loopoffset = 0;
	if (printbufferbool){
		while (offset < len){
			//cerr<<"offset "<<offset<<endl;
			SerialData* temp = (SerialData*)(buffer + offset);
			if (len - offset >= sizeof(uint32_t)*2 && temp->_size <= len - offset){
				cerr<<"parse len "<< temp->_size<<endl;
				SerialData* st = (SerialData*)(buffer+offset);
				cerr<<"Recived ********************"<<endl
						<<"\ttype "<<st->_type <<endl
						<<"\tsize "<<st->_size<<endl;

				switch(temp->_type)
				{
					case SerialType::SerialTime:{
						SerialTime* st = (SerialTime*)(buffer+offset);
						cerr<<"Recived RegTime*************"<<endl
						<<"\tTime "<<st->time<<endl;
						cerr<<"****************************"<<endl;

						break;
					}
					case SerialType::SerialReqJoin:{
						SerialReqJoin* st = (SerialReqJoin*)(buffer+offset);
						cerr<<"Recived RegJoin*************"<<endl
						<<"\tid "<<st->_unitId<<endl
						<<"\tpass "<<st->_pass<<endl;
						cerr<<"****************************"<<endl;
						break;
					}
					case SerialType::SerialPlayerTeam:{
						SerialPlayerTeam* st = (SerialPlayerTeam*)(buffer+offset);
						cerr<<"Recived SerialPlayerTeam*************"<<endl
						<<"\tplayerid "<<st->_playerId<<endl
						<<"\tteam "<<st->_team<<endl;
						cerr<<"****************************"<<endl;
						break;
					}
					case SerialType::SerialLoadout:{
						SerialLoadout* st = (SerialLoadout*)(buffer+offset);
						cerr<<"Recived SerialLoadout*************"<<endl
						<<"\tid "<<st->_id<<endl
						<<"\tshiptype "<<st->_shiptype<<endl
						<<"\tname "<<st->_name<<endl;
						cerr<<"****************************"<<endl;
						break;
					}
					case SerialType::SerialGrid:{
						if (printposbufferbool){
						SerialGrid* st = (SerialGrid*)(buffer+offset);
						cerr<<"Recived SerialGrid*******"<<endl
						<<"\tid "<<st->_Id<<endl
							<<"\t\twight "<<st->_wight<<endl
							<<"\t\thight "<<st->_hight<<endl

							<<endl;

						cerr<<"****************************"<<endl;
						}
						break;
					}
					case SerialType::SerialObjFullUpdate:{
						if (printposbufferbool){
						SerialObjFullUpdate* st = (SerialObjFullUpdate*)(buffer+offset);
						cerr<<"Recived ObjFullUpdate*******"<<endl
						<<"\tid "<<st->_Id<<endl
							<<"\t\tp_x "<<st->_Pos_x<<endl
							<<"\t\tp_y "<<st->_Pos_y<<endl
							<<"\t\tp_d "<<st->_Pos_d<<endl
							<<endl;

						cerr<<"****************************"<<endl;
						}
						break;
					}
					case SerialType::SerialReqChangePrio:{
						if (printposbufferbool){
						SerialReqChangePrio* st = (SerialReqChangePrio*)(buffer+offset);
						cerr<<"Recived SerialReqChangePrio*******"<<endl
						<<"\tid "<<st->_Id<<endl
						<<"\t\tprio "<<(int)st->_prio<<endl
						<<endl;
						
						cerr<<"****************************"<<endl;
						}
						break;
					}
					case SerialType::SerialObjPrio:{
						if (printposbufferbool){
						SerialObjPrio* st = (SerialObjPrio*)(buffer+offset);
						cerr<<"Recived SerialObjPrio*******"<<endl
						<<"\tid "<<st->_Id<<endl
						<<"\t\tprio "<<(int)st->_prio<<endl
						<<endl;

						cerr<<"****************************"<<endl;
						}
						break;
					}
					case SerialType::SerialReqSetOrdreUnit:{
						if (printposbufferbool){
						SerialReqSetOrdreUnit* st = (SerialReqSetOrdreUnit*)(buffer+offset);
						cerr<<"Recived SerialReqSetOrdreUnit*******"<<endl
						<<"\tId "<<st->_Id<<endl
						<<"\toindex "<<st->_oindex<<endl
						<<"\tToId "<<st->_ToId<<endl;
						cerr<<"****************************"<<endl;
						}
						break;
					}
					
					case SerialType::SerialReqSetOrdrePos:{
						if (printposbufferbool){
						SerialReqSetOrdrePos* st = (SerialReqSetOrdrePos*)(buffer+offset);
						cerr<<"Recived SerialReqSetOrdrePos*******"<<endl
						<<"\tid "<<st->_Id<<endl
						<<"\toindex "<<st->_oindex<<endl
							<<"\t\tp_x "<<st->_Pos_x<<endl
							<<"\t\tp_y "<<st->_Pos_y<<endl
							<<"\t\tp_d "<<st->_Pos_d<<endl
							<<endl;

						cerr<<"****************************"<<endl;
						}
						break;
					}


					case SerialType::SerialShipFullUpdate:{
						if (printposbufferbool){
						SerialShipFullUpdate* st = (SerialShipFullUpdate*)(buffer+offset);
						cerr<<"Recived SerialShipFullUpdate*******"<<endl
						<<"\tid "<<st->_Id<<endl
						<<"\tplayerOwner "<<st->_playerOwner<<endl
						<<"\ttypeid "<<st->_ShipType<<endl
							<<"\t\tp_x "<<st->_Pos_x<<endl
							<<"\t\tp_y "<<st->_Pos_y<<endl
							<<"\t\tp_d "<<st->_Pos_d<<endl
							<<endl;

						cerr<<"****************************"<<endl;
						}
						break;
					}
					case SerialType::SerialShipDetailUpdate:{
						if (printposbufferbool){
						SerialShipDetailUpdate* st = (SerialShipDetailUpdate*)(buffer+offset);
						cerr<<"Recived SerialShipDetailUpdate*******"<<endl
						<<"\tid "<<st->_Id<<endl
						<<"\tOrdreId "<<st->_OrdreId<<endl
						<<"\tEnergy "<<st->_energy<<endl
						<<endl;

						cerr<<"****************************"<<endl;
						}
						break;
					}
					case SerialType::SerialAstoroidFullUpdate:{
						if (printposbufferbool){
						SerialAstoroidFullUpdate* st = (SerialAstoroidFullUpdate*)(buffer+offset);
						cerr<<"Recived SerialAstoroidFullUpdate*******"<<endl
						<<"\tid "<<st->_Id<<endl
						<<"\ttypeid "<<st->_astoroidType<<endl
							<<"\t\tp_x "<<st->_Pos_x<<endl
							<<"\t\tp_y "<<st->_Pos_y<<endl
							<<"\t\tp_d "<<st->_Pos_d<<endl
							<<endl;

						cerr<<"****************************"<<endl;
						}
						break;
					}
					case SerialType::SerialShipDestroy:{
						if (printposbufferbool){
						SerialShipDestroy* st = (SerialShipDestroy*)(buffer+offset);
						cerr<<"Recived SerialShipDestroy*******"<<endl
						<<"\tid "<<st->_Id<<endl
						<<"\tmode "<<st->_mode<<endl
						<<endl;

						cerr<<"****************************"<<endl;
						}
						break;
					}
					case SerialType::SerialAstoroidDestroy:{
						if (printposbufferbool){
						SerialAstoroidDestroy* st = (SerialAstoroidDestroy*)(buffer+offset);
						cerr<<"Recived SerialAstoroidDestroy*******"<<endl
						<<"\tid "<<st->_Id<<endl
						<<"\tmode "<<st->_mode<<endl
						<<endl;

						cerr<<"****************************"<<endl;
						}
						break;
					}
					case SerialType::SerialCargoItem:{
						if (printposbufferbool){
						SerialCargoItem* st = (SerialCargoItem*)(buffer+offset);
						cerr<<"Recived SerialCargoItem*******"<<endl
						<<"\tid "<<st->_Id<<endl
						<<"\titemId "<<st->_itemid<<endl
						<<"\tquantity "<<st->_quantity<<endl
						<<endl;
						cerr<<"****************************"<<endl;
						}
						break;
					}
					case SerialType::SerialReqTransfereCargo:{
						if (printposbufferbool){
						SerialReqTransfereCargo* st = (SerialReqTransfereCargo*)(buffer+offset);
						cerr<<"Recived SerialReqTransfereCargo*******"<<endl
						<<"\tFrom "<<st->_FromId<<endl
						<<"\tTo "<<st->_ToId<<endl
						<<"\titemId "<<st->_itemid<<endl
						<<"\tquantity "<<st->_quantity<<endl
						<<endl;
						cerr<<"****************************"<<endl;
						}
						break;
					}
					case SerialType::SerialReqFitLoadout:{
						if (printposbufferbool){
						SerialReqFitLoadout* st = (SerialReqFitLoadout*)(buffer+offset);
						cerr<<"Recived SerialReqFitLoadout*******"<<endl
						<<"\tFrom "<<st->_FromId<<endl
						<<"\tTo "<<st->_ToId<<endl
						<<"\tLoadoutId "<<st->_loadoutId<<endl
						<<endl;
						cerr<<"****************************"<<endl;
						}
						break;
					}
					case SerialType::SerialReqFit:{
						if (printposbufferbool){
						SerialReqFit* st = (SerialReqFit*)(buffer+offset);
						cerr<<"Recived SerialReqFit*******"<<endl
						<<"\tFrom "<<st->_FromId<<endl
						<<"\tTo "<<st->_ToId<<endl
						<<"\tsubid "<<st->_subid<<endl
						<<"\titemId "<<st->_itemid<<endl
						<<"\tquantity "<<st->_quantity<<endl
						<<endl;
						cerr<<"****************************"<<endl;
						}
						break;
					}
					case SerialType::SerialReqChangeSubTG:{
						if (printposbufferbool){
						SerialReqChangeSubTG* st = (SerialReqChangeSubTG*)(buffer+offset);
						cerr<<"Recived SerialReqChangeSubTG*******"<<endl
						<<"\tshipID "<<st->_ShipId<<endl
						<<"\tsubid "<<st->_SubId<<endl
						<<"\ttargetGroup "<<st->_TargetGroup<<endl
						<<endl;
						cerr<<"****************************"<<endl;
						}
						break;
					}
					case SerialType::SerialReqChangeOrdres:{
						if (printposbufferbool){
						SerialReqChangeOrdres* st = (SerialReqChangeOrdres*)(buffer+offset);
						cerr<<"Recived SerialReqChangeOrdres*******"<<endl
						<<"\tshipID "<<st->_ShipId<<endl
						<<"\tordreid "<<st->_OrdreId <<endl
						<<endl;
						cerr<<"****************************"<<endl;
						}
						break;
					}
					case SerialType::SerialReqChangeSubStatus:{
						if (printposbufferbool){
						SerialReqChangeSubStatus* st = (SerialReqChangeSubStatus*)(buffer+offset);
						cerr<<"Recived serialReqChangeSubStatus*******"<<endl
						<<"\tshipID "<<st->_ShipId<<endl
						<<"\tsubid "<<st->_SubId<<endl
						<<"\tstatusfield "<<st->_StatusField<<endl
						<<endl;
						cerr<<"****************************"<<endl;
						}
						break;
					}
					case SerialType::SerialReqUnfit:{
						if (printposbufferbool){
						SerialReqUnfit* st = (SerialReqUnfit*)(buffer+offset);
						cerr<<"Recived SerialReqUnfit*******"<<endl
						<<"\tFrom "<<st->_FromId<<endl
						<<"\tsubid "<<st->_subid<<endl
						<<"\tTo "<<st->_ToId<<endl
						<<"\tquantity "<<st->_quantity<<endl
						<<endl;
						cerr<<"****************************"<<endl;
						}
						break;
					}
					case SerialType::SerialShipSub:{
						if (printposbufferbool){
						SerialShipSub* st = (SerialShipSub*)(buffer+offset);
						cerr<<"Recived SerialShipSub*******"<<endl
						<<"\tid "<<st->_Id<<endl
						<<"\tsubId "<<st->_subId<<endl
						<<"\titemType "<<st->_itemType<<endl
						<<"\txItem "<<st->_xitem<<endl
						<<"\tStatusField "<<st->_statusField<<endl
						<<"\tAmo "<<st->_amo<<endl
						<<"\tEnergy "<<st->_shipEnergy<<endl
						<<"\ttargetGroup "<<st->_targetGroup<<endl;

						for (uint16_t i = 0; i < st->_xitem;i++){
							SerialShipSubIndu* st2 = (SerialShipSubIndu*)(buffer+offset+sizeof(SerialShipSub)+(sizeof(SerialShipSubIndu)*i));
							cerr<<"\t\tdurration "<<st2->_durration<<endl
							<<"\t\tmaxdurration "<<st2->_maxdurration<<endl
							<<"\t\thp "<<st2->_hp<<endl;
						}
						cerr<<endl;
						cerr<<"****************************"<<endl;
						}
						break;
					}

					case SerialType::SerialReqCreateLoadOut:{
						if (printposbufferbool){
						SerialReqCreateLoadOut* st = (SerialReqCreateLoadOut*)(buffer+offset);
						cerr<<"Recived SerialReqCreateLoadOut*******"<<endl
						<<"\tname "<<st->_name<<endl
						<<"\tshipType "<<st->_shiptype<<endl
						<<"\t_xloaditems "<<st->_xloaditems<<endl;

						for (uint16_t i = 0; i < st->_xloaditems;i++){
							SerialReqCreateLoadItems* st2 = (SerialReqCreateLoadItems*)(buffer+offset+sizeof(SerialReqCreateLoadOut)+(sizeof(SerialReqCreateLoadItems)*i));
							cerr<<"\t\titem "<<st2->_itemid<<endl
								<<"\t\txitem"<<st2->_xitem<<endl
								<<"\t\tslot"<<st2->_slotid<<endl
								<<"\t\ttartgetgroup"<<st2->_targetgroup<<endl;
						}
						cerr<<endl;

						cerr<<"****************************"<<endl;
						}
						break;
					}


					case SerialType::SerialShipType:{
						if (printposbufferbool){
						SerialShipType* st = (SerialShipType*)(buffer+offset);
						cerr<<"Recived SerialShipType*******"<<endl
						<<"\tshipTypeId "<<st->_ShipTypeId<<endl
						<<"\tshipSize "<<st->_ShipSize<<endl
						<<"\tmass "<<st->_mass<<endl
						<<"\ttopspeed "<<st->_topspeed<<endl
						<<"\tagility "<<st->_agility<<endl
						<<"\ttexture "<<st->_texture<<endl
						<<"\tItemId "<<st->_item._itemId<<endl
						<<"\titemTex "<<st->_item._itemtex<<endl
						<<"\tmatcount "<<st->_item._matcount<<endl;

							for (uint16_t i = 0; i < st->_item._matcount;i++){
								SerialPartMat* st2 = (SerialPartMat*)(buffer+offset+sizeof(SerialShipType)+(sizeof(SerialPartMat)*i));
								cerr<<"\t\t\tmatid "<<st2->_matid<<endl
								<<"\t\t\tquantity "<<st2->_quantity<<endl;
							}
							for(int i = 0 ; i < 6; i++)
								cerr<<"\t\tshield "<<i<<" "<<st->_shield[i]<<endl;
						
							cerr<<"\t\tdeflector "<<st->_deflector<<endl
							<<"\t\tshieldStr "<<st->_shieldStr<<endl
							<<"\t\tarmor "<<st->_armor<<endl
							<<"\t\thull "<<st->_hull<<endl
							<<"\t\tcargo "<<st->_cargo<<endl
							<<"\t\tscanrange "<<st->_scanrange<<endl
							<<"\t\tscanprange "<<st->_scanprange<<endl
						<<endl;					

						cerr<<"****************************"<<endl;
						}
						break;
					}
					case SerialType::SerialShipTypeSlotNode:{
						if (printposbufferbool){
						SerialShipTypeSlotNode* st = (SerialShipTypeSlotNode*)(buffer+offset);
						cerr<<"Recived SerialShipTypeSlotNode*******"<<endl
						<<"\tshiptypeId "<<st->_ShipTypeId<<endl
						<<"\tslotId"<<st->_SlotId<<endl
						<<"\tslotType "<<st->_slotType<<endl
						<<"\tgX "<<st->_gX<<endl
						<<"\tgY "<<st->_gY<<endl
						<<"\tuiX "<<st->_uiX<<endl
						<<"\tuiY "<<st->_uiY<<endl
						<<endl;
						cerr<<"****************************"<<endl;
						}
						break;
					}

					case SerialType::SerialShipTargetPosUpdate:{
						if (printposbufferbool){
						SerialShipTargetPosUpdate* st = (SerialShipTargetPosUpdate*)(buffer+offset);
						cerr<<"Recived SerialShipTargetPosUpdate*******"<<endl
						<<"\tid "<<st->_Id<<endl
						<<"\tspeed "<<st->_Speed<<endl
							<<"\t\tp_x "<<st->_Pos_x<<endl
							<<"\t\tp_y "<<st->_Pos_y<<endl
							<<"\t\tp_d "<<st->_Pos_d<<endl
							<<"\t\ttp_x "<<st->_TargetPos_x<<endl
							<<"\t\ttp_y "<<st->_TargetPos_y<<endl
							<<"\t\ttp_d "<<st->_TargetPos_d<<endl
						<<"\tmoveST "<<st->_MovementStatus<<endl
							<<endl;

						cerr<<"****************************"<<endl;
						}
						break;
					}
					case SerialType::SerialAstoroidPosUpdate:{
						if (printposbufferbool){
						SerialAstoroidPosUpdate* st = (SerialAstoroidPosUpdate*)(buffer+offset);
						cerr<<"Recived SerialAstoroidPosUpdate*******"<<endl
						<<"\tid "<<st->_Id<<endl
							<<"\t\tp_x "<<st->_Pos_x<<endl
							<<"\t\tp_y "<<st->_Pos_y<<endl
							<<"\t\tp_d "<<st->_Pos_d<<endl
							<<endl;

						cerr<<"****************************"<<endl;
						}
						break;
					}
					case SerialType::SerialPCShipTargetPosUpdate:{
						SerialPCShipTargetPosUpdate* st = (SerialPCShipTargetPosUpdate*)(buffer+offset);
						cerr<<"Recived SerialPCShipTargetPosUpdate*******"<<endl
						<<"\tid "<<st->_Id<<endl
							<<"\t\ttp_x "<<st->_TargetPos_x<<endl
							<<"\t\ttp_y "<<st->_TargetPos_y<<endl
							<<"\t\ttp_d "<<st->_TargetPos_d<<endl
							<<endl;

						cerr<<"****************************"<<endl;
						break;
					}
					case SerialType::SerialShotFullUpdate:{
						SerialShotFullUpdate* st = (SerialShotFullUpdate*)(buffer+offset);
						cerr<<"Recived SerialShotFullUpdate*******"<<endl
						<<"\tid "<<st->_Id<<endl
						<<"\ttargetId "<<st->_targetId<<endl
						<<"\ttexId "<<st->_texId<<endl
						<<"\tflightTime "<<st->_FlightTime<<endl
						<<"\tmaxFlightTime "<<st->_maxFlightTime<<endl
						<<"\ttracking "<<st->_tracking<<endl
						<<"\ttrackingTime "<<st->_trackingTime<<endl
						<<"\tspeed "<<st->_speed<<endl
							<<"\t\tp_x "<<st->_Pos_x<<endl
							<<"\t\tp_y "<<st->_Pos_y<<endl
							<<"\t\tp_d "<<st->_Pos_d<<endl
							<<"\t\ttp_x "<<st->_TargetPos_x<<endl
							<<"\t\ttp_y "<<st->_TargetPos_y<<endl
							<<"\t\ttp_d "<<st->_TargetPos_d<<endl
							<<endl;

						cerr<<"****************************"<<endl;
						break;
					}
					case SerialType::SerialObjHpUpdate:{
						SerialObjHpUpdate* st = (SerialObjHpUpdate*)(buffer+offset);
						cerr<<"Recived SerialObjHpUpdate*******"<<endl
						<<"\tid "<<st->_Id<<endl;
							for(int i = 0 ; i < 6; i++)
								cerr<<"\t\tshield "<<i<<" "<<st->_shield[i]<<endl;
							cerr<<"\t\tdeflector "<<st->_deflector<<endl
							<<"\t\tarmor "<<st->_armor<<endl
							<<"\t\thull "<<st->_hull<<endl
						<<endl;

						cerr<<"****************************"<<endl;
						break;
					}
					case SerialType::SerialOrders:{
						if (printposbufferbool){
						SerialOrders* st = (SerialOrders*)(buffer+offset);
						cerr<<"Recived SerialOrders*******"<<endl
						<<"\tPlayer "<<st->_PlayerId<<endl
						<<"\tOrdreId "<<st->_OrdreId<<endl
						<<"\tname "<<st->_name<<endl
						<<"\tunitSet "<<st->_unitsset<<endl
						<<"\tposSet "<<st->_posesset<<endl;
						cerr<<"**********************1******"<<endl;
						}
						break;
					}
					case SerialType::SerialShotHitTarget:{
						SerialShotHitTarget* st = (SerialShotHitTarget*)(buffer+offset);
						cerr<<"Recived SerialShotHitTarget*******"<<endl
						<<"\tid "<<st->_Id<<endl
						<<"\ttextype "<<st->_textype<<endl
						<<"\ttargetId "<<st->_targetId<<endl
							<<"\t\thitp_x "<<st->_hitPos_x<<endl
							<<"\t\thitp_y "<<st->_hitPos_y<<endl
							<<"\t\thitp_d "<<st->_hitPos_d<<endl

							<<endl;

						cerr<<"****************************"<<endl;

						break;
					}
					case SerialType::SerialTypeWeapon:{
						SerialTypeWeapon* st = (SerialTypeWeapon*)(buffer+offset);
						cerr<<"Recived SerialTypeWeapon*******"<<endl
						<<"\tid "<<st->_item._itemId<<endl
						<<"\tname "<<st->_item._name<<endl
						<<"\titemTex "<<st->_item._itemtex<<endl
						<<"\tmass "<<st->_item._mass<<endl
						<<"\tbuildtime "<<st->_item._buildtime<<endl
						<<"\tprotex "<<st->_protex<<endl
						<<"\tmatcount "<<st->_item._matcount<<endl;

						for (uint16_t i = 0; i < st->_item._matcount;i++){
							SerialPartMat* st2 = (SerialPartMat*)(buffer+offset+sizeof(SerialTypeWeapon)+(sizeof(SerialPartMat)*i));
							cerr<<"\t\t\tmatid "<<st2->_matid<<endl
							<<"\t\t\tquantity "<<st2->_quantity<<endl;
						}
						cerr<<"\t\tfireseq";
						for(int i = 0 ; i < 10; i++)
							cerr<<" "<<st->_seq[i];
						cerr<<endl<<"\t\tamocost "<<st->_amocost<<endl
						<<"\t\tmaxAmo "<<st->_maxamo<<endl
						<<"\t\tamotype "<<st->_amotype<<endl
						<<"\t\tcooldown "<<st->_cooldown<<endl
						<<"\t\tfitClass "<<st->_fitClass<<endl
						<<"\t\tmaxdmg "<<st->_maxdmg<<endl
						<<"\t\tmindmg "<<st->_mindmg<<endl
						<<"\t\tmaxseq "<<st->_maxseq<<endl
						<<"\t\tmount "<<st->_mount<<endl
						<<"\t\tprospeed "<<st->_prospeed<<endl

						<<endl;

						cerr<<"****************************"<<endl;
						break;
					}



					case SerialType::SerialTypeFac:{
						SerialTypeFac* st = (SerialTypeFac*)(buffer+offset);
						cerr<<"Recived SerialTypeFac*******"<<endl
						<<"\tid "<<st->_item._itemId<<endl
						<<"\titemTex "<<st->_item._itemtex<<endl
						<<"\tmass "<<st->_item._mass<<endl
						<<"\tbuildtime "<<st->_item._buildtime<<endl
						<<"\tbuildCount "<<st->_xcanbuild<<endl
						<<"\tmatcount "<<st->_item._matcount<<endl;

						for (uint32_t i = 0 ; i < st->_xcanbuild; i++){
							SerialPartConstruct* st2 = (SerialPartConstruct*)(buffer+offset+sizeof(SerialTypeFac)+(sizeof(SerialPartConstruct)*i));
							cerr<<"\t\tcanBuildId "<<st2->_buildTypeId<<endl;
							
						}
						for (uint16_t i = 0; i < st->_item._matcount;i++){
							SerialPartMat* st2 = (SerialPartMat*)(buffer+offset+sizeof(SerialTypeFac)+(sizeof(SerialPartConstruct)*st->_xcanbuild)+(sizeof(SerialPartMat)*i));
							cerr<<"\t\t\tmatid "<<st2->_matid<<endl
							<<"\t\t\tquantity "<<st2->_quantity<<endl;
						}
						cerr<<"\t\tfitClass "<<st->_fitClass<<endl
						<<"\t\tmount "<<st->_mount<<endl
						<<endl;

						cerr<<"****************************"<<endl;
						break;
					}
					case SerialType::SerialTypeRef:{
						SerialTypeRef* st = (SerialTypeRef*)(buffer+offset);
						cerr<<"Recived SerialTypeRef*******"<<endl
						<<"\tid "<<st->_item._itemId<<endl
						<<"\titemTex "<<st->_item._itemtex<<endl
						<<"\tmass "<<st->_item._mass<<endl
						<<"\tbuildtime "<<st->_item._buildtime<<endl
						<<"\tbuildCount "<<st->_xcanRefine<<endl
						<<"\tmatcount "<<st->_item._matcount<<endl;

						for (uint32_t i = 0 ; i < st->_xcanRefine; i++){
							SerialPartRefine* st2 = (SerialPartRefine*)(buffer+offset+sizeof(SerialTypeRef)+(sizeof(SerialPartRefine)*i));
							cerr<<"\t\tcanRefineId "<<st2->_refineTypeId<<endl;

						}
						for (uint16_t i = 0; i < st->_item._matcount;i++){
							SerialPartMat* st2 = (SerialPartMat*)(buffer+offset+sizeof(SerialTypeRef)+(sizeof(SerialPartRefine)*st->_xcanRefine)+(sizeof(SerialPartMat)*i));
							cerr<<"\t\t\tmatid "<<st2->_matid<<endl
							<<"\t\t\tquantity "<<st2->_quantity<<endl;
						}
						cerr<<"\t\tfitClass "<<st->_fitClass<<endl
						<<"\t\tmount "<<st->_mount<<endl
						<<endl;

						cerr<<"****************************"<<endl;
						break;
					}
					case SerialType::SerialTypeBonus:{
						SerialTypeBonus* st = (SerialTypeBonus*)(buffer+offset);
						cerr<<"Recived SerialTypeBonus*******"<<endl
						<<"\tid "<<st->_item._itemId<<endl
						<<"\tname "<<st->_item._name<<endl
						<<"\titemTex "<<st->_item._itemtex<<endl
						<<"\tmass "<<st->_item._mass<<endl
						<<"\tbuildtime "<<st->_item._buildtime<<endl
						<<"\tmatcount "<<st->_item._matcount<<endl;

						for (uint16_t i = 0; i < st->_item._matcount;i++){
							SerialPartMat* st2 = (SerialPartMat*)(buffer+offset+sizeof(SerialTypeWeapon)+(sizeof(SerialPartMat)*i));
							cerr<<"\t\t\tmatid "<<st2->_matid<<endl
							<<"\t\t\tquantity "<<st2->_quantity<<endl;
						}

						cerr<<"\t\tfitClass "<<st->_fitClass<<endl
						<<"\t\tmount "<<st->_mount<<endl

						<<"\t\tarmor "<<st->_bonus._armor<<endl
						<<"\t\thull "<<st->_bonus._hull<<endl
						<<"\t\tdeflector "<<st->_bonus._deflector<<endl
						<<"\t\tenergy "<<st->_bonus._energy<<endl
						<<"\t\tshstr "<<st->_bonus._shStr<<endl
						<<"\t\tscanrange "<<st->_bonus._scanrange<<endl
						<<"\t\tscanprange "<<st->_bonus._scanprange<<endl
						<<"\t\tspeedthruster "<<st->_bonus._speedthruster<<endl
						<<"\t\tmanuverethruster "<<st->_bonus._manuverethruster<<endl
						<<endl;

						cerr<<"****************************"<<endl;
						break;
					}

					case SerialType::SerialTypeBoost:{
						SerialTypeBoost* st = (SerialTypeBoost*)(buffer+offset);
						cerr<<"Recived SerialTypeBoost*******"<<endl
						<<"\tid "<<st->_item._itemId<<endl
						<<"\tname "<<st->_item._name<<endl
						<<"\titemTex "<<st->_item._itemtex<<endl
						<<"\tmass "<<st->_item._mass<<endl
						<<"\tbuildtime "<<st->_item._buildtime<<endl
						<<"\tmatcount "<<st->_item._matcount<<endl;

						for (uint16_t i = 0; i < st->_item._matcount;i++){
							SerialPartMat* st2 = (SerialPartMat*)(buffer+offset+sizeof(SerialTypeWeapon)+(sizeof(SerialPartMat)*i));
							cerr<<"\t\t\tmatid "<<st2->_matid<<endl
							<<"\t\t\tquantity "<<st2->_quantity<<endl;
						}
						cerr<<endl<<"\t\tamocost "<<st->_amocost<<endl
						<<"\t\tboostType "<<st->_boostType<<endl
						<<"\t\tboostvalue "<<st->_boostValue<<endl
						<<"\t\tmaxAmo "<<st->_maxamo<<endl
						<<"\t\tamotype "<<st->_amotype<<endl
						<<"\t\tcooldown "<<st->_cooldown<<endl
						<<"\t\tfitClass "<<st->_fitClass<<endl
						<<"\t\tmount "<<st->_mount<<endl

						<<"\t\tarmor "<<st->_bonus._armor<<endl
						<<"\t\thull "<<st->_bonus._hull<<endl
						<<"\t\tdeflector "<<st->_bonus._deflector<<endl
						<<"\t\tenergy "<<st->_bonus._energy<<endl
						<<"\t\tshstr "<<st->_bonus._shStr<<endl
						<<"\t\tscanrange "<<st->_bonus._scanrange<<endl
						<<"\t\tscanprange "<<st->_bonus._scanprange<<endl
						<<endl;

						cerr<<"****************************"<<endl;
						break;
					}

					case SerialType::SerialTypeMaterial:{
						SerialTypeMaterial* st = (SerialTypeMaterial*)(buffer+offset);
						cerr<<"Recived SerialTypeMaterial*******"<<endl
						<<"\tid "<<st->_item._itemId<<endl
						<<"\titemTex "<<st->_item._itemtex<<endl
						<<"\tmass "<<st->_item._mass<<endl
						<<"\tbuildtime "<<st->_item._buildtime<<endl
						<<"\tmatcount "<<st->_item._matcount<<endl;

						for (uint16_t i = 0; i < st->_item._matcount;i++){
							SerialPartMat* st2 = (SerialPartMat*)(buffer+offset+sizeof(SerialTypeMaterial)+(sizeof(SerialPartMat)*i));
							cerr<<"\t\t\tmatid "<<st2->_matid<<endl
							<<"\t\t\tquantity "<<st2->_quantity<<endl;
						}
						cerr<<endl;

						cerr<<"****************************"<<endl;
						break;
					}
					case SerialType::SerialTypeAstoroid:{
						SerialTypeAstoroid* st = (SerialTypeAstoroid*)(buffer+offset);
						cerr<<"Recived SerialTypeAstoroid*******"<<endl
						<<"\ttypeid "<<st->_astoroidTypeid<<endl
						<<"\ttexture "<<st->_texture<<endl
						<<"\tsize "<<st->_astoroidsize<<endl
						<<"\titemType "<<st->_itemTypeId<<endl;
						cerr<<endl;
						cerr<<"****************************"<<endl;
						break;
					}

					case SerialType::SerialReqInitBuild:{
						SerialReqInitBuild* st = (SerialReqInitBuild*)(buffer+offset);
						cerr<<"Recived SerialReqInitBuild*******"<<endl
						<<"\tShipId "<<st->_ShipId<<endl
						<<"\tSubId "<<st->_SubId<<endl
						<<"\tItemId "<<st->_BuildItem<<endl
						<<"\tquantity "<<st->_Quantity<<endl;
						cerr<<endl;

						cerr<<"****************************"<<endl;
						break;
					}


					case SerialType::SerialSubscribeObj:{
						SerialSubscribeObj* st = (SerialSubscribeObj*)(buffer+offset);
						cerr<<"Recived SerialSubscribeObj*******"<<endl
						<<"\tid "<<st->_Id<<endl;
						cerr<<endl;

						cerr<<"****************************"<<endl;
						break;
					}

					case SerialType::SerialUnSubscribeObj:{
						SerialUnSubscribeObj* st = (SerialUnSubscribeObj*)(buffer+offset);
						cerr<<"Recived SerialUnSubscribeObj*******"<<endl
						<<"\tid "<<st->_Id<<endl;
						cerr<<endl;

						cerr<<"****************************"<<endl;
						break;
					}
					default:{
						cerr<<"error recived unknown packate in GLobal"<<endl;
						offset = len;
						break;
					}
				}
				cerr<<"offset += "<<temp->_size<<endl;
		
				offset += temp->_size;

			}else{
				cerr<<"missing data "<<endl;
				break;
			}
		}
	}
}

uint32_t myrandom(uint32_t min,uint32_t max){

	return ((rand()+ (rand()<<16)) % (1+max-min)) + min;
}

int32_t Deg(double x, double y){

	if(x > 0 && y == 0)
		return 0;
	else if(x > 0 && y < 0 )
		return 180 * atan((0-y)/x)/PI;
	else if(x == 0 && y < 0)
		return 90;
	else if(x < 0 && y < 0)
		return (180 * atan((0-x)/(0-y))/PI) +90;
	else if(x < 0 && y == 0)
		return 180;
	else if(x < 0 && y > 0)
		return (180 * atan(y/(0-x))/PI) +180;
	else if(x == 0 && y > 0)
		return 270;
	else if(x > 0 && y > 0)
		return (180 * atan(x/y)/PI) +270;
	return 0;
}

double VektorUnitX(uint32_t deg){
	if (deg >= 0 || deg < 360)
		return MyCos[deg];
	else
		cerr<<"ERROR out of degs rage"<<endl;
	return 0;
}

double VektorUnitY(uint32_t deg){
	if (deg >= 0 || deg < 360)
		return MySin[deg];
	else
		cerr<<"ERROR out of degs rage"<<endl;
	return 0;
}

uint32_t Rangecord(int32_t p1x,  int32_t p1y, int32_t p2x,int32_t p2y)
{
	p1x = p1x/100;
	p2x = p2x/100;
	p1y = p1y/100;
	p2y = p2y/100;

	return 100* sqrt(((p1x - p2x)*(p1x - p2x)) + ((p1y - p2y)*(p1y - p2y)));
}


bool LinePointIntersect(int32_t p1x,  int32_t p1y, int32_t p2x,int32_t p2y, int32_t pointx, int32_t pointy, int32_t range){
double a = 100 * Rangecord(p1x,p1y,p2x,p2y);
	if(a < range/2){
		int32_t x1 = p1x - pointx;
		int32_t y1 = p1y - pointy;
		int32_t x2 = p1x+p2x - pointx;
		int32_t y2 = p1y+p2y - pointy;

		int32_t dx = x2 - x1;
		int32_t dy = y2 - y1;
		double dr = sqrt((dx*dx)+(dy*dy));
		double D = x1*y2 - x2*y1;
		double dis = ((range/2)*(range/2))*(dr*dr)-(D*D);

		if(dis >= 0)
			return true;
		else
			return false;
	}
}

int32_t dirDiff(uint32_t d1, uint32_t d2){
	int32_t dd = d1 - d2;
	if(dd < 0)
		dd += 36000;

	if(dd > 18000)
		return  36000 - dd;
	else
		return dd;
}

string getTargetGroupstring(TargetGroup::Enum en){
		switch(en){
			case TargetGroup::Primary:{return "Primary";}
			case TargetGroup::Heavy:{return "Heavy";}
			case TargetGroup::Medium:{return "Medium";}
			case TargetGroup::Light:{return "Light";}
			case TargetGroup::Special:{return "Special";}
			default:{return "invalid";}
		}
	}