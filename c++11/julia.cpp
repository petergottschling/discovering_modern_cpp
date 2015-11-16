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

class julia_pixel
{
  public:
    julia_pixel(SDL_Surface* screen, complex<float> k, int x, int y, int xdim, int ydim, int max_iter)
      : screen(screen), max_iter(max_iter), iter(0),
	c(2.4f * float(x) / float(ydim), 2.4f * float(y) / float(ydim)), // scale proportionally such that y=[-1.2,1.2] 
	k(k)
    {
	c-= complex<float>(1.2 * xdim / ydim, 1.2); // shift (-0.5, 0) to center
	iterate();
    }

    int iterations() const { return iter; }
    uint32_t color() const 
    {
	if (iter == max_iter) return SDL_MapRGB(screen->format, 0, 0, 0);
	const int ci= 512 * iter / max_iter; // incremental value for color
	return iter < max_iter/2 ? SDL_MapRGB(screen->format, ci, 0, 0)
	                         : SDL_MapRGB(screen->format, 255, ci-255, ci-255);
    }

  private:
    void iterate()
    {
	complex<float> z= c;
	for (; iter < max_iter && norm(z) <= 4.0f; iter++)
	    z= z * z + k;
    };

    SDL_Surface* screen;
    const int max_iter;
    int iter;
    complex<float> c, k;
};

int main (int argc, char* argv[]) 
{
    const int max_iter= 40;
    int xdim= 800, ydim= 600;
    if (argc >= 3)
	xdim= atoi(argv[1]), ydim= atoi(argv[2]);
    complex<float> k(-0.6, 0.6); // Cantor dust (?) // k(0.353,0.288);
    if (argc >= 5)
	k.real(atof(argv[3])), k.imag(atof(argv[4]));   

    sdl_check(SDL_Init(SDL_INIT_VIDEO) != -1);
    SDL_Surface* screen = SDL_SetVideoMode(xdim, ydim, 32, SDL_DOUBLEBUF); sdl_check(screen);
    SDL_WM_SetCaption("Julia Set", "Julia Set");
    
    SDL_LockSurface(screen);
    for (int y= 0; y < ydim; y++)
	for (int x= 0; x < xdim; x++) {
	    julia_pixel m(screen, k, x, y, xdim, ydim, max_iter);
	    put_pixel(screen, x, y, m.color());
	}
    SDL_UnlockSurface(screen);
    SDL_Flip(screen);	
    SDL_SaveBMP(screen, "julia.bmp");

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

    return 0;
}

