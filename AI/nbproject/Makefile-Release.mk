#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/2105459482/CDatabase.o \
	${OBJECTDIR}/_ext/2105459482/CFunctions.o \
	${OBJECTDIR}/_ext/2105459482/CGlobals.o \
	${OBJECTDIR}/_ext/2105459482/CPlayerObjHandle.o \
	${OBJECTDIR}/_ext/1085242399/CEmitter.o \
	${OBJECTDIR}/_ext/1085242399/CPartical.o \
	${OBJECTDIR}/_ext/1085242399/Grafic.o \
	${OBJECTDIR}/_ext/101628821/CItemType.o \
	${OBJECTDIR}/_ext/1326849432/CUIBuildFrame.o \
	${OBJECTDIR}/_ext/513393915/CUIButtonBuild.o \
	${OBJECTDIR}/_ext/513393915/CUIButtonCancel.o \
	${OBJECTDIR}/_ext/513393915/CUIButtonChangeOrdre.o \
	${OBJECTDIR}/_ext/513393915/CUIButtonChangeTG.o \
	${OBJECTDIR}/_ext/513393915/CUIButtonChangeView.o \
	${OBJECTDIR}/_ext/513393915/CUIButtonCreateFit.o \
	${OBJECTDIR}/_ext/513393915/CUIButtonFitLoadout.o \
	${OBJECTDIR}/_ext/513393915/CUIButtonItem.o \
	${OBJECTDIR}/_ext/513393915/CUIButtonOK.o \
	${OBJECTDIR}/_ext/513393915/CUIButtonOpenCargo.o \
	${OBJECTDIR}/_ext/513393915/CUIButtonSetUnitPos.o \
	${OBJECTDIR}/_ext/41085353/CUIBaseFrame.o \
	${OBJECTDIR}/_ext/41085353/CUIButton.o \
	${OBJECTDIR}/_ext/41085353/CUIButtonFrame.o \
	${OBJECTDIR}/_ext/41085353/CUICargoViewer.o \
	${OBJECTDIR}/_ext/41085353/CUIComboBox.o \
	${OBJECTDIR}/_ext/41085353/CUIDragDrop.o \
	${OBJECTDIR}/_ext/41085353/CUIFrame.o \
	${OBJECTDIR}/_ext/41085353/CUIMainFrame.o \
	${OBJECTDIR}/_ext/41085353/CUIMoveCloseBar.o \
	${OBJECTDIR}/_ext/41085353/CUIRightClickMenu.o \
	${OBJECTDIR}/_ext/41085353/CUIShipDetailFrame.o \
	${OBJECTDIR}/_ext/41085353/CUISubSystem.o \
	${OBJECTDIR}/_ext/41085353/CUITextInputField.o \
	${OBJECTDIR}/_ext/768971997/CUIComboOrdreChange.o \
	${OBJECTDIR}/_ext/768971997/CUIComboTgChange.o \
	${OBJECTDIR}/_ext/1323325399/CUICreateFitForm.o \
	${OBJECTDIR}/_ext/453979591/CUIListBox.o \
	${OBJECTDIR}/_ext/1705946370/CUIRCMenuLoadout.o \
	${OBJECTDIR}/_ext/2096236352/CUIVScroll.o \
	${OBJECTDIR}/_ext/1568962013/CAstoroid.o \
	${OBJECTDIR}/_ext/1568962013/CAstoroidType.o \
	${OBJECTDIR}/_ext/1568962013/CMovable.o \
	${OBJECTDIR}/_ext/1568962013/CObj.o \
	${OBJECTDIR}/_ext/1568962013/COrdres.o \
	${OBJECTDIR}/_ext/1568962013/CPos.o \
	${OBJECTDIR}/_ext/1568962013/CShip.o \
	${OBJECTDIR}/_ext/1568962013/CShipType.o \
	${OBJECTDIR}/_ext/1568962013/CShot.o \
	${OBJECTDIR}/_ext/1568962013/CSubAble.o \
	${OBJECTDIR}/_ext/1568962013/CTargetable.o \
	${OBJECTDIR}/_ext/1199231184/CCargoBay.o \
	${OBJECTDIR}/_ext/1778765488/CLoadout.o \
	${OBJECTDIR}/_ext/1778765488/CShipTypeSlotData.o \
	${OBJECTDIR}/_ext/1778765488/CSingleFac.o \
	${OBJECTDIR}/_ext/1778765488/CSingleRef.o \
	${OBJECTDIR}/_ext/1778765488/CSingleWep.o \
	${OBJECTDIR}/_ext/1778765488/CSlotNode.o \
	${OBJECTDIR}/_ext/1778765488/CSubSystem.o \
	${OBJECTDIR}/_ext/1778765488/CSubSystemBonus.o \
	${OBJECTDIR}/_ext/1778765488/CSubSystemBoost.o \
	${OBJECTDIR}/_ext/1778765488/CSubSystemFac.o \
	${OBJECTDIR}/_ext/1778765488/CSubSystemRef.o \
	${OBJECTDIR}/_ext/1778765488/CSubSystemW.o \
	${OBJECTDIR}/_ext/1778765488/CSubType.o \
	${OBJECTDIR}/_ext/1778765488/CSubTypeBonus.o \
	${OBJECTDIR}/_ext/1778765488/CSubTypeBoost.o \
	${OBJECTDIR}/_ext/1778765488/CSubTypeFac.o \
	${OBJECTDIR}/_ext/1778765488/CSubTypeRef.o \
	${OBJECTDIR}/_ext/1778765488/CSubTypeWep.o \
	${OBJECTDIR}/_ext/59283363/CGrid.o \
	${OBJECTDIR}/_ext/59283363/CWorld.o \
	${OBJECTDIR}/_ext/2098112761/GCommands.o \
	${OBJECTDIR}/_ext/2098112761/GFunctions.o \
	${OBJECTDIR}/_ext/2098112761/GGlobals.o \
	${OBJECTDIR}/AFunctions.o \
	${OBJECTDIR}/AI/ABeacon.o \
	${OBJECTDIR}/AI/AChoice.o \
	${OBJECTDIR}/AI/AGlobals.o \
	${OBJECTDIR}/AI/AIMain.o \
	${OBJECTDIR}/AI/AObjGroup.o \
	${OBJECTDIR}/AI/Ordre/AOrdre.o \
	${OBJECTDIR}/AI/Ordre/AOrdreBuild.o \
	${OBJECTDIR}/AI/Ordre/AOrdreChangeOrdre.o \
	${OBJECTDIR}/AI/Ordre/AOrdreMine.o \
	${OBJECTDIR}/AI/Ordre/AOrdreMove.o \
	${OBJECTDIR}/AI/Ordre/AOrdreSet.o \
	${OBJECTDIR}/AI/UnitControle/AUnitControle.o \
	${OBJECTDIR}/mainAI.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/ai

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/ai: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/ai ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/2105459482/CDatabase.o: ../Client/CDatabase.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2105459482
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/2105459482/CDatabase.o ../Client/CDatabase.cpp

