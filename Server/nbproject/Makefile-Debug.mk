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
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/SDatabase.o \
	${OBJECTDIR}/Sspacebjects/SAstoroidType.o \
	${OBJECTDIR}/Commands/CommandProcessor.o \
	${OBJECTDIR}/Sspacebjects/SMovable.o \
	${OBJECTDIR}/Sspacebjects/subsystems/SSubTypeFac.o \
	${OBJECTDIR}/Sspacebjects/Ordres/SOrdreActionMoveTo.o \
	${OBJECTDIR}/Sspacebjects/Ordres/SOrdreConditionUnitEqTo.o \
	${OBJECTDIR}/Sspacebjects/Ordres/SOrdreRule.o \
	${OBJECTDIR}/Sspacebjects/SPos.o \
	${OBJECTDIR}/Commands/Command.o \
	${OBJECTDIR}/Sspacebjects/Ordres/SOrdreConditionStatOp.o \
	${OBJECTDIR}/Sspacebjects/subsystems/SSubSystemFighter.o \
	${OBJECTDIR}/Sspacebjects/subsystems/SSubType.o \
	${OBJECTDIR}/Sspacebjects/subsystems/SSubTypeBonus.o \
	${OBJECTDIR}/Sspacebjects/Ordres/SOrdreConditionAND.o \
	${OBJECTDIR}/mainServer.o \
	${OBJECTDIR}/Sspacebjects/subsystems/SSubSystem.o \
	${OBJECTDIR}/Sspacebjects/SFighterType.o \
	${OBJECTDIR}/Sspacebjects/SShip.o \
	${OBJECTDIR}/Sspacebjects/STargetable.o \
	${OBJECTDIR}/Sspacebjects/SShipType.o \
	${OBJECTDIR}/Sspacebjects/Ordres/SOrdreCondition.o \
	${OBJECTDIR}/Sspacebjects/SFighter.o \
	${OBJECTDIR}/SItems/SItem.o \
	${OBJECTDIR}/NetworkControler.o \
	${OBJECTDIR}/Sspacebjects/SMetaObj.o \
	${OBJECTDIR}/Commands/CommandUpdateMetas.o \
	${OBJECTDIR}/Sspacebjects/subsystems/SSubTypeRef.o \
	${OBJECTDIR}/Client.o \
	${OBJECTDIR}/Sspacebjects/Ordres/SOrdreConditionOR.o \
	${OBJECTDIR}/Commands/CommandAddSubscriptions.o \
	${OBJECTDIR}/Sspacebjects/SShot.o \
	${OBJECTDIR}/World/SWorld.o \
	${OBJECTDIR}/Sspacebjects/subsystems/SSubSystemBoost.o \
	${OBJECTDIR}/Sspacebjects/subsystems/SSubTypeBoost.o \
	${OBJECTDIR}/_ext/2098112761/GGlobals.o \
	${OBJECTDIR}/Sspacebjects/subsystems/SSingleWep.o \
	${OBJECTDIR}/Sspacebjects/Ordres/SOrdreActionTrasfereCargo.o \
	${OBJECTDIR}/SFunctions.o \
	${OBJECTDIR}/Sspacebjects/subsystems/SSubSystemBonus.o \
	${OBJECTDIR}/Commands/CommandTransfere.o \
	${OBJECTDIR}/SItems/SItemType.o \
	${OBJECTDIR}/SGlobals.o \
	${OBJECTDIR}/Sspacebjects/subsystems/SSlotNode.o \
	${OBJECTDIR}/Sspacebjects/subsystems/SSubSystemW.o \
	${OBJECTDIR}/Commands/Processor.o \
	${OBJECTDIR}/Sspacebjects/SUnit.o \
	${OBJECTDIR}/Commands/Processable.o \
	${OBJECTDIR}/World/SGrid.o \
	${OBJECTDIR}/Sspacebjects/SObj.o \
	${OBJECTDIR}/Sspacebjects/subsystems/SLoadout.o \
	${OBJECTDIR}/Sspacebjects/Ordres/SOrdreAction.o \
	${OBJECTDIR}/Sspacebjects/subsystems/SShipTypeSlotData.o \
	${OBJECTDIR}/Sspacebjects/SSubAble.o \
	${OBJECTDIR}/Sspacebjects/SOrdres.o \
	${OBJECTDIR}/Sspacebjects/SAstoroid.o \
	${OBJECTDIR}/Sspacebjects/subsystems/SSubTypeWep.o \
	${OBJECTDIR}/Sspacebjects/cargo/SCargoBay.o \
	${OBJECTDIR}/Sspacebjects/subsystems/SSubSystemRef.o \
	${OBJECTDIR}/Sspacebjects/subsystems/SSingleRef.o \
	${OBJECTDIR}/_ext/2098112761/GFunctions.o \
	${OBJECTDIR}/Commands/CommandTimedSubscribeUpdate.o \
	${OBJECTDIR}/Sspacebjects/SUnitType.o \
	${OBJECTDIR}/Sspacebjects/subsystems/SSubSystemFac.o \
	${OBJECTDIR}/Sspacebjects/subsystems/SSubTypeFighter.o \
	${OBJECTDIR}/Sspacebjects/SAstoroidBelt.o \
	${OBJECTDIR}/Commands/CommandAdd.o \
	${OBJECTDIR}/Sspacebjects/subsystems/SSingleFac.o


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
LDLIBSOPTIONS=-lpthread -lSDLmain -lSDL

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/server

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/server: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/server ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/SDatabase.o: SDatabase.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/SDatabase.o SDatabase.cpp

