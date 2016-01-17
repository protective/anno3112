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
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/2098112761/GFunctions.o \
	${OBJECTDIR}/_ext/2098112761/GGlobals.o \
	${OBJECTDIR}/Client.o \
	${OBJECTDIR}/Commands/CargoCommands/CommandCargoAdd.o \
	${OBJECTDIR}/Commands/CargoCommands/CommandCargoTransOnReciver.o \
	${OBJECTDIR}/Commands/CargoCommands/CommandCargoTransOnSender.o \
	${OBJECTDIR}/Commands/CargoCommands/CommandCargoTransfere.o \
	${OBJECTDIR}/Commands/Command.o \
	${OBJECTDIR}/Commands/CommandAdd.o \
	${OBJECTDIR}/Commands/CommandAddSubscriptions.o \
	${OBJECTDIR}/Commands/CommandClientSubscription.o \
	${OBJECTDIR}/Commands/CommandEnterGrid.o \
	${OBJECTDIR}/Commands/CommandExitGrid.o \
	${OBJECTDIR}/Commands/CommandHit.o \
	${OBJECTDIR}/Commands/CommandInitShot.o \
	${OBJECTDIR}/Commands/CommandMetaHit.o \
	${OBJECTDIR}/Commands/CommandProcesMetas.o \
	${OBJECTDIR}/Commands/CommandProcessor.o \
	${OBJECTDIR}/Commands/CommandQueryCmp.o \
	${OBJECTDIR}/Commands/CommandRemove.o \
	${OBJECTDIR}/Commands/CommandSignalFighter.o \
	${OBJECTDIR}/Commands/CommandTargetPosUpdate.o \
	${OBJECTDIR}/Commands/CommandTimedSubscribeUpdate.o \
	${OBJECTDIR}/Commands/CommandTransfere.o \
	${OBJECTDIR}/Commands/CommandUpdateMetas.o \
	${OBJECTDIR}/Commands/Processable.o \
	${OBJECTDIR}/Commands/Processor.o \
	${OBJECTDIR}/Commands/Query/CommandQuery.o \
	${OBJECTDIR}/Commands/Query/CommandQueryRsp.o \
	${OBJECTDIR}/Commands/inputCommands/CommandIChangeOrders.o \
	${OBJECTDIR}/Commands/inputCommands/CommandIChangeSubTG.o \
	${OBJECTDIR}/Commands/inputCommands/CommandIFit.o \
	${OBJECTDIR}/Commands/inputCommands/CommandISubStatusField.o \
	${OBJECTDIR}/Commands/inputCommands/CommandIUnfit.o \
	${OBJECTDIR}/NetworkControler.o \
	${OBJECTDIR}/SDatabase.o \
	${OBJECTDIR}/SFunctions.o \
	${OBJECTDIR}/SGlobals.o \
	${OBJECTDIR}/SItems/SItem.o \
	${OBJECTDIR}/SItems/SItemType.o \
	${OBJECTDIR}/Sspacebjects/Ordres/CommandOrderThread.o \
	${OBJECTDIR}/Sspacebjects/Ordres/Compiler/CommandCompiler.o \
	${OBJECTDIR}/Sspacebjects/Ordres/Compiler/CompilerEmitAssist.o \
	${OBJECTDIR}/Sspacebjects/Ordres/Compiler/SOrderCompilerVisitor.o \
	${OBJECTDIR}/Sspacebjects/Ordres/Compiler/SOrderProgramPrinter.o \
	${OBJECTDIR}/Sspacebjects/Ordres/Compiler/TypeChecker.o \
	${OBJECTDIR}/Sspacebjects/Ordres/Generated/Lexer.o \
	${OBJECTDIR}/Sspacebjects/Ordres/Generated/Parser.o \
	${OBJECTDIR}/Sspacebjects/Ordres/Nodes/SOrderVisit.o \
	${OBJECTDIR}/Sspacebjects/Ordres/SOrderSystemCalls.o \
	${OBJECTDIR}/Sspacebjects/Ordres/SOrdreAction.o \
	${OBJECTDIR}/Sspacebjects/Ordres/SOrdreActionMoveTo.o \
	${OBJECTDIR}/Sspacebjects/Ordres/SOrdreActionTrasfereCargo.o \
	${OBJECTDIR}/Sspacebjects/Ordres/SOrdreCondition.o \
	${OBJECTDIR}/Sspacebjects/Ordres/SOrdreConditionAND.o \
	${OBJECTDIR}/Sspacebjects/Ordres/SOrdreConditionOR.o \
	${OBJECTDIR}/Sspacebjects/Ordres/SOrdreConditionStatOp.o \
	${OBJECTDIR}/Sspacebjects/Ordres/SOrdreConditionUnitEqTo.o \
	${OBJECTDIR}/Sspacebjects/Ordres/SOrdreProgram.o \
	${OBJECTDIR}/Sspacebjects/Ordres/SOrdreRule.o \
	${OBJECTDIR}/Sspacebjects/Ordres/Terminals/SOrderIntegerLiteral.o \
	${OBJECTDIR}/Sspacebjects/Ordres/Utils/SOrderDotBuilder.o \
	${OBJECTDIR}/Sspacebjects/Ordres/Utils/SOrderSourcePosition.o \
	${OBJECTDIR}/Sspacebjects/Ordres/Utils/SOrderVisitor.o \
	${OBJECTDIR}/Sspacebjects/SAstoroid.o \
	${OBJECTDIR}/Sspacebjects/SAstoroidBelt.o \
	${OBJECTDIR}/Sspacebjects/SAstoroidType.o \
	${OBJECTDIR}/Sspacebjects/SFighter.o \
	${OBJECTDIR}/Sspacebjects/SFighterType.o \
	${OBJECTDIR}/Sspacebjects/SMetaObj.o \
	${OBJECTDIR}/Sspacebjects/SMetaShot.o \
	${OBJECTDIR}/Sspacebjects/SMovable.o \
	${OBJECTDIR}/Sspacebjects/SObj.o \
	${OBJECTDIR}/Sspacebjects/SOrdres.o \
	${OBJECTDIR}/Sspacebjects/SPos.o \
	${OBJECTDIR}/Sspacebjects/SProgrammable.o \
	${OBJECTDIR}/Sspacebjects/SShip.o \
	${OBJECTDIR}/Sspacebjects/SShipType.o \
	${OBJECTDIR}/Sspacebjects/SShot.o \
	${OBJECTDIR}/Sspacebjects/SSubAble.o \
	${OBJECTDIR}/Sspacebjects/STargetable.o \
	${OBJECTDIR}/Sspacebjects/SUnit.o \
	${OBJECTDIR}/Sspacebjects/SUnitType.o \
	${OBJECTDIR}/Sspacebjects/cargo/SCargoBay.o \
	${OBJECTDIR}/Sspacebjects/subsystems/SLoadout.o \
	${OBJECTDIR}/Sspacebjects/subsystems/SShipTypeSlotData.o \
	${OBJECTDIR}/Sspacebjects/subsystems/SSingleFac.o \
	${OBJECTDIR}/Sspacebjects/subsystems/SSingleRef.o \
	${OBJECTDIR}/Sspacebjects/subsystems/SSingleWep.o \
	${OBJECTDIR}/Sspacebjects/subsystems/SSlotNode.o \
	${OBJECTDIR}/Sspacebjects/subsystems/SSubSystem.o \
	${OBJECTDIR}/Sspacebjects/subsystems/SSubSystemBonus.o \
	${OBJECTDIR}/Sspacebjects/subsystems/SSubSystemBoost.o \
	${OBJECTDIR}/Sspacebjects/subsystems/SSubSystemFac.o \
	${OBJECTDIR}/Sspacebjects/subsystems/SSubSystemFighter.o \
	${OBJECTDIR}/Sspacebjects/subsystems/SSubSystemRef.o \
	${OBJECTDIR}/Sspacebjects/subsystems/SSubSystemW.o \
	${OBJECTDIR}/Sspacebjects/subsystems/SSubType.o \
	${OBJECTDIR}/Sspacebjects/subsystems/SSubTypeBonus.o \
	${OBJECTDIR}/Sspacebjects/subsystems/SSubTypeBoost.o \
	${OBJECTDIR}/Sspacebjects/subsystems/SSubTypeFac.o \
	${OBJECTDIR}/Sspacebjects/subsystems/SSubTypeFighter.o \
	${OBJECTDIR}/Sspacebjects/subsystems/SSubTypeRef.o \
	${OBJECTDIR}/Sspacebjects/subsystems/SSubTypeWep.o \
	${OBJECTDIR}/World/Destiny/Destiny.o \
	${OBJECTDIR}/World/Destiny/QTreeIndex.o \
	${OBJECTDIR}/World/SGrid.o \
	${OBJECTDIR}/World/SWorld.o \
	${OBJECTDIR}/mainServer.o


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