${OBJECTDIR}/_ext/2105459482/CFunctions.o: ../Client/CFunctions.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2105459482
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/2105459482/CFunctions.o ../Client/CFunctions.cpp

${OBJECTDIR}/_ext/2105459482/CGlobals.o: ../Client/CGlobals.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2105459482
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/2105459482/CGlobals.o ../Client/CGlobals.cpp

${OBJECTDIR}/_ext/2105459482/CPlayerObjHandle.o: ../Client/CPlayerObjHandle.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2105459482
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/2105459482/CPlayerObjHandle.o ../Client/CPlayerObjHandle.cpp

${OBJECTDIR}/_ext/1085242399/CEmitter.o: ../Client/Grafic/CEmitter.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1085242399
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1085242399/CEmitter.o ../Client/Grafic/CEmitter.cpp

${OBJECTDIR}/_ext/1085242399/CPartical.o: ../Client/Grafic/CPartical.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1085242399
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1085242399/CPartical.o ../Client/Grafic/CPartical.cpp

${OBJECTDIR}/_ext/1085242399/Grafic.o: ../Client/Grafic/Grafic.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1085242399
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1085242399/Grafic.o ../Client/Grafic/Grafic.cpp

${OBJECTDIR}/_ext/101628821/CItemType.o: ../Client/Items/CItemType.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/101628821
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/101628821/CItemType.o ../Client/Items/CItemType.cpp

