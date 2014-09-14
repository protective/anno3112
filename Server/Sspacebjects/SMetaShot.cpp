/* 
 * File:   SMetaShot.cpp
 * Author: karsten
 * 
 * Created on 16. juli 2014, 16:48
 */

#include "SMetaShot.h"
#include "../World/SWorld.h"
#include "../Commands/CommandMetaHit.h"
#include "../Commands/Processor.h"
#include "../Sspacebjects/SUnit.h"

SMetaShot::SMetaShot(uint32_t id ) :
SMetaObj(id){
	
}
void SMetaShot::checkCollisions(Processor* processor){
	//if(!this->posValid)
	//	return;
	SPos temppos;
	temppos = this->getRPos();
	
	for(map<uint32_t, Processable*>::iterator it = processor->getLocalProcssables().begin(); it != processor->getLocalProcssables().end(); it++){
		SUnit* oobj = it->second->isUnit();
		if(!oobj || oobj->getTeam() == this->getTeam()){
			continue;
		}
		
		int32_t negsize = 0-oobj->getTargetSize();
		int32_t possize = oobj->getTargetSize();
		if(temppos.z > (negsize)/2 && temppos.z < possize/2){
			double a = 100 * Rangeobj(temppos, oobj->getPos());
			
			if(oobj->getTargetType()==TargetType::Invalid){
				continue;
			}
			
			if(a >= oobj->getTargetSize()/2){
				continue;
			}
			
			double movementX = this->vecX; //(VektorUnitX(this->pos.d/100) * this->getSpeed());
			double movementY = this->vecY; // (-(VektorUnitY(this->pos.d/100) * this->getSpeed()));
			int32_t x1 = temppos.x - oobj->getPos().x;
			int32_t y1 = temppos.y - oobj->getPos().y;
			int32_t x2 = temppos.x+movementX - oobj->getPos().x;
			int32_t y2 = temppos.y+movementY - oobj->getPos().y;
			int32_t dx = x2 - x1;
			int32_t dy = y2 - y1;
			double dr = sqrt((dx*dx)+(dy*dy));
			double D = x1*y2 - x2*y1;
			double dis = ((oobj->getTargetSize()/2)*(oobj->getTargetSize()/2))*(dr*dr)-(D*D);

			if(dis >= 0 ){// || _flightTime <= 1){//hit
				double hitx = ((D *dy -dx * (sqrt(pow((oobj->getTargetSize()/2),2) * pow(dr,2)- pow(D,2))))/ pow(dr,2));
				double hity = ((-D *dx -dy * (sqrt(pow((oobj->getTargetSize()/2),2) * pow(dr,2)- pow(D,2))))/ pow(dr,2));
				double H_x = (oobj->getTargetSize()/2);
				double H_y = 0;

				double P_x = hitx;
				double P_y = hity;

				double ph = Rangecord(H_x,H_y,P_x,P_y);
				double ch =(oobj->getTargetSize()/2);
				double cp = Rangecord(0,0,P_x,P_y);
				double rad = 0;
				if (2*cp*ch)
					rad = acos(((ch*ch)+(cp*cp)-(ph*ph))/(2*cp*ch));
				double V = (rad/3.14)*180;

				if( P_y > H_y)
					V = 360 - V;

				double V2 = V - (oobj->getPos().d/100);

				if(V2 < 0)
					V2 = V2 + 360;

				int i = 0;
				if ((V2 >= 0 && V2 <= 30) ||(V2 >= 330 && V2 <= 360)){
					i = 0;
				}else if(V2 >= 31 && V2 <= 90){
					i = 1;
				}else if(V2 >= 91 && V2 <= 150){
					i = 4;
				}else if(V2 >= 151 && V2 <= 209){
					i = 3;
				}else if(V2 >= 210 && V2 <= 269){
					i = 5;
				}else if(V2 >= 270 && V2 <= 329){
					i = 2;
				}
				//cerr<<"meta shot hit"<<endl;
				networkControl->addCommandToProcesable(new CommandMetaHit(_id, it->first,(Shields::Enum)i,0,0), _id);
				//Hit(it->first, (Shields::Enum)i,0,0);
			}
		}	
	}
}

SMetaShot::~SMetaShot() {
}

