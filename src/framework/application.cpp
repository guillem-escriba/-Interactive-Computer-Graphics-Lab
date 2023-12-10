#include "application.h"
#include "utils.h"
#include "image.h"

Application::Application(const char* caption, int width, int height)
{
	this->window = createWindow(caption, width, height);

	// initialize attributes
	// Warning: DO NOT CREATE STUFF HERE, USE THE INIT 
	// things create here cannot access opengl
	int w,h;
	SDL_GetWindowSize(window,&w,&h);

	this->window_width = w;
	this->window_height = h;
	this->keystate = SDL_GetKeyboardState(NULL);

	framebuffer.resize(w, h);
}

//Here we have already GL working, so we can create meshes and textures
void Application::init(void)
{
	std::cout << "initiating app..." << std::endl;

	//here add your init stuff
	//Guardamos la imagen
	if (pict.loadTGA("myfile.tga") == false)
	{
		std::cout << "image not found" << std::endl;;
	}

	//Creamos un array de partículas con coordenadas y tamaños aleatorios
	particles = new Particle[200];
	for (int i = 0; i < 200; i++) {
		particles[i].x = 10+randomValue()*(framebuffer.width-20);
		particles[i].y = 10+randomValue() * (framebuffer.height-20);
		particles[i].size = randomValue()*5; 
	}


	std::cout << "Mantain pressed the following buttons for the different options:" << std::endl;
	std::cout << "1: Drawing\n2: Radial Gradient\n3: Gradient \n4: Inverse Filter\n5: Channel Swap\n6: Rotate Image\n7:  Scale\n0: Restore the image" << std::endl;
}

//render one frame
void Application::render( Image& framebuffer )
{
	if (!isPaint) {
		for (int x = 0; x < framebuffer.width; x++) {
			for (int y = 0; y < framebuffer.height; y++) {
				Color c = pict.getPixel(x, y);
				framebuffer.setPixel(x, y, c);
			}
		}

		//Dibujamos la imagen
		
		
		/*framebuffer.Bresenham(400, 300, 500, 350, Color::RED); // O1 
		framebuffer.Bresenham(400, 300, 500, 250, Color::BLUE); // O8 
		framebuffer.Bresenham(400, 300, 450, 200, Color::PURPLE); // O7
		framebuffer.Bresenham(400, 300, 450, 400, Color::WHITE); // O2 
		framebuffer.Bresenham(400, 300, 300, 250, Color::YELLOW); // O5  
		framebuffer.Bresenham(400, 300, 300, 350, Color::CYAN); // O4
		framebuffer.Bresenham(400, 300, 350, 200, Color::GREEN); // O6 
		framebuffer.Bresenham(400, 300, 350, 400, Color::GRAY); // O3
		framebuffer.Bresenham(400, 300, 500, 300, Color::RED); // HORIZONTAL 1
		framebuffer.Bresenham(400, 300, 300, 300, Color::RED); // HORIZONTAL 2
		framebuffer.Bresenham(400, 300, 400, 400, Color::RED); // VERTICAL 1
		framebuffer.Bresenham(400, 300, 400, 200, Color::RED); // VERTICAL 2
		framebuffer.Bresenham(400, 300, 487, 387, Color::RED); // DIAGONAL 1
		framebuffer.Bresenham(400, 300, 313, 213, Color::RED); // DIAGONAL 2
		framebuffer.Bresenham(400, 300, 487, 213, Color::RED); // DIAGONAL 3
		framebuffer.Bresenham(400, 300, 313, 387, Color::RED); // DIAGONAL 4
		*/
		
		//framebuffer.BresenhamCircle(400, 300, 100, Color::RED, FALSE);





		if (keystate[SDL_SCANCODE_1]) {
			//clear framebuffer if we want to start from scratch
			framebuffer.fill(Color::BLACK);
			task1();
		}
		if (keystate[SDL_SCANCODE_2]) {
			task2_1();
		}
		if (keystate[SDL_SCANCODE_3]) {
			task2_2();
		}
		if (keystate[SDL_SCANCODE_4]) {
			task3_1();
		}
		if (keystate[SDL_SCANCODE_5]) {
			task3_2();
		}
		if (keystate[SDL_SCANCODE_6]) {
			task4_1();
		}
		if (keystate[SDL_SCANCODE_7]) {
			task4_2();
		}
		if (keystate[SDL_SCANCODE_8]) {
			framebuffer.fill(Color::BLACK);
			task5();
		}
	}
}
	
	
	

