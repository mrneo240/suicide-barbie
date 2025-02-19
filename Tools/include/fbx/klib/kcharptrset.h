/*!  \file kcharptrset.h
 */

#ifndef _FBXSDK_CHARPTRSET_H_
#define _FBXSDK_CHARPTRSET_H_

/**************************************************************************************

 Copyright � 2001 - 2006 Autodesk, Inc. and/or its licensors.
 All Rights Reserved.

 The coded instructions, statements, computer programs, and/or related material
 (collectively the "Data") in these files contain unpublished information
 proprietary to Autodesk, Inc. and/or its licensors, which is protected by
 Canada and United States of America federal copyright law and by international
 treaties.

 The Data may not be disclosed or distributed to third parties, in whole or in
 part, without the prior written consent of Autodesk, Inc. ("Autodesk").

 THE DATA IS PROVIDED "AS IS" AND WITHOUT WARRANTY.
 ALL WARRANTIES ARE EXPRESSLY EXCLUDED AND DISCLAIMED. AUTODESK MAKES NO
 WARRANTY OF ANY KIND WITH RESPECT TO THE DATA, EXPRESS, IMPLIED OR ARISING
 BY CUSTOM OR TRADE USAGE, AND DISCLAIMS ANY IMPLIED WARRANTIES OF TITLE,
 NON-INFRINGEMENT, MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE OR USE.
 WITHOUT LIMITING THE FOREGOING, AUTODESK DOES NOT WARRANT THAT THE OPERATION
 OF THE DATA WILL BE UNINTERRUPTED OR ERROR FREE.

 IN NO EVENT SHALL AUTODESK, ITS AFFILIATES, PARENT COMPANIES, LICENSORS
 OR SUPPLIERS ("AUTODESK GROUP") BE LIABLE FOR ANY LOSSES, DAMAGES OR EXPENSES
 OF ANY KIND (INCLUDING WITHOUT LIMITATION PUNITIVE OR MULTIPLE DAMAGES OR OTHER
 SPECIAL, DIRECT, INDIRECT, EXEMPLARY, INCIDENTAL, LOSS OF PROFITS, REVENUE
 OR DATA, COST OF COVER OR CONSEQUENTIAL LOSSES OR DAMAGES OF ANY KIND),
 HOWEVER CAUSED, AND REGARDLESS OF THE THEORY OF LIABILITY, WHETHER DERIVED
 FROM CONTRACT, TORT (INCLUDING, BUT NOT LIMITED TO, NEGLIGENCE), OR OTHERWISE,
 ARISING OUT OF OR RELATING TO THE DATA OR ITS USE OR ANY OTHER PERFORMANCE,
 WHETHER OR NOT AUTODESK HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH LOSS
 OR DAMAGE.

**************************************************************************************/

#include <kbaselib_h.h>
#include <kbaselib_nsbegin.h>

    #define KITEM_PER_BLOCK   20

    struct SCharPtrSet;

/** This class contains the data structure support for char pointer set.
  */

	class KBASELIB_DLL KCharPtrSet {
    public:

	/** Class constructor
	*	\param pItemPerBlock Number of item per block. Default is 20.
	  */
		KCharPtrSet( int pItemPerBlock = KITEM_PER_BLOCK );

	/** Class destructor
	  */	    
		~KCharPtrSet();

	/** Add a new item.
	  *	\param pReference char pointer reference to the item.
	  *	\param kReference to the item.
	  */
        void	Add        ( char* pReference, kReference pItem );

	/** Removes an item.
	  *	\param pReference char reference to the item.
  	  * \return true if succes.
	  */
		bool	Remove     ( char* pReference );

	/** Get an item's reference.
	  *	\param pReference char reference to the item.
	  *	\param PIndex index to the item.
  	  * \return kReference to the item, NULL if fails.
	  */
        kReference Get    ( char* pReference, int* PIndex = NULL );

	/** Get an item's reference from index.
	  *	\param PIndex index to the item.
  	  * \return kReference to the item, NULL if fails.
	  */
        kReference& operator[]( int pIndex );
	
	/** Get an item's reference from index.
	  *	\param PIndex index to the item.
  	  * \return kReference to the item, NULL if fails.
	  */
        kReference	GetFromIndex	( int pIndex, char* *pReference = NULL);

	/** Removes an item by index.
	  *	\param pReference char reference to the item.
  	  * \return true if succes.
	  */
        void		RemoveFromIndex	( int pIndex );

   	/** Get the number of item in the array.
	  */
	    inline int	GetCount (){ return mCharPtrSetCount; }

	/** Sorts the array.
	  */        
		void	Sort();

	/** Clears the array.
	  */
        void   Clear();

#ifndef DOXYGEN_SHOULD_SKIP_THIS

    private:
	    // internal functions for CharPtrSets manipulation
	    SCharPtrSet*		FindEqual( char* pReference);


	    SCharPtrSet*		mCharPtrSetrray;
	    int					mCharPtrSetCount;
	    int					mBlockCount;
	    int					mItemPerBlock;
	    bool				mIsChanged;
	    bool				mIsCaseSensitive;
    public:
	    inline void			SetCaseSensitive(bool pIsCaseSensitive) {mIsCaseSensitive=pIsCaseSensitive;}

#endif
    };

#include <kbaselib_nsend.h>

#endif
