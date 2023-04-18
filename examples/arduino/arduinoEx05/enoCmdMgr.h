// Enodia Command Manager
// Brygg Ullmer, Clemson University
// Partial support from NSF CNS-1828611
// Begun 2023-04
// LLGPL3

#ifndef enoCommandMgr_h
#define enoCommandMgr_h
#endif

#define MAX_COMMANDS 15

#include "enoCommandmapper.h"

///////////////////////// Enodia Command Manager /////////////////////////////

class enoCommandMgr {
  public:
    enoCommandMgr(int maxNumCommands=#MAX_COMMANDS);
    void registerHandler();
    void registerCommand();

    char *getCommandMgrStr();

    char *getCommandMgrStr();
    char *getCommandMgrYamlStr();

  protected:
    int  numCommands, numMaxCommands;
    enoCommand *enoCommands;

    const char *helpHeader; // "idx col brt key name";
    const char *helpTempl;  // "%2i %1c %2X %1c %s\n";
};

/// end ///
