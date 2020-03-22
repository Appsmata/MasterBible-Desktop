; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

#define MyAppName "mBible"
#define MyAppVersion "0.0.6.3"
#define MyAppPublisher "Appsmata Solutions"
#define MyAppURL "https://www.appsmata.com"
#define MyAppExeName "mBible.exe"

[Setup]
; NOTE: The value of AppId uniquely identifies this application. Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{0F3B4E69-99CB-4236-84DB-F1FEDAE81D51}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
VersionInfoVersion={#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName={autopf}\{#MyAppName}
DisableDirPage=yes
DisableProgramGroupPage=yes
; The [Icons] "quicklaunchicon" entry uses {userappdata} but its [Tasks] entry has a proper IsAdminInstallMode Check.
UsedUserAreasWarning=no
; Remove the following line to run in administrative install mode (install for all users.)
PrivilegesRequired=lowest
OutputDir=D:\Cpp\mbible4pc\publish
OutputBaseFilename=mBible_{#MyAppVersion}_x64
SetupIconFile=D:\Cpp\mbible4pc\publish\mbible.ico
Compression=lzma
SolidCompression=yes
WizardStyle=modern

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}";
Name: "quicklaunchicon"; Description: "{cm:CreateQuickLaunchIcon}"; GroupDescription: "{cm:AdditionalIcons}"; OnlyBelowVersion: 6.1; Check: not IsAdminInstallMode

[Files]
Source: "D:\Cpp\mbible4pc\Release\mBible.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\Cpp\mbible4pc\Release\Qt5Concurrent.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\Cpp\mbible4pc\Release\Qt5Core.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\Cpp\mbible4pc\Release\Qt5Gui.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\Cpp\mbible4pc\Release\Qt5Network.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\Cpp\mbible4pc\Release\Qt5PrintSupport.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\Cpp\mbible4pc\Release\Qt5Widgets.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\Cpp\mbible4pc\Release\Qt5Xml.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\Cpp\mbible4pc\Release\sqlite3.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\Cpp\mbible4pc\Release\Data\*"; DestDir: "{app}\Data"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "D:\Cpp\mbible4pc\Release\res\*"; DestDir: "{app}\res"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "D:\Cpp\dependencies\licenses\*"; DestDir: "{app}\licenses"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "D:\Cpp\dependencies\platforms\*"; DestDir: "{app}\platforms"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "D:\Cpp\dependencies\printsupport\*"; DestDir: "{app}\printsupport"; Flags: ignoreversion recursesubdirs createallsubdirs 
Source: "D:\Cpp\dependencies\vc_redist.x64.exe"; DestDir: "{app}"; Flags: ignoreversion
; NOTE: Don't use "Flags: ignoreversion" on any shared system files

[Icons]
Name: "{autoprograms}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
Name: "{autodesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon
Name: "{userappdata}\Microsoft\Internet Explorer\Quick Launch\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: quicklaunchicon

[Run]
Filename: "{app}\vc_redist.x64.exe"; StatusMsg: "Installing Visual C++ 2015 Redistributable (x64)"; Check: IsWin64(); Flags: skipifsilent
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"; Flags: nowait postinstall skipifsilent
 
[Setup]
UninstallDisplayIcon={app}\{#MyAppExeName}
UninstallDisplayName={#MyAppName}