${OBJECTDIR}/_ext/2098112761/GFunctions.o: ../GShare/GFunctions.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2098112761
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/2098112761/GFunctions.o ../GShare/GFunctions.cpp

${OBJECTDIR}/_ext/2098112761/GGlobals.o: ../GShare/GGlobals.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2098112761
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/2098112761/GGlobals.o ../GShare/GGlobals.cpp

${OBJECTDIR}/Client.o: Client.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Client.o Client.cpp

${OBJECTDIR}/Commands/CargoCommands/CommandCargoAdd.o: Commands/CargoCommands/CommandCargoAdd.cpp 
	${MKDIR} -p ${OBJECTDIR}/Commands/CargoCommands
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Commands/CargoCommands/CommandCargoAdd.o Commands/CargoCommands/CommandCargoAdd.cpp

${OBJECTDIR}/Commands/CargoCommands/CommandCargoTransOnReciver.o: Commands/CargoCommands/CommandCargoTransOnReciver.cpp 
	${MKDIR} -p ${OBJECTDIR}/Commands/CargoCommands
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Commands/CargoCommands/CommandCargoTransOnReciver.o Commands/CargoCommands/CommandCargoTransOnReciver.cpp

${OBJECTDIR}/Commands/CargoCommands/CommandCargoTransOnSender.o: Commands/CargoCommands/CommandCargoTransOnSender.cpp 
	${MKDIR} -p ${OBJECTDIR}/Commands/CargoCommands
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Commands/CargoCommands/CommandCargoTransOnSender.o Commands/CargoCommands/CommandCargoTransOnSender.cpp

