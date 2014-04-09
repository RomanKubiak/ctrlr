/*
 *
 *  Copyright (c) 2008-2009 Erich Hoover
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
#ifdef LINUX
#include "libr.h"

/* Obtain file information */
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>

/* Compress files */
#include <zlib.h>
#include <math.h> /* for ceil */

/* Handle strings and variable arguments*/
#include <string.h>
#include <stdarg.h>

/* For C99 number types */
#include <stdint.h>

/* Handle status codes for multiple threads */
#include <pthread.h>

#include <unistd.h>
#include <dirent.h>
#include <errno.h>

#define SPEC_VERSION             '1'
#define OFFSET_TYPE              ((unsigned long) 4)
#define OFFSET_UNCOMPRESSED      ((unsigned long) OFFSET_TYPE+sizeof(unsigned char))
#define OFFSET_UNCOMPRESSED_SIZE ((unsigned long) OFFSET_TYPE+sizeof(unsigned char))
#define OFFSET_COMPRESSED        ((unsigned long) OFFSET_UNCOMPRESSED_SIZE+sizeof(uint32_t))

#if 0
 extern const char * __progname_full;
 #define progpath() (char *) __progname_full
#endif
#define getself() ((char *) "/proc/self/exe")

pthread_key_t error_key;

/*
 * Free the error status code/message structure
 * (called on thread destruction or when a new code is set)
 */
void free_error_key(void *_m)
{
	libr_intstatus *error = (libr_intstatus *) _m;

	if(error != NULL)
	{
		/* Free the error structure */
		if(error->message != NULL)
			free(error->message);
		free(error);
	}
}

/*
 * Set the error code and message for retrieval
 */
void libr_set_error(libr_intstatus error)
{
	static int thread_key_initialized = false;
	libr_intstatus *status = NULL;

	if(!thread_key_initialized)
	{
		if(pthread_key_create(&error_key, free_error_key) != 0)
			return; /* a serious pthread-related error occurred */
		if(pthread_setspecific(error_key, NULL) != 0)
			return; /* a serious pthread-related error occurred */
		thread_key_initialized = true;
	}
	free_error_key(pthread_getspecific(error_key));
	status = (libr_intstatus *) malloc(sizeof(libr_intstatus));
	memcpy(status, &error, sizeof(libr_intstatus));
	if(pthread_setspecific(error_key, (void *) status) != 0)
		return; /* a serious pthread-related error occurred */
}

/*
 * Make an internal status passing structure, set the error code with this status
 * if the status is not LIBR_OK.
 */
libr_intstatus make_status(const char *function, libr_status code, char *message, ...)
{
	libr_intstatus status = {NULL, code, function};
	va_list args;

	if(message != NULL)
	{
		status.message = (char *) malloc(1024);
		va_start(args, message);
		vsnprintf(status.message, 1024, message, args);
		va_end(args);
	}

	libr_set_error(status);
	return status;
}

/*
 * Make sure that the section is libr-compatible
 */
libr_intstatus section_ok(libr_section *scn, libr_data *data)
{
	char required_header[5], test_header[4] = {'R', 'E', 'S', SPEC_VERSION};
	void *ptr = data_pointer(scn, data);
	size_t size = data_size(scn, data);

	if(ptr == NULL || size < sizeof(required_header))
		RETURN(LIBR_ERROR_NOTRESOURCE, "Not a valid libr-resource");
	memcpy(required_header, ptr, sizeof(required_header));
	if(strncmp(required_header, test_header, sizeof(test_header)) != 0)
		RETURN(LIBR_ERROR_NOTRESOURCE, "Not a valid libr-resource");
	RETURN_OK;
}

/*
 * Remove a resourcefrom the ELF binary handle
 */
