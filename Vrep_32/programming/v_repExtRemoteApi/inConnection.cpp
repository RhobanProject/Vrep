// This file is part of the REMOTE API
// 
// Copyright 2006-2013 Dr. Marc Andreas Freese. All rights reserved. 
// marc@coppeliarobotics.com
// www.coppeliarobotics.com
// 
// The REMOTE API is licensed under the terms of GNU GPL:
// 
// -------------------------------------------------------------------
// The REMOTE API is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// The REMOTE API is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with the REMOTE API.  If not, see <http://www.gnu.org/licenses/>.
// -------------------------------------------------------------------
//
// This file was automatically created for V-REP release V3.0.1 on January 20th 2013

#include "stdafx.h"
#include "inConnection.h"
#include "simxUtils.h"
#define HEADER_LENGTH 6 // WORD0=1 (to detect endianness), WORD1=packetSize, WORD2=packetsLeftToRead
#define SOCKET_TIMEOUT_READ 10000 // in ms

CInConnection::CInConnection(int theConnectionPort,WORD maxPacketSize/*=250*/)
{
  _socketConnectionPort=theConnectionPort;
  _socketConnectWasOk=false;
  _maxPacketSize=maxPacketSize;
  _otherSideIsBigEndian=false;
  memset(&_socketLocal,0,sizeof(struct sockaddr_in));
#if defined (__linux) || defined (__APPLE__)
  _socketServer=-1;
  _socketClient=-1;
#endif /* __linux || __APPLE__ */
}

CInConnection::~CInConnection()
{
    if (_socketConnectWasOk)
    {
#ifdef _WIN32
      shutdown(_socketClient,SD_BOTH);
      closesocket(_socketServer);
      WSACleanup();
#endif /* _WIN32 */
#if defined (__linux) || defined (__APPLE__)
      if (_socketServer!=-1)
      {
        close(_socketServer);
      }
      if (_socketClient!=-1)
      {
        close(_socketClient);
      }
#endif /* __linux || __APPLE__ */
    }
}

bool CInConnection::connectToClient()
{
#ifdef _WIN32
    // 1. connect to port:
    if (WSAStartup(0x101,&_socketWsaData)!=0)
      return(false);	 // WSAStartup failed.
#endif /* _WIN32 */

    _socketLocal.sin_family=AF_INET;
    _socketLocal.sin_addr.s_addr=INADDR_ANY;
    _socketLocal.sin_port=htons((u_short)_socketConnectionPort);
    _socketServer=socket(AF_INET,SOCK_STREAM,0);
    if (_socketServer==INVALID_SOCKET)
      return(false); // socket failed.

    if (bind(_socketServer,(struct sockaddr*)&_socketLocal,sizeof(_socketLocal))!=0)
      return(false); // bind failed.

    if (listen(_socketServer,10)!=0)
      return(false); // listen failed.

    // 2. accept client:
    struct sockaddr_in from;
    int fromlen=sizeof(from);

    _socketClient=accept(_socketServer,(struct sockaddr*) &from, (_socklen *) &fromlen);
    _socketConnectedMachineIP=inet_ntoa(from.sin_addr);
    _socketTimeOut.tv_sec=1; // 1 second max between successive receive for the same packet
    _socketTimeOut.tv_usec=0;
    FD_ZERO(&_socketTheSet);
    FD_SET(_socketClient,&_socketTheSet);

    _socketConnectWasOk=true;
    return(true);
}

char* CInConnection::receiveMessage(int& messageSize)
{ // Returns the data size if >0, 0=we had a read time out, -1=we have an error
  if (!_socketConnectWasOk)
  {
    messageSize=-1; // error
    return(NULL);
  }
  std::vector<char> receivedData;
  while (true)
  {
    std::vector<char> inDat;
    int result=_receiveSimplePacket(inDat);
    if (result<0)
    {
      messageSize=result+1; // error or read time-out
      return(NULL);
    }
    receivedData.insert(receivedData.end(),inDat.begin(),inDat.end());
    if (result==0)
    { // success
      messageSize=int(receivedData.size());
      char* retBuff=new char[messageSize];
      for (int i=0;i<messageSize;i++)
        retBuff[i]=receivedData[i];
      return(retBuff);
    }
  }
}

