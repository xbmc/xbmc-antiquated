/*
 *      Copyright (C) 2005-2007 Team XboxMediaCenter
 *      http://www.xboxmediacenter.com
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with GNU Make; see the file COPYING.  If not, write to
 *  the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
 *  http://www.gnu.org/copyleft/gpl.html
 *
 */

#include "stdafx.h"
#include "PlayListB4S.h"
#include "Util.h"

using namespace XFILE;
using namespace PLAYLIST;

/* ------------------------ example b4s playlist file ---------------------------------
 <?xml version="1.0" encoding='UTF-8' standalone="yes"?>
 <WinampXML>
 <!-- Generated by: Nullsoft Winamp3 version 3.0d -->
  <playlist num_entries="2" label="Playlist 001">
   <entry Playstring="file:E:\Program Files\Winamp3\demo.mp3">
    <Name>demo</Name>
    <Length>5982</Length>
   </entry>
   <entry Playstring="file:E:\Program Files\Winamp3\demo.mp3">
    <Name>demo</Name>
    <Length>5982</Length>
   </entry>
  </playlist>
 </WinampXML>
------------------------ end of example b4s playlist file ---------------------------------*/
CPlayListB4S::CPlayListB4S(void)
{}

CPlayListB4S::~CPlayListB4S(void)
{}


bool CPlayListB4S::LoadData(std::istream& stream)
{
  TiXmlDocument xmlDoc;

  stream >> xmlDoc;

  if (xmlDoc.Error())
  {
    CLog::Log(LOGERROR, "Unable to parse B4S info Error: %s", xmlDoc.ErrorDesc());
    return false;
  }

  TiXmlElement* pRootElement = xmlDoc.RootElement();
  if (!pRootElement ) return false;

  TiXmlElement* pPlayListElement = pRootElement->FirstChildElement("playlist");
  if (!pPlayListElement ) return false;
  m_strPlayListName = pPlayListElement->Attribute("label");

  TiXmlElement* pEntryElement = pPlayListElement->FirstChildElement("entry");

  if (!pEntryElement) return false;
  while (pEntryElement)
  {
    CStdString strFileName = pEntryElement->Attribute("Playstring");
    int iColon = strFileName.Find(":");
    if (iColon > 0)
    {
      iColon++;
      strFileName = strFileName.Right((int)strFileName.size() - iColon);
    }
    if (strFileName.size())
    {
      TiXmlNode* pNodeInfo = pEntryElement->FirstChild("Name");
      TiXmlNode* pNodeLength = pEntryElement->FirstChild("Length");
      long lDuration = 0;
      if (pNodeLength)
      {
        lDuration = atol(pNodeLength->FirstChild()->Value());
      }
      if (pNodeInfo)
      {
        CStdString strInfo = pNodeInfo->FirstChild()->Value();
        if (CUtil::IsRemote(m_strBasePath) && g_advancedSettings.m_pathSubstitutions.size() > 0)
          strFileName = CUtil::SubstitutePath(strFileName);
        CUtil::GetQualifiedFilename(m_strBasePath, strFileName);
        CPlayListItem newItem(strInfo, strFileName, lDuration);
        Add(newItem);
      }
    }
    pEntryElement = pEntryElement->NextSiblingElement();
  }
  return true;
}

void CPlayListB4S::Save(const CStdString& strFileName) const
{
  if (!m_vecItems.size()) return ;
  CStdString strPlaylist = strFileName;
  // force HD saved playlists into fatx compliance
  if (CUtil::IsHD(strPlaylist))
    CUtil::GetFatXQualifiedPath(strPlaylist);
  FILE *fd = fopen(strPlaylist.c_str(), "w+");
  if (!fd)
  {
    CLog::Log(LOGERROR, "Could not save B4S playlist: [%s]", strPlaylist.c_str());
    return ;
  }
  fprintf(fd, "<?xml version=%c1.0%c encoding='UTF-8' standalone=%cyes%c?>\n", 34, 34, 34, 34);
  fprintf(fd, "<WinampXML>\n");
  fprintf(fd, "  <playlist num_entries=%c%i%c label=%c%s%c>\n", 34, m_vecItems.size(), 34, 34, m_strPlayListName.c_str(), 34);
  for (int i = 0; i < (int)m_vecItems.size(); ++i)
  {
    const CPlayListItem& item = m_vecItems[i];
    fprintf(fd, "    <entry Playstring=%cfile:%s%c>\n", 34, item.GetFileName().c_str(), 34 );
    fprintf(fd, "      <Name>%s</Name>\n", item.GetDescription().c_str());
    fprintf(fd, "      <Length>%lu</Length>\n", item.GetDuration());
  }
  fprintf(fd, "  </playlist>\n");
  fprintf(fd, "</WinampXML>\n");
  fclose(fd);
}