${OBJECTDIR}/Sspacebjects/SAstoroidType.o: Sspacebjects/SAstoroidType.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Sspacebjects/SAstoroidType.o Sspacebjects/SAstoroidType.cpp

${OBJECTDIR}/Commands/CommandProcessor.o: Commands/CommandProcessor.cpp 
	${MKDIR} -p ${OBJECTDIR}/Commands
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Commands/CommandProcessor.o Commands/CommandProcessor.cpp

${OBJECTDIR}/Sspacebjects/SMovable.o: Sspacebjects/SMovable.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Sspacebjects/SMovable.o Sspacebjects/SMovable.cpp

${OBJECTDIR}/Sspacebjects/subsystems/SSubTypeFac.o: Sspacebjects/subsystems/SSubTypeFac.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects/subsystems
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Sspacebjects/subsystems/SSubTypeFac.o Sspacebjects/subsystems/SSubTypeFac.cpp

${OBJECTDIR}/Sspacebjects/Ordres/SOrdreActionMoveTo.o: Sspacebjects/Ordres/SOrdreActionMoveTo.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects/Ordres
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Sspacebjects/Ordres/SOrdreActionMoveTo.o Sspacebjects/Ordres/SOrdreActionMoveTo.cpp

${OBJECTDIR}/Sspacebjects/Ordres/SOrdreConditionUnitEqTo.o: Sspacebjects/Ordres/SOrdreConditionUnitEqTo.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects/Ordres
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Sspacebjects/Ordres/SOrdreConditionUnitEqTo.o Sspacebjects/Ordres/SOrdreConditionUnitEqTo.cpp

${OBJECTDIR}/Sspacebjects/Ordres/SOrdreRule.o: Sspacebjects/Ordres/SOrdreRule.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects/Ordres
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Sspacebjects/Ordres/SOrdreRule.o Sspacebjects/Ordres/SOrdreRule.cpp

${OBJECTDIR}/Sspacebjects/SPos.o: Sspacebjects/SPos.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Sspacebjects/SPos.o Sspacebjects/SPos.cpp

${OBJECTDIR}/Commands/Command.o: Commands/Command.cpp 
	${MKDIR} -p ${OBJECTDIR}/Commands
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Commands/Command.o Commands/Command.cpp

${OBJECTDIR}/Sspacebjects/Ordres/SOrdreConditionStatOp.o: Sspacebjects/Ordres/SOrdreConditionStatOp.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects/Ordres
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Sspacebjects/Ordres/SOrdreConditionStatOp.o Sspacebjects/Ordres/SOrdreConditionStatOp.cpp

${OBJECTDIR}/Sspacebjects/subsystems/SSubSystemFighter.o: Sspacebjects/subsystems/SSubSystemFighter.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects/subsystems
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Sspacebjects/subsystems/SSubSystemFighter.o Sspacebjects/subsystems/SSubSystemFighter.cpp

${OBJECTDIR}/Sspacebjects/subsystems/SSubType.o: Sspacebjects/subsystems/SSubType.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects/subsystems
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Sspacebjects/subsystems/SSubType.o Sspacebjects/subsystems/SSubType.cpp

