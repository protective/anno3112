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
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/spaceobjects/CAstoroid.o \
	${OBJECTDIR}/world/CGrid.o \
	${OBJECTDIR}/spaceobjects/subsystems/CSubType.o \
	${OBJECTDIR}/UI/CUIButtonFrame.o \
	${OBJECTDIR}/spaceobjects/subsystems/CSingleWep.o \
	${OBJECTDIR}/spaceobjects/COrdres.o \
	${OBJECTDIR}/spaceobjects/subsystems/CSubSystemBonus.o \
	${OBJECTDIR}/Items/CItemType.o \
	${OBJECTDIR}/UI/CUITextInputField.o \
	${OBJECTDIR}/UI/Buttons/CUIButtonOK.o \
	${OBJECTDIR}/spaceobjects/subsystems/CSubSystemW.o \
	${OBJECTDIR}/UI/CUIShipDetailFrame.o \
	${OBJECTDIR}/spaceobjects/subsystems/CSubTypeBonus.o \
	${OBJECTDIR}/spaceobjects/subsystems/CSubTypeWep.o \
	${OBJECTDIR}/spaceobjects/subsystems/CSubSystemRef.o \
	${OBJECTDIR}/UI/Scrolls/CUIVScroll.o \
	${OBJECTDIR}/UI/CUIRightClickMenu.o \
	${OBJECTDIR}/Grafic/CPartical.o \
	${OBJECTDIR}/UI/Forms/CUICreateFitForm.o \
	${OBJECTDIR}/UI/Buttons/CUIButtonOpenCargo.o \
	${OBJECTDIR}/UI/Buttons/CUIButtonChangeTG.o \
	${OBJECTDIR}/UI/CUIMainFrame.o \
	${OBJECTDIR}/UI/CUIButton.o \
	${OBJECTDIR}/spaceobjects/subsystems/CLoadout.o \
	${OBJECTDIR}/spaceobjects/subsystems/CSlotNode.o \
	${OBJECTDIR}/spaceobjects/subsystems/CSubTypeBoost.o \
	${OBJECTDIR}/UI/Build/CUIBuildFrame.o \
	${OBJECTDIR}/UI/Buttons/CUIButtonSetUnitPos.o \
	${OBJECTDIR}/UI/Buttons/CUIButtonBuild.o \
	${OBJECTDIR}/spaceobjects/subsystems/CSubTypeRef.o \
	${OBJECTDIR}/UI/Buttons/CUIButtonChangeOrdre.o \
	${OBJECTDIR}/spaceobjects/subsystems/CSubSystemBoost.o \
	${OBJECTDIR}/UI/CUISubSystem.o \
	${OBJECTDIR}/UI/Buttons/CUIButtonChangeView.o \
	${OBJECTDIR}/CGlobals.o \
	${OBJECTDIR}/spaceobjects/CSubAble.o \
	${OBJECTDIR}/UI/CUIDragDrop.o \
	${OBJECTDIR}/UI/Buttons/CUIButtonFitLoadout.o \
	${OBJECTDIR}/UI/CUIBaseFrame.o \
	${OBJECTDIR}/UI/Buttons/CUIButtonCreateFit.o \
	${OBJECTDIR}/_ext/2098112761/GGlobals.o \
	${OBJECTDIR}/spaceobjects/subsystems/CShipTypeSlotData.o \
	${OBJECTDIR}/Grafic/Grafic.o \
	${OBJECTDIR}/world/CWorld.o \
	${OBJECTDIR}/UI/CUIMoveCloseBar.o \
	${OBJECTDIR}/CPlayerObjHandle.o \
	${OBJECTDIR}/spaceobjects/subsystems/CSingleFac.o \
	${OBJECTDIR}/UI/CUIFrame.o \
	${OBJECTDIR}/CDatabase.o \
	${OBJECTDIR}/UI/CUIComboBox.o \
	${OBJECTDIR}/spaceobjects/subsystems/CSingleRef.o \
	${OBJECTDIR}/UI/ComboBox/CUIComboOrdreChange.o \
	${OBJECTDIR}/UI/Buttons/CUIButtonItem.o \
	${OBJECTDIR}/CFunctions.o \
	${OBJECTDIR}/spaceobjects/CTargetable.o \
	${OBJECTDIR}/spaceobjects/cargo/CCargoBay.o \
	${OBJECTDIR}/UI/ComboBox/CUIComboTgChange.o \
	${OBJECTDIR}/mainClient.o \
	${OBJECTDIR}/UI/Buttons/CUIButtonCancel.o \
	${OBJECTDIR}/spaceobjects/subsystems/CSubTypeFac.o \
	${OBJECTDIR}/spaceobjects/CShot.o \
	${OBJECTDIR}/spaceobjects/CMovable.o \
	${OBJECTDIR}/UI/RightClickMenus/CUIRCMenuLoadout.o \
	${OBJECTDIR}/spaceobjects/CShip.o \
	${OBJECTDIR}/spaceobjects/CPos.o \
	${OBJECTDIR}/spaceobjects/CShipType.o \
	${OBJECTDIR}/_ext/2098112761/GFunctions.o \
	${OBJECTDIR}/spaceobjects/subsystems/CSubSystemFac.o \
	${OBJECTDIR}/spaceobjects/CAstoroidType.o \
	${OBJECTDIR}/UI/ListBox/CUIListBox.o \
	${OBJECTDIR}/spaceobjects/subsystems/CSubSystem.o \
	${OBJECTDIR}/UI/CUICargoViewer.o \
	${OBJECTDIR}/Grafic/CEmitter.o \
	${OBJECTDIR}/_ext/2098112761/GCommands.o \
	${OBJECTDIR}/spaceobjects/CObj.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/client

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/client: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/client ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/spaceobjects/CAstoroid.o: spaceobjects/CAstoroid.cpp 
	${MKDIR} -p ${OBJECTDIR}/spaceobjects
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/spaceobjects/CAstoroid.o spaceobjects/CAstoroid.cpp

