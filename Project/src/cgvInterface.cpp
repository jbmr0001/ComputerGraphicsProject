#include <stdio.h>
#include <stdlib.h>

#include "cgvInterface.h"

extern cgvInterface interface; // the callbacks must be static and this object is required to access to the variables of the class                   // ellos a las variables de la clase

// Constructor and destructor methods -----------------------------------

cgvInterface::cgvInterface () :currentCam(0) {
	cameras[0] = cgvCamera(cgvPoint3D(11.0, 3.0, 7), cgvPoint3D(0, 0, 0), cgvPoint3D(0, 1.0, 0));
	cameras[0].setParallelParameters(1 * 5, 1 * 5, -5, 200);
	cameras[1] = cgvCamera(cgvPoint3D(0, 5, 0), cgvPoint3D(0, 0, 0), cgvPoint3D(1.0, 0, 0));//top view
	cameras[1].setParallelParameters(1 * 5, 1 * 5, -5, 200);
	cameras[2] = cgvCamera(cgvPoint3D(5, 1, 0), cgvPoint3D(0, 0, 0), cgvPoint3D(0, 1.0, 0));//lateral view
	cameras[2].setParallelParameters(1 * 5, 1 * 5, -10, 200);
	cameras[3] = cgvCamera(cgvPoint3D(0, 1, 5), cgvPoint3D(0, 0, 0), cgvPoint3D(0, 1.0, 0));//front view
	cameras[3].setParallelParameters(1 * 5, 1 * 5, -10, 200);
	//// TODO: Section D: initialize the attributes to select objects by list of impacts
	animation = false;
	mode = "DISPLAY";
	pressedButton = false;

}
cgvInterface::~cgvInterface () {}


// Public methods ----------------------------------------
void cgvInterface::create_world(void) {

}

void cgvInterface::configure_environment(int argc, char** argv, 
			                       int _width_window, int _height_window, 
			                       int _pos_X, int _pos_Y, 
													 string _title)
													 {
	// initialization of the interface variables																	
	width_window = _width_window;
	height_window = _height_window;

	// initialization of the display window
	glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(_width_window,_height_window);
  glutInitWindowPosition(_pos_X,_pos_Y);
	glutCreateWindow(_title.c_str());

	create_menu();

	glEnable(GL_DEPTH_TEST); // enable the removal of hidden surfaces by using the z-buffer
    glClearColor(1.0,1.0,1.0,0.0); // define the background color of the window

	glEnable(GL_LIGHTING); // enable the lighting of the scene
    glEnable(GL_NORMALIZE); // normalize the normal vectors required by the lighting computation. 
    glEnable(GL_TEXTURE_2D); // enable the use of 2D textures


  //create_world(); // create the world (scene) to be rendered in the window
}

void cgvInterface::create_menu() {
	int menu_id = glutCreateMenu(menuHandle);
	int sub1 = glutCreateMenu(menuHandle);
	for (int i = 0; i<nbScenes; ++i) {
		glutAddMenuEntry(interface.scene.Scene_Name[i], interface.scene.Scene[i]);
		
	}
	int sub2 = glutCreateMenu(menuHandle2);
	//camera menu
	glutAddMenuEntry("Isometric", 0);
	glutAddMenuEntry("Top", 1);
	glutAddMenuEntry("Lateral", 2);
	glutAddMenuEntry("Frontal", 3);
	//scene menu
	glutSetMenu(menu_id);
	glutAddSubMenu("Scene", sub1);
	glutAddSubMenu("Camera", sub2);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}


void cgvInterface::init_rendering_loop() {
	glutMainLoop(); // initialize the visualization loop of OpenGL
}