int libr_clear(libr_file *file_handle, char *resource_name)
{
	libr_data *data = NULL;
	libr_section *scn = NULL;

	/* Ensure valid inputs */
	if(file_handle == NULL || resource_name == NULL)
		PUBLIC_RETURN(LIBR_ERROR_INVALIDPARAMS, "Invalid parameters passed to function");
	if(file_handle->access != LIBR_READ_WRITE)
		PUBLIC_RETURN(LIBR_ERROR_NOPERM, "Open handle with LIBR_READ_WRITE access");
	/* Find the section containing the icon */
	if(find_section(file_handle, resource_name, &scn).status != LIBR_OK)
		return false; /* error already set */
	/* Get the section data (interested in header) */
	if((data = get_data(file_handle, scn)) == NULL)
		PUBLIC_RETURN(LIBR_ERROR_GETDATA, "Failed to obtain data of section");
	/* Confirm that this resource is libr-compatible */
	if(section_ok(scn, data).status != LIBR_OK)
		return false; /* error already set */
	/* Clear the data resource */
	if(set_data(file_handle, scn, data, 0, NULL, 0).status != LIBR_OK)
		return false; /* error already set */
	/* Remove the section */
	if(remove_section(file_handle, scn).status != LIBR_OK)
		return false; /* error already set */
	return true;
}

/*
 * Close the specified ELF binary handle
 */
void libr_close(libr_file *file_handle)
{
	unregister_handle_cleanup(file_handle);
	libr_close_internal(file_handle);
}
/* Only called directly by cleanup routine, all other calls should be through libr_close */
void libr_close_internal(libr_file *file_handle)
{
	write_output(file_handle);
	free(file_handle);
}

/*
 * Return the last error message for the active thread
 */
char *libr_errmsg(void)
{
	libr_intstatus *error = (libr_intstatus *) pthread_getspecific(error_key);

	if(error == NULL)
		return NULL;
	return error->message;
}

/*
 * Return the last error code for the active thread (or LIBR_OK for no error)
 */
libr_status libr_errno(void)
{
	libr_intstatus *error = (libr_intstatus *) pthread_getspecific(error_key);

	if(error == NULL) /* Nothing has happened yet */
		return LIBR_OK;
	return error->status;
}

/*
 * Return the name of a libr-compatible resource
 */
char *libr_list(libr_file *file_handle, unsigned int resourceid)
{
	libr_section *scn = NULL;
	libr_data *data = NULL;
	int i = 0;

	while((scn = next_section(file_handle, scn)) != NULL)
	{
		/* Get the section data (interested in header) */
		if((data = get_data(file_handle, scn)) == NULL)
			return NULL;
		if(section_ok(scn, data).status == LIBR_OK)
		{
			if(i == resourceid)
				return strdup(section_name(file_handle, scn));
			i++;
		}
	}
	return NULL;
}

/*
 * Allocate a buffer containing the data of a resource
 */
char *libr_malloc(libr_file *file_handle, char *resource_name, size_t *size)
{
	char *buffer = NULL;
	size_t size_local;

	if(size == NULL)
		size = &size_local;
	if(!libr_size(file_handle, resource_name, size))
		return NULL; /* error already set */
	buffer = (char *) malloc(*size);
	if(!libr_read(file_handle, resource_name, buffer))
	{
		free(buffer);
		return NULL; /* error already set */
	}
	return buffer;
}

/*
 * Open the specified ELF binary (caller if filename is NULL)
 */
libr_file *libr_open(char *filename, libr_access_t access)
{
	libr_file *file_handle = NULL;
	static int initialized = false;

	if(!initialized)
	{
		if(strncmp(zlibVersion(), ZLIB_VERSION, 1) != 0)
		{
			SET_ERROR(LIBR_ERROR_ZLIBINIT, "zlib library initialization failed");
			return NULL;
		}
		initialize_backend();
		initialized = true;
	}

	if(filename == NULL)
		filename = getself();
	file_handle = (libr_file *) malloc(sizeof(libr_file));
	memset(file_handle, 0, sizeof(libr_file));
	if(open_handles(file_handle, filename, access).status != LIBR_OK)
	{
		/* failed to open file for processing, error already set */
		free(file_handle);
		file_handle = NULL;
	}
	/* Cleanup handles automatically when libr exits memory */
	if(file_handle != NULL)
		register_handle_cleanup(file_handle);
	return file_handle;
}

