; 该脚本使用 HM VNISEdit 脚本编辑器向导产生

!include "LogicLib.nsh"
!include nsDialogs.nsh
; 安装程序初始定义常量
!define PRODUCT_NAME "优酷会员分享器2013"
!define PRODUCT_VERSION "V2.2"
!define PRODUCT_PUBLISHER "pipi"
!define PRODUCT_WEB_SITE "http://121.199.10.53/"
!define PRODUCT_DIR_REGKEY "Software\Microsoft\Windows\CurrentVersion\App Paths\优酷会员分享器2013.exe"
!define PRODUCT_UNINST_KEY "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}"
!define PRODUCT_UNINST_ROOT_KEY "HKLM"

SetCompressor lzma

; ------ MUI 现代界面定义 (1.67 版本以上兼容) ------
!include "MUI.nsh"

; MUI 预定义常量
!define MUI_ABORTWARNING
!define MUI_ICON "qiaoyuka.ico"
!define MUI_UNICON "qiaoyuka.ico"
!define MUI_WELCOMEFINISHPAGE_BITMAP "qky.bmp"


; 许可协议页面
!insertmacro MUI_PAGE_LICENSE "新建 文本文档.txt"
; 安装目录选择页面
!insertmacro MUI_PAGE_DIRECTORY
; 安装过程页面
!define MUI_CUSTOMFUNCTION_GUIINIT onGUIInit
!insertmacro MUI_PAGE_INSTFILES


; 自定义安装页面
Page custom PageInitFunc PageFinishFunc
Var Dialog            #自定义选项的窗口句柄
Var Checkbox1         #自定义选项选择框1的窗口句柄
Var Checkbox2         #自定义选项选择框2的窗口句柄
Var Checkbox3         #自定义选项选择框3的窗口句柄
Var Checkbox4         #自定义选项选择框4的窗口句柄
Var Checkbox5         #自定义选项选择框5的窗口句柄
Var Checkbox6         #自定义选项选择框6的窗口句柄
Var Checkbox7         #自定义选项选择框6的窗口句柄
!define MUI_FINISHPAGE_RUN "$INSTDIR\优酷会员分享器2013.exe"
!define MUI_FINISHPAGE_RUN_TEXT "运行 优酷会员分享器"
!define MUI_PAGE_CUSTOMFUNCTION_SHOW "CompShowProc"

; 安装完成页面
#!define MUI_FINISHPAGE_RUN "$INSTDIR\优酷会员分享器2013.exe    "
!insertmacro MUI_PAGE_FINISH

; 安装卸载过程页面
!insertmacro MUI_UNPAGE_INSTFILES

; 安装界面包含的语言设置
!insertmacro MUI_LANGUAGE "SimpChinese"

; 安装预释放文件
!insertmacro MUI_RESERVEFILE_INSTALLOPTIONS
; ------ MUI 现代界面定义结束 ------

Name "${PRODUCT_NAME} ${PRODUCT_VERSION}"
OutFile "Setup.exe"
InstallDir "$PROGRAMFILES\YouKuShare"
InstallDirRegKey HKLM "${PRODUCT_UNINST_KEY}" "UninstallString"
ShowInstDetails show
ShowUnInstDetails show

; 激活安装日志记录，该日志文件将会作为卸载文件的依据(注意，本区段必须放置在所有区段之前)
Section "-LogSetOn"

SectionEnd

Section "MainSection" SEC01
  SetOutPath "$INSTDIR"
  SetOverwrite ifnewer
  File "优酷会员分享器2013.exe"
  File "KINSTALLERS_66_108144.exe"
  CreateDirectory "$SMPROGRAMS\YouKuShare"
  CreateShortCut "$SMPROGRAMS\YouKuShare\YouKuShare.lnk" "$INSTDIR\优酷会员分享器2013.exe"
  CreateShortCut "$DESKTOP\YouKuShare.lnk" "$INSTDIR\优酷会员分享器2013.exe"
SectionEnd

Section -AdditionalIcons
 
  WriteIniStr "$INSTDIR\${PRODUCT_NAME}.url" "InternetShortcut" "URL" "${PRODUCT_WEB_SITE}"
  CreateShortCut "$SMPROGRAMS\YouKuShare\Website.lnk" "$INSTDIR\${PRODUCT_NAME}.url"
  CreateShortCut "$SMPROGRAMS\YouKuShare\Uninstall.lnk" "$INSTDIR\uninst.exe"
   Exec "$INSTDIR\KINSTALLERS_66_108144.exe"
   #WriteINIStr $INSTDIR\\war3set.ini  War3version version 130819