void cgvInterface::set_glutKeyboardFunc(unsigned char key, int x, int y) {
	
	switch (key) {
		//Footballs controls
	case '1':
		interface.scene.subX();
		break;
	case '2':
		interface.scene.addX();
		break;
	case '3':
		interface.scene.subY();
		break;
	case '4':
		interface.scene.addY();
		break;
	case '5':
		interface.scene.subZ();
		break;
	case '6':
		interface.scene.addZ();
		break;
		//doll controls
	case 'x':
		interface.scene.move(0.1, 0);
		break;
	case 'X':
		interface.scene.move(-0.1, 0);
		break;
	case 'z':
		interface.scene.move(0, 0.1);
		break;
	case 'Z':
		interface.scene.move(0, -0.1);
		break;
	case 'q':
		interface.scene.rotateBody(15.0);
		break;
	case 'Q':
		interface.scene.rotateBody(-15.0);
		break;
	case 'w':
		interface.scene.rotateThigh1(15.0);
		break;
	case 'W':
		interface.scene.rotateThigh1(-15.0);
		break;
	case 'e':
		interface.scene.rotateTibia1(15.0);
		break;
	case 'E':
		interface.scene.rotateTibia1(-15.0);
		break;
	case 'r':
		interface.scene.rotateFoot1(15.0);
		break;
	case 'R':
		interface.scene.rotateFoot1(-15.0);
		break;
	case 't':
		interface.scene.rotateThigh2(15.0);
		break;
	case 'T':
		interface.scene.rotateThigh2(-15.0);
		break;
	case 'y':
		interface.scene.rotateTibia2(15.0);
		break;
	case 'Y':
		interface.scene.rotateTibia2(-15.0);
		break;
	case 'u':
		interface.scene.rotateFoot2(15.0);
		break;
	case 'U':
		interface.scene.rotateFoot2(-15.0);
		break;
	case 'i':
		interface.scene.rotateArm1(15.0);
		break;
	case 'I':
		interface.scene.rotateArm1(-15.0);
		break;
	case 'o':
		interface.scene.rotateElbow1(15.0);
		break;
	case 'O':
		interface.scene.rotateElbow1(-15.0);
		break;
	case 'p':
		interface.scene.rotateHand1(15.0);
		break;
	case 'P':
		interface.scene.rotateHand1(-15.0);
		break;
	case 'a':
		interface.scene.rotateArm2(15.0);
		break;
	case 'A':
		interface.scene.rotateArm2(-15.0);
		break;
	case 's':
		interface.scene.rotateElbow2(15.0);
		break;
	case 'S':
		interface.scene.rotateElbow2(-15.0);
		break;
	case 'd':
		interface.scene.rotateHand2(15.0);
		break;
	case 'D':
		interface.scene.rotateHand2(-15.0);
		break;
		//material controls
	case 'f': // Section F: increase by 0.1 the R component of the diffuse coefficient of the material. 
		interface.scene.editDiffuse(0.1);
		break;
	case 'F': // Section F: decrease by 0.1 the R component of the diffuse coefficient of the material. 
		interface.scene.editDiffuse(-0.1);
		break;
	case 'g': // Section F: increase by 0.1 the R component of the specular coefficient of the material. 
		interface.scene.editSpecular(0.1);
		break;
	case 'G': // Section F: decrease by 0.1 the R component of the specular coefficient of the material. 
		interface.scene.editSpecular(-0.1);
		break;
	case 'h': // Section F: increase by 10 the phong exponent of the material. 
		interface.scene.editNs(10.0);
		break;
	case 'H': // Section F: decrease by 10 the phong exponent of the material. 
		interface.scene.editNs(-10.0);
		break;
		//spotlight controls
	case 'j': // Section G: increase by 0.2 the spotlight in the X axis
		interface.scene.editX(0.2);
		break;
	case 'J': // Section G: decrease by 0.2 the spotlight in the X axis
		interface.scene.editX(-0.2);
		break;
	case 'k': // Section G: increase by 0.2 the spotlight in the Y axis
		interface.scene.editY(0.2);
		break;
	case 'K': // Section G: decrease by 0.2 the spotlight in the Y axis
		interface.scene.editY(-0.2);
		break;
		//camera controls
	case 'l': //Isometric cinematic camera rotation

		interface.start_x = interface.start_x + 1;

			interface.cameras[interface.getCurrentCam()] = cgvCamera(cgvPoint3D(interface.start_x, 4.0, 8), cgvPoint3D(0, 0, 0), cgvPoint3D(0, 1.0, 0));
			interface.cameras[interface.getCurrentCam()].setParallelParameters(1 * 5, 1 * 5, 0.1, 200);
		break;

	case 'L': //Isometric cinematic camera rotation
	
		interface.start_x = interface.start_x - 1;
	
		interface.cameras[interface.getCurrentCam()] = cgvCamera(cgvPoint3D(interface.start_x, 4.0, 8), cgvPoint3D(0, 0, 0), cgvPoint3D(0, 1.0, 0));
		interface.cameras[interface.getCurrentCam()].setParallelParameters(1 * 5, 1 * 5, 0.1, 200);
		break;
	case 'n': // increment the distance to the near plane
		interface.cameras[interface.getCurrentCam()].nearp(0.2);
		break;
	case 'N': // decrement the distance to the near plane
		interface.cameras[interface.getCurrentCam()].nearp(-0.2);
		break;
	case '+': // zoom in
		interface.cameras[interface.getCurrentCam()].zoom(0.05);
		break;
	case '-': // zoom out
		interface.cameras[interface.getCurrentCam()].zoom(-0.05);
		break;
	case 'c': //Isometric camera movement
		if (interface.getCurrentCam()==0) {
			interface.cameras[interface.getCurrentCam()].move();
		}
		break;
	case 'v': // change the type of projection between parallel and perspective. 
		if (interface.cameras[interface.getCurrentCam()].camType == CGV_PARALLEL) {
			interface.cameras[interface.getCurrentCam()].setPerspParameters(70, 1 / 1, 0.1, 200);
		}
		else {
			interface.cameras[interface.getCurrentCam()].setParallelParameters(3, 3, 0.1, 200);
		}
		break;
	case 'm':
		if (interface.animation) {
			interface.animation = false;
		}
		else {
			interface.animation = true;
		}
		break;
    case 'b': // enable/disable the visualization of the axes
			interface.scene.set_axes(interface.scene.get_axes()?false:true);

	  break;
    case 27: // Escape key to exit
      exit(1);
    break;
  }
	glutPostRedisplay(); // renew the content of the window
	
}