${OBJECTDIR}/world/CGrid.o: world/CGrid.cpp 
	${MKDIR} -p ${OBJECTDIR}/world
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/world/CGrid.o world/CGrid.cpp

${OBJECTDIR}/spaceobjects/subsystems/CSubType.o: spaceobjects/subsystems/CSubType.cpp 
	${MKDIR} -p ${OBJECTDIR}/spaceobjects/subsystems
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/spaceobjects/subsystems/CSubType.o spaceobjects/subsystems/CSubType.cpp

${OBJECTDIR}/UI/CUIButtonFrame.o: UI/CUIButtonFrame.cpp 
	${MKDIR} -p ${OBJECTDIR}/UI
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/UI/CUIButtonFrame.o UI/CUIButtonFrame.cpp

${OBJECTDIR}/spaceobjects/subsystems/CSingleWep.o: spaceobjects/subsystems/CSingleWep.cpp 
	${MKDIR} -p ${OBJECTDIR}/spaceobjects/subsystems
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/spaceobjects/subsystems/CSingleWep.o spaceobjects/subsystems/CSingleWep.cpp

${OBJECTDIR}/spaceobjects/COrdres.o: spaceobjects/COrdres.cpp 
	${MKDIR} -p ${OBJECTDIR}/spaceobjects
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/spaceobjects/COrdres.o spaceobjects/COrdres.cpp

${OBJECTDIR}/spaceobjects/subsystems/CSubSystemBonus.o: spaceobjects/subsystems/CSubSystemBonus.cpp 
	${MKDIR} -p ${OBJECTDIR}/spaceobjects/subsystems
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/spaceobjects/subsystems/CSubSystemBonus.o spaceobjects/subsystems/CSubSystemBonus.cpp

${OBJECTDIR}/Items/CItemType.o: Items/CItemType.cpp 
	${MKDIR} -p ${OBJECTDIR}/Items
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Items/CItemType.o Items/CItemType.cpp

${OBJECTDIR}/UI/CUITextInputField.o: UI/CUITextInputField.cpp 
	${MKDIR} -p ${OBJECTDIR}/UI
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/UI/CUITextInputField.o UI/CUITextInputField.cpp

${OBJECTDIR}/UI/Buttons/CUIButtonOK.o: UI/Buttons/CUIButtonOK.cpp 
	${MKDIR} -p ${OBJECTDIR}/UI/Buttons
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/UI/Buttons/CUIButtonOK.o UI/Buttons/CUIButtonOK.cpp

${OBJECTDIR}/spaceobjects/subsystems/CSubSystemW.o: spaceobjects/subsystems/CSubSystemW.cpp 
	${MKDIR} -p ${OBJECTDIR}/spaceobjects/subsystems
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/spaceobjects/subsystems/CSubSystemW.o spaceobjects/subsystems/CSubSystemW.cpp

