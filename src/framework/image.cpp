#include "image.h"


Image::Image() {
	width = 0; height = 0;
	pixels = NULL;
}

Image::Image(unsigned int width, unsigned int height)
{
	this->width = width;
	this->height = height;
	pixels = new Color[width*height];
	memset(pixels, 0, width * height * sizeof(Color));
}

//copy constructor
Image::Image(const Image& c) {
	pixels = NULL;

	width = c.width;
	height = c.height;
	if(c.pixels)
	{
		pixels = new Color[width*height];
		memcpy(pixels, c.pixels, width*height*sizeof(Color));
	}
}

//basic functions
void Image::drawRectangle(int x0, int y0, int w, int h, Color color, bool fill) {
	for (int x = x0; x < (x0 + w); ++x)
	{
		if (fill)
		{
			for (int y = y0; y < (y0 + h); ++y) //pintamos el interior
			{
				setPixel(x, y, color);
			}
		}
		else //pintamos solo el contorno, en este caso los costados horizontales
		{
			setPixel(x, y0, color);
			setPixel(x, y0 + h - 1, color);
		}
	}
	if (fill == false) //si hemos pintado solo el contorno debemos crear otro for para los costados verticales
	{
		for (int y = y0 + 1; y < (y0 + h - 1); ++y)
		{
			setPixel(x0, y, color);
			setPixel(x0 + w - 1, y, color);
		}
	}
}

void Image::drawCircle(int x, int y, int r, Color color, bool fill) {
	for (int xi = (x-r-1); xi < (x+ r+1); ++xi)
	{
		for (int yi = (y-r-1); yi < (y + r+1); ++yi) //iteramos las coordenadas como si fuera un cuadrado
		{
			//Pintamos el contorno en todos los píxeles que se encuentren a distancia r del centro, con un margen de error de +-1
			if (sqrt(pow(xi - x, 2) + pow(yi - y, 2)) < (r+1) && sqrt(pow(xi - x, 2) + pow(yi - y, 2)) > (r - 1)) { 
				setPixel(xi, yi, color);
			}
			//pintamos el interior en el caso de los círculos con relleno
			else if ((sqrt(pow(xi - x, 2) + pow(yi - y, 2)) <= r) && fill)  {
				setPixel(xi, yi, color);
			}
		}
	}
}
void Image::drawLine(int x1, int y1, int x2, int y2, Color color) {
	//Cambiamos los puntos si P1 está a la derecha de P2 (para pintar hacia la derecha) 
	if (x1 > x2) {
		int temp = x1;
		x1 = x2;
		x2 = temp;
		temp = y1;
		y1 = y2;
		y2 = temp;
	}
	if (x1 == x2) {
		//Cambiamos los y si P1 está arriba de P2 y tienen la misma x para dibujar hacia arriba
		if (y1 > y2) {
			int tempy = y1;
			y1 = y2;
			y2 = tempy;
		}
		//Dibujamos una línea vertical
		for (int y = y1; y <= y2; ++y)
		{
			setPixel(x1, y, color);
		}
	}
	else if (y1 == y2) {
		//Dibujamos una línea horizontal
		for (int x = x1; x <= x2; ++x)
		{
			setPixel(x, y1, color);
		}
	}
	else {

		float m = (float)(y2 - y1) / (x2 - x1); //Calculamos la pendiente
		for (int x = x1; x <= x2; ++x)
		{
			if (y1 < y2) { //Si dibujamos hacia arriba
				for (int y = y1; y <= y2; ++y)
				{
					//Sustituímos x e y en la ecuación para comprobar si forma parte de la recta con un margen de error de +-1
					if ((float)(y - y1) <= m * (float)(x - x1) + 1 && (float)(y - y1) >= m *(float) (x - x1) - 1) {
						setPixel(x, y, color);
					}
				}
			}
			else {
				for (int y = y1; y >= y2; --y) //Si dibujamos hacia arriba
				{
					if ((y - y1) <= m * (x - x1) + 1 && (y - y1) >= m * (x - x1) - 1) {
						setPixel(x, y, color);
					}
				}
			}
		}
	}
}