${OBJECTDIR}/Commands/CargoCommands/CommandCargoTransfere.o: Commands/CargoCommands/CommandCargoTransfere.cpp 
	${MKDIR} -p ${OBJECTDIR}/Commands/CargoCommands
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Commands/CargoCommands/CommandCargoTransfere.o Commands/CargoCommands/CommandCargoTransfere.cpp

${OBJECTDIR}/Commands/Command.o: Commands/Command.cpp 
	${MKDIR} -p ${OBJECTDIR}/Commands
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Commands/Command.o Commands/Command.cpp

${OBJECTDIR}/Commands/CommandAdd.o: Commands/CommandAdd.cpp 
	${MKDIR} -p ${OBJECTDIR}/Commands
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Commands/CommandAdd.o Commands/CommandAdd.cpp

${OBJECTDIR}/Commands/CommandAddSubscriptions.o: Commands/CommandAddSubscriptions.cpp 
	${MKDIR} -p ${OBJECTDIR}/Commands
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Commands/CommandAddSubscriptions.o Commands/CommandAddSubscriptions.cpp

${OBJECTDIR}/Commands/CommandClientSubscription.o: Commands/CommandClientSubscription.cpp 
	${MKDIR} -p ${OBJECTDIR}/Commands
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Commands/CommandClientSubscription.o Commands/CommandClientSubscription.cpp

${OBJECTDIR}/Commands/CommandEnterGrid.o: Commands/CommandEnterGrid.cpp 
	${MKDIR} -p ${OBJECTDIR}/Commands
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Commands/CommandEnterGrid.o Commands/CommandEnterGrid.cpp

${OBJECTDIR}/Commands/CommandExitGrid.o: Commands/CommandExitGrid.cpp 
	${MKDIR} -p ${OBJECTDIR}/Commands
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Commands/CommandExitGrid.o Commands/CommandExitGrid.cpp

${OBJECTDIR}/Commands/CommandHit.o: Commands/CommandHit.cpp 
	${MKDIR} -p ${OBJECTDIR}/Commands
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Commands/CommandHit.o Commands/CommandHit.cpp

${OBJECTDIR}/Commands/CommandInitShot.o: Commands/CommandInitShot.cpp 
	${MKDIR} -p ${OBJECTDIR}/Commands
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Commands/CommandInitShot.o Commands/CommandInitShot.cpp

${OBJECTDIR}/Commands/CommandMetaHit.o: Commands/CommandMetaHit.cpp 
	${MKDIR} -p ${OBJECTDIR}/Commands
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Commands/CommandMetaHit.o Commands/CommandMetaHit.cpp

${OBJECTDIR}/Commands/CommandProcesMetas.o: Commands/CommandProcesMetas.cpp 
	${MKDIR} -p ${OBJECTDIR}/Commands
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Commands/CommandProcesMetas.o Commands/CommandProcesMetas.cpp

${OBJECTDIR}/Commands/CommandProcessor.o: Commands/CommandProcessor.cpp 
	${MKDIR} -p ${OBJECTDIR}/Commands
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Commands/CommandProcessor.o Commands/CommandProcessor.cpp

${OBJECTDIR}/Commands/CommandQueryCmp.o: Commands/CommandQueryCmp.cpp 
	${MKDIR} -p ${OBJECTDIR}/Commands
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Commands/CommandQueryCmp.o Commands/CommandQueryCmp.cpp

${OBJECTDIR}/Commands/CommandRemove.o: Commands/CommandRemove.cpp 
	${MKDIR} -p ${OBJECTDIR}/Commands
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Commands/CommandRemove.o Commands/CommandRemove.cpp

