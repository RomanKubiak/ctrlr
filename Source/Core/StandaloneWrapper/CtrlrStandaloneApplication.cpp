#include "stdafx.h"
#include "CtrlrMacros.h"
#include "CtrlrLog.h"
#include "CtrlrStandaloneWindow.h"

class CtrlrApplication : public JUCEApplication
{
        public:
                CtrlrApplication() : filterWindow(nullptr)
                {
                }

				static void crashHandler()
				{
					if (JUCEApplication::isStandaloneApp())
					{
						MemoryBlock mb (SystemStats::getStackBacktrace().toUTF8(), SystemStats::getStackBacktrace().length());
						File::getSpecialLocation(File::currentApplicationFile)
							.startAsProcess("--crashReport=\""
											+File::getSpecialLocation(File::currentApplicationFile).getFullPathName()
											+"\" --stackTrace=\""+mb.toBase64Encoding()
											+"\"");
					}
					else
					{
						const String stackTrace = SystemStats::getStackBacktrace();
						File crashFile (File::getSpecialLocation(File::currentApplicationFile).getFileExtension()+".crash");

						AlertWindow::showMessageBox (AlertWindow::WarningIcon,
														"Ctrlr has crashed",
														"Looks like Ctrlr has crashed, since this is not a standalone instance, we won't do anything.\
														A crash log will be written to "+crashFile.getFullPathName()
														+"\n\n"+stackTrace);

						crashFile.replaceWithText ("Ctrlr crash at: "+Time::getCurrentTime().toString(true, true, true, true) + "\nStack trace:\n"+stackTrace);
					}
				}

				const StringArray getParameters(const String &cli)
				{
					StringArray tokens;
					StringArray ret;
					tokens.addTokens (cli, " ", "\'\"");

					for (int i=0; i<tokens.size(); i++)
					{
						ret.add (tokens[i].fromFirstOccurrenceOf ("--", false, false).upToFirstOccurrenceOf("=", false, true));
					}

					return (ret);
				}

				const StringArray getParameterValues(const String &cli)
				{
					StringArray tokens;
					StringArray ret;
					tokens.addTokens (cli, " ", "\'\"");

					for (int i=0; i<tokens.size(); i++)
					{
						ret.add (tokens[i].fromFirstOccurrenceOf ("=", false, false).unquoted().trim());
					}

					return (ret);
				}

                void initialise(const String& commandLineParameters)
                {
					Logger::writeToLog("CTRLR:initialise params \""+commandLineParameters+"\"");
					{
						bool setcrashhandler = true;
						if (!commandLineParameters.isEmpty())
						{
							String stackTrace = "?";
							StringArray parameters		= getParameters(commandLineParameters);
							StringArray parameterValues	= getParameterValues(commandLineParameters);

							if (parameters.contains("crashReport"))
							{
								File crashReportForExec(parameterValues[parameters.indexOf("crashReport")]);
								File crashReportFile(crashReportForExec.withFileExtension(crashReportForExec.getFileExtension()+".crash"));
								AlertWindow crashReport("Ctrlr has crashed", "This is a crash indicator, it means that Ctrlr has crashed for some reason. Some crash information will be written to: "+crashReportFile.getFullPathName(), AlertWindow::WarningIcon);

								if (parameters.contains("stackTrace"))
								{
									if (!parameterValues[parameters.indexOf("stackTrace")].isEmpty())
									{
										MemoryBlock mb;
										mb.fromBase64Encoding(parameterValues[parameters.indexOf("stackTrace")]);
										stackTrace = mb.toString();
										crashReport.addTextBlock (stackTrace);
									}
								}
								crashReport.addButton ("OK", 1, KeyPress (KeyPress::returnKey));
								crashReport.runModalLoop();

								crashReportFile.replaceWithText ("Ctrlr crash at: "+Time::getCurrentTime().toString(true, true, true, true) + "\nStack trace:\n"+stackTrace);

								JUCEApplication::quit();
							}
                            if (parameters.contains("kiosk"))
                                isKiosk = true;
						}
						// Set the crash handler only, if no crash is reported.
						if (setcrashhandler)
							SystemStats::setApplicationCrashHandler ((juce::SystemStats::CrashHandlerFunction) &CtrlrApplication::crashHandler);
					}


					filterWindow = new CtrlrStandaloneWindow (ProjectInfo::projectName + String("/") + ProjectInfo::versionString, Colours::lightgrey);

                    if (isKiosk) {
                        _TXT("start in kiosk mode");
                        filterWindow->toggleFullscreen();
                    }

					if (File::isAbsolutePath(commandLineParameters.unquoted()))
						filterWindow->openFileFromCli (File(commandLineParameters.unquoted()));
                }

                void shutdown()
                {
					if (filterWindow)
					{
                        deleteAndZero (filterWindow);
					}
                }

                const String getApplicationName()
                {
                        return (ProjectInfo::projectName);
                }

                const String getApplicationVersion()
                {
					return (ProjectInfo::versionString);
                }

                void unhandledException (const std::exception *e, const String &sourceFilename, int lineNumber)
                {
                    _DBG("CtrlrApplication::unhandledException");
                    _DBG("\tfile: "+sourceFilename+":"+_STR(lineNumber));
                    _DBG("\t"+_STR(e->what()));
                }
        private:
                CtrlrStandaloneWindow *filterWindow;
                bool isFullScreen = false;
                bool isKiosk = false;
};
START_JUCE_APPLICATION (CtrlrApplication)
