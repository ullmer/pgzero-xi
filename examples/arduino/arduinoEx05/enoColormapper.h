// Enodia colormapper
// Brygg Ullmer, Clemson University
// Partial support from NSF CNS-1828611
// Begun 2023-04
// LLGPL3

#ifndef enoColormapper_h
#define enoColormapper_h
#endif

class enoColormapper {
  public:
    enoColormapper(int maxColorkeysPerChunk);
    int registerColor(char colorKey, char *colorName, int colorVal);
    int allocateBuffers();
    
  private:
    int maxColorkeysPerChunk;
    enoColormapper *nextColormapperChunk;
}

// end //