${OBJECTDIR}/Commands/CommandSignalFighter.o: Commands/CommandSignalFighter.cpp 
	${MKDIR} -p ${OBJECTDIR}/Commands
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Commands/CommandSignalFighter.o Commands/CommandSignalFighter.cpp

${OBJECTDIR}/Commands/CommandTargetPosUpdate.o: Commands/CommandTargetPosUpdate.cpp 
	${MKDIR} -p ${OBJECTDIR}/Commands
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Commands/CommandTargetPosUpdate.o Commands/CommandTargetPosUpdate.cpp

${OBJECTDIR}/Commands/CommandTimedSubscribeUpdate.o: Commands/CommandTimedSubscribeUpdate.cpp 
	${MKDIR} -p ${OBJECTDIR}/Commands
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Commands/CommandTimedSubscribeUpdate.o Commands/CommandTimedSubscribeUpdate.cpp

${OBJECTDIR}/Commands/CommandTransfere.o: Commands/CommandTransfere.cpp 
	${MKDIR} -p ${OBJECTDIR}/Commands
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Commands/CommandTransfere.o Commands/CommandTransfere.cpp

${OBJECTDIR}/Commands/CommandUpdateMetas.o: Commands/CommandUpdateMetas.cpp 
	${MKDIR} -p ${OBJECTDIR}/Commands
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Commands/CommandUpdateMetas.o Commands/CommandUpdateMetas.cpp

${OBJECTDIR}/Commands/Processable.o: Commands/Processable.cpp 
	${MKDIR} -p ${OBJECTDIR}/Commands
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Commands/Processable.o Commands/Processable.cpp

${OBJECTDIR}/Commands/Processor.o: Commands/Processor.cpp 
	${MKDIR} -p ${OBJECTDIR}/Commands
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Commands/Processor.o Commands/Processor.cpp

${OBJECTDIR}/Commands/Query/CommandQuery.o: Commands/Query/CommandQuery.cpp 
	${MKDIR} -p ${OBJECTDIR}/Commands/Query
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Commands/Query/CommandQuery.o Commands/Query/CommandQuery.cpp

${OBJECTDIR}/Commands/Query/CommandQueryRsp.o: Commands/Query/CommandQueryRsp.cpp 
	${MKDIR} -p ${OBJECTDIR}/Commands/Query
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Commands/Query/CommandQueryRsp.o Commands/Query/CommandQueryRsp.cpp

${OBJECTDIR}/Commands/inputCommands/CommandIChangeOrders.o: Commands/inputCommands/CommandIChangeOrders.cpp 
	${MKDIR} -p ${OBJECTDIR}/Commands/inputCommands
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Commands/inputCommands/CommandIChangeOrders.o Commands/inputCommands/CommandIChangeOrders.cpp

${OBJECTDIR}/Commands/inputCommands/CommandIChangeSubTG.o: Commands/inputCommands/CommandIChangeSubTG.cpp 
	${MKDIR} -p ${OBJECTDIR}/Commands/inputCommands
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Commands/inputCommands/CommandIChangeSubTG.o Commands/inputCommands/CommandIChangeSubTG.cpp

${OBJECTDIR}/Commands/inputCommands/CommandIFit.o: Commands/inputCommands/CommandIFit.cpp 
	${MKDIR} -p ${OBJECTDIR}/Commands/inputCommands
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Commands/inputCommands/CommandIFit.o Commands/inputCommands/CommandIFit.cpp

${OBJECTDIR}/Commands/inputCommands/CommandISubStatusField.o: Commands/inputCommands/CommandISubStatusField.cpp 
	${MKDIR} -p ${OBJECTDIR}/Commands/inputCommands
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Commands/inputCommands/CommandISubStatusField.o Commands/inputCommands/CommandISubStatusField.cpp

${OBJECTDIR}/Commands/inputCommands/CommandIUnfit.o: Commands/inputCommands/CommandIUnfit.cpp 
	${MKDIR} -p ${OBJECTDIR}/Commands/inputCommands
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Commands/inputCommands/CommandIUnfit.o Commands/inputCommands/CommandIUnfit.cpp

${OBJECTDIR}/NetworkControler.o: NetworkControler.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/NetworkControler.o NetworkControler.cpp

${OBJECTDIR}/SDatabase.o: SDatabase.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SDatabase.o SDatabase.cpp

${OBJECTDIR}/SFunctions.o: SFunctions.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SFunctions.o SFunctions.cpp

${OBJECTDIR}/SGlobals.o: SGlobals.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SGlobals.o SGlobals.cpp

