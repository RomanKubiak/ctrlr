#ifndef __CTRLR_LOG__
#define __CTRLR_LOG__

#include "CtrlrMacros.h"

#ifdef JUCE_DEBUG
#define _DBG(message)										if (CtrlrLog::ctrlrLog != nullptr) CtrlrLog::ctrlrLog->logMessage(message, CtrlrLog::Debug)
#else
#define _DBG(message)
#endif

#define _WRN(message)										if (CtrlrLog::ctrlrLog != nullptr) CtrlrLog::ctrlrLog->logMessage(message, CtrlrLog::Warn)
#define _ERR(message)										if (CtrlrLog::ctrlrLog != nullptr) CtrlrLog::ctrlrLog->logMessage(message, CtrlrLog::Error)
#define _INF(message)										if (CtrlrLog::ctrlrLog != nullptr) CtrlrLog::ctrlrLog->logMessage(message, CtrlrLog::Info)
#define _LUA(message)										if (CtrlrLog::ctrlrLog != nullptr) CtrlrLog::ctrlrLog->logMessage(message, CtrlrLog::Lua)
#define _LERR(message)										if (CtrlrLog::ctrlrLog != nullptr) CtrlrLog::ctrlrLog->logMessage(message, CtrlrLog::LuaError)
#define _LRUNERR(message)									if (CtrlrLog::ctrlrLog != nullptr) CtrlrLog::ctrlrLog->logMessage(message, CtrlrLog::LuaRuntimeError)
#define _TRANS(message)										if (CtrlrLog::ctrlrLog != nullptr) CtrlrLog::ctrlrLog->logMessage(message, CtrlrLog::Transaction)
#define _MIN(device, midiMessage)							if (CtrlrLog::ctrlrLog != nullptr) CtrlrLog::ctrlrLog->logMessage(device, midiMessage, CtrlrLog::MidiIn)
#define _MOUT(device, midiMessage)							if (CtrlrLog::ctrlrLog != nullptr) CtrlrLog::ctrlrLog->logMessage(device, midiMessage, CtrlrLog::MidiOut)
#define _MINSTR(message)									if (CtrlrLog::ctrlrLog != nullptr) CtrlrLog::ctrlrLog->logMessage(message, CtrlrLog::MidiIn)
#define _MOUTSTR(message)									if (CtrlrLog::ctrlrLog != nullptr) CtrlrLog::ctrlrLog->logMessage(message, CtrlrLog::MidiOut)

class CtrlrLog : public AsyncUpdater, public Logger
{
	public:
		enum LogLevel
		{
			Info,
			Warn,
			Error,
			Debug,
			Lua,
			MidiIn,
			MidiOut,
			LuaError,
			LuaRuntimeError,
			Transaction,
			kLogLevels
		};

		struct CtrlrLogMessage
		{
			String message;
			LogLevel level;
			Time time;
		};

		class Listener
		{
			public:
				virtual ~Listener(){}
				virtual void messageLogged (CtrlrLog::CtrlrLogMessage message)=0;
		};

		CtrlrLog(const bool _logToFile);
		~CtrlrLog();

		void addListener (Listener *l)													{ listeners.add(l); }
		void removeListener (Listener *l)												{ listeners.remove(l); }
		void handleAsyncUpdate();

		void logMessage (const String &message, const LogLevel level);
		void logMessage (const String &device, const MidiMessage &message, const LogLevel level);
		void logMessage (const String &device, const MidiBuffer &buffer, const LogLevel level);
		void logMessage (const String &message);
		void setLogToFile (const bool _logToFile);
		const bool getLogMidiInput ();
		const bool getLogMidiOutput ();
		const String formatMidiMessage (const MidiMessage &message);
		static const LogLevel stringToLevel (const String &level);
		static const String levelToString(const LogLevel &level);
		static const String timeToString(const Time &time);
		static const Colour getColourForMessage(const CtrlrLogMessage &message);
		static const Colour getColourForLevel(const CtrlrLog::LogLevel logLevel);
		static const String formatMessage(const CtrlrLogMessage &m, const bool includeLevel=true, const bool includeTimestamp=true);
		void setMidiLogOptions(const int logOptions) { midiLogOptions.set(logOptions); }
		static CtrlrLog *ctrlrLog;

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CtrlrLog);

	private:
		ReadWriteLock loggerLock;
		bool logToFile;
		FileLogger *fileLogger;
		Array <LogLevel> levels;
		ListenerList <Listener> listeners;
		Array <CtrlrLogMessage,CriticalSection> pendingQueue;
		MidiBuffer logBuffer;
		Atomic <int> midiLogOptions;
};

#endif