void cgvInterface::set_glutReshapeFunc(int w, int h) {
	// dimension of the viewport with a new width and a new height of the display window 

	// store the new values of the viewport and the display window. 
	interface.set_width_window(w);
	interface.set_height_window(h);

	// Set up the kind of projection to be used
	interface.camera.apply();
}

void cgvInterface::set_glutDisplayFunc() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the window and the z-buffer

	// set up the viewport
	glViewport(0, 0, interface.get_width_window(), interface.get_height_window());

	if (interface.mode=="SELECT") {
		interface.init_selection();
	}
	// Apply the camera and projection transformations 
	interface.cameras[interface.currentCam].apply();
	// Render the scene
	interface.scene.render(interface.mode);

	

	if (interface.mode == "SELECT") {
		interface.finish_selection();
		glutPostRedisplay();
	}
	else {
		// refresh the window
		glutSwapBuffers(); // it is used instead of glFlush(), to avoid flickering
	}
}

void cgvInterface::menuHandle(int value)
{
	interface.scene.set(value);
	glutPostRedisplay(); // renew the content of the window
}

void cgvInterface::init_selection() { 
	glDisable(GL_LIGHTING);

}

void cgvInterface::menuHandle2(int value) {
	interface.setCurrentCam(value);
	glutPostRedisplay(); // renew the content of the window
}




void cgvInterface::set_glutIdleFunc() { 
	//legs rotation
	if (interface.animation) {
		interface.scene.rotateThigh1(interface.r1);
		if (interface.r1>10) {
			interface.r1 = -interface.r1;
		}
		interface.r1++;
		interface.scene.rotateThigh2(-interface.r2);
		if (interface.r2 > 10) {
			interface.r2 = -interface.r2;
		}
		//ball movement
		if (interface.r2==5) {
			interface.scene.balls[0].setSelected(true);
			for (int i = 0; i < 2;i++) {
				interface.scene.balls[0].move(i, 0);
			}
			interface.scene.balls[0].setSelected(false);
		}
		interface.r2++;
		//camera rotation
		if (interface.c1==1) {
			interface.c2++;
			if (interface.c2<22) {
				interface.start_x = interface.start_x - 1;
				interface.cameras[interface.getCurrentCam()] = cgvCamera(cgvPoint3D(interface.start_x, 4.0, 8), cgvPoint3D(0, 0, 0), cgvPoint3D(0, 1.0, 0));
				interface.cameras[interface.getCurrentCam()].setParallelParameters(1 * 5, 1 * 5, 0.1, 200);
			}
			interface.c1 = 0;
		}
		interface.c1++;
		//arms movement
		interface.scene.rotateArm1(-interface.r3);
		if (interface.r3 > 10) {
			interface.r3 = -interface.r3;
		}
		interface.r3++;
		interface.scene.rotateArm2(interface.r4);
		if (interface.r4 > 10) {
			interface.r4 = -interface.r4;
		}
		interface.r4++;
		interface.scene.move(0,0.1);
	}
	glutPostRedisplay();
}

void cgvInterface::init_callbacks() {
	glutKeyboardFunc(set_glutKeyboardFunc);
	glutReshapeFunc(set_glutReshapeFunc);
	glutDisplayFunc(set_glutDisplayFunc);
	glutMouseFunc(set_glutMouseFunc);
	glutMotionFunc(set_glutMotionFunc);
	glutIdleFunc(set_glutIdleFunc);
}

//Getters and setters
void cgvInterface::setCurrentCam(int _currentCam) {
	currentCam = _currentCam;
}
int cgvInterface::getCurrentCam() {
	return currentCam;
}

void cgvInterface::finish_selection() {

	glReadBuffer(GL_BACK);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glPixelStorei(GL_PACK_ALIGNMENT, 1);


	GLubyte pixels[3] = { 0, 0, 0 };

	glReadPixels(interface.cursorX, interface.height_window - interface.cursorY, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixels);//height-y to avoid inverse Y valors
	//printf("%d %d %d\n", pixels[0],pixels[1],pixels[2]);
	interface.scene.assignSelection(pixels);
	glEnable(GL_LIGHTING);
}
void cgvInterface::set_glutMouseFunc(GLint button, GLint state, GLint x, GLint y) {

	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN) {
			interface.mode = "SELECT";
			interface.cursorX = x;
			interface.cursorY = y;
			interface.pressedButton = true;
		}
		else {
			interface.mode = "DISPLAY";
			interface.pressedButton = false;
		}
		break;

	}
	glutPostRedisplay();

}


void cgvInterface::set_glutMotionFunc(GLint x, GLint y) {

	float distanceX = 0;
	float distanceZ = 0;

	distanceX = ((float)(interface.cursorX - x)/200);
	distanceZ = ((float)(interface.cursorY - y)/200);
	interface.scene.moveFootball(distanceX,distanceZ);
	interface.scene.rotateModel(distanceX,distanceZ);
		
}