${OBJECTDIR}/SItems/SItem.o: SItems/SItem.cpp 
	${MKDIR} -p ${OBJECTDIR}/SItems
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SItems/SItem.o SItems/SItem.cpp

${OBJECTDIR}/SItems/SItemType.o: SItems/SItemType.cpp 
	${MKDIR} -p ${OBJECTDIR}/SItems
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SItems/SItemType.o SItems/SItemType.cpp

${OBJECTDIR}/Sspacebjects/Ordres/CommandOrderThread.o: Sspacebjects/Ordres/CommandOrderThread.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects/Ordres
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sspacebjects/Ordres/CommandOrderThread.o Sspacebjects/Ordres/CommandOrderThread.cpp

${OBJECTDIR}/Sspacebjects/Ordres/Compiler/CommandCompiler.o: Sspacebjects/Ordres/Compiler/CommandCompiler.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects/Ordres/Compiler
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sspacebjects/Ordres/Compiler/CommandCompiler.o Sspacebjects/Ordres/Compiler/CommandCompiler.cpp

${OBJECTDIR}/Sspacebjects/Ordres/Compiler/CompilerEmitAssist.o: Sspacebjects/Ordres/Compiler/CompilerEmitAssist.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects/Ordres/Compiler
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sspacebjects/Ordres/Compiler/CompilerEmitAssist.o Sspacebjects/Ordres/Compiler/CompilerEmitAssist.cpp

${OBJECTDIR}/Sspacebjects/Ordres/Compiler/SOrderCompilerVisitor.o: Sspacebjects/Ordres/Compiler/SOrderCompilerVisitor.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects/Ordres/Compiler
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sspacebjects/Ordres/Compiler/SOrderCompilerVisitor.o Sspacebjects/Ordres/Compiler/SOrderCompilerVisitor.cpp

${OBJECTDIR}/Sspacebjects/Ordres/Compiler/SOrderProgramPrinter.o: Sspacebjects/Ordres/Compiler/SOrderProgramPrinter.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects/Ordres/Compiler
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sspacebjects/Ordres/Compiler/SOrderProgramPrinter.o Sspacebjects/Ordres/Compiler/SOrderProgramPrinter.cpp

${OBJECTDIR}/Sspacebjects/Ordres/Compiler/TypeChecker.o: Sspacebjects/Ordres/Compiler/TypeChecker.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects/Ordres/Compiler
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sspacebjects/Ordres/Compiler/TypeChecker.o Sspacebjects/Ordres/Compiler/TypeChecker.cpp

${OBJECTDIR}/Sspacebjects/Ordres/Generated/Lexer.o: Sspacebjects/Ordres/Generated/Lexer.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects/Ordres/Generated
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sspacebjects/Ordres/Generated/Lexer.o Sspacebjects/Ordres/Generated/Lexer.cpp

${OBJECTDIR}/Sspacebjects/Ordres/Generated/Parser.o: Sspacebjects/Ordres/Generated/Parser.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects/Ordres/Generated
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sspacebjects/Ordres/Generated/Parser.o Sspacebjects/Ordres/Generated/Parser.cpp

${OBJECTDIR}/Sspacebjects/Ordres/Nodes/SOrderVisit.o: Sspacebjects/Ordres/Nodes/SOrderVisit.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects/Ordres/Nodes
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sspacebjects/Ordres/Nodes/SOrderVisit.o Sspacebjects/Ordres/Nodes/SOrderVisit.cpp

${OBJECTDIR}/Sspacebjects/Ordres/SOrderSystemCalls.o: Sspacebjects/Ordres/SOrderSystemCalls.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects/Ordres
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sspacebjects/Ordres/SOrderSystemCalls.o Sspacebjects/Ordres/SOrderSystemCalls.cpp

${OBJECTDIR}/Sspacebjects/Ordres/SOrdreAction.o: Sspacebjects/Ordres/SOrdreAction.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects/Ordres
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sspacebjects/Ordres/SOrdreAction.o Sspacebjects/Ordres/SOrdreAction.cpp

${OBJECTDIR}/Sspacebjects/Ordres/SOrdreActionMoveTo.o: Sspacebjects/Ordres/SOrdreActionMoveTo.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects/Ordres
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sspacebjects/Ordres/SOrdreActionMoveTo.o Sspacebjects/Ordres/SOrdreActionMoveTo.cpp

${OBJECTDIR}/Sspacebjects/Ordres/SOrdreActionTrasfereCargo.o: Sspacebjects/Ordres/SOrdreActionTrasfereCargo.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects/Ordres
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sspacebjects/Ordres/SOrdreActionTrasfereCargo.o Sspacebjects/Ordres/SOrdreActionTrasfereCargo.cpp

