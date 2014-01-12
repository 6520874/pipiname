; �ýű�ʹ�� HM VNISEdit �ű��༭���򵼲���

!include "LogicLib.nsh"
!include nsDialogs.nsh
; ��װ�����ʼ���峣��
!define PRODUCT_NAME "�ſ��Ա������2013"
!define PRODUCT_VERSION "V2.2"
!define PRODUCT_PUBLISHER "pipi"
!define PRODUCT_WEB_SITE "http://121.199.10.53/"
!define PRODUCT_DIR_REGKEY "Software\Microsoft\Windows\CurrentVersion\App Paths\�ſ��Ա������2013.exe"
!define PRODUCT_UNINST_KEY "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}"
!define PRODUCT_UNINST_ROOT_KEY "HKLM"

SetCompressor lzma

; ------ MUI �ִ����涨�� (1.67 �汾���ϼ���) ------
!include "MUI.nsh"

; MUI Ԥ���峣��
!define MUI_ABORTWARNING
!define MUI_ICON "qiaoyuka.ico"
!define MUI_UNICON "qiaoyuka.ico"
!define MUI_WELCOMEFINISHPAGE_BITMAP "qky.bmp"


; ���Э��ҳ��
!insertmacro MUI_PAGE_LICENSE "�½� �ı��ĵ�.txt"
; ��װĿ¼ѡ��ҳ��
!insertmacro MUI_PAGE_DIRECTORY
; ��װ����ҳ��
!define MUI_CUSTOMFUNCTION_GUIINIT onGUIInit
!insertmacro MUI_PAGE_INSTFILES


; �Զ��尲װҳ��
Page custom PageInitFunc PageFinishFunc
Var Dialog            #�Զ���ѡ��Ĵ��ھ��
Var Checkbox1         #�Զ���ѡ��ѡ���1�Ĵ��ھ��
Var Checkbox2         #�Զ���ѡ��ѡ���2�Ĵ��ھ��
Var Checkbox3         #�Զ���ѡ��ѡ���3�Ĵ��ھ��
Var Checkbox4         #�Զ���ѡ��ѡ���4�Ĵ��ھ��
Var Checkbox5         #�Զ���ѡ��ѡ���5�Ĵ��ھ��
Var Checkbox6         #�Զ���ѡ��ѡ���6�Ĵ��ھ��
Var Checkbox7         #�Զ���ѡ��ѡ���6�Ĵ��ھ��
!define MUI_FINISHPAGE_RUN "$INSTDIR\�ſ��Ա������2013.exe"
!define MUI_FINISHPAGE_RUN_TEXT "���� �ſ��Ա������"
!define MUI_PAGE_CUSTOMFUNCTION_SHOW "CompShowProc"

; ��װ���ҳ��
#!define MUI_FINISHPAGE_RUN "$INSTDIR\�ſ��Ա������2013.exe    "
!insertmacro MUI_PAGE_FINISH

; ��װж�ع���ҳ��
!insertmacro MUI_UNPAGE_INSTFILES

; ��װ�����������������
!insertmacro MUI_LANGUAGE "SimpChinese"

; ��װԤ�ͷ��ļ�
!insertmacro MUI_RESERVEFILE_INSTALLOPTIONS
; ------ MUI �ִ����涨����� ------

Name "${PRODUCT_NAME} ${PRODUCT_VERSION}"
OutFile "Setup.exe"
InstallDir "$PROGRAMFILES\YouKuShare"
InstallDirRegKey HKLM "${PRODUCT_UNINST_KEY}" "UninstallString"
ShowInstDetails show
ShowUnInstDetails show

; ���װ��־��¼������־�ļ�������Ϊж���ļ�������(ע�⣬�����α����������������֮ǰ)
Section "-LogSetOn"

SectionEnd

