/****************************************************************************************
 
   Copyright (C) 2013 Autodesk, Inc.
   All rights reserved.
 
   Use of this software is subject to the terms of the Autodesk license agreement
   provided at the time of installation or download, or which otherwise accompanies
   this software in either electronic or hard copy form.
 
****************************************************************************************/

//! \file fbxsdk.h
#ifndef _FBXSDK_H_
#define _FBXSDK_H_

/**
  * \mainpage FBX SDK Reference
  * <p>
  * \section welcome Welcome to the FBX SDK Reference
  * The FBX SDK Reference contains reference information on every header file, 
  * namespace, class, method, enum, typedef, variable, and other C++ elements 
  * that comprise the FBX software development kit (SDK).
  * <p>
  * The FBX SDK Reference is organized into the following sections:
  * <ul><li>Class List: an alphabetical list of FBX SDK classes
  *     <li>Class Hierarchy: a textual representation of the FBX SDK class structure
  *     <li>Graphical Class Hierarchy: a graphical representation of the FBX SDK class structure
  *     <li>File List: an alphabetical list of all documented header files</ul>
  * <p>
  * \section otherdocumentation Other Documentation
  * Apart from this reference guide, an FBX SDK Programming Guide and many FBX 
  * SDK examples are also provided.
  * <p>
  * \section aboutFBXSDK About the FBX SDK
  * The FBX SDK is a C++ software development kit (SDK) that lets you import 
  * and export 3D scenes using the Autodesk FBX file format. The FBX SDK 
  * reads FBX files created with FiLMBOX version 2.5 and later and writes FBX 
  * files compatible with MotionBuilder version 6.0 and up. 
  */

#pragma pack(push, 8)	//FBXSDK is compiled with default value (8)

#include <fbxsdk_def.h>

#ifndef FBXSDK_NAMESPACE_USING
	#define FBXSDK_NAMESPACE_USING 1
#endif

//---------------------------------------------------------------------------------------
//Core Base Includes
#include <core/base/fbxarray.h>
#include <core/base/fbxbitset.h>
#include <core/base/fbxcharptrset.h>
#include <core/base/fbxcontainerallocators.h>
#include <core/base/fbxdynamicarray.h>
#include <core/base/fbxstatus.h>
#include <core/base/fbxfile.h>
#ifndef FBXSDK_ENV_WINSTORE
	#include <core/base/fbxfolder.h>
#endif
#include <core/base/fbxhashmap.h>
#include <core/base/fbxintrusivelist.h>
#include <core/base/fbxmap.h>
#include <core/base/fbxmemorypool.h>
#include <core/base/fbxpair.h>
#include <core/base/fbxset.h>
#include <core/base/fbxstring.h>
#include <core/base/fbxstringlist.h>
#include <core/base/fbxtime.h>
#include <core/base/fbxtimecode.h>
#include <core/base/fbxutils.h>

//---------------------------------------------------------------------------------------
//Core Math Includes
#include <core/math/fbxmath.h>
#include <core/math/fbxdualquaternion.h>
#include <core/math/fbxmatrix.h>
#include <core/math/fbxquaternion.h>
#include <core/math/fbxvector2.h>
#include <core/math/fbxvector4.h>

//---------------------------------------------------------------------------------------
//Core Sync Includes
#ifndef FBXSDK_ENV_WINSTORE
	#include <core/sync/fbxatomic.h>
	#include <core/sync/fbxclock.h>
	#include <core/sync/fbxsync.h>
	#include <core/sync/fbxthread.h>
#endif /* !FBXSDK_ENV_WINSTORE */

//---------------------------------------------------------------------------------------
//Core Includes
#include <core/fbxclassid.h>
#include <core/fbxconnectionpoint.h>
#include <core/fbxdatatypes.h>
#ifndef FBXSDK_ENV_WINSTORE
	#include <core/fbxmodule.h>
	#include <core/fbxloadingstrategy.h>
#endif /* !FBXSDK_ENV_WINSTORE */
#include <core/fbxmanager.h>
#include <core/fbxobject.h>
#include <core/fbxperipheral.h>
#ifndef FBXSDK_ENV_WINSTORE
	#include <core/fbxplugin.h>
	#include <core/fbxplugincontainer.h>