${OBJECTDIR}/_ext/1326849432/CUIBuildFrame.o: ../Client/UI/Build/CUIBuildFrame.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1326849432
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1326849432/CUIBuildFrame.o ../Client/UI/Build/CUIBuildFrame.cpp

${OBJECTDIR}/_ext/513393915/CUIButtonBuild.o: ../Client/UI/Buttons/CUIButtonBuild.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/513393915
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/513393915/CUIButtonBuild.o ../Client/UI/Buttons/CUIButtonBuild.cpp

${OBJECTDIR}/_ext/513393915/CUIButtonCancel.o: ../Client/UI/Buttons/CUIButtonCancel.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/513393915
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/513393915/CUIButtonCancel.o ../Client/UI/Buttons/CUIButtonCancel.cpp

${OBJECTDIR}/_ext/513393915/CUIButtonChangeOrdre.o: ../Client/UI/Buttons/CUIButtonChangeOrdre.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/513393915
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/513393915/CUIButtonChangeOrdre.o ../Client/UI/Buttons/CUIButtonChangeOrdre.cpp

${OBJECTDIR}/_ext/513393915/CUIButtonChangeTG.o: ../Client/UI/Buttons/CUIButtonChangeTG.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/513393915
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/513393915/CUIButtonChangeTG.o ../Client/UI/Buttons/CUIButtonChangeTG.cpp

${OBJECTDIR}/_ext/513393915/CUIButtonChangeView.o: ../Client/UI/Buttons/CUIButtonChangeView.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/513393915
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/513393915/CUIButtonChangeView.o ../Client/UI/Buttons/CUIButtonChangeView.cpp

${OBJECTDIR}/_ext/513393915/CUIButtonCreateFit.o: ../Client/UI/Buttons/CUIButtonCreateFit.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/513393915
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/513393915/CUIButtonCreateFit.o ../Client/UI/Buttons/CUIButtonCreateFit.cpp

${OBJECTDIR}/_ext/513393915/CUIButtonFitLoadout.o: ../Client/UI/Buttons/CUIButtonFitLoadout.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/513393915
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/513393915/CUIButtonFitLoadout.o ../Client/UI/Buttons/CUIButtonFitLoadout.cpp

${OBJECTDIR}/_ext/513393915/CUIButtonItem.o: ../Client/UI/Buttons/CUIButtonItem.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/513393915
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/513393915/CUIButtonItem.o ../Client/UI/Buttons/CUIButtonItem.cpp

${OBJECTDIR}/_ext/513393915/CUIButtonOK.o: ../Client/UI/Buttons/CUIButtonOK.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/513393915
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/513393915/CUIButtonOK.o ../Client/UI/Buttons/CUIButtonOK.cpp

${OBJECTDIR}/_ext/513393915/CUIButtonOpenCargo.o: ../Client/UI/Buttons/CUIButtonOpenCargo.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/513393915
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/513393915/CUIButtonOpenCargo.o ../Client/UI/Buttons/CUIButtonOpenCargo.cpp

${OBJECTDIR}/_ext/513393915/CUIButtonSetUnitPos.o: ../Client/UI/Buttons/CUIButtonSetUnitPos.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/513393915
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/513393915/CUIButtonSetUnitPos.o ../Client/UI/Buttons/CUIButtonSetUnitPos.cpp

${OBJECTDIR}/_ext/41085353/CUIBaseFrame.o: ../Client/UI/CUIBaseFrame.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/41085353
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/41085353/CUIBaseFrame.o ../Client/UI/CUIBaseFrame.cpp