// Task 1
void Application::task1()
{
	framebuffer.drawRectangle(370, 220, 100, 230, Color(0,0,128), true); //body
	framebuffer.drawRectangle(370, 90, 40, 130, Color::GRAY, true); //left leg
	framebuffer.drawRectangle(430, 90, 40, 130, Color::GRAY, true); //right leg
	framebuffer.drawRectangle(410, 360, 20, 90, Color::GRAY, true); //necktie
	framebuffer.drawRectangle(470, 380, 100, 30, Color(0, 0, 128), true); //right arm
	framebuffer.drawRectangle(270, 380, 100, 30, Color(0, 0, 128), true); //left arm
	framebuffer.drawCircle(575, 395, 20, Color(252, 208, 180), true); //right hand
	framebuffer.drawCircle(275, 395, 20, Color(252, 208, 180), true); //left hand
	framebuffer.drawCircle(270, 360, 15, Color::RED, true); //stick ball
	framebuffer.drawRectangle(260, 70, 20, 275, Color::WHITE, true); //stick
	framebuffer.drawCircle(420, 500, 50, Color(252, 208, 180), true); //head
	framebuffer.drawRectangle(390, 540, 60, 30, Color::GRAY, true); //hat
	framebuffer.drawRectangle(370, 540, 100, 5, Color::GRAY, true);
	framebuffer.drawCircle(400, 520, 8, Color::WHITE, true); //left eye
	framebuffer.drawCircle(400, 520, 3, Color(45, 87, 44), true);//left eye
	framebuffer.drawCircle(440, 520, 8, Color::WHITE, true); //right eye
	framebuffer.drawCircle(440, 520, 3, Color(45, 87, 44), true); //right eye
	framebuffer.drawCircle(420, 490, 3, Color::BLACK, false); //nouse
	framebuffer.drawLine(400, 470, 440, 470, Color::BLACK); //mouth
	framebuffer.drawCircle(420, 320, 5, Color::BLACK, true); //up button
	framebuffer.drawCircle(420, 280, 5, Color::BLACK, true); //down button
	framebuffer.drawRectangle(430, 70, 55, 30, Color(137, 107, 73), true); //right shoe
	framebuffer.drawRectangle(355, 70, 55, 30, Color(137, 107, 73), true); //left shoe
}

// Task 2.1
void Application::task2_1() {

	framebuffer.radialGradient(Color::RED, Color::PURPLE, framebuffer.width / 2, framebuffer.height / 2);

}
// Task 2.2
void Application::task2_2() {

	framebuffer.gradient(Color::BLUE, Color::GREEN);

}

// Task 3.1
void Application::task3_1() {
	framebuffer.inverseFilter();

}
// Task 3.2
void Application::task3_2() {

	framebuffer.channelSwap(1);

}

//Task 4.1

void Application::task4_1() {
	//degree rotation
	framebuffer.rotate(24);

}

//Task 4.2

void Application::task4_2() {
	//scale
	framebuffer.scale(2);
	
}

//Task 5

void Application::task5() {
	for (int i = 0; i < 200; i++) {
		framebuffer.drawCircle(particles[i].x, particles[i].y, particles[i].size, Color::WHITE, true);
	}

}

//called after render
void Application::update(double seconds_elapsed)
{
	//to see all the keycodes: https://wiki.libsdl.org/SDL_Keycode
	if (keystate[SDL_SCANCODE_SPACE]) //if key space is pressed
	{
		//...
	}

	for (int i = 0; i < 200; i++) {
		if (particles[i].x + (float) (40*seconds_elapsed+0.5) >= framebuffer.width-20) {
			particles[i].x = 20;
		}
		else {
			particles[i].x +=(float)(40*seconds_elapsed+0.5);
		}
		if (particles[i].y - seconds_elapsed <= 20) {
			particles[i].y = framebuffer.height-20;
		}
		else {
			particles[i].y -=  seconds_elapsed;
		}
	}
	if (mouse_state && SDL_BUTTON(SDL_BUTTON_LEFT)) { // Si se presiona el click izquierdo 
		if (isPaint && !isCircle  && !isLine && !isTriangle) { // Boleano que impide que se pinte cuando no está en paint o cuando están activas las formas
			float x_position = mouse_position.x; // Posición del mouse
			float y_position = mouse_position.y;
			//if (0 + brush_size <= y_position && y_position < framebuffer.height - 50 - brush_size && 0 + brush_size <= x_position && x_position < framebuffer.width - brush_size) { // evita salirse del framebuffer o pintar la toolbar
			framebuffer.BresenhamCircle(x_position, y_position, brush_size, brush_color, TRUE); // dibuja circulos del tamaño del pincel				
			
		}
	}
}

