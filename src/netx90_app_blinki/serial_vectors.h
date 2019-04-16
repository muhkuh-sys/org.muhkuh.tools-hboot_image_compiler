/***************************************************************************
 *   Copyright (C) 2008 by Christoph Thelen                                *
 *   doc_bacardi@users.sourceforge.net                                     *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/


#ifndef __SERIAL_VECTORS_H__
#define __SERIAL_VECTORS_H__

typedef unsigned char (*PFN_SERIAL_GET_T) (void);
typedef void (*PFN_SERIAL_PUT_T) (unsigned int iChar);
typedef unsigned int (*PFN_SERIAL_PEEK_T) (void);
typedef void (*PFN_SERIAL_FLUSH_T) (void);

#define SERIAL_GET() tSerialVectors.fn.fnGet()
#define SERIAL_PUT(c) tSerialVectors.fn.fnPut(c)
#define SERIAL_PEEK() tSerialVectors.fn.fnPeek()
#define SERIAL_FLUSH() tSerialVectors.fn.fnFlush()

typedef struct
{
	PFN_SERIAL_GET_T fnGet;
	PFN_SERIAL_PUT_T fnPut;
	PFN_SERIAL_PEEK_T fnPeek;
	PFN_SERIAL_FLUSH_T fnFlush;
} SERIAL_COMM_FN_T;

typedef union
{
	SERIAL_COMM_FN_T fn;
	unsigned long aul[4];
} SERIAL_COMM_UI_FN_T;

extern SERIAL_COMM_UI_FN_T tSerialVectors;

#endif	/* __SERIAL_VECTORS_H__ */