${OBJECTDIR}/_ext/41085353/CUIButton.o: ../Client/UI/CUIButton.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/41085353
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/41085353/CUIButton.o ../Client/UI/CUIButton.cpp

${OBJECTDIR}/_ext/41085353/CUIButtonFrame.o: ../Client/UI/CUIButtonFrame.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/41085353
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/41085353/CUIButtonFrame.o ../Client/UI/CUIButtonFrame.cpp

${OBJECTDIR}/_ext/41085353/CUICargoViewer.o: ../Client/UI/CUICargoViewer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/41085353
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/41085353/CUICargoViewer.o ../Client/UI/CUICargoViewer.cpp

${OBJECTDIR}/_ext/41085353/CUIComboBox.o: ../Client/UI/CUIComboBox.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/41085353
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/41085353/CUIComboBox.o ../Client/UI/CUIComboBox.cpp

${OBJECTDIR}/_ext/41085353/CUIDragDrop.o: ../Client/UI/CUIDragDrop.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/41085353
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/41085353/CUIDragDrop.o ../Client/UI/CUIDragDrop.cpp

${OBJECTDIR}/_ext/41085353/CUIFrame.o: ../Client/UI/CUIFrame.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/41085353
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/41085353/CUIFrame.o ../Client/UI/CUIFrame.cpp

${OBJECTDIR}/_ext/41085353/CUIMainFrame.o: ../Client/UI/CUIMainFrame.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/41085353
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/41085353/CUIMainFrame.o ../Client/UI/CUIMainFrame.cpp

${OBJECTDIR}/_ext/41085353/CUIMoveCloseBar.o: ../Client/UI/CUIMoveCloseBar.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/41085353
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/41085353/CUIMoveCloseBar.o ../Client/UI/CUIMoveCloseBar.cpp

${OBJECTDIR}/_ext/41085353/CUIRightClickMenu.o: ../Client/UI/CUIRightClickMenu.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/41085353
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/41085353/CUIRightClickMenu.o ../Client/UI/CUIRightClickMenu.cpp

${OBJECTDIR}/_ext/41085353/CUIShipDetailFrame.o: ../Client/UI/CUIShipDetailFrame.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/41085353
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/41085353/CUIShipDetailFrame.o ../Client/UI/CUIShipDetailFrame.cpp

${OBJECTDIR}/_ext/41085353/CUISubSystem.o: ../Client/UI/CUISubSystem.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/41085353
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/41085353/CUISubSystem.o ../Client/UI/CUISubSystem.cpp

${OBJECTDIR}/_ext/41085353/CUITextInputField.o: ../Client/UI/CUITextInputField.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/41085353
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/41085353/CUITextInputField.o ../Client/UI/CUITextInputField.cpp

${OBJECTDIR}/_ext/768971997/CUIComboOrdreChange.o: ../Client/UI/ComboBox/CUIComboOrdreChange.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/768971997
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/768971997/CUIComboOrdreChange.o ../Client/UI/ComboBox/CUIComboOrdreChange.cpp

${OBJECTDIR}/_ext/768971997/CUIComboTgChange.o: ../Client/UI/ComboBox/CUIComboTgChange.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/768971997
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/768971997/CUIComboTgChange.o ../Client/UI/ComboBox/CUIComboTgChange.cpp

${OBJECTDIR}/_ext/1323325399/CUICreateFitForm.o: ../Client/UI/Forms/CUICreateFitForm.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1323325399
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1323325399/CUICreateFitForm.o ../Client/UI/Forms/CUICreateFitForm.cpp

${OBJECTDIR}/_ext/453979591/CUIListBox.o: ../Client/UI/ListBox/CUIListBox.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/453979591
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/453979591/CUIListBox.o ../Client/UI/ListBox/CUIListBox.cpp

${OBJECTDIR}/_ext/1705946370/CUIRCMenuLoadout.o: ../Client/UI/RightClickMenus/CUIRCMenuLoadout.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1705946370
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1705946370/CUIRCMenuLoadout.o ../Client/UI/RightClickMenus/CUIRCMenuLoadout.cpp