//keyboard press event 
void Application::onKeyDown( SDL_KeyboardEvent event )
{
	//to see all the keycodes: https://wiki.libsdl.org/SDL_Keycode
	switch (event.keysym.scancode)
	{
	case SDL_SCANCODE_ESCAPE:
		exit(0);
		break; //ESC key, kill the app
	}



	if (event.keysym.scancode == SDL_SCANCODE_P) { // Activar paint

		if (isPaint) {
			isPaint = FALSE; // Si ya está activo el paint se desactiva
			printf("Paint Mode : Disabled\n");
			for (int x = 0; x < framebuffer.width; x++) {
				for (int y = 0; y < framebuffer.height; y++) {
					Color c = pict.getPixel(x, y);
					framebuffer.setPixel(x, y, c);
				}
			}
		}
		else {
			printf("Welcome to Paint\n");
			printf("Paint Mode: Enabled\n");
			isPaint = TRUE; // Activa el Paint
			if (framebuffer.loadTGA("toolbar.tga") == false)
			{
				std::cout << "image not found" << std::endl;;
			}
			framebuffer.flipY(); // Voltea la imagen
		}

	}
	
	if (event.keysym.scancode == SDL_SCANCODE_PERIOD) { // Aumentar tamaño del pincel "."
		if (brush_size < 300) { // Max size
			brush_size += 1;
			printf("Brush size: %d\n", brush_size);
		}
		else {
			printf("Max brush size reached: %d\n", brush_size);
		}
	}
	if (event.keysym.scancode == SDL_SCANCODE_COMMA) { // Disminuir tamaño del pincel ","
		if (brush_size > 1) { // Min size
			brush_size -= 1;
			printf("Brush size: %d\n", brush_size);
		}
		else {
			printf("Min brush size reached: %d\n", brush_size);
		}

	}
	if (event.keysym.scancode == SDL_SCANCODE_C) { // Activar círculos
		if (isCircle) { // Si ya está activo se desactiva
			isCircle = FALSE;
			printf("Circle Mode : Disabled\n");
		}
		else {
			isCircle = TRUE;
			printf("Circle Mode : Enabled\n");
		}

	}
	if (event.keysym.scancode == SDL_SCANCODE_T) { // Activar triángulos
		if (isTriangle) { // Si ya está activo se desactiva
			isTriangle = FALSE;
			printf("Triangle Mode : Disabled\n");
		}
		else {
			isTriangle = TRUE;
			printf("Triangle Mode : Enabled\n");
		}

	}
	if (event.keysym.scancode == SDL_SCANCODE_V) { // Activar interpolación en triángulos
		if (interpolation) { // Si ya está activo se desactiva
			interpolation = FALSE;
			printf("Triangle Mode : Normal (no iterpolation)\n");
		}
		else {
			interpolation = TRUE;
			printf("Triangle Mode : Interpolation\n");
		}

	}
	if (event.keysym.scancode == SDL_SCANCODE_L) { // Activar lineas
		if (isLine) { // Si ya está activo se desactiva
			isLine = FALSE;
			printf("Line Mode : Disabled\n");
		}
		else {
			isLine = TRUE;
			printf("Line Mode : Enabled\n");
		}

	}
	if (event.keysym.scancode == SDL_SCANCODE_D) { // Alternar modos línea
		if (isDDA) { // Si ya está activo se desactiva
			isDDA = FALSE;
			printf("Line Mode : Bresenham\n");
		}
		else {
			isDDA = TRUE;
			printf("Line Mode : DDA\n");
		}
	}

	if (event.keysym.scancode == SDL_SCANCODE_F) { // Activar fill
		if (fill) { // Si ya está activo se desactiva
			fill = FALSE;
			printf("Fill : Disabled\n");
		}
		else {
			fill = TRUE;
			printf("Fill : Enabled\n");
		}

	}

}

//keyboard key up event 
void Application::onKeyUp(SDL_KeyboardEvent event)
{
	//...
}