${OBJECTDIR}/Sspacebjects/Ordres/SOrdreCondition.o: Sspacebjects/Ordres/SOrdreCondition.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects/Ordres
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sspacebjects/Ordres/SOrdreCondition.o Sspacebjects/Ordres/SOrdreCondition.cpp

${OBJECTDIR}/Sspacebjects/Ordres/SOrdreConditionAND.o: Sspacebjects/Ordres/SOrdreConditionAND.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects/Ordres
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sspacebjects/Ordres/SOrdreConditionAND.o Sspacebjects/Ordres/SOrdreConditionAND.cpp

${OBJECTDIR}/Sspacebjects/Ordres/SOrdreConditionOR.o: Sspacebjects/Ordres/SOrdreConditionOR.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects/Ordres
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sspacebjects/Ordres/SOrdreConditionOR.o Sspacebjects/Ordres/SOrdreConditionOR.cpp

${OBJECTDIR}/Sspacebjects/Ordres/SOrdreConditionStatOp.o: Sspacebjects/Ordres/SOrdreConditionStatOp.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects/Ordres
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sspacebjects/Ordres/SOrdreConditionStatOp.o Sspacebjects/Ordres/SOrdreConditionStatOp.cpp

${OBJECTDIR}/Sspacebjects/Ordres/SOrdreConditionUnitEqTo.o: Sspacebjects/Ordres/SOrdreConditionUnitEqTo.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects/Ordres
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sspacebjects/Ordres/SOrdreConditionUnitEqTo.o Sspacebjects/Ordres/SOrdreConditionUnitEqTo.cpp

${OBJECTDIR}/Sspacebjects/Ordres/SOrdreProgram.o: Sspacebjects/Ordres/SOrdreProgram.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects/Ordres
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sspacebjects/Ordres/SOrdreProgram.o Sspacebjects/Ordres/SOrdreProgram.cpp

${OBJECTDIR}/Sspacebjects/Ordres/SOrdreRule.o: Sspacebjects/Ordres/SOrdreRule.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects/Ordres
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sspacebjects/Ordres/SOrdreRule.o Sspacebjects/Ordres/SOrdreRule.cpp

${OBJECTDIR}/Sspacebjects/Ordres/Terminals/SOrderIntegerLiteral.o: Sspacebjects/Ordres/Terminals/SOrderIntegerLiteral.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects/Ordres/Terminals
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sspacebjects/Ordres/Terminals/SOrderIntegerLiteral.o Sspacebjects/Ordres/Terminals/SOrderIntegerLiteral.cpp

${OBJECTDIR}/Sspacebjects/Ordres/Utils/SOrderDotBuilder.o: Sspacebjects/Ordres/Utils/SOrderDotBuilder.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects/Ordres/Utils
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sspacebjects/Ordres/Utils/SOrderDotBuilder.o Sspacebjects/Ordres/Utils/SOrderDotBuilder.cpp

${OBJECTDIR}/Sspacebjects/Ordres/Utils/SOrderSourcePosition.o: Sspacebjects/Ordres/Utils/SOrderSourcePosition.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects/Ordres/Utils
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sspacebjects/Ordres/Utils/SOrderSourcePosition.o Sspacebjects/Ordres/Utils/SOrderSourcePosition.cpp

${OBJECTDIR}/Sspacebjects/Ordres/Utils/SOrderVisitor.o: Sspacebjects/Ordres/Utils/SOrderVisitor.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects/Ordres/Utils
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sspacebjects/Ordres/Utils/SOrderVisitor.o Sspacebjects/Ordres/Utils/SOrderVisitor.cpp

${OBJECTDIR}/Sspacebjects/SAstoroid.o: Sspacebjects/SAstoroid.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sspacebjects/SAstoroid.o Sspacebjects/SAstoroid.cpp

${OBJECTDIR}/Sspacebjects/SAstoroidBelt.o: Sspacebjects/SAstoroidBelt.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sspacebjects/SAstoroidBelt.o Sspacebjects/SAstoroidBelt.cpp

${OBJECTDIR}/Sspacebjects/SAstoroidType.o: Sspacebjects/SAstoroidType.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sspacebjects/SAstoroidType.o Sspacebjects/SAstoroidType.cpp

${OBJECTDIR}/Sspacebjects/SFighter.o: Sspacebjects/SFighter.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sspacebjects/SFighter.o Sspacebjects/SFighter.cpp

${OBJECTDIR}/Sspacebjects/SFighterType.o: Sspacebjects/SFighterType.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sspacebjects/SFighterType.o Sspacebjects/SFighterType.cpp

${OBJECTDIR}/Sspacebjects/SMetaObj.o: Sspacebjects/SMetaObj.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sspacebjects/SMetaObj.o Sspacebjects/SMetaObj.cpp