${OBJECTDIR}/Sspacebjects/subsystems/SSubTypeBonus.o: Sspacebjects/subsystems/SSubTypeBonus.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects/subsystems
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Sspacebjects/subsystems/SSubTypeBonus.o Sspacebjects/subsystems/SSubTypeBonus.cpp

${OBJECTDIR}/Sspacebjects/Ordres/SOrdreConditionAND.o: Sspacebjects/Ordres/SOrdreConditionAND.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects/Ordres
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Sspacebjects/Ordres/SOrdreConditionAND.o Sspacebjects/Ordres/SOrdreConditionAND.cpp

${OBJECTDIR}/mainServer.o: mainServer.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/mainServer.o mainServer.cpp

${OBJECTDIR}/Sspacebjects/subsystems/SSubSystem.o: Sspacebjects/subsystems/SSubSystem.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects/subsystems
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Sspacebjects/subsystems/SSubSystem.o Sspacebjects/subsystems/SSubSystem.cpp

${OBJECTDIR}/Sspacebjects/SFighterType.o: Sspacebjects/SFighterType.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Sspacebjects/SFighterType.o Sspacebjects/SFighterType.cpp

${OBJECTDIR}/Sspacebjects/SShip.o: Sspacebjects/SShip.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Sspacebjects/SShip.o Sspacebjects/SShip.cpp

${OBJECTDIR}/Sspacebjects/STargetable.o: Sspacebjects/STargetable.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Sspacebjects/STargetable.o Sspacebjects/STargetable.cpp

${OBJECTDIR}/Sspacebjects/SShipType.o: Sspacebjects/SShipType.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Sspacebjects/SShipType.o Sspacebjects/SShipType.cpp

${OBJECTDIR}/Sspacebjects/Ordres/SOrdreCondition.o: Sspacebjects/Ordres/SOrdreCondition.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects/Ordres
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Sspacebjects/Ordres/SOrdreCondition.o Sspacebjects/Ordres/SOrdreCondition.cpp

${OBJECTDIR}/Sspacebjects/SFighter.o: Sspacebjects/SFighter.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Sspacebjects/SFighter.o Sspacebjects/SFighter.cpp

${OBJECTDIR}/SItems/SItem.o: SItems/SItem.cpp 
	${MKDIR} -p ${OBJECTDIR}/SItems
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/SItems/SItem.o SItems/SItem.cpp

${OBJECTDIR}/NetworkControler.o: NetworkControler.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/NetworkControler.o NetworkControler.cpp

${OBJECTDIR}/Sspacebjects/SMetaObj.o: Sspacebjects/SMetaObj.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Sspacebjects/SMetaObj.o Sspacebjects/SMetaObj.cpp

${OBJECTDIR}/Commands/CommandUpdateMetas.o: Commands/CommandUpdateMetas.cpp 
	${MKDIR} -p ${OBJECTDIR}/Commands
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Commands/CommandUpdateMetas.o Commands/CommandUpdateMetas.cpp

${OBJECTDIR}/Sspacebjects/subsystems/SSubTypeRef.o: Sspacebjects/subsystems/SSubTypeRef.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects/subsystems
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Sspacebjects/subsystems/SSubTypeRef.o Sspacebjects/subsystems/SSubTypeRef.cpp

${OBJECTDIR}/Client.o: Client.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Client.o Client.cpp

${OBJECTDIR}/Sspacebjects/Ordres/SOrdreConditionOR.o: Sspacebjects/Ordres/SOrdreConditionOR.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects/Ordres
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Sspacebjects/Ordres/SOrdreConditionOR.o Sspacebjects/Ordres/SOrdreConditionOR.cpp

${OBJECTDIR}/Commands/CommandAddSubscriptions.o: Commands/CommandAddSubscriptions.cpp 
	${MKDIR} -p ${OBJECTDIR}/Commands
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Commands/CommandAddSubscriptions.o Commands/CommandAddSubscriptions.cpp

${OBJECTDIR}/Sspacebjects/SShot.o: Sspacebjects/SShot.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Sspacebjects/SShot.o Sspacebjects/SShot.cpp

