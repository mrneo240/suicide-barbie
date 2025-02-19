/*!  \file kfbxgenericnode.h
 */

#ifndef _FBXSDK_GENERIC_NODE_H_
#define _FBXSDK_GENERIC_NODE_H_

/**************************************************************************************

 Copyright � 2005 - 2006 Autodesk, Inc. and/or its licensors.
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

#include <kaydaradef.h>
#ifndef KFBX_DLL 
	#define KFBX_DLL K_DLLIMPORT
#endif

#include <kaydara.h>

#include <kfbxplugins/kfbxtakenodecontainer.h>

#include <klib/kerror.h>

#include <kbaselib_forward.h>

#include <fbxfilesdk_nsbegin.h>

class KFbxSdkManager;
class KFbxGenericNode_internal;

/** Empty node containing properties.
  * \nosubgrouping
  */
class KFBX_DLL KFbxGenericNode : public KFbxTakeNodeContainer
{
	KFBXOBJECT_DECLARE(KFbxGenericNode);

public:
		/**
		  * \name Error Management
		  */
		//@{

		/** Retrieve error object.
		  *	\return Reference to error object.
		  */
		KError& GetError();

		/** \enum EError Error identifiers.
		  * - \e eERROR
		  * - \e eERROR_COUNT
		  */
		typedef enum 
		{
			eERROR,
			eERROR_COUNT
		} EError;	

		/** Get last error code.
		  *	\return     Last error code.
		  */
		EError GetLastErrorID();

		/** Get last error string.
		  *	\return     Textual description of the last error.
		  */
		char* GetLastErrorString();

		//@}

		/** Return the type ID of this class.
		  * \return     KFbxObject::eGENERIC_NODE.
		  */
		virtual KFbxObject::ENameSpace GetNameSpace() const;

///////////////////////////////////////////////////////////////////////////////
//
//  WARNING!
//
//	Anything beyond these lines may not be documented accurately and is 
// 	subject to change without notice.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef DOXYGEN_SHOULD_SKIP_THIS
		virtual KObject*          GetFbxObject_internal(); 
		virtual KObject const*  GetFbxObject_internal() const;

		// Clone
		virtual KFbxObject* Clone(KFbxObject::ECloneType pCloneType) const;

protected:
		static char const* GetNamePrefix() { return 0; }

		KFbxGenericNode(KFbxSdkManager& pManager, char const* pName);
		virtual ~KFbxGenericNode();

		virtual void Destruct(bool pRecursive, bool pDependents);

		virtual KString		GetTypeName() const;
		virtual KStringList	GetTypeFlags() const;

		void AddChannels(KFbxTakeNode *pTakeNode);
		
		KFbxGenericNode_internal* mPH;
private:
		KError mError;
protected:

		friend class KFbxReaderFbx;
		friend class KFbxReaderFbx6;
		friend class KFbxWriterFbx;
		friend class KFbxWriterFbx6;
		friend class KFbxScene;

#endif // #ifndef DOXYGEN_SHOULD_SKIP_THIS
};

typedef KFbxGenericNode* HKFbxGenericNode;

#include <fbxfilesdk_nsend.h>

#endif // _FBXSDK_GENERIC_NODE_H_