${OBJECTDIR}/Sspacebjects/SMetaShot.o: Sspacebjects/SMetaShot.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sspacebjects/SMetaShot.o Sspacebjects/SMetaShot.cpp

${OBJECTDIR}/Sspacebjects/SMovable.o: Sspacebjects/SMovable.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sspacebjects/SMovable.o Sspacebjects/SMovable.cpp

${OBJECTDIR}/Sspacebjects/SObj.o: Sspacebjects/SObj.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sspacebjects/SObj.o Sspacebjects/SObj.cpp

${OBJECTDIR}/Sspacebjects/SOrdres.o: Sspacebjects/SOrdres.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sspacebjects/SOrdres.o Sspacebjects/SOrdres.cpp

${OBJECTDIR}/Sspacebjects/SPos.o: Sspacebjects/SPos.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sspacebjects/SPos.o Sspacebjects/SPos.cpp

${OBJECTDIR}/Sspacebjects/SProgrammable.o: Sspacebjects/SProgrammable.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sspacebjects/SProgrammable.o Sspacebjects/SProgrammable.cpp

${OBJECTDIR}/Sspacebjects/SShip.o: Sspacebjects/SShip.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sspacebjects/SShip.o Sspacebjects/SShip.cpp

${OBJECTDIR}/Sspacebjects/SShipType.o: Sspacebjects/SShipType.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sspacebjects/SShipType.o Sspacebjects/SShipType.cpp

${OBJECTDIR}/Sspacebjects/SShot.o: Sspacebjects/SShot.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sspacebjects/SShot.o Sspacebjects/SShot.cpp

${OBJECTDIR}/Sspacebjects/SSubAble.o: Sspacebjects/SSubAble.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sspacebjects/SSubAble.o Sspacebjects/SSubAble.cpp

${OBJECTDIR}/Sspacebjects/STargetable.o: Sspacebjects/STargetable.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sspacebjects/STargetable.o Sspacebjects/STargetable.cpp

${OBJECTDIR}/Sspacebjects/SUnit.o: Sspacebjects/SUnit.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sspacebjects/SUnit.o Sspacebjects/SUnit.cpp

${OBJECTDIR}/Sspacebjects/SUnitType.o: Sspacebjects/SUnitType.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sspacebjects/SUnitType.o Sspacebjects/SUnitType.cpp

${OBJECTDIR}/Sspacebjects/cargo/SCargoBay.o: Sspacebjects/cargo/SCargoBay.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects/cargo
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sspacebjects/cargo/SCargoBay.o Sspacebjects/cargo/SCargoBay.cpp

${OBJECTDIR}/Sspacebjects/subsystems/SLoadout.o: Sspacebjects/subsystems/SLoadout.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects/subsystems
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sspacebjects/subsystems/SLoadout.o Sspacebjects/subsystems/SLoadout.cpp

${OBJECTDIR}/Sspacebjects/subsystems/SShipTypeSlotData.o: Sspacebjects/subsystems/SShipTypeSlotData.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects/subsystems
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sspacebjects/subsystems/SShipTypeSlotData.o Sspacebjects/subsystems/SShipTypeSlotData.cpp

${OBJECTDIR}/Sspacebjects/subsystems/SSingleFac.o: Sspacebjects/subsystems/SSingleFac.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects/subsystems
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sspacebjects/subsystems/SSingleFac.o Sspacebjects/subsystems/SSingleFac.cpp

${OBJECTDIR}/Sspacebjects/subsystems/SSingleRef.o: Sspacebjects/subsystems/SSingleRef.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects/subsystems
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sspacebjects/subsystems/SSingleRef.o Sspacebjects/subsystems/SSingleRef.cpp

${OBJECTDIR}/Sspacebjects/subsystems/SSingleWep.o: Sspacebjects/subsystems/SSingleWep.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects/subsystems
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sspacebjects/subsystems/SSingleWep.o Sspacebjects/subsystems/SSingleWep.cpp

${OBJECTDIR}/Sspacebjects/subsystems/SSlotNode.o: Sspacebjects/subsystems/SSlotNode.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects/subsystems
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sspacebjects/subsystems/SSlotNode.o Sspacebjects/subsystems/SSlotNode.cpp

${OBJECTDIR}/Sspacebjects/subsystems/SSubSystem.o: Sspacebjects/subsystems/SSubSystem.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects/subsystems
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sspacebjects/subsystems/SSubSystem.o Sspacebjects/subsystems/SSubSystem.cpp