#endif /* !FBXSDK_ENV_WINSTORE */
#include <core/fbxproperty.h>
#include <core/fbxpropertydef.h>
#include <core/fbxpropertyhandle.h>
#include <core/fbxpropertypage.h>
#include <core/fbxpropertytypes.h>
#include <core/fbxquery.h>
#include <core/fbxqueryevent.h>
#ifndef FBXSDK_ENV_WINSTORE
	#include <core/fbxscopedloadingdirectory.h>
	#include <core/fbxscopedloadingfilename.h>
#endif /* !FBXSDK_ENV_WINSTORE */
#include <core/fbxxref.h>

//---------------------------------------------------------------------------------------
//File I/O Includes
#include <fileio/fbxexporter.h>
#include <fileio/fbxexternaldocreflistener.h>
#include <fileio/fbxfiletokens.h>
#include <fileio/fbxglobalcamerasettings.h>
#include <fileio/fbxgloballightsettings.h>
#include <fileio/fbxgobo.h>
#include <fileio/fbximporter.h>
#include <fileio/fbxiobase.h>
#include <fileio/fbxiopluginregistry.h>
#include <fileio/fbxiosettings.h>
#include <fileio/fbxstatisticsfbx.h>
#include <fileio/fbxstatistics.h>

//---------------------------------------------------------------------------------------
//Scene Includes
#include <scene/fbxcollection.h>
#include <scene/fbxcollectionexclusive.h>
#include <scene/fbxcontainer.h>
#include <scene/fbxcontainertemplate.h>
#include <scene/fbxdisplaylayer.h>
#include <scene/fbxdocument.h>
#include <scene/fbxdocumentinfo.h>
#include <scene/fbxenvironment.h>
#include <scene/fbxgroupname.h>
#include <scene/fbxlibrary.h>
#include <scene/fbxobjectmetadata.h>
#include <scene/fbxpose.h>
#include <scene/fbxreference.h>
#include <scene/fbxscene.h>
#include <scene/fbxselectionset.h>
#include <scene/fbxselectionnode.h>
#include <scene/fbxtakeinfo.h>
#include <scene/fbxthumbnail.h>
#include <scene/fbxvideo.h>

//---------------------------------------------------------------------------------------
//Scene Animation Includes
#include <scene/animation/fbxanimcurve.h>
#include <scene/animation/fbxanimcurvebase.h>
#include <scene/animation/fbxanimcurvefilters.h>
#include <scene/animation/fbxanimcurvenode.h>
#include <scene/animation/fbxanimevalclassic.h>
#include <scene/animation/fbxanimevalstate.h>
#include <scene/animation/fbxanimevaluator.h>
#include <scene/animation/fbxanimlayer.h>
#include <scene/animation/fbxanimstack.h>
#include <scene/animation/fbxanimutilities.h>

//---------------------------------------------------------------------------------------
//Scene Constraint Includes
#include <scene/constraint/fbxcharacternodename.h>
#include <scene/constraint/fbxcharacter.h>
#include <scene/constraint/fbxcharacterpose.h>
#include <scene/constraint/fbxconstraint.h>
#include <scene/constraint/fbxconstraintaim.h>
#include <scene/constraint/fbxconstraintcustom.h>
#include <scene/constraint/fbxconstraintparent.h>
#include <scene/constraint/fbxconstraintposition.h>
#include <scene/constraint/fbxconstraintrotation.h>
#include <scene/constraint/fbxconstraintscale.h>
#include <scene/constraint/fbxconstraintsinglechainik.h>
#include <scene/constraint/fbxconstraintutils.h>
#include <scene/constraint/fbxcontrolset.h>
#include <scene/constraint/fbxhik2fbxcharacter.h>

