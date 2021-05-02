#ifndef __LIBR_H
#define __LIBR_H

/*
 *
 *  Copyright (c) 2008-2011 Erich Hoover
 *
 *  libr - Add resources into ELF binaries
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 * To provide feedback, report bugs, or otherwise contact me:
 * ehoover at mines dot edu
 *
 */

#include <sys/types.h>

#define ENABLE_NLS 1
// #define HAVE_BFD_2_34 1
/* Define to 1 if you have the MacOS X function CFLocaleCopyCurrent in the
   CoreFoundation framework. */
/* #undef HAVE_CFLOCALECOPYCURRENT */

/* Define to 1 if you have the MacOS X function CFPreferencesCopyAppValue in
   the CoreFoundation framework. */
/* #undef HAVE_CFPREFERENCESCOPYAPPVALUE */

/* Define if the GNU dcgettext() function is already present or preinstalled.
   */
#define HAVE_DCGETTEXT 1

/* Define to 1 if you have the <dlfcn.h> header file. */
#define HAVE_DLFCN_H 1

/* Define if the GNU gettext() function is already present or preinstalled. */
#define HAVE_GETTEXT 1

/* Define if you have the iconv() function and it works. */
/* #undef HAVE_ICONV */

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* Define to 1 if you have the <math.h> header file. */
#define HAVE_MATH_H 1

/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1

/* Define to 1 if you have the <pthread.h> header file. */
#define HAVE_PTHREAD_H 1

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* Define to 1 if you have the <zlib.h> header file. */
#define HAVE_ZLIB_H 1

/* Define to the sub-directory in which libtool stores uninstalled libraries.
   */
#define LT_OBJDIR ".libs/"

/* Name of package */
#define PACKAGE "libr"

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT ""

/* Define to the full name of this package. */
#define PACKAGE_NAME ""

/* Define to the full name and version of this package. */
#define PACKAGE_STRING ""

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME ""

/* Define to the home page for this package. */
#define PACKAGE_URL ""

/* Define to the version of this package. */
#define PACKAGE_VERSION ""

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* Version number of package */
#define VERSION "0.4.0"

#define DEPRECATED_FN           __attribute__ ((deprecated))
#define ALIAS_FN(fn)            __attribute__ ((weak, alias (#fn)))

#include <bfd.h>

/**
 * @addtogroup libr_status libr_status
 * @brief Enumeration of possible libr status values.
 * @{
 * \#include <libr.h>
 */
/** Possible libr status values */
typedef enum {
	LIBR_OK                     =   0, /**< Success */
	LIBR_ERROR_GETEHDR          =  -1, /**< Failed to obtain ELF header: */
	LIBR_ERROR_NOTABLE          =  -2, /**< No ELF string table */
	LIBR_ERROR_TABLE            =  -3, /**< Failed to open string table: */
	LIBR_ERROR_GETDATA          =  -4, /**< Failed to obtain data of section */
	LIBR_ERROR_GETSHDR          =  -5, /**< Failed to obtain ELF section header: */
	LIBR_ERROR_SIZEMISMATCH     =  -6, /**< Section's data size does not make sense */
	LIBR_ERROR_UPDATE           =  -7, /**< Failed to perform dynamic update: */
	LIBR_ERROR_NEWSECTION       =  -8, /**< Failed to create new section */
	LIBR_ERROR_NEWDATA          =  -9, /**< Failed to create data for section */
	LIBR_ERROR_REMOVESECTION    = -10, /**< Failed to remove section: */
	LIBR_ERROR_NOSECTION        = -11, /**< ELF resource section not found */
	LIBR_ERROR_STRPTR           = -12, /**< Failed to obtain section string pointer: */
	LIBR_ERROR_NOTRESOURCE      = -13, /**< Not a valid libr-resource */
	LIBR_ERROR_EXPANDSECTION    = -14, /**< Failed to expand section */
	LIBR_ERROR_WRONGFORMAT      = -15, /**< Invalid input file format */
	LIBR_ERROR_SETFLAGS         = -16, /**< Failed to set flags for section */
	LIBR_ERROR_NOPERM           = -17, /**< Open handle with LIBR_READ_WRITE access */
	LIBR_ERROR_NOSIZE           = -18, /**< Failed to obtain file size */
	LIBR_ERROR_SETFORMAT        = -19, /**< Failed to set output file format to input file format */
	LIBR_ERROR_SETARCH          = -20, /**< Failed to set output file architecture to input file architecture */
	LIBR_ERROR_OVERWRITE        = -21, /**< Section already exists, over-write not specified */
	LIBR_ERROR_COMPRESS         = -22, /**< Failed to compress resource data */
	LIBR_ERROR_INVALIDTYPE      = -23, /**< Invalid data storage type specified */
	LIBR_ERROR_MEMALLOC         = -24, /**< Failed to allocate memory for data */
	LIBR_ERROR_INVALIDPARAMS    = -25, /**< Invalid parameters passed to function */
	LIBR_ERROR_UNCOMPRESS       = -26, /**< Failed to uncompress resource data */
	LIBR_ERROR_ZLIBINIT         = -27, /**< zlib library initialization failed */
	LIBR_ERROR_OPENFAILED       = -28, /**< Failed to open input file */
	LIBR_ERROR_BEGINFAILED      = -29, /**< Failed to open ELF file: */
	LIBR_ERROR_WRITEPERM        = -30, /**< No write permission for file */
	LIBR_ERROR_UNSUPPORTED      = -31, /**< The requested operation is not supported by the backend */
} libr_status;
/**
 * @}
 */