${OBJECTDIR}/UI/CUIShipDetailFrame.o: UI/CUIShipDetailFrame.cpp 
	${MKDIR} -p ${OBJECTDIR}/UI
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/UI/CUIShipDetailFrame.o UI/CUIShipDetailFrame.cpp

${OBJECTDIR}/spaceobjects/subsystems/CSubTypeBonus.o: spaceobjects/subsystems/CSubTypeBonus.cpp 
	${MKDIR} -p ${OBJECTDIR}/spaceobjects/subsystems
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/spaceobjects/subsystems/CSubTypeBonus.o spaceobjects/subsystems/CSubTypeBonus.cpp

${OBJECTDIR}/spaceobjects/subsystems/CSubTypeWep.o: spaceobjects/subsystems/CSubTypeWep.cpp 
	${MKDIR} -p ${OBJECTDIR}/spaceobjects/subsystems
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/spaceobjects/subsystems/CSubTypeWep.o spaceobjects/subsystems/CSubTypeWep.cpp

${OBJECTDIR}/spaceobjects/subsystems/CSubSystemRef.o: spaceobjects/subsystems/CSubSystemRef.cpp 
	${MKDIR} -p ${OBJECTDIR}/spaceobjects/subsystems
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/spaceobjects/subsystems/CSubSystemRef.o spaceobjects/subsystems/CSubSystemRef.cpp

${OBJECTDIR}/UI/Scrolls/CUIVScroll.o: UI/Scrolls/CUIVScroll.cpp 
	${MKDIR} -p ${OBJECTDIR}/UI/Scrolls
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/UI/Scrolls/CUIVScroll.o UI/Scrolls/CUIVScroll.cpp

${OBJECTDIR}/UI/CUIRightClickMenu.o: UI/CUIRightClickMenu.cpp 
	${MKDIR} -p ${OBJECTDIR}/UI
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/UI/CUIRightClickMenu.o UI/CUIRightClickMenu.cpp

${OBJECTDIR}/Grafic/CPartical.o: Grafic/CPartical.cpp 
	${MKDIR} -p ${OBJECTDIR}/Grafic
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Grafic/CPartical.o Grafic/CPartical.cpp

${OBJECTDIR}/UI/Forms/CUICreateFitForm.o: UI/Forms/CUICreateFitForm.cpp 
	${MKDIR} -p ${OBJECTDIR}/UI/Forms
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/UI/Forms/CUICreateFitForm.o UI/Forms/CUICreateFitForm.cpp

${OBJECTDIR}/UI/Buttons/CUIButtonOpenCargo.o: UI/Buttons/CUIButtonOpenCargo.cpp 
	${MKDIR} -p ${OBJECTDIR}/UI/Buttons
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/UI/Buttons/CUIButtonOpenCargo.o UI/Buttons/CUIButtonOpenCargo.cpp

${OBJECTDIR}/UI/Buttons/CUIButtonChangeTG.o: UI/Buttons/CUIButtonChangeTG.cpp 
	${MKDIR} -p ${OBJECTDIR}/UI/Buttons
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/UI/Buttons/CUIButtonChangeTG.o UI/Buttons/CUIButtonChangeTG.cpp

${OBJECTDIR}/UI/CUIMainFrame.o: UI/CUIMainFrame.cpp 
	${MKDIR} -p ${OBJECTDIR}/UI
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/UI/CUIMainFrame.o UI/CUIMainFrame.cpp

${OBJECTDIR}/UI/CUIButton.o: UI/CUIButton.cpp 
	${MKDIR} -p ${OBJECTDIR}/UI
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/UI/CUIButton.o UI/CUIButton.cpp

${OBJECTDIR}/spaceobjects/subsystems/CLoadout.o: spaceobjects/subsystems/CLoadout.cpp 
	${MKDIR} -p ${OBJECTDIR}/spaceobjects/subsystems
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/spaceobjects/subsystems/CLoadout.o spaceobjects/subsystems/CLoadout.cpp

${OBJECTDIR}/spaceobjects/subsystems/CSlotNode.o: spaceobjects/subsystems/CSlotNode.cpp 
	${MKDIR} -p ${OBJECTDIR}/spaceobjects/subsystems
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/spaceobjects/subsystems/CSlotNode.o spaceobjects/subsystems/CSlotNode.cpp

${OBJECTDIR}/spaceobjects/subsystems/CSubTypeBoost.o: spaceobjects/subsystems/CSubTypeBoost.cpp 
	${MKDIR} -p ${OBJECTDIR}/spaceobjects/subsystems
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/spaceobjects/subsystems/CSubTypeBoost.o spaceobjects/subsystems/CSubTypeBoost.cpp

