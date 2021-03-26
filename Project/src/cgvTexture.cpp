#include "cgvTexture.h"
#include <iostream>

// Constructor and destructor methods

cgvTexture::cgvTexture() {
	
  SDL_Surface* image = NULL;
	GLubyte texture[64][64][4];
	width = 64;
	height = 64;

  // store a chessboard image as a texture array
	
	int i, j, c;
 for (i = 0; i < height ; i++) {
    for (j = 0; j < width ; j++) {
		  c = (((i&0x8) == 0) ^ ((j&0x8)) == 0) * 255;
		  texture[i][j][0] = (GLubyte) c;
		  texture[i][j][1] = (GLubyte) c;
		  texture[i][j][2] = (GLubyte) c;
		  texture[i][j][3] = (GLubyte) 255;
	  }
	}
	
	
  if (!glIsTexture(idTexture)) {

	  image = IMG_Load("grass.jpg");//load map.png from project directory
	  

	  if (!image)
	  {
		  /* image failed to load */
		  printf("IMG_Load failed: %s\n", IMG_GetError());
		  std::cout << "error" << std::endl;
		  return;

	  }
	  /* print some info about the image */
	  printf("loaded %s: %dx%d %dbpp\n", "map.png",
		  image->w, image->h, image->format->BitsPerPixel);

	  /*
	  - Enable GL_TEXTURE_2D
	  - Generate the identifier of the texture and assign it to the attribute idTexture (use glGenTextures)
	  - Bind the texture with its name. (glBindTexture)
	  - Environment mode of the texture  (glTexEnvf)
	  - Parameters of the texture: repeat and filters glTexParameteri
	  - Specify the texture assigning it the image array.
	  */
	  // Generate the texture name
	  glGenTextures(1, &idTexture);
	  // Bind the texture
	  glBindTexture(GL_TEXTURE_2D, idTexture);
	  // - Define the application mode of the texture
	  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	  // - Texture parameters: 
	  //		- repeat
	  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	  //		- filters
	  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	  // - Specify the texture
	  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->w, image->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->pixels);

	  SDL_FreeSurface(image);

  }
}

cgvTexture::cgvTexture(char *file) {
	SDL_Surface *image = NULL;

	

	if (!glIsTexture(idTexture)) {

		image = IMG_Load(file);//load map.png from project directory


		if (!image)
		{
			/* image failed to load */
			printf("IMG_Load failed: %s\n", IMG_GetError());
			std::cout << "error" << std::endl;
			return;

		}
		/* print some info about the image */
		//printf("loaded %s: %dx%d %dbpp\n", "map.png",
			//image->w, image->h, image->format->BitsPerPixel);

		/*
		- Enable GL_TEXTURE_2D
		- Generate the identifier of the texture and assign it to the attribute idTexture (use glGenTextures)
		- Bind the texture with its name. (glBindTexture)
		- Environment mode of the texture  (glTexEnvf)
		- Parameters of the texture: repeat and filters glTexParameteri
		- Specify the texture assigning it the image array.
		*/
		// Generate the texture name
		glGenTextures(1, &idTexture);
		// Bind the texture
		glBindTexture(GL_TEXTURE_2D, idTexture);
		// - Define the application mode of the texture
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		// - Texture parameters: 
		//		- repeat
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		//		- filters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		// - Specify the texture
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->w, image->h, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

		SDL_FreeSurface(image);

	}
}

void cgvTexture::apply(void) {
  
  glBindTexture(GL_TEXTURE_2D, idTexture);
 
}

cgvTexture::~cgvTexture() {
  glDeleteTextures(1, &idTexture); 
}