/*
 * Read a resource from the specified ELF binary handle
 */
int libr_read(libr_file *file_handle, char *resource_name, char *buffer)
{
	unsigned long uncompressed_size = 0, compressed_size = 0;
	char *data_buffer = NULL;
	libr_section *scn = NULL;
	libr_data *data = NULL;
	libr_type_t type;

	/* Find the section containing the icon */
	if(find_section(file_handle, resource_name, &scn).status != LIBR_OK)
		return false; /* error already set */
	/* Get the section data (interested in header) */
	if((data = get_data(file_handle, scn)) == NULL)
		PUBLIC_RETURN(LIBR_ERROR_GETDATA, "Failed to obtain data of section");
	/* Confirm that this resource is libr-compatible */
	if(section_ok(scn, data).status != LIBR_OK)
		return false; /* error already set */
	data_buffer = (char *) data_pointer(scn, data);
	/* Get the size of the data resource */
	type = (libr_type_t) data_buffer[OFFSET_TYPE];
	switch(type)
	{
		case LIBR_UNCOMPRESSED:
		{	if(data_size(scn, data)-OFFSET_UNCOMPRESSED < 0)
				PUBLIC_RETURN(LIBR_ERROR_SIZEMISMATCH, "Section's data size does not make sense");
			uncompressed_size = data_size(scn, data)-OFFSET_UNCOMPRESSED;
			memcpy(buffer, &data_buffer[OFFSET_UNCOMPRESSED], uncompressed_size);
		}	break;
		case LIBR_COMPRESSED:
		{
			uint32_t size_temp;

			memcpy(&size_temp, &data_buffer[OFFSET_UNCOMPRESSED_SIZE], sizeof(uint32_t));
			uncompressed_size = size_temp;
			compressed_size = data_size(scn, data)-OFFSET_COMPRESSED;
			if(uncompress((unsigned char *)buffer, &uncompressed_size, (unsigned char *)&data_buffer[OFFSET_COMPRESSED], compressed_size) != Z_OK)
				PUBLIC_RETURN(LIBR_ERROR_UNCOMPRESS, "Failed to uncompress resource data");
		}	break;
		default:
			PUBLIC_RETURN(LIBR_ERROR_INVALIDTYPE, "Invalid data storage type specified");
	}
	return true;
}

/*
 * Retrieve the number of libr-compatible resources
 */
unsigned int libr_resources(libr_file *file_handle)
{
	libr_section *scn = NULL;
	libr_data *data = NULL;
	int i = 0;

	while((scn = next_section(file_handle, scn)) != NULL)
	{
		if((data = get_data(file_handle, scn)) == NULL)
			continue;
		if(section_ok(scn, data).status == LIBR_OK)
			i++;
	}
	return i;
}

/*
 * Get the size of a resource from the specified ELF binary handle
 */
int libr_size(libr_file *file_handle, char *resource_name, size_t *retsize)
{
	char *data_buffer = NULL;
	libr_section *scn = NULL;
	libr_data *data = NULL;
	unsigned long size = 0;
	libr_type_t type;

	/* Find the section containing the icon */
	if(find_section(file_handle, resource_name, &scn).status != LIBR_OK)
		return false; /* error already set */
	/* Get the section data (interested in header) */
	if((data = get_data(file_handle, scn)) == NULL)
		PUBLIC_RETURN(LIBR_ERROR_GETDATA, "Failed to obtain data of section");
	/* Confirm that this resource is libr-compatible */
	if(section_ok(scn, data).status != LIBR_OK)
		return false; /* error already set */
	data_buffer = (char *) data_pointer(scn, data);
	/* Get the size of the data resource */
	type = (libr_type_t) data_buffer[OFFSET_TYPE];
	switch(type)
	{
		case LIBR_UNCOMPRESSED:
		{
			size_t full_size = data_size(scn, data);

			if(full_size-OFFSET_UNCOMPRESSED < 0)
				PUBLIC_RETURN(LIBR_ERROR_SIZEMISMATCH, "Section's data size does not make sense");
			size = full_size - OFFSET_UNCOMPRESSED;
		}	break;
		case LIBR_COMPRESSED:
		{
			memcpy(&size, &data_buffer[OFFSET_UNCOMPRESSED_SIZE], sizeof(uint32_t));
		}	break;
		default:
			PUBLIC_RETURN(LIBR_ERROR_INVALIDTYPE, "Invalid data storage type specified");
	}
	*retsize = size;
	return true;
}