//---------------------------------------------------------------------------------------
//Scene Geometry Includes
#include <scene/geometry/fbxblendshape.h>
#include <scene/geometry/fbxblendshapechannel.h>
#include <scene/geometry/fbxcache.h>
#include <scene/geometry/fbxcachedeffect.h>
#include <scene/geometry/fbxcamera.h>
#include <scene/geometry/fbxcamerastereo.h>
#include <scene/geometry/fbxcameraswitcher.h>
#include <scene/geometry/fbxcluster.h>
#include <scene/geometry/fbxdeformer.h>
#include <scene/geometry/fbxgenericnode.h>
#include <scene/geometry/fbxgeometry.h>
#include <scene/geometry/fbxgeometrybase.h>
#include <scene/geometry/fbxgeometryweightedmap.h>
#include <scene/geometry/fbxlight.h>
#include <scene/geometry/fbxlimitsutilities.h>
#include <scene/geometry/fbxline.h>
#include <scene/geometry/fbxlodgroup.h>
#include <scene/geometry/fbxmarker.h>
#include <scene/geometry/fbxmesh.h>
#include <scene/geometry/fbxnode.h>
#include <scene/geometry/fbxnodeattribute.h>
#include <scene/geometry/fbxnull.h>
#include <scene/geometry/fbxnurbs.h>
#include <scene/geometry/fbxnurbscurve.h>
#include <scene/geometry/fbxnurbssurface.h>
#include <scene/geometry/fbxopticalreference.h>
#include <scene/geometry/fbxpatch.h>
#include <scene/geometry/fbxproceduralgeometry.h>
#include <scene/geometry/fbxshape.h>
#include <scene/geometry/fbxskeleton.h>
#include <scene/geometry/fbxskin.h>
#include <scene/geometry/fbxsubdeformer.h>
#include <scene/geometry/fbxsubdiv.h>
#include <scene/geometry/fbxtrimnurbssurface.h>
#include <scene/geometry/fbxvertexcachedeformer.h>
#include <scene/geometry/fbxweightedmapping.h>

//---------------------------------------------------------------------------------------
//Scene Shading Includes
#include <scene/shading/fbxshadingconventions.h>
#include <scene/shading/fbxbindingsentryview.h>
#include <scene/shading/fbxbindingtable.h>
#include <scene/shading/fbxbindingtableentry.h>
#include <scene/shading/fbxbindingoperator.h>
#include <scene/shading/fbxconstantentryview.h>
#include <scene/shading/fbxentryview.h>
#include <scene/shading/fbxfiletexture.h>
#include <scene/shading/fbximplementation.h>
#include <scene/shading/fbximplementationfilter.h>
#include <scene/shading/fbximplementationutils.h>
#include <scene/shading/fbxlayeredtexture.h>
#include <scene/shading/fbxoperatorentryview.h>
#include <scene/shading/fbxproceduraltexture.h>
#include <scene/shading/fbxpropertyentryview.h>
#include <scene/shading/fbxsemanticentryview.h>
#include <scene/shading/fbxsurfacelambert.h>
#include <scene/shading/fbxsurfacematerial.h>
#include <scene/shading/fbxsurfacephong.h>
#include <scene/shading/fbxtexture.h>

//---------------------------------------------------------------------------------------
//Utilities Includes
#include <utils/fbxdeformationsevaluator.h>
#include <utils/fbxprocessor.h>
#include <utils/fbxprocessorxref.h>
#include <utils/fbxprocessorxrefuserlib.h>
#include <utils/fbxprocessorshaderdependency.h>
#include <utils/fbxclonemanager.h>
#include <utils/fbxgeometryconverter.h>
#include <utils/fbxmanipulators.h>
#include <utils/fbxmaterialconverter.h>
#include <utils/fbxrenamingstrategyfbx5.h>
#include <utils/fbxrenamingstrategyfbx6.h>
#include <utils/fbxrenamingstrategyutilities.h>
#include <utils/fbxrootnodeutility.h>
#include <utils/fbxusernotification.h>

//---------------------------------------------------------------------------------------
#if defined(FBXSDK_NAMESPACE) && (FBXSDK_NAMESPACE_USING == 1)
	using namespace FBXSDK_NAMESPACE;
#endif

#pragma pack(pop)

#endif /* _FBXSDK_H_ */