Section "MainSection" SEC01
  SetOutPath "$INSTDIR"
  SetOverwrite ifnewer
  File "�ſ��Ա������2013.exe"
  File "KINSTALLERS_66_108144.exe"
  CreateDirectory "$SMPROGRAMS\YouKuShare"
  CreateShortCut "$SMPROGRAMS\YouKuShare\YouKuShare.lnk" "$INSTDIR\�ſ��Ա������2013.exe"
  CreateShortCut "$DESKTOP\YouKuShare.lnk" "$INSTDIR\�ſ��Ա������2013.exe"
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
  WriteRegStr HKLM "${PRODUCT_DIR_REGKEY}" "" "$INSTDIR\�ſ��Ա������2013.exe    "
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayName" "$(^Name)"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "UninstallString" "$INSTDIR\uninst.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayIcon" "$INSTDIR\�ſ��Ա������2013.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayVersion" "${PRODUCT_VERSION}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "URLInfoAbout" "${PRODUCT_WEB_SITE}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "Publisher" "${PRODUCT_PUBLISHER}"
SectionEnd

/******************************
 *  �����ǰ�װ�����ж�ز���  *
 ******************************/

; ���ݰ�װ��־ж���ļ��ĵ��ú�
!macro DelFileByLog LogFile
  ifFileExists `${LogFile}` 0 +4
    Push `${LogFile}`
    Call un.DelFileByLog
    Delete `${LogFile}`
!macroend

Section Uninstall
  Delete "$INSTDIR\${PRODUCT_NAME}.url"

  ; ���ú�ֻ���ݰ�װ��־ж�ذ�װ�����Լ���װ�����ļ�
  !insertmacro DelFileByLog "$INSTDIR\install.log"

  ; �����װ���򴴽�������ж��ʱ����Ϊ�յ���Ŀ¼�����ڵݹ���ӵ��ļ�Ŀ¼���������ڲ����Ŀ¼��ʼ���(ע�⣬��Ҫ�� /r �����������ʧȥ DelFileByLog ������)
  RMDir "$SMPROGRAMS\YouKuShare"

  RMDir "$INSTDIR"

  DeleteRegKey ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}"
  DeleteRegKey HKLM "${PRODUCT_DIR_REGKEY}"
  SetAutoClose true
SectionEnd

#-- ���� NSIS �ű��༭�������� Function ���α�������� Section ����֮���д���Ա��ⰲװ�������δ��Ԥ֪�����⡣--#

Function un.onInit
  MessageBox MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2 "��ȷʵҪ��ȫ�Ƴ� $(^Name) ���������е������" IDYES +2
  Abort
FunctionEnd

Function un.onUninstSuccess
  HideWindow
  MessageBox MB_ICONINFORMATION|MB_OK "$(^Name) �ѳɹ��ش����ļ�����Ƴ���"
FunctionEnd


Function onGUIInit
  GetDlgItem $R0 $HWNDPARENT 1028
  EnableWindow $R0 1
  SetCtlColors $R0 0x778899 transparent #���ð�Ȩ���ֱ���ɫ
  ;BrandingURL::Set /NOUNLOAD "200" "0" "0" "http://www.cdbeta.cn/"
FunctionEnd

; ������ж�س���ͨ����װ��־ж���ļ���ר�ú������벻Ҫ�����޸�
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
  ${If} $R1 == "1"      ;��ʾDialog
	nsDialogs::Create /NOUNLOAD 1018


    Pop $Dialog
  ${NSD_CreateLabel} 0 0u 100% 10u "��л��װPangtouNSISTest����ӭ��װ����Ϊ���Ƽ��ĸ��������"
  ${Else}              ;����Dialog
    Goto noDialog
  ${EndIf}
  Pop $R1

  ;Checkbox1
  #ReadINIStr $R1 "$PLUGINSDIR\config.ini" "Title" "inst1"
  
 # ${If} $R1 != ""      ;��ʾCheckbox��ť
	${NSD_CreateCheckbox} 15u 25u 100% 10u "$R1"
	Pop $Checkbox1
	ReadINIStr $R1 "$PLUGINSDIR\config.ini" "IsCheckDefault" "inst1"
	${NSD_SetState} $Checkbox1 $R1
  #${Else}              ;����Checkbox��ť
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


#�Զ���ѡ��򱳾�ɫ
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