${OBJECTDIR}/Sspacebjects/subsystems/SSubSystemBonus.o: Sspacebjects/subsystems/SSubSystemBonus.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects/subsystems
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sspacebjects/subsystems/SSubSystemBonus.o Sspacebjects/subsystems/SSubSystemBonus.cpp

${OBJECTDIR}/Sspacebjects/subsystems/SSubSystemBoost.o: Sspacebjects/subsystems/SSubSystemBoost.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects/subsystems
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sspacebjects/subsystems/SSubSystemBoost.o Sspacebjects/subsystems/SSubSystemBoost.cpp

${OBJECTDIR}/Sspacebjects/subsystems/SSubSystemFac.o: Sspacebjects/subsystems/SSubSystemFac.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects/subsystems
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sspacebjects/subsystems/SSubSystemFac.o Sspacebjects/subsystems/SSubSystemFac.cpp

${OBJECTDIR}/Sspacebjects/subsystems/SSubSystemFighter.o: Sspacebjects/subsystems/SSubSystemFighter.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects/subsystems
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sspacebjects/subsystems/SSubSystemFighter.o Sspacebjects/subsystems/SSubSystemFighter.cpp

${OBJECTDIR}/Sspacebjects/subsystems/SSubSystemRef.o: Sspacebjects/subsystems/SSubSystemRef.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects/subsystems
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sspacebjects/subsystems/SSubSystemRef.o Sspacebjects/subsystems/SSubSystemRef.cpp

${OBJECTDIR}/Sspacebjects/subsystems/SSubSystemW.o: Sspacebjects/subsystems/SSubSystemW.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects/subsystems
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sspacebjects/subsystems/SSubSystemW.o Sspacebjects/subsystems/SSubSystemW.cpp

${OBJECTDIR}/Sspacebjects/subsystems/SSubType.o: Sspacebjects/subsystems/SSubType.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects/subsystems
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sspacebjects/subsystems/SSubType.o Sspacebjects/subsystems/SSubType.cpp

${OBJECTDIR}/Sspacebjects/subsystems/SSubTypeBonus.o: Sspacebjects/subsystems/SSubTypeBonus.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects/subsystems
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sspacebjects/subsystems/SSubTypeBonus.o Sspacebjects/subsystems/SSubTypeBonus.cpp

${OBJECTDIR}/Sspacebjects/subsystems/SSubTypeBoost.o: Sspacebjects/subsystems/SSubTypeBoost.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects/subsystems
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sspacebjects/subsystems/SSubTypeBoost.o Sspacebjects/subsystems/SSubTypeBoost.cpp

${OBJECTDIR}/Sspacebjects/subsystems/SSubTypeFac.o: Sspacebjects/subsystems/SSubTypeFac.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects/subsystems
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sspacebjects/subsystems/SSubTypeFac.o Sspacebjects/subsystems/SSubTypeFac.cpp

${OBJECTDIR}/Sspacebjects/subsystems/SSubTypeFighter.o: Sspacebjects/subsystems/SSubTypeFighter.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects/subsystems
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sspacebjects/subsystems/SSubTypeFighter.o Sspacebjects/subsystems/SSubTypeFighter.cpp

${OBJECTDIR}/Sspacebjects/subsystems/SSubTypeRef.o: Sspacebjects/subsystems/SSubTypeRef.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects/subsystems
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sspacebjects/subsystems/SSubTypeRef.o Sspacebjects/subsystems/SSubTypeRef.cpp

${OBJECTDIR}/Sspacebjects/subsystems/SSubTypeWep.o: Sspacebjects/subsystems/SSubTypeWep.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sspacebjects/subsystems
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sspacebjects/subsystems/SSubTypeWep.o Sspacebjects/subsystems/SSubTypeWep.cpp

${OBJECTDIR}/World/Destiny/Destiny.o: World/Destiny/Destiny.cpp 
	${MKDIR} -p ${OBJECTDIR}/World/Destiny
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/World/Destiny/Destiny.o World/Destiny/Destiny.cpp

${OBJECTDIR}/World/Destiny/QTreeIndex.o: World/Destiny/QTreeIndex.cpp 
	${MKDIR} -p ${OBJECTDIR}/World/Destiny
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/World/Destiny/QTreeIndex.o World/Destiny/QTreeIndex.cpp

${OBJECTDIR}/World/SGrid.o: World/SGrid.cpp 
	${MKDIR} -p ${OBJECTDIR}/World
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/World/SGrid.o World/SGrid.cpp

${OBJECTDIR}/World/SWorld.o: World/SWorld.cpp 
	${MKDIR} -p ${OBJECTDIR}/World
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/World/SWorld.o World/SWorld.cpp

${OBJECTDIR}/mainServer.o: mainServer.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/mainServer.o mainServer.cpp

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
