/**
* Const and macro define 
*
* Defined some common const and macro.
*
* @project: common
* @file : Define.h
* @date : 2011-11-14
* @author : Robin.L
*
*/

#if !defined(_IPBC_2MUSE_COMMON_DEFINE_H_)
#define _IPBC_2MUSE_COMMON_DEFINE_H_


#ifdef WIN32
const char PATH_SEPARATOR = '\\';		///<Separator of path for Windows
const char PATH_SEPARATOR_OTHER = '/';

#else
const char PATH_SEPARATOR = '/';		///<Separator of path for Linux
const char PATH_SEPARATOR_OTHER = '\\';

#endif // WIN32

#endif	//_IPBC_2MUSE_COMMON_DEFINE_H_