// Utils			
float Image::computeDistance(int x1, int y1, int x2, int y2) {
	float vx = x2 - x1;
	float vy = y2 - y1;
	vx *= vx;
	vy *= vy;
	float d = sqrt(vx + vy);
	return d;
}


// Task 3.2

// RADIAL GRADIENT
void Image::radialGradient(Color s_color, Color f_color, unsigned int x0, unsigned int y0) {
	int delta_r = f_color.r - s_color.r;
	int delta_g = f_color.g - s_color.g;
	int delta_b = f_color.b - s_color.b;
	float dmax = computeDistance(x0, y0, width, height); //Distancia entre el punto inicial y los extremos

	for (unsigned int x = 0; x < width; x++) {
		for (unsigned int y = 0; y < height; y++) {
			float d = computeDistance(x0, y0, x, y);
			float p = d / dmax; //porcentaje de la distancia
			setPixel(x, y, Color(s_color.r + delta_r * p, s_color.b + delta_g * p, s_color.r + delta_b * p));
		}
	}
}

// GRADIENT
void Image::gradient(Color s_color, Color f_color) {
	int delta_r = f_color.r - s_color.r;
	int delta_g = f_color.g - s_color.g;
	int delta_b = f_color.b - s_color.b;

	for (unsigned int x = 0; x < width; x++) {
		for (unsigned int y = 0; y < height; y++) {
			float g = (float)x/(float)width; //Calculamos la diferencia de los puntos en porcentaje
			setPixel(x, y, Color(s_color.r+ delta_r * g, s_color.g+ delta_g * g, s_color.b+ delta_b * g));
		}
	}
}


void Image::setPixelP(unsigned int x, unsigned int y, Color c) {
	if (0 < x && x < width && 0 < y && y < height-50) { // Evita que se dibuje un pixel fuera del framebuffer o en la toolbar, solo es necesario para el Paint, concretamente para los círculos.
		setPixel(x, y, c);
	}
}

void Image::Bresenham(int x0, int y0, int x1, int y1, Color c) {
	
	 int dx, dy, inc_E, inc_NE, m, x, y; // Inicializar variables
	
	if (x0 > x1) { // Cambiar coordenadas
		x = x0;
		y = y0;
		x0 = x1;
		y0 = y1;
		x1 = x;
		y1 = y;
	}

	// Operaciones comunes
	dx = x1 - x0;
	dy = y1 - y0;
	x = x0;
	y = y0;
	setPixel(x, y, c);

	if (dx >= dy && dy >= 0) { // octante 1 (p <=1; x1 < x2) = octante 5
		
		inc_E = 2 * dy;
		inc_NE = 2 * (dy - dx);
		m = 2 * dy - dx;
		
		while (x < x1) {
			if (m <= 0) {
				m += inc_E;
				x++;
			}
			else {
				m += inc_NE;
				x++;
				y++;
			}
			setPixel(x, y, c);
		}
	} else if (dx < dy && dy >=0) { // octante 2 (p > 1; x1 < x2) = = octante 6
		
		inc_E = 2 * dx;
		inc_NE = 2 * (dx - dy);
		m = 2 * dx - dy;

		while (y < y1) {
			if (m <= 0) {
				m += inc_E;
				y++;
			}
			else {
				m += inc_NE;
				x++;
				y++;
			}
			setPixel(x, y, c);
		}
	} else if (dx <= -dy) { // octante 7 (p < -1; x1 < x2) = octante 3
		
		inc_E = 2 * dx;
		inc_NE = 2 * (dx + dy);
		m = 2 * dx + dy;

		while (y > y1) {
			if (m <= 0) {
				m += inc_E;
				y--;
			}
			else {
				m += inc_NE;
				x++;
				y--;
			}
			setPixel(x, y, c);
		}
	} else { //if (dx > -dy && dy < 0) { // octante 8 (p >= -1; x1 < x2) = octante 4
		
		inc_E = 2 * -dy;
		inc_NE = 2 * (-dy - dx);
		m = 2 * -dy - dx;
		
		while (x < x1) {
				
			if (m <= 0) {
				m += inc_E;
				x++;
			}
			else {
				m += inc_NE;
				x++;
				y--;
			}
			setPixel(x, y, c);
		}
	}
}