typedef enum {
	LIBR_READ       = 0,
	LIBR_READ_WRITE = 1,
} libr_access_t;

typedef enum {
	LIBR_UNCOMPRESSED = 0,
	LIBR_COMPRESSED   = 1
} libr_type_t;

typedef enum {
	LIBR_NOOVERWRITE = 0,
	LIBR_OVERWRITE   = 1
} libr_overwrite_t;

#ifdef __LIBR_BUILD__
	#include "libr-internal.h"
	#if __LIBR_BACKEND_libbfd__
		#include "libr-bfd.h"
	#elif __LIBR_BACKEND_libelf__
		#include "libr-elf.h"
	#elif __LIBR_BACKEND_readonly__
		#include "libr-ro.h"
	#else /* LIBR_BACKEND */
		#error "Unhandled backend"
	#endif /* LIBR_BACKEND */
	#include "libr-backends.h"
#else
	struct _libr_file;
	typedef struct _libr_file libr_file;
#endif /* __LIBR_BUILD__ */

#define false                       0
#define true                        1
#define ERROR                      -1
#define EXPORT_FN				   void
#define INTERNAL_FN                void
#define LIBR_TEMPFILE              "/tmp/libr-temp.XXXXXX"
#define LIBR_TEMPFILE_LEN          21

typedef struct {
	char *message;
	libr_status status;
	const char *function;
} libr_intstatus;

struct _libr_file;

void libr_set_error(libr_intstatus error);
libr_intstatus make_status(const char *function, libr_status code, char *message, ...);
/* Only called directly by cleanup routine, all other calls should be through libr_close */
void libr_close_internal(struct _libr_file *file_handle);

#define SET_ERROR(code,...)           make_status(__FUNCTION__, code, __VA_ARGS__)
#define RETURN(code,...)              return SET_ERROR(code, __VA_ARGS__)
#define RETURN_OK                     return SET_ERROR(LIBR_OK, NULL)
#define PUBLIC_RETURN(code,message)   {SET_ERROR(code, message); return (code == LIBR_OK);}

#if BFD_HOST_64BIT_LONG
	#if defined(__i386)
		#warning "Using incorrect binutils header file for architecture."
	#endif
#else
	#if defined(__amd64)
		#warning "Using incorrect binutils header file for architecture."
	#endif
#endif

typedef struct _libr_file {
	int fd_handle;
	bfd *bfd_read;
	bfd *bfd_write;
	char *filename;
	mode_t filemode;
	uid_t fileowner;
	gid_t filegroup;
	char tempfile[LIBR_TEMPFILE_LEN];
	libr_access_t access;
} libr_file;

/* for a clean internal API */
typedef asection libr_section;
typedef void libr_data;

