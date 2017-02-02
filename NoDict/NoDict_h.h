

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Thu Dec 29 13:44:05 2016
 */
/* Compiler settings for NoDict.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.00.0603 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __NoDict_h_h__
#define __NoDict_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __INoDict_FWD_DEFINED__
#define __INoDict_FWD_DEFINED__
typedef interface INoDict INoDict;

#endif 	/* __INoDict_FWD_DEFINED__ */


#ifndef __CNoDictDoc_FWD_DEFINED__
#define __CNoDictDoc_FWD_DEFINED__

#ifdef __cplusplus
typedef class CNoDictDoc CNoDictDoc;
#else
typedef struct CNoDictDoc CNoDictDoc;
#endif /* __cplusplus */

#endif 	/* __CNoDictDoc_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __NoDict_LIBRARY_DEFINED__
#define __NoDict_LIBRARY_DEFINED__

/* library NoDict */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_NoDict;

#ifndef __INoDict_DISPINTERFACE_DEFINED__
#define __INoDict_DISPINTERFACE_DEFINED__

/* dispinterface INoDict */
/* [uuid] */ 


EXTERN_C const IID DIID_INoDict;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("BC642DE5-49CD-4FEF-96C0-EDD78DFAD1DD")
    INoDict : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct INoDictVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            INoDict * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            INoDict * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            INoDict * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            INoDict * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            INoDict * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            INoDict * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            INoDict * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } INoDictVtbl;

    interface INoDict
    {
        CONST_VTBL struct INoDictVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define INoDict_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define INoDict_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define INoDict_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define INoDict_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define INoDict_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define INoDict_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define INoDict_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __INoDict_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_CNoDictDoc;

#ifdef __cplusplus

class DECLSPEC_UUID("21F42050-6CC6-448F-8116-618F06707FD7")
CNoDictDoc;
#endif
#endif /* __NoDict_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