/*
 * Write a resource to the specified ELF binary handle
 */
int libr_write(libr_file *file_handle, char *resource_name, char *buffer, size_t size, libr_type_t type, libr_overwrite_t overwrite)
{
	char header[9] = {'R', 'E', 'S', SPEC_VERSION};
	unsigned int header_size = 4;
	libr_section *scn = NULL;
	libr_data *data = NULL;
	libr_intstatus ret;

	/* Ensure valid inputs */
	if(file_handle == NULL || resource_name == NULL || buffer == NULL)
		PUBLIC_RETURN(LIBR_ERROR_INVALIDPARAMS, "Invalid parameters passed to function");
	if(file_handle->access != LIBR_READ_WRITE)
		PUBLIC_RETURN(LIBR_ERROR_NOPERM, "Open handle with LIBR_READ_WRITE access");
	/* Get the section if it already exists */
	ret = find_section(file_handle, resource_name, &scn);
	if(ret.status == LIBR_OK)
	{
		/* If the section exists (and overwrite is not specified) then fail */
		if(!overwrite)
			PUBLIC_RETURN(LIBR_ERROR_OVERWRITE, "Section already exists, over-write not specified");
		/* Grab the existing data section for overwriting */
		if((data = get_data(file_handle, scn)) == NULL)
			PUBLIC_RETURN(LIBR_ERROR_GETDATA, "Failed to obtain data of section");
	}
	else if(ret.status == LIBR_ERROR_NOSECTION)
	{
		/* Create a new section named "resource_name" */
		if(add_section(file_handle, resource_name, &scn).status != LIBR_OK)
			return false; /* error already set */
		/* Create a data segment to store the compressed image */
		if((data = new_data(file_handle, scn)) == NULL)
			PUBLIC_RETURN(LIBR_ERROR_NEWDATA, "Failed to create data for section");
	}
	else
		return false; /* error already set */

	header[header_size++] = (char) type;
	switch(type)
	{
		case LIBR_UNCOMPRESSED:
			/* Do nothing, just stick the data in */
			break;
		case LIBR_COMPRESSED:
		{
			char *compressed_buffer = NULL, *uncompressed_buffer = buffer;
			unsigned long compressed_size = 0, uncompressed_size = size;
			uint32_t size_temp;

			/* Store the uncompressed size to the header */
			size_temp = uncompressed_size;
			memcpy(&header[header_size], &size_temp, sizeof(uint32_t));
			header_size += sizeof(uint32_t);
			/* Compress the data for storage */
			compressed_size = ceil((uncompressed_size+12)*1.1);
			compressed_buffer = (char *) malloc(compressed_size);
			if(compress((unsigned char *)compressed_buffer, &compressed_size, (unsigned char *)uncompressed_buffer, uncompressed_size) != Z_OK)
			{
				free(compressed_buffer);
				PUBLIC_RETURN(LIBR_ERROR_COMPRESS, "Failed to compress resource data");
			}
			/* From here on treat the compressed buffer as the data */
			buffer = compressed_buffer;
			size = compressed_size;
		}	break;
		default:
			PUBLIC_RETURN(LIBR_ERROR_INVALIDTYPE, "Invalid data storage type specified");
	}
	/* Store the resource header data */
	if(set_data(file_handle, scn, data, 0, &header[0], header_size).status != LIBR_OK)
		return false; /* error already set */
	/* Create a data segment to store the post-header data
	 * NOTE: For existing files the data of the section is represented as a continuous stream
	 * (so calling elf_getdata now WILL NOT return the post-header data)
	 */
	if((data = new_data(file_handle, scn)) == NULL)
		PUBLIC_RETURN(LIBR_ERROR_NEWDATA, "Failed to create data for section");
	/* Store the actual user data to the section */
	if(set_data(file_handle, scn, data, header_size, buffer, size).status != LIBR_OK)
		return false; /* error already set */
	/* Close compression resources */
	if(type == LIBR_COMPRESSED)
		free(buffer);
	return true;
}