libr_intstatus add_section(libr_file *file_handle, char *resource_name, libr_section **retscn);
void *data_pointer(libr_section *scn, libr_data *data);
size_t data_size(libr_section *scn, libr_data *data);
libr_intstatus find_section(libr_file *file_handle, char *section, libr_section **retscn);
libr_data *get_data(libr_file *file_handle, libr_section *scn);
void initialize_backend(void);
libr_data *new_data(libr_file *file_handle, libr_section *scn);
libr_section *next_section(libr_file *file_handle, libr_section *scn);
libr_intstatus remove_section(libr_file *file_handle, libr_section *scn);
char *section_name(libr_file *file_handle, libr_section *scn);
libr_intstatus set_data(libr_file *file_handle, libr_section *scn, libr_data *data, off_t offset, char *buffer, size_t size);
libr_intstatus open_handles(libr_file *file_handle, char *filename, libr_access_t access);
int write_output(libr_file *file_handle);

void cleanup_folder(char *temp_folder);
void register_handle_cleanup(libr_file *handle);
void unregister_handle_cleanup(libr_file *handle);
void register_internal_handle(libr_file *handle);
void register_folder_cleanup(char *temp_folder);
char *libr_extract_resources(libr_file *handle);

/*************************************************************************
 * libr Resource Management API
 *************************************************************************/

/**
 * @page libr_clear Remove a resource from an ELF executable.
 * @section SYNOPSIS
 * 	\#include <libr.h>
 *
 * 	<b>int libr_clear(libr_file *handle, char *resourcename);</b>
 *
 * @section DESCRIPTION
 * 	Removes a libr-compatible resource from an ELF executable.  The handle
 * 	must be opened using <b>libr_open</b>(3) with either <b>LIBR_WRITE</b>
 * 	 or <b>LIBR_READ_WRITE</b> access in order to remove a resource.
 *
 * 	Please note that resource removal does not occur until the handle is
 * 	closed using <b>libr_close</b>(3).
 *
 * 	@param handle A handle returned by <b>libr_open</b>(3).
 * 	@param resourcename The name of the libr-compatible resource to remove.
 *
 * @section SA SEE ALSO
 * 	<b>libr_open</b>(3), <b>libr_close</b>(3)
 *
 * @section AUTHOR
 * 	Erich Hoover <ehoover@mines.edu>
 */
int libr_clear(libr_file *handle, char *resourcename);

/**
 * @page libr_close Close a handle to an ELF executable.
 * @section SYNOPSIS
 * 	\#include <libr.h>
 *
 * 	<b>void libr_close(libr_file *handle);</b>
 *
 * @section DESCRIPTION
 * 	Handles opened with <b>libr_open</b>(3) should be closed with
 * 	<b>libr_close</b>() when they are no-longer needed by the calling
 * 	application.
 *
 * 	@param handle The handle to close.
 *
 * @section SA SEE ALSO
 * 	<b>libr_open</b>(3)
 *
 * @section AUTHOR
 * 	Erich Hoover <ehoover@mines.edu>
 */
void libr_close(libr_file *handle);

/**
 * @page libr_errmsg Return a detailed description of the last
 * 	libr-related error.
 * @section SYNOPSIS
 * 	\#include <libr.h>
 *
 * 	<b>char *libr_errmsg(void);</b>
 *
 * @section DESCRIPTION
 * 	Returns a detailed string describing the last error encountered by
 * 	the libr resource library.  The string is an internal error
 * 	description, so it should not be freed.
 *
 * 	If no errors have been encountered then NULL is returned.
 *
 * @section SA SEE ALSO
 * 	<b>libr_errno</b>(3)
 *
 * @section AUTHOR
 * 	Erich Hoover <ehoover@mines.edu>
 */
char *libr_errmsg(void);

/**
 * @page libr_errno Return a status code describing the last
 * 	libr-related error.
 * @section SYNOPSIS
 * 	\#include <libr.h>
 *
 * 	<b>libr_status libr_errno(void);</b>
 *
 * @section DESCRIPTION
 * 	Returns a code corresponding to the last error encountered by
 * 	the libr resource library.  For a detailed description of possible
 * 	return values see <b>libr_status</b>(3).
 *
 * 	To get a user-readable string corresponding to the last error the
 * 	<b>libr_errmsg</b>(3) function should be used instead.
 *
 * 	If no errors have been encountered then <b>LIBR_OK</b> is returned.
 *
 * @section SA SEE ALSO
 * 	<b>libr_errmsg</b>(3)
 *
 * @section AUTHOR
 * 	Erich Hoover <ehoover@mines.edu>
 */
libr_status libr_errno(void);