${OBJECTDIR}/_ext/2096236352/CUIVScroll.o: ../Client/UI/Scrolls/CUIVScroll.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2096236352
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/2096236352/CUIVScroll.o ../Client/UI/Scrolls/CUIVScroll.cpp

${OBJECTDIR}/_ext/1568962013/CAstoroid.o: ../Client/spaceobjects/CAstoroid.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1568962013
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1568962013/CAstoroid.o ../Client/spaceobjects/CAstoroid.cpp

${OBJECTDIR}/_ext/1568962013/CAstoroidType.o: ../Client/spaceobjects/CAstoroidType.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1568962013
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1568962013/CAstoroidType.o ../Client/spaceobjects/CAstoroidType.cpp

${OBJECTDIR}/_ext/1568962013/CMovable.o: ../Client/spaceobjects/CMovable.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1568962013
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1568962013/CMovable.o ../Client/spaceobjects/CMovable.cpp

${OBJECTDIR}/_ext/1568962013/CObj.o: ../Client/spaceobjects/CObj.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1568962013
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1568962013/CObj.o ../Client/spaceobjects/CObj.cpp

${OBJECTDIR}/_ext/1568962013/COrdres.o: ../Client/spaceobjects/COrdres.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1568962013
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1568962013/COrdres.o ../Client/spaceobjects/COrdres.cpp

${OBJECTDIR}/_ext/1568962013/CPos.o: ../Client/spaceobjects/CPos.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1568962013
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1568962013/CPos.o ../Client/spaceobjects/CPos.cpp

${OBJECTDIR}/_ext/1568962013/CShip.o: ../Client/spaceobjects/CShip.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1568962013
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1568962013/CShip.o ../Client/spaceobjects/CShip.cpp

${OBJECTDIR}/_ext/1568962013/CShipType.o: ../Client/spaceobjects/CShipType.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1568962013
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1568962013/CShipType.o ../Client/spaceobjects/CShipType.cpp

${OBJECTDIR}/_ext/1568962013/CShot.o: ../Client/spaceobjects/CShot.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1568962013
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1568962013/CShot.o ../Client/spaceobjects/CShot.cpp

${OBJECTDIR}/_ext/1568962013/CSubAble.o: ../Client/spaceobjects/CSubAble.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1568962013
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1568962013/CSubAble.o ../Client/spaceobjects/CSubAble.cpp

${OBJECTDIR}/_ext/1568962013/CTargetable.o: ../Client/spaceobjects/CTargetable.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1568962013
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1568962013/CTargetable.o ../Client/spaceobjects/CTargetable.cpp

${OBJECTDIR}/_ext/1199231184/CCargoBay.o: ../Client/spaceobjects/cargo/CCargoBay.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1199231184
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1199231184/CCargoBay.o ../Client/spaceobjects/cargo/CCargoBay.cpp

${OBJECTDIR}/_ext/1778765488/CLoadout.o: ../Client/spaceobjects/subsystems/CLoadout.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1778765488
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1778765488/CLoadout.o ../Client/spaceobjects/subsystems/CLoadout.cpp

${OBJECTDIR}/_ext/1778765488/CShipTypeSlotData.o: ../Client/spaceobjects/subsystems/CShipTypeSlotData.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1778765488
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1778765488/CShipTypeSlotData.o ../Client/spaceobjects/subsystems/CShipTypeSlotData.cpp

${OBJECTDIR}/_ext/1778765488/CSingleFac.o: ../Client/spaceobjects/subsystems/CSingleFac.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1778765488
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1778765488/CSingleFac.o ../Client/spaceobjects/subsystems/CSingleFac.cpp

${OBJECTDIR}/_ext/1778765488/CSingleRef.o: ../Client/spaceobjects/subsystems/CSingleRef.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1778765488
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1778765488/CSingleRef.o ../Client/spaceobjects/subsystems/CSingleRef.cpp