//mouse button event
void Application::onMouseButtonDown( SDL_MouseButtonEvent event )
{
	if (event.button == SDL_BUTTON_LEFT) //left mouse pressed
	{
		//if you read mouse position from the event, careful, Y is reversed, use mouse_position instead
		float x = mouse_position.x;
		float y = mouse_position.y;
		
		if (isPaint) {


			// New canvas
			if (11 < x && x < 34 && framebuffer.height - 8 > y && y > framebuffer.height - 40) {
				for (unsigned int y = 0; y < framebuffer.height - 50; ++y) {
					for (unsigned int x = 0; x < framebuffer.width; ++x) {
						framebuffer.setPixel(x, y, Color::WHITE);
					}
				}
			}
			// Save
			if (60 < x && x < 91 && framebuffer.height - 9 > y && y > framebuffer.height - 40) {
				framebuffer.saveTGA("newcanvas.tga");
			}
			if (framebuffer.height - 12 > y && y > framebuffer.height - 38) {
				// BLACK
				if (112 < x && x < 138) {
					brush_color = Color::BLACK;
				}
				// RED
				if (162 < x && x < 188) {
					brush_color = Color::RED;
				}
				// GREEN
				if (212 < x && x < 238) {
					brush_color = Color::GREEN;
				}
				// BLUE
				if (262 < x && x < 288) {
					brush_color = Color::BLUE;
				}
				// YELLOW
				if (312 < x && x < 338) {
					brush_color = Color::YELLOW;
				}
				// MAGENTA
				if (362 < x && x < 388) {
					brush_color = Color::PURPLE;
				}
				// CYAN
				if (412 < x && x < 438) {
					brush_color = Color::CYAN;
				}
				// WHITE
				if (462 < x && x < 488) {
					brush_color = Color::WHITE;
				}
				
			}
		}
		
			
		if (isCircle) { // Dibujar círculo
			printf("Circle center: (%f,%f)\n",x,y);
			framebuffer.BresenhamCircle(x, y, brush_size, brush_color, fill); // x e y del mouse y el resto de parámetros son variables globales

		}

		if (0 + brush_size <= y && y < framebuffer.height - 50 - brush_size && 0 + brush_size <= x && x < framebuffer.width - brush_size) { // evita salirse del framebuffer o pintar la toolbar
			if (isLine) { // Dibujar línea
				if (s[0] == -1) { // Nueva línea
					printf("Line start: (%f,%f)\n", x, y);
					s[0] = x;
					s[1] = y;
				}
				else {
					printf("Line end: (%f,%f)\n", x, y);
					if (isDDA) {
						framebuffer.Bresenham(s[0], s[1], x, y, Color::RED); // Función DDA

					}
					else {
						framebuffer.Bresenham(s[0], s[1], x, y, brush_color); // Función Bresenham
					}
					s[0] = -1; // Se resetea línea
				}
			}

			if (isTriangle) { // Dibujar triangulo
				if (v0[0] == -1) { // Nueva triángulo
					printf("Triangle v0: (%f,%f)\n", x, y);
					v0[0] = x;
					v0[1] = y;
					if (interpolation) {
						Color c0 = brush_color;
						printf("Color c0: (%d,%d,%d)\n", c0.r, c0.g, c0.b);
					}
				}
				else if (v1[0] == -1) {
					printf("Triangle v1: (%f,%f)\n", x, y);
					v1[0] = x;
					v1[1] = y;
					if (interpolation) {
						Color c1 = brush_color;
						printf("Color c1: (%d,%d,%d)\n", c1.r, c1.g, c1.b);
					}
				}
				else {
					printf("Triangle v2: (%f,%f)\n", x, y);
					if (interpolation) {
						printf("Color c2: (%d,%d,%d)\n", brush_color.r, brush_color.g, brush_color.b);
						//framebuffer.TriangleInterpolation(v0[0],v0[1],v1[0],v1[1], x, y,c0,c1,brush_color, TRUE);
					}
					else
					{
						//framebuffer.Triangle(v0[0],v0[1],v1[0],v1[1], x, y, brush_color, fill);
					}
					v0[0] = -1; // Se resetea triángulo
					v1[0] = -1;
				}
			}
		}
		
	}
}

void Application::onMouseButtonUp( SDL_MouseButtonEvent event )
{
	if (event.button == SDL_BUTTON_LEFT) //left mouse unpressed
	{

	}
}

//when the app starts
void Application::start()
{
	std::cout << "launching loop..." << std::endl;
	launchLoop(this);
}