/**
 * @page libr_list Obtain the name of a libr ELF resource (by index).
 * @section SYNOPSIS
 * 	\#include <libr.h>
 *
 * 	<b>char *libr_list(libr_file *file_handle, unsigned int resourceid);</b>
 *
 * @section DESCRIPTION
 * 	Returns the name of a libr-compatible resource stored in an ELF binary
 * 	corresponding to the given resource index.  The index value ranges from
 * 	0 to the value returned by <b>libr_resources</b>(3), which returns the
 * 	total number of libr-compatible resources stored in the ELF binary.
 *
 * 	@param handle A handle returned by <b>libr_open</b>(3).
 * 	@param resourceid The index of the libr-compatible resource for which
 * 		the name will be returned.
 *
 * 	@return Returns a string containing the name of the resource section.  This
 * 		string is allocated when the function is called, so it <i>must be
 * 		unallocated</i> with a call to <b>free</b>(3) when it is no-longer
 * 		needed.  NULL is returned on failure.
 *
 * @section SA SEE ALSO
 * 	<b>libr_open</b>(3), <b>free</b>(3)
 *
 * @section AUTHOR
 * 	Erich Hoover <ehoover@mines.edu>
 */
char *libr_list(libr_file *file_handle, unsigned int resourceid);

/**
 * @page libr_malloc Obtain the data corresponding to a libr ELF resource.
 * @section SYNOPSIS
 * 	\#include <libr.h>
 *
 * 	<b>char *libr_malloc(libr_file *handle, char *resourcename, size_t *size);</b>
 *
 * @section DESCRIPTION
 * 	Returns the contents of a libr-compatible resource stored in an ELF binary
 * 	corresponding to the given resource name.
 *
 * 	@param handle A handle returned by <b>libr_open</b>(3).
 * 	@param resourcename The name of the libr-compatible resource for which
 * 		the data will be returned.
 * 	@param size A pointer for storing the length of the data contained in the
 * 		the resource.  May be NULL.
 *
 * 	@return Returns NULL on failure, the pointer to a buffer containing the data
 * 		for the resource on success.  When the buffer is no-longer used it must
 * 		be unallocated using a call to <b>free</b>(3).
 *
 * @section SA SEE ALSO
 * 	<b>libr_open</b>(3), <b>free</b>(3)
 *
 * @section AUTHOR
 * 	Erich Hoover <ehoover@mines.edu>
 */
char *libr_malloc(libr_file *handle, char *resourcename, size_t *size);

/**
 * @page libr_open Open an ELF executable file for resource management.
 * @section SYNOPSIS
 * 	\#include <libr.h>
 *
 * 	<b>libr_file *libr_open(char *filename, libr_access_t access);</b>
 *
 * @section DESCRIPTION
 * 	<b>libr_open</b>() can be used on any ELF executable, however,
 * 	<b>libr_open</b>() called with <b>LIBR_READ</b> access is only useful
 * 	for executables that already contain libr-compatible stored resources.
 *
 * 	An application can easily access its own resources by passing NULL for
 * 	the filename and requesting <b>LIBR_READ</b> access.  For the obvious
 * 	reason that an actively-open application cannot edit itself, the
 * 	calling binary may only request <b>LIBR_READ</b> access.
 *
 * 	@param filename ELF executable to manage.  Pass a NULL pointer as the
 * 		filename in order to access the calling binary (<b>LIBR_READ</b>
 * 		access only) @param access Requested access type (<b>LIBR_READ</b>,
 * 		<b>LIBR_WRITE</b>, <b>LIBR_READ_WRITE</b>), the valid operations for
 * 		the returned handle will be restricted based upon the requested access.
 * 	@return Returns a libr file handle on success, NULL on failure.  The
 * 		handle should be freed with <b>libr_close</b>(3) when no-longer used.
 *
 * @section SA SEE ALSO
 * 	<b>libr_close</b>(3)
 *
 * @section AUTHOR
 * 	Erich Hoover <ehoover@mines.edu>
 */
libr_file *libr_open(char *filename, libr_access_t access);