${OBJECTDIR}/_ext/1778765488/CSingleWep.o: ../Client/spaceobjects/subsystems/CSingleWep.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1778765488
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1778765488/CSingleWep.o ../Client/spaceobjects/subsystems/CSingleWep.cpp

${OBJECTDIR}/_ext/1778765488/CSlotNode.o: ../Client/spaceobjects/subsystems/CSlotNode.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1778765488
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1778765488/CSlotNode.o ../Client/spaceobjects/subsystems/CSlotNode.cpp

${OBJECTDIR}/_ext/1778765488/CSubSystem.o: ../Client/spaceobjects/subsystems/CSubSystem.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1778765488
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1778765488/CSubSystem.o ../Client/spaceobjects/subsystems/CSubSystem.cpp

${OBJECTDIR}/_ext/1778765488/CSubSystemBonus.o: ../Client/spaceobjects/subsystems/CSubSystemBonus.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1778765488
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1778765488/CSubSystemBonus.o ../Client/spaceobjects/subsystems/CSubSystemBonus.cpp

${OBJECTDIR}/_ext/1778765488/CSubSystemBoost.o: ../Client/spaceobjects/subsystems/CSubSystemBoost.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1778765488
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1778765488/CSubSystemBoost.o ../Client/spaceobjects/subsystems/CSubSystemBoost.cpp

${OBJECTDIR}/_ext/1778765488/CSubSystemFac.o: ../Client/spaceobjects/subsystems/CSubSystemFac.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1778765488
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1778765488/CSubSystemFac.o ../Client/spaceobjects/subsystems/CSubSystemFac.cpp

${OBJECTDIR}/_ext/1778765488/CSubSystemRef.o: ../Client/spaceobjects/subsystems/CSubSystemRef.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1778765488
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1778765488/CSubSystemRef.o ../Client/spaceobjects/subsystems/CSubSystemRef.cpp

${OBJECTDIR}/_ext/1778765488/CSubSystemW.o: ../Client/spaceobjects/subsystems/CSubSystemW.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1778765488
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1778765488/CSubSystemW.o ../Client/spaceobjects/subsystems/CSubSystemW.cpp

${OBJECTDIR}/_ext/1778765488/CSubType.o: ../Client/spaceobjects/subsystems/CSubType.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1778765488
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1778765488/CSubType.o ../Client/spaceobjects/subsystems/CSubType.cpp

${OBJECTDIR}/_ext/1778765488/CSubTypeBonus.o: ../Client/spaceobjects/subsystems/CSubTypeBonus.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1778765488
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1778765488/CSubTypeBonus.o ../Client/spaceobjects/subsystems/CSubTypeBonus.cpp

${OBJECTDIR}/_ext/1778765488/CSubTypeBoost.o: ../Client/spaceobjects/subsystems/CSubTypeBoost.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1778765488
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1778765488/CSubTypeBoost.o ../Client/spaceobjects/subsystems/CSubTypeBoost.cpp

${OBJECTDIR}/_ext/1778765488/CSubTypeFac.o: ../Client/spaceobjects/subsystems/CSubTypeFac.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1778765488
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1778765488/CSubTypeFac.o ../Client/spaceobjects/subsystems/CSubTypeFac.cpp

${OBJECTDIR}/_ext/1778765488/CSubTypeRef.o: ../Client/spaceobjects/subsystems/CSubTypeRef.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1778765488
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1778765488/CSubTypeRef.o ../Client/spaceobjects/subsystems/CSubTypeRef.cpp

${OBJECTDIR}/_ext/1778765488/CSubTypeWep.o: ../Client/spaceobjects/subsystems/CSubTypeWep.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1778765488
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1778765488/CSubTypeWep.o ../Client/spaceobjects/subsystems/CSubTypeWep.cpp

${OBJECTDIR}/_ext/59283363/CGrid.o: ../Client/world/CGrid.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/59283363
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/59283363/CGrid.o ../Client/world/CGrid.cpp

${OBJECTDIR}/_ext/59283363/CWorld.o: ../Client/world/CWorld.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/59283363
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/59283363/CWorld.o ../Client/world/CWorld.cpp