void Image::BresenhamCircle(int x0, int y0, int radius, Color c, bool fill) {
	/*if (x0 + radius > width || x0 - radius < 0 || y0 + radius > height || y0 - radius < 0) {
		printf("Circle out of framebuffer!\n");
	}*/
	
	// Se utiliza una función nueva llamada setPixelP, que es para que los píxeles seleccionas no pinten ni la toolbar ni se salgan fuera de rango del framebuffer.

	int x, y, v; // Variables que se usan
	x = 0;
	y = radius;
	v = 1 - radius;
		
	if (fill) { // Se rellena, se utilizan dos formas distintas para optimizar el número de instrucciones
		while (y > x) { // Se va recorriendo el arco hasta que x e y estén a la par
			if (v < 0) { // Sigue en la misma y
				v += 2 * x + 3;
				x++;
			}
			else { // Aumenta la y
				v += 2 * (x - y) + 5;
				x++;
				y--;
				for (int i = -x; i <= x; i++) {
					//printf("X: %d, -X: %d, i = %d\n", -x, x, i);
					setPixelP(x0 + i, y0 + y, c);
					setPixelP(x0 + i, y0 - y, c);
					setPixelP(x0 - y, y0 + i, c);
					setPixelP(x0 + y, y0 - i, c);

				}
			}
		}

		for (int i = -x; i <= x; i++) {
			for (int j = -x; j <= x; j++) {
				setPixelP(x0 + i, y0 + j, c);
			}
		}
	}
	else { // No se rellena
		// Se rellenan los 2 pixeles iniciales, uno arriba y otro abajo, ya que a partir de ahí empezaran a iterar
		setPixelP(x0 + x, y0 + y, c);
		setPixelP(x0 + x, y0 - y, c);

		while (y > x) { // Se va recorriendo el arco hasta que x e y estén a la par
			if (v < 0) { // Sigue en la misma y
				v += 2 * x + 3;
				x++;
			}
			else { // Aumenta la y
				v += 2 * (x - y) + 5;
				x++;
				y--;
					
			}
			// Se rellenan 8 píxeles por iteración, uno en cada octante
			setPixelP(x0 + x, y0 + y, c);
			setPixelP(x0 - x, y0 - y, c);
			setPixelP(x0 + x, y0 - y, c);
			setPixelP(x0 - x, y0 + y, c);
			setPixelP(x0 + y, y0 + x, c);
			setPixelP(x0 - y, y0 - x, c);
			setPixelP(x0 + y, y0 - x, c);
			setPixelP(x0 - y, y0 + x, c);
				
		}
	}
	
}



//Task 3.3
// INVERSE

void Image::inverseFilter() {
	for (unsigned int x = 0; x < width; x++) {
		for (unsigned int y = 0; y < height; y++) {
			Color color = getPixelSafe(x, y);
			//Calculamos los valores inversos 
			color.r = 255 - color.r;
			color.g = 255 - color.g;
			color.b = 255 - color.b;

			setPixel(x, y, color);
		}
	}
}

//CHANNEL SWAP

void Image::channelSwap(int option) {
	for (unsigned int x = 0; x < width; x++) {
		for (unsigned int y = 0; y < height; y++) {
			Color color = getPixel(x, y);
			int red = color.r;
			int green = color.g;
			int blue = color.b;

			// Case 1
			if (option == 1) {
				color.r = green; //El valor del canal rojo se le atribuye al canal verde
				color.g = blue; 
				color.b = red;
			}// Case 2
			else if (option == 2) {
				color.r = blue;
				color.g = red;
				color.b = green;
			}// Case 3
			else if (option == 3) {
				color.r = green;
				color.g = red;
			}// Case 4
			else if (option == 4) {
				color.r = blue;
				color.b = red;
			} // Case 5
			else if (option == 5) {
				color.g = blue;
				color.b = green;
			}
			setPixel(x, y, color);
		}
	}
}

