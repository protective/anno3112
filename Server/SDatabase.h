/* 
 * File:   SDatabase.h
 * Author: karsten
 *
 * Created on 7. september 2011, 10:46
 */

#ifndef SDATABASE_H
#define	SDATABASE_H
#include "SFunctions.h"
#include "Sspacebjects/subsystems/SSubTypeWep.h"
#include "SItems/SItemType.h"
#include <dirent.h>
class SDatabase {
public:
	SDatabase();
	void LoadAllItems();
	void ReadSubDir(DIR *dp, string datapath);
	void LoadGame();
	virtual ~SDatabase();
private:
	void CheckRefs();
};

#endif	/* SDATABASE_H */

