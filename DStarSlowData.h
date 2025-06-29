/*
*   Copyright (C) 2016,2023,2025 by Jonathan Naylor G4KLX
*
*   This program is free software; you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation; either version 2 of the License, or
*   (at your option) any later version.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program; if not, write to the Free Software
*   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

#ifndef	DStarSlowData_H
#define	DStarSlowData_H

#include "DStarHeader.h"

class CDStarSlowData {
public:
	CDStarSlowData();
	~CDStarSlowData();

	void add(const unsigned char* data);

	CDStarHeader*        getHeader();
	const unsigned char* getText();
	unsigned char        getType() const;

	bool isComplete() const;

	void start();
	void reset();

	void setText(const char* text);
	void getSlowData(unsigned char* data);

private:
	unsigned char* m_header;
	unsigned int   m_ptr;
	unsigned char* m_buffer;
	unsigned char* m_text;
	unsigned int   m_textPtr;
	unsigned char  m_textBits;

	enum class SDD_STATE {
		FIRST,
		SECOND
	};

	SDD_STATE      m_state;
	bool           m_complete;

	void loadHeader();
	void loadText();
};

#endif
