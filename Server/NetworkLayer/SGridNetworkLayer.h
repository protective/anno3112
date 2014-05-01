/* 
 * File:   SGridNetworkLayer.h
 * Author: karsten
 *
 * Created on 13. april 2014, 22:00
 */

#ifndef SGRIDNETWORKLAYER_H
#define	SGRIDNETWORKLAYER_H
#include <list>
using namespace std;
inline void sendGridFull(list<uint32_t>& clients, SGrid* grid){
	//NETWORK*********
	char message[sizeof (SerialGrid)];
	memset(message, 0, sizeof (SerialGrid));

	SerialGrid* data = (SerialGrid*) (message);
	data->_type = SerialType::SerialGrid;
	data->_size = sizeof (SerialGrid);
	data->_Id = grid->_id;
	data->_wight = grid->getWight();
	data->_hight = grid->getHight();
	cerr<<"network ready go send"<<endl;
	for(list<uint32_t>::iterator it = clients.begin(); it != clients.end(); it++){
		networkControl->sendToC(*it,message,sizeof(SerialGrid));
	}
}

inline void sendGridFull(uint32_t client, SGrid* grid){
	list<uint32_t> temp;
	temp.push_back(client);
	sendGridFull(temp, grid);
}

#endif	/* SGRIDNETWORKLAYER_H */

