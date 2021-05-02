#include "stdafx.h"
#include "CtrlrUtilities.h"
#include "CtrlrLog.h"

CtrlrLog *CtrlrLog::ctrlrLog = nullptr;

CtrlrLog::CtrlrLog(const bool _logToFile)
	:	logToFile(_logToFile),
		fileLogger(nullptr)
{
	CtrlrLog::ctrlrLog = this;

	setLogToFile (logToFile);
}

CtrlrLog::~CtrlrLog()
{
	ctrlrLog = nullptr;
	if (fileLogger)
	{
		Logger::setCurrentLogger (0);
		deleteAndZero (fileLogger);
	}
	else
	{
		Logger::setCurrentLogger (0);
	}
}

void CtrlrLog::setLogToFile (const bool _logToFile)
{
	logToFile = _logToFile;

	if (logToFile)
	{
		Logger::writeToLog ("CtrlrLog::setLogToFile: " + File::getSpecialLocation(File::currentApplicationFile).withFileExtension(".log").getFullPathName());
		if (fileLogger)
		{
			deleteAndZero (fileLogger);
		}
		fileLogger = new FileLogger (File::getSpecialLocation(File::currentApplicationFile).withFileExtension(".log"), "Ctrlr debug log");

		Logger::setCurrentLogger (fileLogger);
	}
	else
	{
		if (fileLogger)
		{
			Logger::setCurrentLogger (this);
			deleteAndZero (fileLogger);
		}
		else
		{
			Logger::setCurrentLogger (this);
		}
	}
}

void CtrlrLog::logMessage(CtrlrLog::LogLevel, const String &file, const String &function, const int line, char *format, ...)
{
    char buffer[512];
    va_list args;
    va_start (args, format);
    vsnprintf (buffer,512,format, args);
    va_end (args);
    logMessage ("[" + File(file).getFileName() + ":" + function + ":" + String(line) + "]: " + String(buffer));
}

void CtrlrLog::logMessage (const String &message)
{
	logMessage (message, Info);
}

void CtrlrLog::logMessage (const String &message, const LogLevel level)
{
	Logger::outputDebugString (message);

	CtrlrLogMessage m;
	m.level		= level;
	m.message	= message.trim();
	m.time		= Time::getCurrentTime();

	if (fileLogger)
	{
		fileLogger->logMessage(formatMessage(m).trim());
	}

	pendingQueue.add (m);
	triggerAsyncUpdate();
}

void CtrlrLog::logMessage (const String &device, const MidiMessage &message, const LogLevel level)
{
	if (getBitOption(midiLogOptions.get(), midiLogInput) && level == MidiIn)
	{
		logMessage ((getBitOption(midiLogOptions.get(), midiLogDevice) ? (" Dev:["+device+"]") : "")+ formatMidiMessage(message), level);
	}

	if (getBitOption(midiLogOptions.get(), midiLogOutput) && level == MidiOut)
	{
		logMessage ((getBitOption(midiLogOptions.get(), midiLogDevice) ? (" Dev:["+device+"]") : "")+ formatMidiMessage(message), level);
	}
}

void CtrlrLog::logMessage (const String &device, const MidiMessage &message, const double time, const LogLevel level)
{
	if (getBitOption(midiLogOptions.get(), midiLogInput) && level == MidiIn)
	{
		logMessage ((getBitOption(midiLogOptions.get(), midiLogDevice) ? (" Dev:["+device+"]") : "")+ formatMidiMessage(message, time), level);
	}

	if (getBitOption(midiLogOptions.get(), midiLogOutput) && level == MidiOut)
	{
		logMessage ((getBitOption(midiLogOptions.get(), midiLogDevice) ? (" Dev:["+device+"]") : "")+ formatMidiMessage(message, time), level);
	}
}

void CtrlrLog::logMessage (const String &device, const MidiBuffer &buffer, const double time, const LogLevel level)
{
	MidiBuffer::Iterator i(buffer);
	MidiMessage m;
	int t;
	while (i.getNextEvent (m,t))
	{
		logMessage (device, m, level);
	}
}