/**
 * @page libr_read Read out the contents of a libr ELF resource.
 * @section SYNOPSIS
 * 	\#include <libr.h>
 *
 * 	<b>int libr_read(libr_file *handle, char *resourcename, char *buffer);</b>
 *
 * @section WARNING
 * 	This function does not allocate memory for the buffer, so the buffer must
 * 	be large enough to fit the resource data.  For this reason it is suggested
 * 	that <b>libr_malloc</b>(3) be used in preference over this function.
 *
 * @section DESCRIPTION
 * 	Reads the contents of a resource embedded in an ELF binary, the resource
 * 	must be compatible with the libr specification.
 *
 * 	@param handle A handle returned by <b>libr_open</b>(3).
 * 	@return Returns 1 on success, 0 on failure.
 *
 * @section SA SEE ALSO
 * 	<b>libr_open</b>(3)
 *
 * @section AUTHOR
 * 	Erich Hoover <ehoover@mines.edu>
 */
int libr_read(libr_file *handle, char *resourcename, char *buffer);

/**
 * @page libr_resources Returns the number of resources contained in
 * 	the ELF binary.
 * @section SYNOPSIS
 * 	\#include <libr.h>
 *
 * 	<b>unsigned int libr_resources(libr_file *handle);</b>
 *
 * @section DESCRIPTION
 * 	Returns the total number of libr-compatible resources contained
 * 	in the ELF binary.  Intended to be used with <b>libr_list</b>(3)
 * 	to return the full list of resources contained in the binary.
 *
 * 	@param handle A handle returned by <b>libr_open</b>(3).
 * 	@return The total number of libr resources in the binary.
 *
 * @section SA SEE ALSO
 * 	<b>libr_open</b>(3), <b>libr_list</b>(3)
 *
 * @section AUTHOR
 * 	Erich Hoover <ehoover@mines.edu>
 */
unsigned int libr_resources(libr_file *handle);

/**
 * @page libr_size Returns the uncompressed size of a libr resource.
 * @section SYNOPSIS
 * 	\#include <libr.h>
 *
 * 	<b>int libr_size(libr_file *handle, char *resourcename, size_t *size);</b>
 *
 * @section DESCRIPTION
 * 	Obtain the total number of bytes consumed by the uncompressed
 * 	version of the specific libr-resource.  Intended to be used with
 * 	<b>libr_read</b>(3) in order to allocate a large enough buffer
 * 	for the resource.
 *
 * 	@param handle A handle returned by <b>libr_open</b>(3).
 * 	@param resourcename The name of the resource for which the
 * 		size of the data section will be returned.
 * 	@param size A pointer for storing the size of the data section.
 * 		This pointer cannot be NULL.
 * 	@return Returns 1 on success, 0 on failure.
 *
 * @section SA SEE ALSO
 * 	<b>libr_open</b>(3), <b>libr_read</b>(3)
 *
 * @section AUTHOR
 * 	Erich Hoover <ehoover@mines.edu>
 */
int libr_size(libr_file *handle, char *resourcename, size_t *size);

/**
 * @page libr_write Adds a libr resource to an ELF binary.
 * @section SYNOPSIS
 * 	\#include <libr.h>
 *
 * 	<b>int libr_write(libr_file *handle, char *resourcename, char *buffer, size_t size, libr_type_t type, libr_overwrite_t overwrite);</b>
 *
 * @section DESCRIPTION
 * 	Adds a libr-compatible resource into the ELF binary.  The handle
 * 	must be opened using <b>libr_open</b>(3) with either <b>LIBR_WRITE</b>
 * 	or <b>LIBR_READ_WRITE</b> access in order to add a resource.
 *
 * 	@param handle A handle returned by <b>libr_open</b>(3).
 * 	@param resourcename The name of the resource to create.
 * 	@param buffer A string containing the data of the resource.
 * 	@param size The total size of the buffer.
 * 	@param type The method which should be used for storing the
 * 		data (either <b>LIBR_UNCOMPRESSED</b> or
 * 		<b>LIBR_COMPRESSED</b>).
 * 	@param overwrite Whether overwriting an existing resource
 * 		should be permitted (either <b>LIBR_NOOVERWRITE</b> or
 * 		<b>LIBR_OVERWRITE</b>).
 * 	@return Returns 1 on success, 0 on failure.
 *
 * @section SA SEE ALSO
 * 	<b>libr_open</b>(3)
 *
 * @section AUTHOR
 * 	Erich Hoover <ehoover@mines.edu>
 */
int libr_write(libr_file *handle, char *resourcename, char *buffer, size_t size, libr_type_t type, libr_overwrite_t overwrite);

#endif /* __LIBR_H */