${OBJECTDIR}/_ext/2098112761/GCommands.o: ../GShare/GCommands.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2098112761
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/2098112761/GCommands.o ../GShare/GCommands.cpp

${OBJECTDIR}/_ext/2098112761/GFunctions.o: ../GShare/GFunctions.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2098112761
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/2098112761/GFunctions.o ../GShare/GFunctions.cpp

${OBJECTDIR}/_ext/2098112761/GGlobals.o: ../GShare/GGlobals.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2098112761
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/2098112761/GGlobals.o ../GShare/GGlobals.cpp

${OBJECTDIR}/AFunctions.o: AFunctions.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/AFunctions.o AFunctions.cpp

${OBJECTDIR}/AI/ABeacon.o: AI/ABeacon.cpp 
	${MKDIR} -p ${OBJECTDIR}/AI
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/AI/ABeacon.o AI/ABeacon.cpp

${OBJECTDIR}/AI/AChoice.o: AI/AChoice.cpp 
	${MKDIR} -p ${OBJECTDIR}/AI
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/AI/AChoice.o AI/AChoice.cpp

${OBJECTDIR}/AI/AGlobals.o: AI/AGlobals.cpp 
	${MKDIR} -p ${OBJECTDIR}/AI
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/AI/AGlobals.o AI/AGlobals.cpp

${OBJECTDIR}/AI/AIMain.o: AI/AIMain.cpp 
	${MKDIR} -p ${OBJECTDIR}/AI
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/AI/AIMain.o AI/AIMain.cpp

${OBJECTDIR}/AI/AObjGroup.o: AI/AObjGroup.cpp 
	${MKDIR} -p ${OBJECTDIR}/AI
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/AI/AObjGroup.o AI/AObjGroup.cpp

${OBJECTDIR}/AI/Ordre/AOrdre.o: AI/Ordre/AOrdre.cpp 
	${MKDIR} -p ${OBJECTDIR}/AI/Ordre
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/AI/Ordre/AOrdre.o AI/Ordre/AOrdre.cpp

${OBJECTDIR}/AI/Ordre/AOrdreBuild.o: AI/Ordre/AOrdreBuild.cpp 
	${MKDIR} -p ${OBJECTDIR}/AI/Ordre
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/AI/Ordre/AOrdreBuild.o AI/Ordre/AOrdreBuild.cpp

${OBJECTDIR}/AI/Ordre/AOrdreChangeOrdre.o: AI/Ordre/AOrdreChangeOrdre.cpp 
	${MKDIR} -p ${OBJECTDIR}/AI/Ordre
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/AI/Ordre/AOrdreChangeOrdre.o AI/Ordre/AOrdreChangeOrdre.cpp

${OBJECTDIR}/AI/Ordre/AOrdreMine.o: AI/Ordre/AOrdreMine.cpp 
	${MKDIR} -p ${OBJECTDIR}/AI/Ordre
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/AI/Ordre/AOrdreMine.o AI/Ordre/AOrdreMine.cpp

${OBJECTDIR}/AI/Ordre/AOrdreMove.o: AI/Ordre/AOrdreMove.cpp 
	${MKDIR} -p ${OBJECTDIR}/AI/Ordre
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/AI/Ordre/AOrdreMove.o AI/Ordre/AOrdreMove.cpp

${OBJECTDIR}/AI/Ordre/AOrdreSet.o: AI/Ordre/AOrdreSet.cpp 
	${MKDIR} -p ${OBJECTDIR}/AI/Ordre
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/AI/Ordre/AOrdreSet.o AI/Ordre/AOrdreSet.cpp

${OBJECTDIR}/AI/UnitControle/AUnitControle.o: AI/UnitControle/AUnitControle.cpp 
	${MKDIR} -p ${OBJECTDIR}/AI/UnitControle
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/AI/UnitControle/AUnitControle.o AI/UnitControle/AUnitControle.cpp

${OBJECTDIR}/mainAI.o: mainAI.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/mainAI.o mainAI.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/ai

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
