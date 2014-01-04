/* 
 * File:   Texture.h
 * Author: karsten
 *
 * Created on 15. maj 2011, 21:52
 */

#ifndef GRAFIC_H
#define	GRAFIC_H

#define Basewidth 1366
#define Basehight 768

#include <GL/gl.h>
#include <SDL/SDL_image.h>
#include "../CFunctions.h"
#include <FTGL/ftgl.h>

class CPos;
GLuint loadTexture(Textures::Enum texture);
void Drawbox( float x, float y, float width, float hight, float r, float g, float b, float a );

#endif	/* GRAFIC_H */