${OBJECTDIR}/World/SWorld.o: World/SWorld.cpp 
	${MKDIR} -p ${OBJECTDIR}/World
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/World/SWorld.o World/SWorld.cpp

${OBJECTDIR}/Sspacebjects/subsystems/SSubSystemBoost.o: Sspacebjects/subsystems/SSubSystemBoost.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects/subsystems
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Sspacebjects/subsystems/SSubSystemBoost.o Sspacebjects/subsystems/SSubSystemBoost.cpp

${OBJECTDIR}/Sspacebjects/subsystems/SSubTypeBoost.o: Sspacebjects/subsystems/SSubTypeBoost.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects/subsystems
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Sspacebjects/subsystems/SSubTypeBoost.o Sspacebjects/subsystems/SSubTypeBoost.cpp

${OBJECTDIR}/_ext/2098112761/GGlobals.o: ../GShare/GGlobals.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2098112761
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/2098112761/GGlobals.o ../GShare/GGlobals.cpp

${OBJECTDIR}/Sspacebjects/subsystems/SSingleWep.o: Sspacebjects/subsystems/SSingleWep.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects/subsystems
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Sspacebjects/subsystems/SSingleWep.o Sspacebjects/subsystems/SSingleWep.cpp

${OBJECTDIR}/Sspacebjects/Ordres/SOrdreActionTrasfereCargo.o: Sspacebjects/Ordres/SOrdreActionTrasfereCargo.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects/Ordres
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Sspacebjects/Ordres/SOrdreActionTrasfereCargo.o Sspacebjects/Ordres/SOrdreActionTrasfereCargo.cpp

${OBJECTDIR}/SFunctions.o: SFunctions.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/SFunctions.o SFunctions.cpp

${OBJECTDIR}/Sspacebjects/subsystems/SSubSystemBonus.o: Sspacebjects/subsystems/SSubSystemBonus.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects/subsystems
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Sspacebjects/subsystems/SSubSystemBonus.o Sspacebjects/subsystems/SSubSystemBonus.cpp

${OBJECTDIR}/Commands/CommandTransfere.o: Commands/CommandTransfere.cpp 
	${MKDIR} -p ${OBJECTDIR}/Commands
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Commands/CommandTransfere.o Commands/CommandTransfere.cpp

${OBJECTDIR}/SItems/SItemType.o: SItems/SItemType.cpp 
	${MKDIR} -p ${OBJECTDIR}/SItems
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/SItems/SItemType.o SItems/SItemType.cpp

${OBJECTDIR}/SGlobals.o: SGlobals.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/SGlobals.o SGlobals.cpp

${OBJECTDIR}/Sspacebjects/subsystems/SSlotNode.o: Sspacebjects/subsystems/SSlotNode.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects/subsystems
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Sspacebjects/subsystems/SSlotNode.o Sspacebjects/subsystems/SSlotNode.cpp

${OBJECTDIR}/Sspacebjects/subsystems/SSubSystemW.o: Sspacebjects/subsystems/SSubSystemW.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects/subsystems
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Sspacebjects/subsystems/SSubSystemW.o Sspacebjects/subsystems/SSubSystemW.cpp

${OBJECTDIR}/Commands/Processor.o: Commands/Processor.cpp 
	${MKDIR} -p ${OBJECTDIR}/Commands
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Commands/Processor.o Commands/Processor.cpp

${OBJECTDIR}/Sspacebjects/SUnit.o: Sspacebjects/SUnit.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Sspacebjects/SUnit.o Sspacebjects/SUnit.cpp

${OBJECTDIR}/Commands/Processable.o: Commands/Processable.cpp 
	${MKDIR} -p ${OBJECTDIR}/Commands
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Commands/Processable.o Commands/Processable.cpp

${OBJECTDIR}/World/SGrid.o: World/SGrid.cpp 
	${MKDIR} -p ${OBJECTDIR}/World
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/World/SGrid.o World/SGrid.cpp

${OBJECTDIR}/Sspacebjects/SObj.o: Sspacebjects/SObj.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Sspacebjects/SObj.o Sspacebjects/SObj.cpp

${OBJECTDIR}/Sspacebjects/subsystems/SLoadout.o: Sspacebjects/subsystems/SLoadout.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects/subsystems
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Sspacebjects/subsystems/SLoadout.o Sspacebjects/subsystems/SLoadout.cpp