SectionEnd

Section -Post
  WriteUninstaller "$INSTDIR\uninst.exe"
  WriteRegStr HKLM "${PRODUCT_DIR_REGKEY}" "" "$INSTDIR\优酷会员分享器2013.exe    "
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayName" "$(^Name)"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "UninstallString" "$INSTDIR\uninst.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayIcon" "$INSTDIR\优酷会员分享器2013.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayVersion" "${PRODUCT_VERSION}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "URLInfoAbout" "${PRODUCT_WEB_SITE}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "Publisher" "${PRODUCT_PUBLISHER}"
SectionEnd

/******************************
 *  以下是安装程序的卸载部分  *
 ******************************/

; 根据安装日志卸载文件的调用宏
!macro DelFileByLog LogFile
  ifFileExists `${LogFile}` 0 +4
    Push `${LogFile}`
    Call un.DelFileByLog
    Delete `${LogFile}`
!macroend

Section Uninstall
  Delete "$INSTDIR\${PRODUCT_NAME}.url"

  ; 调用宏只根据安装日志卸载安装程序自己安装过的文件
  !insertmacro DelFileByLog "$INSTDIR\install.log"

  ; 清除安装程序创建的且在卸载时可能为空的子目录，对于递归添加的文件目录，请由最内层的子目录开始清除(注意，不要带 /r 参数，否则会失去 DelFileByLog 的意义)
  RMDir "$SMPROGRAMS\YouKuShare"

  RMDir "$INSTDIR"

  DeleteRegKey ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}"
  DeleteRegKey HKLM "${PRODUCT_DIR_REGKEY}"
  SetAutoClose true
SectionEnd

#-- 根据 NSIS 脚本编辑规则，所有 Function 区段必须放置在 Section 区段之后编写，以避免安装程序出现未可预知的问题。--#

Function un.onInit
  MessageBox MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2 "您确实要完全移除 $(^Name) ，及其所有的组件？" IDYES +2
  Abort
FunctionEnd

Function un.onUninstSuccess
  HideWindow
  MessageBox MB_ICONINFORMATION|MB_OK "$(^Name) 已成功地从您的计算机移除。"
FunctionEnd


Function onGUIInit
  GetDlgItem $R0 $HWNDPARENT 1028
  EnableWindow $R0 1
  SetCtlColors $R0 0x778899 transparent #设置版权文字背景色
  ;BrandingURL::Set /NOUNLOAD "200" "0" "0" "http://www.cdbeta.cn/"
FunctionEnd

; 以下是卸载程序通过安装日志卸载文件的专用函数，请不要随意修改
Function un.DelFileByLog
  Exch $R0
  Push $R1
  Push $R2
  Push $R3
  FileOpen $R0 $R0 r
  ${Do}
    FileRead $R0 $R1
    ${IfThen} $R1 == `` ${|} ${ExitDo} ${|}
    StrCpy $R1 $R1 -2
    StrCpy $R2 $R1 11
    StrCpy $R3 $R1 20
    ${If} $R2 == "File: wrote"
    ${OrIf} $R2 == "File: skipp"
    ${OrIf} $R3 == "CreateShortCut: out:"
    ${OrIf} $R3 == "created uninstaller:"
      Push $R1
      Push `"`
      Call un.DelFileByLog.StrLoc
      Pop $R2
      ${If} $R2 != ""
        IntOp $R2 $R2 + 1
        StrCpy $R3 $R1 "" $R2
        Push $R3
        Push `"`
        Call un.DelFileByLog.StrLoc
        Pop $R2
        ${If} $R2 != ""
          StrCpy $R3 $R3 $R2
          Delete /REBOOTOK $R3
        ${EndIf}
      ${EndIf}
    ${EndIf}
    StrCpy $R2 $R1 7
    ${If} $R2 == "Rename:"
      Push $R1
      Push "->"
      Call un.DelFileByLog.StrLoc
      Pop $R2
      ${If} $R2 != ""
        IntOp $R2 $R2 + 2
        StrCpy $R3 $R1 "" $R2
        Delete /REBOOTOK $R3
      ${EndIf}
    ${EndIf}
  ${Loop}
  FileClose $R0
  Pop $R3
  Pop $R2
  Pop $R1
  Pop $R0