//Task 4.1
void Image::rotate(int degree) {
	//calculamos el centro
	int x0 = (int)(width / 2); 
	int y0 = (int)(height / 2);

	Image aux(800, 600);
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			Color color = getPixel(x , y );
			//calculamos las nuevas coordenadas x,y
			int x1 = (int)(cos(DEG2RAD * degree) * (x - x0) - sin(DEG2RAD * degree) * (y - y0) + x0);
			int y1 = (int)(sin(DEG2RAD * degree) * (x - x0) + cos(DEG2RAD * degree) * (y - y0)  +y0);
			if (x1 < width && y1 < height) {
				aux.setPixel(x1, y1, color); //Dibujamos la imagen auxiliar
			}
		}
	}

	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			setPixel(x, y, aux.getPixel(x, y)); //Copiamos la imagen auxiliar a la original
		}
	}
}

//Task 4.2
void Image::scale(float s) {
	Image aux(800, 600);
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			Color color;
			if ((int)x * s >= width ||(int) s * y >= height) {
				color = Color::BLACK; //Los píxeles restantes los pintamos de negrp
			} else {
				color = getPixel((int)(x * s),(int)( y * s));
			}
			aux.setPixel(x, y, color); //dibujamos los píxeles en la imagen auxiliar
		}
	}

	//copiamos la imagen en el framebuffer original
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			setPixel(x, y, aux.getPixel(x, y));
		}
	}
}

//assign operator
Image& Image::operator = (const Image& c)
{
	if(pixels) delete pixels;
	pixels = NULL;

	width = c.width;
	height = c.height;
	if(c.pixels)
	{
		pixels = new Color[width*height*sizeof(Color)];
		memcpy(pixels, c.pixels, width*height*sizeof(Color));
	}
	return *this;
}

Image::~Image()
{
	if(pixels) 
		delete pixels;
}



//change image size (the old one will remain in the top-left corner)
void Image::resize(unsigned int width, unsigned int height)
{
	Color* new_pixels = new Color[width*height];
	unsigned int min_width = this->width > width ? width : this->width;
	unsigned int min_height = this->height > height ? height : this->height;

	for(unsigned int x = 0; x < min_width; ++x)
		for(unsigned int y = 0; y < min_height; ++y)
			new_pixels[ y * width + x ] = getPixel(x,y);

	delete pixels;
	this->width = width;
	this->height = height;
	pixels = new_pixels;
}

//change image size and scale the content
void Image::scale(unsigned int width, unsigned int height)
{
	Color* new_pixels = new Color[width*height];

	for(unsigned int x = 0; x < width; ++x)
		for(unsigned int y = 0; y < height; ++y)
			new_pixels[ y * width + x ] = getPixel((unsigned int)(this->width * (x / (float)width)), (unsigned int)(this->height * (y / (float)height)) );

	delete pixels;
	this->width = width;
	this->height = height;
	pixels = new_pixels;
}

Image Image::getArea(unsigned int start_x, unsigned int start_y, unsigned int width, unsigned int height)
{
	Image result(width, height);
	for(unsigned int x = 0; x < width; ++x)
		for(unsigned int y = 0; y < height; ++y)
		{
			if( (x + start_x) < this->width && (y + start_y) < this->height) 
				result.setPixel( x, y, getPixel(x + start_x,y + start_y) );
		}
	return result;
}

void Image::flipX()
{
	for(unsigned int x = 0; x < width * 0.5; ++x)
		for(unsigned int y = 0; y < height; ++y)
		{
			Color temp = getPixel(width - x - 1, y);
			setPixel( width - x - 1, y, getPixel(x,y));
			setPixel( x, y, temp );
		}
}

void Image::flipY()
{
	for(unsigned int x = 0; x < width; ++x)
		for(unsigned int y = 0; y < height * 0.5; ++y)
		{
			Color temp = getPixel(x, height - y - 1);
			setPixel( x, height - y - 1, getPixel(x,y) );
			setPixel( x, y, temp );
		}
}


