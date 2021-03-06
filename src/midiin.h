// MIT License

// Copyright (c) 2016 Luis Lloret

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.


#pragma once

#include <thread>
#include <memory>
#include <vector>
#include <map>
#include "RtMidi.h"

// This class manages a MIDI input device as seen by RtMidi
class MidiIn {
public:
    MidiIn(std::string portName);
    MidiIn(const MidiIn&) = delete;
    MidiIn& operator=(const MidiIn&) = delete;
    
    ~MidiIn();

    bool checkValid() const;

    void setCallback(RtMidiIn::RtMidiCallback callback, void *userData);
    std::string getPortName() const;
    int getPortId() const;

    static std::vector<std::string> getInputNames();
    static int getPortIdFromName(std::string portName);
    static void updateMidiDevicesNamesMapping();

private:
    RtMidiIn m_midiIn;
    std::string m_portName;
    // TODO: There will be a port id for the rtmidi, and a higher level portid at the MidiIn level, to help with hotplug
    // getPortId should retyurn the high level one
    // The RtMIDI one should be internal to this class and completely private
    unsigned int m_portId;

    static std::map<std::string, int> m_midiInputNameToId;
    static std::vector<std::string> m_midiInputIdToName;
};