/* Hold on to folder names for cleanup when libr is removed from memory */
typedef struct CLEANUPFOLDER {
	char *folder;
	struct CLEANUPFOLDER *next;
} CleanupFolder;
CleanupFolder *folders_to_remove = NULL;

/* Hold on to libr handles for cleanup when libr is removed from memory */
typedef struct CLEANUPHANDLE {
	int internal; /* do not warn the user about cleaning this handle up */
	libr_file *handle;
	struct CLEANUPHANDLE *next;
} CleanupHandle;
CleanupHandle *handles_to_remove = NULL;

/*
 * Register a folder for cleanup when libr is removed from memory
 */
void register_folder_cleanup(char *temp_folder)
{
	CleanupFolder *folder = malloc(sizeof(CleanupFolder));

	folder->folder = strdup(temp_folder);
	folder->next = NULL;
	if(folders_to_remove != NULL)
	{
		CleanupFolder *f;

		for(f = folders_to_remove; f->next != NULL; f = f->next) {}
		f->next = folder;
	}
	else
		folders_to_remove = folder;
}

/*
 * Register a libr handle for cleanup when libr is removed from memory
 */
void register_handle_cleanup(libr_file *handle)
{
	CleanupHandle *h = malloc(sizeof(CleanupHandle));

	h->handle = handle;
	h->internal = FALSE;
	h->next = NULL;
	if(handles_to_remove != NULL)
	{
		CleanupHandle *i;

		for(i = handles_to_remove; i->next != NULL; i = i->next) {}
		i->next = h;
	}
	else
		handles_to_remove = h;
}

/*
 * Remove a libr handle from the cleanup list
 */
void unregister_handle_cleanup(libr_file *handle)
{
	CleanupHandle *i, *last = NULL;
	int found = FALSE;

	if(handles_to_remove == NULL)
	{
		printf("Unregistering handle with no list of cleanup handles!\n");
		return;
	}
	for(i = handles_to_remove; i != NULL; last = i, i = i->next)
	{
		if(i->handle == handle)
		{
			if(last == NULL)
				handles_to_remove = i->next;
			else
				last->next = i->next;
			free(i);
			found = TRUE;
			break;
		}
	}
	if(!found)
		printf("Could not find handle to remove from cleanup list!\n");
}

/*
 * Flag a handle as internal (do not warn about unsafe cleanup)
 */
void register_internal_handle(libr_file *handle)
{
	int found = FALSE;
	CleanupHandle *i;

	if(handles_to_remove == NULL)
	{
		printf("No cleanup list!\n");
		return;
	}
	for(i = handles_to_remove; i != NULL; i = i->next)
	{
		if(i->handle == handle)
		{
			i->internal = TRUE;
			found = TRUE;
			break;
		}
	}
	if(!found)
		printf("Could not find handle in cleanup list!\n");
}

/*
 * Cleanup a temporary folder used to hack the inability to load resources from a buffer
 */