${OBJECTDIR}/UI/Build/CUIBuildFrame.o: UI/Build/CUIBuildFrame.cpp 
	${MKDIR} -p ${OBJECTDIR}/UI/Build
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/UI/Build/CUIBuildFrame.o UI/Build/CUIBuildFrame.cpp

${OBJECTDIR}/UI/Buttons/CUIButtonSetUnitPos.o: UI/Buttons/CUIButtonSetUnitPos.cpp 
	${MKDIR} -p ${OBJECTDIR}/UI/Buttons
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/UI/Buttons/CUIButtonSetUnitPos.o UI/Buttons/CUIButtonSetUnitPos.cpp

${OBJECTDIR}/UI/Buttons/CUIButtonBuild.o: UI/Buttons/CUIButtonBuild.cpp 
	${MKDIR} -p ${OBJECTDIR}/UI/Buttons
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/UI/Buttons/CUIButtonBuild.o UI/Buttons/CUIButtonBuild.cpp

${OBJECTDIR}/spaceobjects/subsystems/CSubTypeRef.o: spaceobjects/subsystems/CSubTypeRef.cpp 
	${MKDIR} -p ${OBJECTDIR}/spaceobjects/subsystems
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/spaceobjects/subsystems/CSubTypeRef.o spaceobjects/subsystems/CSubTypeRef.cpp

${OBJECTDIR}/UI/Buttons/CUIButtonChangeOrdre.o: UI/Buttons/CUIButtonChangeOrdre.cpp 
	${MKDIR} -p ${OBJECTDIR}/UI/Buttons
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/UI/Buttons/CUIButtonChangeOrdre.o UI/Buttons/CUIButtonChangeOrdre.cpp

${OBJECTDIR}/spaceobjects/subsystems/CSubSystemBoost.o: spaceobjects/subsystems/CSubSystemBoost.cpp 
	${MKDIR} -p ${OBJECTDIR}/spaceobjects/subsystems
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/spaceobjects/subsystems/CSubSystemBoost.o spaceobjects/subsystems/CSubSystemBoost.cpp

${OBJECTDIR}/UI/CUISubSystem.o: UI/CUISubSystem.cpp 
	${MKDIR} -p ${OBJECTDIR}/UI
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/UI/CUISubSystem.o UI/CUISubSystem.cpp

${OBJECTDIR}/UI/Buttons/CUIButtonChangeView.o: UI/Buttons/CUIButtonChangeView.cpp 
	${MKDIR} -p ${OBJECTDIR}/UI/Buttons
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/UI/Buttons/CUIButtonChangeView.o UI/Buttons/CUIButtonChangeView.cpp

${OBJECTDIR}/CGlobals.o: CGlobals.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/CGlobals.o CGlobals.cpp

${OBJECTDIR}/spaceobjects/CSubAble.o: spaceobjects/CSubAble.cpp 
	${MKDIR} -p ${OBJECTDIR}/spaceobjects
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/spaceobjects/CSubAble.o spaceobjects/CSubAble.cpp

${OBJECTDIR}/UI/CUIDragDrop.o: UI/CUIDragDrop.cpp 
	${MKDIR} -p ${OBJECTDIR}/UI
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/UI/CUIDragDrop.o UI/CUIDragDrop.cpp

${OBJECTDIR}/UI/Buttons/CUIButtonFitLoadout.o: UI/Buttons/CUIButtonFitLoadout.cpp 
	${MKDIR} -p ${OBJECTDIR}/UI/Buttons
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/UI/Buttons/CUIButtonFitLoadout.o UI/Buttons/CUIButtonFitLoadout.cpp

${OBJECTDIR}/UI/CUIBaseFrame.o: UI/CUIBaseFrame.cpp 
	${MKDIR} -p ${OBJECTDIR}/UI
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/UI/CUIBaseFrame.o UI/CUIBaseFrame.cpp

${OBJECTDIR}/UI/Buttons/CUIButtonCreateFit.o: UI/Buttons/CUIButtonCreateFit.cpp 
	${MKDIR} -p ${OBJECTDIR}/UI/Buttons
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/UI/Buttons/CUIButtonCreateFit.o UI/Buttons/CUIButtonCreateFit.cpp

${OBJECTDIR}/_ext/2098112761/GGlobals.o: ../GShare/GGlobals.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2098112761
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/2098112761/GGlobals.o ../GShare/GGlobals.cpp

