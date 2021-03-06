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
#include <vector>
#include <memory>
#include <regex>

#include "midiin.h"
#include "oscout.h"

class MidiInProcessor
{
public:
    MidiInProcessor(std::unique_ptr<MidiIn>&& input, std::vector<std::shared_ptr<OscOutput>> outputs, bool monitor = false);
    static void onMidi(double deltatime, std::vector<unsigned char> *message, void *userData);
    void setOscTemplate(const std::string& oscTemplate);
    
private:
    void doTemplateSubst(std::string &str, const std::string& portName, int portId, int channel, const std::string& message_type) const;
    void dumpMIDIMessage(std::vector<unsigned char> *message) const;
    std::unique_ptr<MidiIn> m_input;
    std::vector<std::shared_ptr<OscOutput>> m_outputs;
    bool m_useOscTemplate;
    std::string m_oscTemplate;

    bool m_monitor;

    // To avoid having to construct the regex everytime
    static std::regex regexName;
    static std::regex regexId;
    static std::regex regexChannel;
    static std::regex regexMessageType;
    static std::regex regexDoubleSlash;
};
