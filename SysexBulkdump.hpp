//
//  SysexBulkdump.hpp
//  MOXFVst3SongMode - VST3
//
//  Created by James on 22/04/2019.
//

#ifndef SysexBulkdump_hpp
#define SysexBulkdump_hpp

#include "MOXFSongState.hpp"
#include "../JuceLibraryCode/JuceHeader.h"

class MOXFBulkdump
{
public:
    MOXFBulkdump( MOXFSongState& state, MidiOutput* output,  int millisconds = 0 );
    ~MOXFBulkdump();
    void send( int milliseconds = 0);
    
private:
    MOXFSongState& state_;
    int send_delay_;
    MidiMessage bulk_footer_;
    MidiMessage bulk_header_;
    MidiOutput* output_;
};



#endif /* SysexBulkdump_hpp */
