/* 
 * File:   CPartical.cpp
 * Author: karsten
 * 
 * Created on 9. juli 2011, 15:40
 */

#include "CPartical.h"

CPartical::CPartical(ParticalTex::Enum tex, CPos& pos) {
	this->_pos.x = pos.x;
	this->_pos.y = pos.y;
	this->_pos.d = pos.d;
	this->_move_x = 0;
	this->_move_y = 0;
	this->_rotate = 0;
	this->_tex = tex;
	this->_tick = 0;

	this->_procedTime = getTime();
	switch (_tex){
		#include "../Textures/effects/tick.txt"
	}

}

void CPartical::Proces(uint32_t DTime){
	while(this->_procedTime<= getTime()){
		this->_procedTime += 1000/25;
		if(_tick < _tickmax)
			_tick++;
		//else
			//_tick = 0;
		this->_pos.d +=_rotate;

	}

	this->Move(DTime);

}

void CPartical::Move(uint32_t deltaT){
	double speed = 0;
	speed = (deltaT)/((double)1000/25);
	this->MovePos(_move_x * speed ,_move_y * speed );
}

void CPartical::Draw(){
	int32_t uvx1;
	int32_t uvx2;
	int32_t uvy1;
	int32_t uvy2;
	int32_t size2;
	switch (_tex){
		#include "../Textures/effects/cords.txt"

	default:{
		uvx1 = 0;
		uvy1 = 0;
		size2 = 10;
		cerr<<"Warning partical tex"<<endl;
		break;
		}
	}

	int32_t zsize2 =size2*viewZoom;
	glLoadIdentity();
	glColor4f(1,1,1,1);
	glTranslated((GLfloat)(((this->_pos.x-viewPos->x)*viewZoom)/100),(GLfloat)(((this->_pos.y-viewPos->y)*viewZoom)/100),0);

	glRotatef((GLfloat)(180-(this->_pos.d/100)),0,0,0.1);

	glBegin( GL_QUADS );
	//Bottom-left vertex (corner)
	glTexCoord2f((((double)1)/1024)*(uvx1), (((double)1)/1024)*(uvy1) );
	glVertex3f( -zsize2/2, -zsize2/2, 0.0f );

	//Bottom-right vertex (corner)
	glTexCoord2f((((double)1)/1024)*(uvx1+size2), (((double)1)/1024)*(uvy1) );
	glVertex3f( zsize2/2, -zsize2/2, 0.f );

	//Top-right vertex (corner)
	glTexCoord2f((((double)1)/1024)*(uvx1+size2), (((double)1)/1024)*(uvy1+size2) );
	glVertex3f( zsize2/2, zsize2/2, 0.f );

	//Top-left vertex (corner)
	glTexCoord2f((((double)1)/1024)*(uvx1), (((double)1)/1024)*(uvy1+size2) );
	glVertex3f( -zsize2/2, zsize2/2, 0.f );
	glEnd();


}

void CPartical::MovePos(int32_t x, int32_t y){
	this->_pos.x+= x;
	this->_pos.y+= y;
}

CPartical::~CPartical() {
}