${OBJECTDIR}/Sspacebjects/Ordres/SOrdreAction.o: Sspacebjects/Ordres/SOrdreAction.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects/Ordres
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Sspacebjects/Ordres/SOrdreAction.o Sspacebjects/Ordres/SOrdreAction.cpp

${OBJECTDIR}/Sspacebjects/subsystems/SShipTypeSlotData.o: Sspacebjects/subsystems/SShipTypeSlotData.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects/subsystems
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Sspacebjects/subsystems/SShipTypeSlotData.o Sspacebjects/subsystems/SShipTypeSlotData.cpp

${OBJECTDIR}/Sspacebjects/SSubAble.o: Sspacebjects/SSubAble.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Sspacebjects/SSubAble.o Sspacebjects/SSubAble.cpp

${OBJECTDIR}/Sspacebjects/SOrdres.o: Sspacebjects/SOrdres.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Sspacebjects/SOrdres.o Sspacebjects/SOrdres.cpp

${OBJECTDIR}/Sspacebjects/SAstoroid.o: Sspacebjects/SAstoroid.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Sspacebjects/SAstoroid.o Sspacebjects/SAstoroid.cpp

${OBJECTDIR}/Sspacebjects/subsystems/SSubTypeWep.o: Sspacebjects/subsystems/SSubTypeWep.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects/subsystems
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Sspacebjects/subsystems/SSubTypeWep.o Sspacebjects/subsystems/SSubTypeWep.cpp

${OBJECTDIR}/Sspacebjects/cargo/SCargoBay.o: Sspacebjects/cargo/SCargoBay.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects/cargo
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Sspacebjects/cargo/SCargoBay.o Sspacebjects/cargo/SCargoBay.cpp

${OBJECTDIR}/Sspacebjects/subsystems/SSubSystemRef.o: Sspacebjects/subsystems/SSubSystemRef.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects/subsystems
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Sspacebjects/subsystems/SSubSystemRef.o Sspacebjects/subsystems/SSubSystemRef.cpp

${OBJECTDIR}/Sspacebjects/subsystems/SSingleRef.o: Sspacebjects/subsystems/SSingleRef.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects/subsystems
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Sspacebjects/subsystems/SSingleRef.o Sspacebjects/subsystems/SSingleRef.cpp

${OBJECTDIR}/_ext/2098112761/GFunctions.o: ../GShare/GFunctions.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2098112761
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/2098112761/GFunctions.o ../GShare/GFunctions.cpp

${OBJECTDIR}/Commands/CommandTimedSubscribeUpdate.o: Commands/CommandTimedSubscribeUpdate.cpp 
	${MKDIR} -p ${OBJECTDIR}/Commands
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Commands/CommandTimedSubscribeUpdate.o Commands/CommandTimedSubscribeUpdate.cpp

${OBJECTDIR}/Sspacebjects/SUnitType.o: Sspacebjects/SUnitType.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Sspacebjects/SUnitType.o Sspacebjects/SUnitType.cpp

${OBJECTDIR}/Sspacebjects/subsystems/SSubSystemFac.o: Sspacebjects/subsystems/SSubSystemFac.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects/subsystems
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Sspacebjects/subsystems/SSubSystemFac.o Sspacebjects/subsystems/SSubSystemFac.cpp

${OBJECTDIR}/Sspacebjects/subsystems/SSubTypeFighter.o: Sspacebjects/subsystems/SSubTypeFighter.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects/subsystems
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Sspacebjects/subsystems/SSubTypeFighter.o Sspacebjects/subsystems/SSubTypeFighter.cpp

${OBJECTDIR}/Sspacebjects/SAstoroidBelt.o: Sspacebjects/SAstoroidBelt.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Sspacebjects/SAstoroidBelt.o Sspacebjects/SAstoroidBelt.cpp

${OBJECTDIR}/Commands/CommandAdd.o: Commands/CommandAdd.cpp 
	${MKDIR} -p ${OBJECTDIR}/Commands
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Commands/CommandAdd.o Commands/CommandAdd.cpp

${OBJECTDIR}/Sspacebjects/subsystems/SSingleFac.o: Sspacebjects/subsystems/SSingleFac.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects/subsystems
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Sspacebjects/subsystems/SSingleFac.o Sspacebjects/subsystems/SSingleFac.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/server

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc