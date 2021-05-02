#ifndef __CTRLR_LOG__
#define __CTRLR_LOG__

#include "JuceHeader.h"

#ifdef JUCE_DEBUG
#define _DBG(message)										if (CtrlrLog::ctrlrLog != nullptr) CtrlrLog::ctrlrLog->logMessage(message, CtrlrLog::Debug)
#else
#define _DBG(message)										do {} while (0)
#endif

#define _TXT(...)                                           if (CtrlrLog::ctrlrLog != nullptr) CtrlrLog::ctrlrLog->logMessage(CtrlrLog::Info, __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)
#define _WRN(message)										if (CtrlrLog::ctrlrLog != nullptr) CtrlrLog::ctrlrLog->logMessage(message, CtrlrLog::Warn)
#define _ERR(message)										if (CtrlrLog::ctrlrLog != nullptr) CtrlrLog::ctrlrLog->logMessage(message, CtrlrLog::Error)
#define _INF(message)										if (CtrlrLog::ctrlrLog != nullptr) CtrlrLog::ctrlrLog->logMessage(message, CtrlrLog::Info)
#define _LUA(message)										if (CtrlrLog::ctrlrLog != nullptr) CtrlrLog::ctrlrLog->logMessage(message, CtrlrLog::Lua)
#define _LERR(message)										if (CtrlrLog::ctrlrLog != nullptr) CtrlrLog::ctrlrLog->logMessage(message, CtrlrLog::LuaError)
#define _LRUNERR(message)									if (CtrlrLog::ctrlrLog != nullptr) CtrlrLog::ctrlrLog->logMessage(message, CtrlrLog::LuaRuntimeError)
#define _TRANS(message)										if (CtrlrLog::ctrlrLog != nullptr) CtrlrLog::ctrlrLog->logMessage(message, CtrlrLog::Transaction)
#define _MIN(device, midiMessage, time)						if (CtrlrLog::ctrlrLog != nullptr) CtrlrLog::ctrlrLog->logMessage(device, midiMessage, time, CtrlrLog::MidiIn)
#define _MOUT(device, midiMessage, time)					if (CtrlrLog::ctrlrLog != nullptr) CtrlrLog::ctrlrLog->logMessage(device, midiMessage, time, CtrlrLog::MidiOut)
#define _MINSTR(message)									if (CtrlrLog::ctrlrLog != nullptr) CtrlrLog::ctrlrLog->logMessage(message, CtrlrLog::MidiIn)
#define _MOUTSTR(message)									if (CtrlrLog::ctrlrLog != nullptr) CtrlrLog::ctrlrLog->logMessage(message, CtrlrLog::MidiOut)


class CtrlrLog : public AsyncUpdater, public Logger, public DeletedAtShutdown
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
			juce::Time time;
		};

		class Listener
		{
			public:
				virtual ~Listener(){}
				virtual void messageLogged (CtrlrLog::CtrlrLogMessage message)=0;
		};

		CtrlrLog(const bool _logToFile);
		~CtrlrLog();

		void addListener (Listener *l);
		void removeListener (Listener *l);
		void handleAsyncUpdate();

		void logMessage (const String &message, const LogLevel level);
		void logMessage (const String &device, const MidiMessage &message, const LogLevel level);
		void logMessage (const String &device, const MidiMessage &message, const double time, const LogLevel level);
		void logMessage (const String &device, const MidiBuffer &buffer, const LogLevel level);
		void logMessage (const String &device, const MidiBuffer &buffer, const double time, const LogLevel level);
		void logMessage (const String &message);
        void logMessage(CtrlrLog::LogLevel, const String &file, const String &function, const int line, char *fmt, ...);

		void setLogToFile (const bool _logToFile);
		bool getLogMidiInput ();
		bool getLogMidiOutput ();
		const String formatMidiMessage (const MidiMessage &message, const double timestamp = -1);
		static LogLevel stringToLevel (const String &level);
		static String levelToString(const LogLevel &level);
		static String timeToString(const juce::Time &time);
		static Colour getColourForMessage(const CtrlrLogMessage &message);
		static Colour getColourForLevel(const CtrlrLog::LogLevel logLevel);
		static String formatMessage(const CtrlrLogMessage &m, const bool includeLevel=true, const bool includeTimestamp=true);
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