${OBJECTDIR}/spaceobjects/subsystems/CShipTypeSlotData.o: spaceobjects/subsystems/CShipTypeSlotData.cpp 
	${MKDIR} -p ${OBJECTDIR}/spaceobjects/subsystems
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/spaceobjects/subsystems/CShipTypeSlotData.o spaceobjects/subsystems/CShipTypeSlotData.cpp

${OBJECTDIR}/Grafic/Grafic.o: Grafic/Grafic.cpp 
	${MKDIR} -p ${OBJECTDIR}/Grafic
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Grafic/Grafic.o Grafic/Grafic.cpp

${OBJECTDIR}/world/CWorld.o: world/CWorld.cpp 
	${MKDIR} -p ${OBJECTDIR}/world
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/world/CWorld.o world/CWorld.cpp

${OBJECTDIR}/UI/CUIMoveCloseBar.o: UI/CUIMoveCloseBar.cpp 
	${MKDIR} -p ${OBJECTDIR}/UI
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/UI/CUIMoveCloseBar.o UI/CUIMoveCloseBar.cpp

${OBJECTDIR}/CPlayerObjHandle.o: CPlayerObjHandle.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/CPlayerObjHandle.o CPlayerObjHandle.cpp

${OBJECTDIR}/spaceobjects/subsystems/CSingleFac.o: spaceobjects/subsystems/CSingleFac.cpp 
	${MKDIR} -p ${OBJECTDIR}/spaceobjects/subsystems
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/spaceobjects/subsystems/CSingleFac.o spaceobjects/subsystems/CSingleFac.cpp

${OBJECTDIR}/UI/CUIFrame.o: UI/CUIFrame.cpp 
	${MKDIR} -p ${OBJECTDIR}/UI
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/UI/CUIFrame.o UI/CUIFrame.cpp

${OBJECTDIR}/CDatabase.o: CDatabase.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/CDatabase.o CDatabase.cpp

${OBJECTDIR}/UI/CUIComboBox.o: UI/CUIComboBox.cpp 
	${MKDIR} -p ${OBJECTDIR}/UI
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/UI/CUIComboBox.o UI/CUIComboBox.cpp

${OBJECTDIR}/spaceobjects/subsystems/CSingleRef.o: spaceobjects/subsystems/CSingleRef.cpp 
	${MKDIR} -p ${OBJECTDIR}/spaceobjects/subsystems
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/spaceobjects/subsystems/CSingleRef.o spaceobjects/subsystems/CSingleRef.cpp

${OBJECTDIR}/UI/ComboBox/CUIComboOrdreChange.o: UI/ComboBox/CUIComboOrdreChange.cpp 
	${MKDIR} -p ${OBJECTDIR}/UI/ComboBox
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/UI/ComboBox/CUIComboOrdreChange.o UI/ComboBox/CUIComboOrdreChange.cpp

${OBJECTDIR}/UI/Buttons/CUIButtonItem.o: UI/Buttons/CUIButtonItem.cpp 
	${MKDIR} -p ${OBJECTDIR}/UI/Buttons
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/UI/Buttons/CUIButtonItem.o UI/Buttons/CUIButtonItem.cpp

${OBJECTDIR}/CFunctions.o: CFunctions.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/CFunctions.o CFunctions.cpp

${OBJECTDIR}/spaceobjects/CTargetable.o: spaceobjects/CTargetable.cpp 
	${MKDIR} -p ${OBJECTDIR}/spaceobjects
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/spaceobjects/CTargetable.o spaceobjects/CTargetable.cpp

${OBJECTDIR}/spaceobjects/cargo/CCargoBay.o: spaceobjects/cargo/CCargoBay.cpp 
	${MKDIR} -p ${OBJECTDIR}/spaceobjects/cargo
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/spaceobjects/cargo/CCargoBay.o spaceobjects/cargo/CCargoBay.cpp

${OBJECTDIR}/UI/ComboBox/CUIComboTgChange.o: UI/ComboBox/CUIComboTgChange.cpp 
	${MKDIR} -p ${OBJECTDIR}/UI/ComboBox
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/UI/ComboBox/CUIComboTgChange.o UI/ComboBox/CUIComboTgChange.cpp

${OBJECTDIR}/mainClient.o: mainClient.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/mainClient.o mainClient.cpp

${OBJECTDIR}/UI/Buttons/CUIButtonCancel.o: UI/Buttons/CUIButtonCancel.cpp 
	${MKDIR} -p ${OBJECTDIR}/UI/Buttons
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/UI/Buttons/CUIButtonCancel.o UI/Buttons/CUIButtonCancel.cpp

