#include <cstdlib>
#include <cstdint>
#include <cassert>
#include <complex>

#ifdef WIN32
#include <SDL.h>
#else
#include <SDL/SDL.h>
#endif

using namespace std;

struct sdl_error {};
inline void sdl_check(bool allclear) { if (!allclear) throw sdl_error(); }

inline void put_pixel(SDL_Surface* screen, int x, int y, uint32_t pixel)
{
    assert(screen->format->BytesPerPixel == 4);
    auto pixel_address= reinterpret_cast<uint32_t*>(screen->pixels) + y * screen->w + x;
    *pixel_address= pixel;
}

class mandel_pixel
{
  public:
    mandel_pixel(SDL_Surface* screen, int x, int y, int xdim, int ydim, int max_iter)
      : screen(screen), max_iter(max_iter), iter(0), c(x, y)
    {
	// scale y to [-1.2,1.2] and shift -0.5+0i to the center
	c*= 2.4f / static_cast<float>(ydim);  
	c-= complex<float>(1.2 * xdim / ydim + 0.5, 1.2); 
	iterate();
    }

    int iterations() const { return iter; }
    uint32_t color() const 
    {
	if (iter == max_iter) return SDL_MapRGB(screen->format, 0, 0, 0);
	const int ci= 512 * iter / max_iter; // incremental value for color
	// return SDL_MapRGB(screen->format, 40*iter & 255, 66*iter & 255, 100*iter & 255);
	return iter < max_iter/2 ? SDL_MapRGB(screen->format, ci, 0, 0)
	                         : SDL_MapRGB(screen->format, 255, ci-255, ci-255);
    }

  private:
    void iterate()
    {
	complex<float> z= c;
	for (; iter < max_iter && norm(z) <= 4.0f; iter++)
	    z= z * z + c;
    };

    SDL_Surface* screen;
    const int max_iter;
    int iter;
    complex<float> c;
};

int main (int argc, char* argv[]) 
{
    const int max_iter= 30;
    int xdim= 1200, ydim= 800;
    if (argc >= 3)
	xdim= atoi(argv[1]), ydim= atoi(argv[2]);

    sdl_check(SDL_Init(SDL_INIT_VIDEO) != -1);
    SDL_Surface* screen = SDL_SetVideoMode(xdim, ydim, 32, SDL_DOUBLEBUF); sdl_check(screen);
    SDL_WM_SetCaption("Mandelbrot's Apple Manikin", "Mandelbrot's Apple Manikin");
    
    SDL_LockSurface(screen);
    for (int y= 0; y < ydim; y++)
	for (int x= 0; x < xdim; x++) {
	    mandel_pixel m(screen, x, y, xdim, ydim, max_iter);
	    put_pixel(screen, x, y, m.color());
	}
    SDL_UnlockSurface(screen);
    SDL_Flip(screen);	
    // SDL_SaveBMP(screen, "mandelbrot.bmp"); // if you want to save the fractal

    bool run = true;
    while(run) {
    	// Polling for events as long as there exists some
    	SDL_Event event;
    	while(SDL_PollEvent(&event))
    	    switch(event.type) {
    	      case SDL_QUIT: run = false; break;
    	    }
    }
    SDL_Quit();
}