void cleanup_folder(char *temp_folder)
{
	char *filepath = (char *) malloc(PATH_MAX);
	DIR *dir = opendir(temp_folder);
	struct dirent *file;

	while((file = readdir(dir)) != NULL)
	{
		char *filename = file->d_name;

		/* Do not delete "self" or "parent" directory entries */
		if(!strcmp(filename, ".") || !strcmp(filename, ".."))
			continue;
		/* But delete anything else */
		strcpy(filepath, temp_folder);
		strcat(filepath, "/");
		strcat(filepath, filename);
		if(file->d_type == DT_DIR)
			cleanup_folder(filepath);
		else
		{
			if(unlink(filepath))
				printf("libr failed to cleanup '%s' in temporary folder: %m\n", filename);
		}
	}
	free(filepath);
	closedir(dir);
	if(rmdir(temp_folder) != 0)
		printf("libr failed to remove temporary folder: %m\n");
}

/*
 * Perform cleanup when libr is removed from memory
 */
void do_cleanup(void) __attribute__((destructor));
void do_cleanup(void)
{
	CleanupFolder *f, *fnext;
	CleanupHandle *h, *hnext;

	/* Cleanup folders */
	for(f = folders_to_remove; f != NULL; f = fnext)
	{
		folders_to_remove = NULL;
		fnext = f->next;
		cleanup_folder(f->folder);
		free(f->folder);
		free(f);
	}
	/* Cleanup handles */
	for(h = handles_to_remove; h != NULL; h = hnext)
	{
		handles_to_remove = NULL;
		hnext = h->next;
		/* Unless the handle was created internally then warn the developer to cleanup their act */
		if(!h->internal)
			printf("Warning: Application did not cleanup resource handle: %p\n", h->handle);
		libr_close_internal(h->handle);
		free(h);
	}
}

/*
 * Build all the directories required by a resource
 * (and construct the output string)
 */
int make_valid_path(char *out_path, size_t maxpath, char *start_folder, char *resource_name)
{
	char *a, *c = resource_name;

	strcpy(out_path, start_folder);
	while((a=strchr(c, '/')) != NULL)
	{
		strcat(out_path, "/");
		strncat(out_path, c, (size_t) (a-c));
		if(mkdir(out_path, S_IRUSR|S_IWUSR|S_IXUSR) != 0)
		{
			if(errno != EEXIST)
			{
				printf("failed to make directory: %s %m\n", out_path);
				return false;
			}
		}
		c = a+1;
	}
	strcat(out_path, "/");
	strcat(out_path, c);
	return true;
}

/*
 * Extract all the resources from the ELF file for use by the resource loader
 */
char *libr_extract_resources(libr_file *handle)
{
	char *temp_mask = strdup(LIBR_TEMPFILE);
	char *temp_folder;
	int i = 0;

	temp_folder = mkdtemp(temp_mask);
	if(temp_folder == NULL)
	{
		/* failed to extract ELF resources, could not create a temporary path */
		goto failed;
	}
	/* If this library cannot dynamically load resources then pull out all the resources to a temporary directory */
	for(i=0;i<libr_resources(handle);i++)
	{
		char *resource_name = libr_list(handle, i);
		char *file_path[PATH_MAX];
		size_t resource_size;
		FILE *file_handle;
		char *resource;

		resource = libr_malloc(handle, resource_name, &resource_size);
		if(!make_valid_path((char *)file_path, sizeof(file_path), temp_folder, resource_name))
		{
			/* failed to build the path required by a resource */
			cleanup_folder(temp_folder);
			temp_folder = NULL;
			goto failed;
		}
		file_handle = fopen((const char *) file_path, "w");
		if(file_handle == NULL)
		{
			/* failed to extract ELF resources, could not write to temporary path */
			cleanup_folder(temp_folder);
			temp_folder = NULL;
			goto failed;
		}
		/* if the resource is empty then fwrite will fail */
		if( (resource_size != 0) && (fwrite(resource, resource_size, 1, file_handle) != 1) )
		{
			/* failed to extract ELF resources, temporary path out of space? */
			cleanup_folder(temp_folder);
			temp_folder = NULL;
			goto failed;
		}
		fclose(file_handle);
		free(resource);
	}
failed:
	if(temp_folder != NULL)
		temp_folder = strdup(temp_folder);
	free(temp_mask);
	return temp_folder;
}

#endif