//Loads an image from a TGA file
bool Image::loadTGA(const char* filename)
{
	unsigned char TGAheader[12] = {0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	unsigned char TGAcompare[12];
	unsigned char header[6];
	unsigned int bytesPerPixel;
	unsigned int imageSize;

	FILE * file = fopen(filename, "rb");
   	if ( file == NULL || fread(TGAcompare, 1, sizeof(TGAcompare), file) != sizeof(TGAcompare) ||
		memcmp(TGAheader, TGAcompare, sizeof(TGAheader)) != 0 ||
		fread(header, 1, sizeof(header), file) != sizeof(header))
	{
		std::cerr << "File not found: " << filename << std::endl;
		if (file == NULL)
			return NULL;
		else
		{
			fclose(file);
			return NULL;
		}
	}

	TGAInfo* tgainfo = new TGAInfo;
    
	tgainfo->width = header[1] * 256 + header[0];
	tgainfo->height = header[3] * 256 + header[2];
    
	if (tgainfo->width <= 0 || tgainfo->height <= 0 || (header[4] != 24 && header[4] != 32))
	{
		std::cerr << "TGA file seems to have errors or it is compressed, only uncompressed TGAs supported" << std::endl;
		fclose(file);
		delete tgainfo;
		return NULL;
	}
    
	tgainfo->bpp = header[4];
	bytesPerPixel = tgainfo->bpp / 8;
	imageSize = tgainfo->width * tgainfo->height * bytesPerPixel;
    
	tgainfo->data = new unsigned char[imageSize];
    
	if (tgainfo->data == NULL || fread(tgainfo->data, 1, imageSize, file) != imageSize)
	{
		if (tgainfo->data != NULL)
			delete tgainfo->data;
            
		fclose(file);
		delete tgainfo;
		return false;
	}

	fclose(file);

	//save info in image
	if(pixels)
		delete pixels;

	width = tgainfo->width;
	height = tgainfo->height;
	pixels = new Color[width*height];

	//convert to float all pixels
	for(unsigned int y = 0; y < height; ++y)
		for(unsigned int x = 0; x < width; ++x)
		{
			unsigned int pos = y * width * bytesPerPixel + x * bytesPerPixel;
			this->setPixel(x , height - y - 1, Color( tgainfo->data[pos+2], tgainfo->data[pos+1], tgainfo->data[pos]) );
		}

	delete tgainfo->data;
	delete tgainfo;

	return true;
}

// Saves the image to a TGA file
bool Image::saveTGA(const char* filename)
{
	unsigned char TGAheader[12] = {0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	FILE *file = fopen(filename, "wb");
	if ( file == NULL )
	{
		fclose(file);
		return false;
	}

	unsigned short header_short[3];
	header_short[0] = width;
	header_short[1] = height;
	unsigned char* header = (unsigned char*)header_short;
	header[4] = 24;
	header[5] = 0;

	//tgainfo->width = header[1] * 256 + header[0];
	//tgainfo->height = header[3] * 256 + header[2];

	fwrite(TGAheader, 1, sizeof(TGAheader), file);
	fwrite(header, 1, 6, file);

	//convert pixels to unsigned char
	unsigned char* bytes = new unsigned char[width*height*3];
	for(unsigned int y = 0; y < height; ++y)
		for(unsigned int x = 0; x < width; ++x)
		{
			Color c = pixels[(height-y-1)*width+x];
			unsigned int pos = (y*width+x)*3;
			bytes[pos+2] = c.r;
			bytes[pos+1] = c.g;
			bytes[pos] = c.b;
		}

	fwrite(bytes, 1, width*height*3, file);
	fclose(file);
	return true;
}


#ifndef IGNORE_LAMBDAS

//you can apply and algorithm for two images and store the result in the first one
//forEachPixel( img, img2, [](Color a, Color b) { return a + b; } );
template <typename F>
void forEachPixel(Image& img, const Image& img2, F f) {
	for(unsigned int pos = 0; pos < img.width * img.height; ++pos)
		img.pixels[pos] = f( img.pixels[pos], img2.pixels[pos] );
}

#endif