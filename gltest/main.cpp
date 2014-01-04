/* 
 * File:   main.cpp
 * Author: karsten
 *
 * Created on 26. april 2011, 21:58
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstdlib>
#include <iostream>
#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"
#include "GL/gl.h"
using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {


	if ( SDL_Init(SDL_INIT_VIDEO) != 0 ) {
	printf("Unable to initialize SDL: %s\n", SDL_GetError());
	return 1;
	}

SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 ); // *new*

SDL_Surface* screen = SDL_SetVideoMode( 640, 480, 16, SDL_OPENGL  ); // *changed*

	glEnable( GL_TEXTURE_2D );

	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

	glViewport( 0, 0, 640, 480 );

	glClear( GL_COLOR_BUFFER_BIT );

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();

	glOrtho(0.0f, 640, 480, 0.0f, -1.0f, 1.0f);

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();





	GLuint texture;			// This is a handle to our texture object
SDL_Surface *surface;	// This surface will tell us the details of the image
GLenum texture_format;
GLint  nOfColors;

if ( (surface = SDL_LoadBMP("test2.bmp")) ) {

	// Check that the image's width is a power of 2
	if ( (surface->w & (surface->w - 1)) != 0 ) {
		printf("warning: image.bmp's width is not a power of 2\n");
	}

	// Also check if the height is a power of 2
	if ( (surface->h & (surface->h - 1)) != 0 ) {
		printf("warning: image.bmp's height is not a power of 2\n");
	}

        // get the number of channels in the SDL surface
        nOfColors = surface->format->BytesPerPixel;
        if (nOfColors == 4)     // contains an alpha channel
        {
                if (surface->format->Rmask == 0x000000ff)
                        texture_format = GL_RGBA;
                else
                        texture_format = GL_BGRA;
        } else if (nOfColors == 3)     // no alpha channel
        {
                if (surface->format->Rmask == 0x000000ff)
                        texture_format = GL_RGB;
                else
                        texture_format = GL_BGR;
        } else {
                printf("warning: the image is not truecolor..  this will probably break\n");
                // this error should not go unhandled
        }
cerr<<texture<<endl;
	// Have OpenGL generate a texture object handle for us
	glGenTextures( 1, &texture );
cerr<<texture<<endl;
	// Bind the texture object
	glBindTexture( GL_TEXTURE_2D, texture );

	// Set the texture's stretching properties
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	// Edit the texture object's image data using the information SDL_Surface gives us
	glTexImage2D( GL_TEXTURE_2D, 0, nOfColors, surface->w, surface->h, 0,
                      texture_format, GL_UNSIGNED_BYTE, surface->pixels );
}
else {
	printf("SDL could not load image.bmp: %s\n", SDL_GetError());
	SDL_Quit();
	return 1;
}

glBindTexture( GL_TEXTURE_2D, texture );

while(true){
	glClear(GL_COLOR_BUFFER_BIT);
glLoadIdentity();
	glTranslated(200,100,0);
	
glRotatef(1,0,0,0.1);

glBegin( GL_QUADS );


	//Bottom-left vertex (corner)
	glTexCoord2i( 0, 0 );
	glVertex3f( -100.f, -100.f, 0.0f );

	//Bottom-right vertex (corner)
	glTexCoord2i( 1, 0 );
	glVertex3f( 100.f, -100.f, 0.f );

	//Top-right vertex (corner)
	glTexCoord2i( 1, 1 );
	glVertex3f( 100.f, 100.f, 0.f );

	//Top-left vertex (corner)
	glTexCoord2i( 0, 1 );
	glVertex3f( -100.f, 100.f, 0.f );
glEnd();

	SDL_GL_SwapBuffers();

}
// Free the SDL_Surface only if it was successfully created
if ( surface ) {
	SDL_FreeSurface( surface );
}




	return 0;
}