void CtrlrLog::handleAsyncUpdate()
{
	for (int i=0; i<pendingQueue.size(); i++)
	{
		if (pendingQueue[i].level == Error)
		{
			WARN(formatMessage(pendingQueue[i], true, true));
		}
		listeners.call (&CtrlrLog::Listener::messageLogged, pendingQueue[i]);
	}
	pendingQueue.clear();
}

Colour CtrlrLog::getColourForLevel(const CtrlrLog::LogLevel logLevel)
{
	switch (logLevel)
	{
		case Info:
			return Colours::black;
		case Warn:
			return Colours::yellow.darker();
		case LuaRuntimeError:
		case LuaError:
		case Error:
			return Colours::red.darker();
		case Debug:
			return Colours::darkgrey;
		case Lua:
			return Colours::blue.darker();
		case MidiIn:
			return Colours::steelblue;
		case MidiOut:
			return Colours::darkseagreen;
		case Transaction:
			return (Colours::darkmagenta);
		case kLogLevels:
		default:
			break;
	}

	return Colours::black;
}

Colour CtrlrLog::getColourForMessage(const CtrlrLogMessage &message)
{
	return (getColourForLevel(message.level));
}

String CtrlrLog::levelToString (const LogLevel &level)
{
	switch (level)
	{
	case Info:
		return ("[INFO    ]");
	case Warn:
		return ("[WARN    ]");
	case Error:
		return ("[ERROR   ]");
	case Debug:
		return ("[DEBUG   ]");
	case Lua:
		return ("[LUA     ]");
	case MidiIn:
		return ("[MIDI IN ]");
	case MidiOut:
		return ("[MIDI OUT]");
	case LuaError:
		return ("[LUA ERR ]");
	case LuaRuntimeError:
		return ("[LUA RERR]");
	case Transaction:
		return ("[TRANS   ]");
	case kLogLevels:
		return ("[INFO    ]");
	}
	return ("[INFO   ]");
}

CtrlrLog::LogLevel CtrlrLog::stringToLevel (const String &_level)
{
	const String level = _level.trim();
	if (level == "INFO")
		return (Info);
	if (level == "WARN")
		return (Warn);
	if (level == "ERROR")
		return (Error);
	if (level == "DEBUG")
		return (Debug);
	if (level == "LUA")
		return (Lua);
	if (level == "MIDI IN")
		return (MidiIn);
	if (level == "MIDI OUT")
		return (MidiOut);
	if (level == "LUA ERR")
		return (LuaError);
	if (level == "LUA RERR")
		return (LuaRuntimeError);
	if (level == "TRANS")
		return (Transaction);

	return (kLogLevels);
}

String CtrlrLog::timeToString(const Time &time)
{
	return (time.formatted ("[%H:%M:%S:") + String::formatted ("%06d]", time.getMilliseconds()));
}

String CtrlrLog::formatMessage(const CtrlrLogMessage &m, const bool includeLevel, const bool includeTimestamp)
{
	String ret;

	if (includeLevel)
		ret << levelToString (m.level);

	if (includeTimestamp)
		ret << timeToString (m.time);

	ret << ": ";

	if (m.message.endsWith("\n"))
	{
		ret << m.message.substring(1);
	}
	else
	{
		ret << m.message;
	}

	return (ret);
}

const String CtrlrLog::formatMidiMessage (const MidiMessage &message, const double timestamp)
{
	return (getMidiMessageAsLogString (
													message,
													timestamp,
													getBitOption(midiLogOptions.get(), midiLogName),
													getBitOption(midiLogOptions.get(), midiLogChannel),
													getBitOption(midiLogOptions.get(), midiLogNumber),
													getBitOption(midiLogOptions.get(), midiLogValue),
													getBitOption(midiLogOptions.get(), midiLogTimestamp),
													getBitOption(midiLogOptions.get(), midiLogRawData),
													getBitOption(midiLogOptions.get(), midiLogRawDecimal),
													getBitOption(midiLogOptions.get(), midiLogDataSize)
										)
	);
}

void CtrlrLog::addListener (Listener *l)
{
    listeners.add (l);
}

void CtrlrLog::removeListener (Listener *l)
{
    listeners.remove(l);
}