bool CInConnection::replyToReceivedMessage(char* message,int messageSize)
{
  if (!_socketConnectWasOk)
    return(false);
  if (messageSize==0)
    return(false);

  // In Following we make sure we don't send too big packets (we might send the data in several packets)
  int packetCount=0;
  int s=messageSize;
  while (s!=0)
  {
    packetCount++;
    if (s>_maxPacketSize-HEADER_LENGTH)
      s-=_maxPacketSize-HEADER_LENGTH;
    else
      s=0;
  }

  s=messageSize;
  int ptr=0;
  while (s!=0)
  {
    packetCount--;
    int sizeToSend=s;
    if (s>_maxPacketSize-HEADER_LENGTH)
      sizeToSend=_maxPacketSize-HEADER_LENGTH;
    s-=sizeToSend;
    if (!_sendSimplePacket(message+ptr,sizeToSend,packetCount))
      return(false);
    ptr+=sizeToSend;
  }
  return(true);
}

std::string CInConnection::getConnectedMachineIP()
{
	if (!_socketConnectWasOk)
		return("NONE (reception line is not open)");
	return(_socketConnectedMachineIP);
}

bool CInConnection::isOtherSideBigEndian()
{
	return(_otherSideIsBigEndian);
}

bool CInConnection::_sendSimplePacket(char* packet,int packetLength,WORD packetsLeft)
{
  if (packetLength==0)
    return(false);
  // Insert the header:
  WORD s=WORD(packetLength);
  char header[HEADER_LENGTH];
  ((WORD*)header)[0]=1; // Allows to detect endianness on the other side
  ((WORD*)header)[1]=littleEndianShortConversion(s,_otherSideIsBigEndian);
  ((WORD*)header)[2]=littleEndianShortConversion(packetsLeft,_otherSideIsBigEndian);

  std::vector<char> toSend;
  for (int i=0;i<HEADER_LENGTH;i++)
    toSend.push_back(header[i]);
  for (int i=0;i<packetLength;i++)
    toSend.push_back(packet[i]);
  // Send the packet:

  return(send(_socketClient,&toSend[0],packetLength+HEADER_LENGTH,0)==packetLength+HEADER_LENGTH);
}

int CInConnection::_receiveSimplePacket(std::vector<char>& packet)
{
    _socketTimeOut.tv_sec=10; // 1 second max between successive receive for the same packet
    _socketTimeOut.tv_usec=0;
    FD_ZERO(&_socketTheSet);
    FD_SET(_socketClient,&_socketTheSet);
#ifdef _WIN32
    int selectResult=select(0,&_socketTheSet,NULL,NULL,&_socketTimeOut);
#endif /* _WIN32 */
#if defined (__linux) || defined (__APPLE__)
    int selectResult=select(_socketClient+1, &_socketTheSet,NULL,NULL,&_socketTimeOut);
#endif /* __linux || __APPLE__ */
    if (selectResult==1)
    {
      //1. Read the header and packet size:
      char headerAndSize[HEADER_LENGTH];
      int totalReceived=0;
      DWORD startT=getTimeInMs();
      while(totalReceived!=HEADER_LENGTH)
      {
        int nb=recv(_socketClient,headerAndSize+totalReceived,HEADER_LENGTH-totalReceived,0);
        if (nb<1)
          break;
        totalReceived+=nb;
        if (getTimeDiffInMs(startT)>SOCKET_TIMEOUT_READ)
          break;
      }
      // 2. Check if the header is consistent:
      if (totalReceived!=HEADER_LENGTH)
        return(-2); // Error reading

      _otherSideIsBigEndian=(((WORD*)headerAndSize)[0]!=1);

       WORD dataLength=littleEndianShortConversion(((WORD*)headerAndSize)[1],_otherSideIsBigEndian);

      // 3. Read the data with correct length:
      packet.clear();
      packet.resize(dataLength,0);
      totalReceived=0;
      startT=getTimeInMs();
      while(totalReceived!=dataLength)
      {
        int nb=recv(_socketClient,&packet[0]+totalReceived,dataLength-totalReceived,0);
        if (nb<1)
          break;
        totalReceived+=nb;
        if (getTimeDiffInMs(startT)>SOCKET_TIMEOUT_READ)
          break;
      }
      if (totalReceived!=dataLength)
        return(-2); // wrong size or nothing received
      return(int(littleEndianShortConversion(((WORD*)headerAndSize)[2],_otherSideIsBigEndian)));
    }
    if (selectResult==0)
      return(-1);
    return(-2);
}