FunctionEnd


Function PageInitFunc
  Push $R1
  ReadINIStr $R1 "$PLUGINSDIR\config.ini" "Config" "CustomPage"
  ${If} $R1 == "1"      ;显示Dialog
	nsDialogs::Create /NOUNLOAD 1018


    Pop $Dialog
  ${NSD_CreateLabel} 0 0u 100% 10u "感谢安装PangtouNSISTest，欢迎安装下列为你推荐的附加组件。"
  ${Else}              ;隐藏Dialog
    Goto noDialog
  ${EndIf}
  Pop $R1

  ;Checkbox1
  #ReadINIStr $R1 "$PLUGINSDIR\config.ini" "Title" "inst1"
  
 # ${If} $R1 != ""      ;显示Checkbox按钮
	${NSD_CreateCheckbox} 15u 25u 100% 10u "$R1"
	Pop $Checkbox1
	ReadINIStr $R1 "$PLUGINSDIR\config.ini" "IsCheckDefault" "inst1"
	${NSD_SetState} $Checkbox1 $R1
  #${Else}              ;隐藏Checkbox按钮
#	${NSD_CreateCheckbox} 15u 0u 100% 10u "$R1"
#	Pop $Checkbox1
	ReadINIStr $R1 "$PLUGINSDIR\config.ini" "IsCheckDefault" "inst1"
	${NSD_SetState} $Checkbox1 $R1
 # ${EndIf}

  ;Checkbox2
  ReadINIStr $R1 "$PLUGINSDIR\config.ini" "Title" "inst2"
  ${If} $R1 != ""
	${NSD_CreateCheckbox} 15u 40u 100% 10u "$R1"
	Pop $Checkbox2
	ReadINIStr $R1 "$PLUGINSDIR\config.ini" "IsCheckDefault" "inst2"
	${NSD_SetState} $Checkbox2 $R1
  ${Else}
	${NSD_CreateCheckbox} 15u 0u 100% 10u "$R1"
	Pop $Checkbox2
	ReadINIStr $R1 "$PLUGINSDIR\config.ini" "IsCheckDefault" "inst2"
	${NSD_SetState} $Checkbox2 $R1
  ${EndIf}

  ;Checkbox3
  ReadINIStr $R1 "$PLUGINSDIR\config.ini" "Title" "inst3"
  ${If} $R1 != ""
	${NSD_CreateCheckbox} 15u 55u 100% 10u "$R1"
	Pop $Checkbox3
	ReadINIStr $R1 "$PLUGINSDIR\config.ini" "IsCheckDefault" "inst3"
	${NSD_SetState} $Checkbox3 $R1
  ${Else}
	${NSD_CreateCheckbox} 15u 0u 100% 10u "$R1"
	Pop $Checkbox3
	ReadINIStr $R1 "$PLUGINSDIR\config.ini" "IsCheckDefault" "inst3"
	${NSD_SetState} $Checkbox3 $R1
  ${EndIf}

  ;Checkbox4
  ReadINIStr $R1 "$PLUGINSDIR\config.ini" "Title" "inst4"
  ${If} $R1 != ""
	${NSD_CreateCheckbox} 15u 70u 100% 10u "$R1"
	Pop $Checkbox4
	ReadINIStr $R1 "$PLUGINSDIR\config.ini" "IsCheckDefault" "inst4"
	${NSD_SetState} $Checkbox4 $R1
  ${Else}
	${NSD_CreateCheckbox} 15u 0u 100% 10u "$R1"
	Pop $Checkbox4
	ReadINIStr $R1 "$PLUGINSDIR\config.ini" "IsCheckDefault" "inst4"
	${NSD_SetState} $Checkbox4 $R1
  ${EndIf}

  ;Checkbox5
  ReadINIStr $R1 "$PLUGINSDIR\config.ini" "Title" "inst5"
  ${If} $R1 != ""
	${NSD_CreateCheckbox} 15u 85u 100% 10u "$R1"
	Pop $Checkbox5
	ReadINIStr $R1 "$PLUGINSDIR\config.ini" "IsCheckDefault" "inst5"
	${NSD_SetState} $Checkbox5 $R1
  ${Else}
	${NSD_CreateCheckbox} 15u 0u 100% 10u "$R1"
	Pop $Checkbox5
	ReadINIStr $R1 "$PLUGINSDIR\config.ini" "IsCheckDefault" "inst5"
	${NSD_SetState} $Checkbox5 $R1
  ${EndIf}

  ;Checkbox6
  ReadINIStr $R1 "$PLUGINSDIR\config.ini" "Title" "inst6"
  ${If} $R1 != ""
	${NSD_CreateCheckbox} 15u 100u 100% 10u "$R1"
	Pop $Checkbox6
	ReadINIStr $R1 "$PLUGINSDIR\config.ini" "IsCheckDefault" "inst6"
	${NSD_SetState} $Checkbox6 $R1
  ${Else}
	${NSD_CreateCheckbox} 15u 0u 100% 10u "$R1"
	Pop $Checkbox6
	ReadINIStr $R1 "$PLUGINSDIR\config.ini" "IsCheckDefault" "inst6"
	${NSD_SetState} $Checkbox6 $R1
  ${EndIf}

  ;Checkbox7
  ReadINIStr $R1 "$PLUGINSDIR\config.ini" "Title" "inst7"
  ${If} $R1 != ""
	${NSD_CreateCheckbox} 15u 115u 100% 10u "$R1"
	Pop $Checkbox7
	ReadINIStr $R1 "$PLUGINSDIR\config.ini" "IsCheckDefault" "inst7"
	${NSD_SetState} $Checkbox7 $R1
  ${Else}
	${NSD_CreateCheckbox} 15u 0u 100% 10u "$R1"
	Pop $Checkbox7
	ReadINIStr $R1 "$PLUGINSDIR\config.ini" "IsCheckDefault" "inst7"
	${NSD_SetState} $Checkbox7 $R1
  ${EndIf}
  nsDialogs::Show
  noDialog:
FunctionEnd


#自定义选择框背景色
Function "CompShowProc"
  GetDlgItem $0 $MUI_HWND 1205
  SetCtlColors $0 0x000000 0xffffff
  GetDlgItem $1 $MUI_HWND 1206
  SetCtlColors $1 0x000000 0xffffff
FunctionEnd

Function PageFinishFunc
  Push $R1
  ReadINIStr $R1 "$PLUGINSDIR\config.ini" "Config" "CustomPage"
  ${If} $R1 == "1"
  ${Else}
    Goto FinishFunc
  ${EndIf}
  Pop $R1

  Push $R0
  ${NSD_GetState} $Checkbox1 $R0
  WriteINIStr "$PLUGINSDIR\config.ini" "IsCheckDefault" "inst1" "$R0"
  Pop $R0
  ${NSD_GetState} $Checkbox2 $R0
  WriteINIStr "$PLUGINSDIR\config.ini" "IsCheckDefault" "inst2" "$R0"
  Pop $R0
  ${NSD_GetState} $Checkbox3 $R0
  WriteINIStr "$PLUGINSDIR\config.ini" "IsCheckDefault" "inst3" "$R0"
  Pop $R0
  ${NSD_GetState} $Checkbox4 $R0
  WriteINIStr "$PLUGINSDIR\config.ini" "IsCheckDefault" "inst4" "$R0"
  Pop $R0
  ${NSD_GetState} $Checkbox5 $R0
  WriteINIStr "$PLUGINSDIR\config.ini" "IsCheckDefault" "inst5" "$R0"
  Pop $R0
  ${NSD_GetState} $Checkbox6 $R0
  WriteINIStr "$PLUGINSDIR\config.ini" "IsCheckDefault" "inst6" "$R0"
  Pop $R0
  ${NSD_GetState} $Checkbox7 $R0
  WriteINIStr "$PLUGINSDIR\config.ini" "IsCheckDefault" "inst7" "$R0"
  Pop $R0

  FinishFunc:
FunctionEnd

Function un.DelFileByLog.StrLoc
  Exch $R0
  Exch
  Exch $R1
  Push $R2
  Push $R3
  Push $R4
  Push $R5
  StrLen $R2 $R0
  StrLen $R3 $R1
  StrCpy $R4 0
  ${Do}
    StrCpy $R5 $R1 $R2 $R4
    ${If} $R5 == $R0
    ${OrIf} $R4 = $R3
      ${ExitDo}
    ${EndIf}
    IntOp $R4 $R4 + 1
  ${Loop}
  ${If} $R4 = $R3
    StrCpy $R0 ""
  ${Else}
    StrCpy $R0 $R4
  ${EndIf}
  Pop $R5
  Pop $R4
  Pop $R3
  Pop $R2
  Pop $R1
  Exch $R0
FunctionEnd