${OBJECTDIR}/spaceobjects/subsystems/CSubTypeFac.o: spaceobjects/subsystems/CSubTypeFac.cpp 
	${MKDIR} -p ${OBJECTDIR}/spaceobjects/subsystems
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/spaceobjects/subsystems/CSubTypeFac.o spaceobjects/subsystems/CSubTypeFac.cpp

${OBJECTDIR}/spaceobjects/CShot.o: spaceobjects/CShot.cpp 
	${MKDIR} -p ${OBJECTDIR}/spaceobjects
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/spaceobjects/CShot.o spaceobjects/CShot.cpp

${OBJECTDIR}/spaceobjects/CMovable.o: spaceobjects/CMovable.cpp 
	${MKDIR} -p ${OBJECTDIR}/spaceobjects
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/spaceobjects/CMovable.o spaceobjects/CMovable.cpp

${OBJECTDIR}/UI/RightClickMenus/CUIRCMenuLoadout.o: UI/RightClickMenus/CUIRCMenuLoadout.cpp 
	${MKDIR} -p ${OBJECTDIR}/UI/RightClickMenus
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/UI/RightClickMenus/CUIRCMenuLoadout.o UI/RightClickMenus/CUIRCMenuLoadout.cpp

${OBJECTDIR}/spaceobjects/CShip.o: spaceobjects/CShip.cpp 
	${MKDIR} -p ${OBJECTDIR}/spaceobjects
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/spaceobjects/CShip.o spaceobjects/CShip.cpp

${OBJECTDIR}/spaceobjects/CPos.o: spaceobjects/CPos.cpp 
	${MKDIR} -p ${OBJECTDIR}/spaceobjects
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/spaceobjects/CPos.o spaceobjects/CPos.cpp

${OBJECTDIR}/spaceobjects/CShipType.o: spaceobjects/CShipType.cpp 
	${MKDIR} -p ${OBJECTDIR}/spaceobjects
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/spaceobjects/CShipType.o spaceobjects/CShipType.cpp

${OBJECTDIR}/_ext/2098112761/GFunctions.o: ../GShare/GFunctions.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2098112761
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/2098112761/GFunctions.o ../GShare/GFunctions.cpp

${OBJECTDIR}/spaceobjects/subsystems/CSubSystemFac.o: spaceobjects/subsystems/CSubSystemFac.cpp 
	${MKDIR} -p ${OBJECTDIR}/spaceobjects/subsystems
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/spaceobjects/subsystems/CSubSystemFac.o spaceobjects/subsystems/CSubSystemFac.cpp

${OBJECTDIR}/spaceobjects/CAstoroidType.o: spaceobjects/CAstoroidType.cpp 
	${MKDIR} -p ${OBJECTDIR}/spaceobjects
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/spaceobjects/CAstoroidType.o spaceobjects/CAstoroidType.cpp

${OBJECTDIR}/UI/ListBox/CUIListBox.o: UI/ListBox/CUIListBox.cpp 
	${MKDIR} -p ${OBJECTDIR}/UI/ListBox
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/UI/ListBox/CUIListBox.o UI/ListBox/CUIListBox.cpp

${OBJECTDIR}/spaceobjects/subsystems/CSubSystem.o: spaceobjects/subsystems/CSubSystem.cpp 
	${MKDIR} -p ${OBJECTDIR}/spaceobjects/subsystems
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/spaceobjects/subsystems/CSubSystem.o spaceobjects/subsystems/CSubSystem.cpp

${OBJECTDIR}/UI/CUICargoViewer.o: UI/CUICargoViewer.cpp 
	${MKDIR} -p ${OBJECTDIR}/UI
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/UI/CUICargoViewer.o UI/CUICargoViewer.cpp

${OBJECTDIR}/Grafic/CEmitter.o: Grafic/CEmitter.cpp 
	${MKDIR} -p ${OBJECTDIR}/Grafic
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Grafic/CEmitter.o Grafic/CEmitter.cpp

${OBJECTDIR}/_ext/2098112761/GCommands.o: ../GShare/GCommands.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2098112761
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/2098112761/GCommands.o ../GShare/GCommands.cpp

${OBJECTDIR}/spaceobjects/CObj.o: spaceobjects/CObj.cpp 
	${MKDIR} -p ${OBJECTDIR}/spaceobjects
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/spaceobjects/CObj.o spaceobjects/CObj.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/client

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
